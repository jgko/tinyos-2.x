/* Copyright (c) 2007 Johns Hopkins University.
*  All rights reserved.
*
*  Permission to use, copy, modify, and distribute this software and its
*  documentation for any purpose, without fee, and without written
*  agreement is hereby granted, provided that the above copyright
*  notice, the (updated) modification history and the author appear in
*  all copies of this source code.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS
*  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, LOSS OF USE, DATA,
*  OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
*  THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @author Chieh-Jan Mike Liang <cliang4@cs.jhu.edu>
 * @author Razvan Musaloiu-E. <razvanm@cs.jhu.edu>
 */

#include "FlashVolumeManager.h"

generic module FlashVolumeManagerP()
{
#ifdef DELUGE
  provides interface Notify<uint8_t>;
#endif
  uses {
    interface BlockRead[uint8_t img_num];
    interface BlockWrite[uint8_t img_num];
    interface StorageMap[uint8_t img_num];
    interface AMSend as SerialAMSender;
    interface Receive as SerialAMReceiver;
    interface Leds;
#ifdef DELUGE
    interface NetProg;
    interface Timer<TMilli> as Timer;
#endif
  }
}

implementation
{
  // States for keeping track of split-phase events
  enum {
    S_IDLE,
    S_ERASE,
    S_WRITE,
    S_READ,
    S_CRC,
    S_REPROG,
  };
  
  message_t serialMsg;
  uint8_t buffer[TOSH_DATA_LENGTH];   // Temporary buffer for "write" operation
  uint8_t img_num_reboot = 0xFF;       // Image number to reprogram
  uint8_t state = S_IDLE;              // Manager state for multiplexing "done" events
  
  /**
   * Replies to the PC request with operation results
   */
  void sendReply(error_t error, storage_len_t len)
  {
    SerialReplyPacket *srpkt = (SerialReplyPacket *)call SerialAMSender.getPayload(&serialMsg);
    if (error == SUCCESS) {
      srpkt->error = SERIALMSG_SUCCESS;
    } else {
      srpkt->error = SERIALMSG_FAIL;
    }
    call SerialAMSender.send(AM_BROADCAST_ADDR, &serialMsg, len);
  }
  
  event void BlockRead.readDone[uint8_t img_num](storage_addr_t addr, 
				void* buf, 
				storage_len_t len, 
				error_t error)
  {
    if (state == S_READ) {
      SerialReplyPacket *serialMsg_payload = (SerialReplyPacket *)call SerialAMSender.getPayload(&serialMsg);
      if (buf == serialMsg_payload->data) {
        state = S_IDLE;
        sendReply(error, len + sizeof(SerialReplyPacket));
      }
    }
  }
  
  event void BlockRead.computeCrcDone[uint8_t img_num](storage_addr_t addr, 
				      storage_len_t len, 
				      uint16_t crc, 
				      error_t error)
  {
    if (state == S_CRC) {
      state = S_IDLE;
      
      if (error == SUCCESS) {
        SerialReplyPacket *srpkt = (SerialReplyPacket *)call SerialAMSender.getPayload(&serialMsg);
        srpkt->data[1] = crc & 0xFF;
        srpkt->data[0] = (crc >> 8) & 0xFF;
      }
      sendReply(error, 2 + sizeof(SerialReplyPacket));
    }
  }
  
  event void BlockWrite.writeDone[uint8_t img_num](storage_addr_t addr, 
				  void* buf, 
				  storage_len_t len, 
				  error_t error)
  {
    if (state == S_WRITE && buf == buffer) {
      state = S_IDLE;
      sendReply(error, sizeof(SerialReplyPacket));
    }
  }
  
  event void BlockWrite.eraseDone[uint8_t img_num](error_t error)
  {
    if (state == S_ERASE) {
      state = S_IDLE;
      sendReply(error, sizeof(SerialReplyPacket));
    }
  }
  
  event void BlockWrite.syncDone[uint8_t img_num](error_t error) {}
  
  event void SerialAMSender.sendDone(message_t* msg, error_t error) {}
  
  event message_t* SerialAMReceiver.receive(message_t* msg, void* payload, uint8_t len)
  {
    error_t error = SUCCESS;
    SerialReqPacket *srpkt = (SerialReqPacket *)payload;
    SerialReplyPacket *serialMsg_payload =
                              (SerialReplyPacket *)call SerialAMSender.getPayload(&serialMsg);
    
    switch (srpkt->msg_type) {
      case SERIALMSG_ERASE:    // === Erases a volume ===
        state = S_ERASE;
        error = call BlockWrite.erase[srpkt->img_num]();
        break;
      case SERIALMSG_WRITE:    // === Writes to a volume ===
        state = S_WRITE;
        memcpy(buffer, srpkt->data, srpkt->len);
        error = call BlockWrite.write[srpkt->img_num](srpkt->offset,
                                                      buffer,
                                                      srpkt->len);
        break;
      case SERIALMSG_READ:     // === Reads a portion of a volume ===
        state = S_READ;
        error = call BlockRead.read[srpkt->img_num](srpkt->offset,
                                                    serialMsg_payload->data,
                                                    srpkt->len);
        break;
      case SERIALMSG_CRC:      // === Computes CRC over a portion of a volume ===
        state = S_CRC;
        error = call BlockRead.computeCrc[srpkt->img_num](srpkt->offset,
                                                          srpkt->len, 0);
        break;
      case SERIALMSG_ADDR:     // === Gets the physical starting address of a volume ===
	*(nx_uint32_t*)(&serialMsg_payload->data) =
	                      (uint32_t)call StorageMap.getPhysicalAddress[srpkt->img_num](0);
	sendReply(SUCCESS, sizeof(SerialReplyPacket) + 4);
        break;
#ifdef DELUGE
      case SERIALMSG_REPROG:   // === Reboots and reprograms ===
        state = S_REPROG;
        sendReply(SUCCESS, sizeof(SerialReplyPacket));
        img_num_reboot = srpkt->img_num;
	call Timer.startOneShot(1024);
	break;
      case SERIALMSG_DISS:     // === Starts disseminating a volume ===
	signal Notify.notify(srpkt->img_num);   // Notifies Deluge to start disseminate
	sendReply(SUCCESS, sizeof(SerialReplyPacket));
	break;
#endif
    }
    
    // If a split-phase operation fails when being requested, signals the failure now
    if (error != SUCCESS) {
      state = S_IDLE;
      sendReply(error, sizeof(SerialReplyPacket));
    }
    
    return msg;
  }

#ifdef DELUGE
  event void Timer.fired()
  {
    // Reboots and reprograms
    call NetProg.programImgAndReboot(img_num_reboot);
  }
  
  command error_t Notify.enable() { return SUCCESS; }
  command error_t Notify.disable() { return SUCCESS; }
#endif

  default command error_t BlockWrite.write[uint8_t img_num](storage_addr_t addr, void* buf, storage_len_t len) { return FAIL; }
  default command error_t BlockWrite.erase[uint8_t img_num]() { return FAIL; }
  default command error_t BlockWrite.sync[uint8_t img_num]() { return FAIL; }
  default command error_t BlockRead.read[uint8_t img_num](storage_addr_t addr, void* buf, storage_len_t len) { return FAIL; }
  default command error_t BlockRead.computeCrc[uint8_t img_num](storage_addr_t addr, storage_len_t len, uint16_t crc) { return FAIL; }

  default command storage_addr_t StorageMap.getPhysicalAddress[uint8_t img_num](storage_addr_t addr) { return 0; }
}
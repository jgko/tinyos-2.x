/**
 * "Copyright (c) 2009 The Regents of the University of California.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement
 * is hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY
 * OF CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 */

#include <color.h>
#include <lcd.h>

/**
 * @author Thomas Schmid
 **/

module TestHLTimerC
{
	uses 
    {
        interface Leds;
        interface Boot;
        interface StdControl as SpiControl;
        interface SpiByte;
        interface SpiPacket;
        interface HplSam3uSpiConfig as SpiConfig;

        interface GpioInterrupt as TCCRInterrupt;

        interface Lcd;
        interface Draw;

        interface Timer<TMilli> as TCHTimer;
    }
}
implementation
{
    // label positions
    enum {
        RX_TCH_LABEL = 30, // RX label position
        RX_TCH_VALUE = 50, // RX value position
        RX_TCCR_LABEL = 70,
        RX_TCCR_VALUE = 90,
    };

    typedef nx_struct
    {
        nx_uint8_t rxreg : 4;
        nx_uint8_t txreg : 4;
        nx_uint64_t reg;
    } __attribute__((__packed__)) hltimer_packet_t;

    hltimer_packet_t tx_packet;
    hltimer_packet_t rx_packet;

    task void transferTCCRPacketTask()
    {

        tx_packet.rxreg = 1;
        tx_packet.txreg = 0;
        tx_packet.reg = 16e7;

        call SpiControl.start();

        call SpiPacket.send((uint8_t*)&tx_packet, (uint8_t*) &rx_packet, sizeof(hltimer_packet_t));
    }

    async event void TCCRInterrupt.fired()
    {
        post transferTCCRPacketTask();
    }

	event void Boot.booted()
	{

        call TCCRInterrupt.enableRisingEdge();
        call Lcd.initialize();
    }

    event void Lcd.initializeDone(error_t err)
    {
        if(err != SUCCESS)
        {
            call Leds.led0On();
            call Leds.led1On();
            call Leds.led2On();
            return;
        }

        call Draw.fill(COLOR_WHITE);
        call Draw.drawString(10, 10, "HighLow Timer Demo", COLOR_BLACK);
        call Lcd.start();
    }
    
    event void Lcd.startDone()
    {
        call Lcd.setBacklight(25);
        call TCHTimer.startPeriodic(2*1024);
    }

    event void TCHTimer.fired()
    {
		post transferTCCRPacketTask();
	}

    async event void SpiPacket.sendDone(uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len, error_t error)
    {
        uint8_t i;

        call SpiControl.stop();

        if(error == SUCCESS)
        {
            if(len == 9)
            {
                hltimer_packet_t* rx = (hltimer_packet_t*)rx_buf; 
                hltimer_packet_t* tx = (hltimer_packet_t*)tx_buf; 
                switch(tx->rxreg) {
                    case 1:
                        {
                            // received TCCR
                            call Draw.drawStringWithBGColor(10, RX_TCCR_LABEL, "RX TCCR", COLOR_BLACK, COLOR_WHITE);
                            call Draw.drawRectangle(0, RX_TCCR_VALUE, BOARD_LCD_WIDTH, 14, COLOR_WHITE);
                            call Draw.drawIntWithBGColor(BOARD_LCD_WIDTH-20, RX_TCCR_VALUE, (uint32_t)(rx->reg&0x00000000FFFFFFFF), 1, COLOR_BLACK, COLOR_WHITE);
                            break;
                        }
                    case 2:
                        {
                            // received TCH
                            call Draw.drawStringWithBGColor(10, RX_TCH_LABEL, "RX TCH", COLOR_BLACK, COLOR_WHITE);
                            call Draw.drawRectangle(0, RX_TCH_VALUE, BOARD_LCD_WIDTH, 14, COLOR_WHITE);
                            call Draw.drawIntWithBGColor(BOARD_LCD_WIDTH-20, RX_TCH_VALUE, (uint32_t)rx->reg, 1, COLOR_BLACK, COLOR_WHITE);
                            break;
                        }
                }

                call Leds.led0Toggle();
                return;
            }
        }
        call Leds.led1Toggle();
    }
}

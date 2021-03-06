/*
* Copyright (c) 2009 Johns Hopkins University.
* All rights reserved.
*
* Permission to use, copy, modify, and distribute this software and its
* documentation for any purpose, without fee, and without written
* agreement is hereby granted, provided that the above copyright
* notice, the (updated) modification history and the author appear in
* all copies of this source code.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS  `AS IS'
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED  TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR  PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR  CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, LOSS OF USE,  DATA,
* OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR  OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * TWI register definitions.
 *
 * @author JeongGil Ko
 */

#ifndef _SAM3UTWIHARDWARE_H
#define _SAM3UTWIHARDWARE_H

/**
 *  TWI Control Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary, p. 665
 */
typedef union
{
  uint32_t flat;
  struct
  {
    uint8_t start      :  1;
    uint8_t stop       :  1;
    uint8_t msen       :  1;
    uint8_t msdis      :  1;
    uint8_t sven       :  1;
    uint8_t svdis      :  1;
    uint8_t quick      :  1;
    uint8_t swrst      :  1;
    uint8_t reserved0  :  8;
    uint16_t reserved1 : 16;
  } __attribute__((__packed__)) bits;
} twi_cr_t; 

/**
 *  TWI Master Mode Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary, p. 667
 */
typedef union
{
  uint32_t flat;
  struct
  {
    uint8_t reserved0  :  8;
    uint8_t iadrsz     :  2;
    uint8_t reserved1  :  2;
    uint8_t mread      :  1;
    uint8_t reserved2  :  3;
    uint8_t dadr       :  7;
    uint8_t reserved3  :  1;
    uint8_t reserved4  :  8;
  } __attribute__((__packed__)) bits;
} twi_mmr_t; 

/**
 *  TWI Slave Mode Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary, p. 668
 */
typedef union
{
  uint32_t flat;
  struct
  {
    uint16_t reserved0 : 16;
    uint8_t sadr       :  7;
    uint8_t reserved1  :  1;
    uint8_t reserved2  :  8;
  } __attribute__((__packed__)) bits;
} twi_smr_t; 

/**
 *  TWI Internal Address Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary, p. 669
 */
typedef union
{
  uint32_t flat;
  struct
  {
    uint32_t iadr      : 24;
    uint8_t reserved0  :  8;
  } __attribute__((__packed__)) bits;
} twi_iadr_t; 

/**
 *  TWI Clock Waveform Generator Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary, p. 670
 */
typedef union
{
  uint32_t flat;
  struct
  {
    uint8_t cldiv      :  8;
    uint8_t chdiv      :  8;
    uint8_t ckdiv      :  3;
    uint8_t reserved0  :  5;
    uint8_t reserved1  :  8;
  } __attribute__((__packed__)) bits;
} twi_cwgr_t; 

/**
 *  TWI Status Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary, p. 671
 */
typedef union
{
  uint32_t flat;
  struct
  {
    uint8_t txcomp     :  1;
    uint8_t rxrdy      :  1;
    uint8_t txrdy      :  1;
    uint8_t svread     :  1;
    uint8_t svacc      :  1;
    uint8_t gacc       :  1;
    uint8_t ovre       :  1;
    uint8_t reserved0  :  1;
    uint8_t nack       :  1;
    uint8_t arblst     :  1;
    uint8_t sclws      :  1;
    uint8_t eosacc     :  1;
    uint8_t endrx      :  1;
    uint8_t endtx      :  1;
    uint8_t rxbuff     :  1;
    uint8_t txbufe     :  1;
    uint16_t reserved1 : 16;
  } __attribute__((__packed__)) bits;
} twi_sr_t; 

/**
 *  TWI Interrupt Enable Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary, p. 675
 */
typedef union
{
  uint32_t flat;
  struct
  {
    uint8_t txcomp     :  1;
    uint8_t rxrdy      :  1;
    uint8_t txrdy      :  1;
    uint8_t reserved0  :  1;
    uint8_t svacc      :  1;
    uint8_t gacc       :  1;
    uint8_t ovre       :  1;
    uint8_t reserved1  :  1;
    uint8_t nack       :  1;
    uint8_t arblst     :  1;
    uint8_t sclws      :  1;
    uint8_t eosacc     :  1;
    uint8_t endrx      :  1;
    uint8_t endtx      :  1;
    uint8_t rxbuff     :  1;
    uint8_t txbufe     :  1;
    uint16_t reserved2 : 16;
  } __attribute__((__packed__)) bits;
} twi_ier_t; 

/**
 *  TWI Interrupt Disable Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary, p. 676
 */
typedef union
{
  uint32_t flat;
  struct
  {
    uint8_t txcomp     :  1;
    uint8_t rxrdy      :  1;
    uint8_t txrdy      :  1;
    uint8_t reserved0  :  1;
    uint8_t svacc      :  1;
    uint8_t gacc       :  1;
    uint8_t ovre       :  1;
    uint8_t reserved1  :  1;
    uint8_t nack       :  1;
    uint8_t arblst     :  1;
    uint8_t sclws      :  1;
    uint8_t eosacc     :  1;
    uint8_t endrx      :  1;
    uint8_t endtx      :  1;
    uint8_t rxbuff     :  1;
    uint8_t txbufe     :  1;
    uint16_t reserved2 : 16;
  } __attribute__((__packed__)) bits;
} twi_idr_t; 

/**
 *  TWI Interrupt Mask Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary, p. 677
 */
typedef union
{
  uint32_t flat;
  struct
  {
    uint8_t txcomp     :  1;
    uint8_t rxrdy      :  1;
    uint8_t txrdy      :  1;
    uint8_t reserved0  :  1;
    uint8_t svacc      :  1;
    uint8_t gacc       :  1;
    uint8_t ovre       :  1;
    uint8_t reserved1  :  1;
    uint8_t nack       :  1;
    uint8_t arblst     :  1;
    uint8_t sclws      :  1;
    uint8_t eosacc     :  1;
    uint8_t endrx      :  1;
    uint8_t endtx      :  1;
    uint8_t rxbuff     :  1;
    uint8_t txbufe     :  1;
    uint16_t reserved2 : 16;
  } __attribute__((__packed__)) bits;
} twi_imr_t; 


/**
 *  TWI Receive Holding Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary, p. 678
 */
typedef union
{
  uint32_t flat;
  struct
  {
    uint8_t rxdata     :  8;
    uint8_t reserved0  :  8;
    uint16_t reserved1 : 16;
  } __attribute__((__packed__)) bits;
} twi_rhr_t; 

/**
 *  TWI Transmit Holding Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary, p. 678
 */
typedef union
{
  uint32_t flat;
  struct
  {
    uint8_t txdata     :  8;
    uint8_t reserved0  :  8;
    uint16_t reserved1 : 16;
  } __attribute__((__packed__)) bits;
} twi_thr_t; 


/**
 * TWI Register definitions, AT91 ARM Cortex-M3 based Microcontrollers SAM3U
 * Series, Preliminary, p. 664
 */
typedef struct twi
{
  volatile twi_cr_t cr;
  volatile twi_mmr_t mmr;
  volatile twi_smr_t smr;
  volatile twi_iadr_t iadr;
  volatile twi_cwgr_t cwgr;
  uint32_t reserved0[4];
  volatile twi_sr_t sr;
  volatile twi_ier_t ier;
  volatile twi_idr_t idr;
  volatile twi_imr_t imr;
  volatile twi_rhr_t rhr;
  volatile twi_thr_t thr;
} twi_t;

volatile twi_t* TWI0 = (volatile twi_t*) 0x40084000; // base addr for twi0
volatile twi_t* TWI1 = (volatile twi_t*) 0x40088000; // base addr for twi1

#define TWI0_BASE_ADDR 0x40084000
#define TWI1_BASE_ADDR 0x40088000

#define SAM3U_TWI_BUS "SAM3UTWI.Resource"
#define SAM3U_HPLTWI_RESOURCE "SAM3UTWI.Resource"

typedef struct {
  unsigned int cldiv :8;
  unsigned int chdiv :8;
  unsigned int ckdiv :3;
  
} sam3u_twi_union_config_t;

#endif // _SAM3UTWIHARDWARE_H

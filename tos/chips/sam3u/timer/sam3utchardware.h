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

/**
 * Timer Counter register definitions.
 *
 * @author Thomas Schmid
 */

#ifndef SAM3UTCHARDWARE_H
#define SAM3UTCHARDWARE_H

/**
 *  TC Block Control Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 828
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t sync      : 1; // synchro command
        uint8_t reserved0 : 7;
        uint8_t reserved1 : 8;
        uint8_t reserved2 : 8;
    } bits;
} tc_bcr_t;

/**
 *  TC Block Mode Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 829
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t tc0xc0s    : 2; // external clock signal 0 selection
        uint8_t tc1xc1s    : 2; // external clock signal 1 selection
        uint8_t tc2xc2s    : 2; // external clock signal 2 selection
        uint8_t reserved0  : 0;
        uint8_t qden       : 1; // quadrature decoder enabled
        uint8_t posen      : 1; // position enabled
        uint8_t speeden    : 1; // speed enabled
        uint8_t qdtrans    : 1; // quadrature decoding transparent
        uint8_t edgpha     : 1; // edge on pha count mode
        uint8_t inva       : 1; // invert pha
        uint8_t invb       : 1; // invert phb
        uint8_t invidx     : 1; // swap pha and phb
        uint8_t swap       : 1; // inverted index
        uint8_t idxphb     : 1; // index pin is phb pin
        uint8_t reserved1  : 1;
        uint8_t filter     : 1; // filter
        uint8_t maxfilt    : 6; // maximum filter
        uint8_t reserved2  : 6;
    } bits;
} tc_bmr_t;

/**
 *  TC Channel Control Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 831 
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t clken      :  1; // counter clock enable command
        uint8_t clkdis     :  1; // counter clock disable command
        uint8_t swtrg      :  1; // software trigger command
        uint8_t reserved0  :  5;
        uint8_t reserved1  :  8;
        uint16_t reserved2 : 16;
    } bits;
} tc_ccr_t;

/**
 *  TC QDEC Interrupt Enable Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 832 
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t idx        :  1; // index
        uint8_t dirchg     :  1; // direction change
        uint8_t qerr       :  1; // quadrature error
        uint8_t reserved0  :  5;
        uint8_t reserved1  :  8;
        uint16_t reserved2 : 16;
    } bits;
} tc_qier_t;

/**
 *  TC QDEC Interrupt Disable Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 833
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t idx        :  1; // index
        uint8_t dirchg     :  1; // direction change
        uint8_t qerr       :  1; // quadrature error
        uint8_t reserved0  :  5;
        uint8_t reserved1  :  8;
        uint16_t reserved2 : 16;
    } bits;
} tc_qidr_t;

/**
 *  TC QDEC Interrupt Mask Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 834
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t idx        :  1; // index
        uint8_t dirchg     :  1; // direction change
        uint8_t qerr       :  1; // quadrature error
        uint8_t reserved0  :  5;
        uint8_t reserved1  :  8;
        uint16_t reserved2 : 16;
    } bits;
} tc_qimr_t;

/**
 *  TC QDEC Interrupt Status Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 835 
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t idx        :  1; // index
        uint8_t dirchg     :  1; // direction change
        uint8_t qerr       :  1; // quadrature error
        uint8_t reserved0  :  5;
        uint8_t dir        :  1; // direction
        uint8_t reserved1  :  7;
        uint16_t reserved2 : 16;
    } bits;
} tc_qisr_t;

/**
 *  TC Channel Mode Register Capture Mode, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 836
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t tcclks    : 3; // clock selection
        uint8_t clki      : 1; // clock invert
        uint8_t burst     : 2; // burst signal selection
        uint8_t ldbstop   : 1; // counter clock stopped with rb loading
        uint8_t ldbdis    : 1; // counter clock disable with rb loading
        uint8_t etrgedg   : 1; // external trigger edge selection
        uint8_t abetrg    : 1; // tioa or tiob external trigger selection
        uint8_t reserved0 : 3;
        uint8_t cpctrg    : 1; // rc compare trigger enable
        uint8_t wave      : 1; // wave
        uint8_t ldra      : 2; // ra loading selection
        uint8_t ldrb      : 2; // rb loading selection
        uint8_t reserved1 : 4;
        uint8_t reserved2 : 8;
    } bits;
} tc_cmr_capture_t;

/**
 *  TC Channel Mode Register Waveform Mode, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 838
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t tcclks    : 3; // clock selection
        uint8_t clki      : 1; // clock invert
        uint8_t burst     : 2; // burst signal selection
        uint8_t cpcstop   : 1; // counter clock stopped with rc compare
        uint8_t cpcdis    : 1; // counter clock disable with rc compare
        uint8_t eevtedg   : 2; // external event edge selection
        uint8_t eevt      : 2; // external event selection
        uint8_t enetrg    : 1; // external event trigger enable
        uint8_t wavsel    : 2; // waveform selection
        uint8_t wave      : 1; // wave
        uint8_t acpa      : 2; // ra compare effect on tioa
        uint8_t acpc      : 2; // rc compare effect on tioa
        uint8_t aeevt     : 2; // external event effect on tioa
        uint8_t aswtrg    : 2; // software trigger effect on tioa
        uint8_t bcpb      : 2; // rb compare effect on tiob
        uint8_t bcpc      : 2; // rc compare effect on tiob
        uint8_t beevt     : 2; // external event effect on tiob
        uint8_t bswtrg    : 2; // software trigger effect on tiob
    } bits;
} tc_cmr_wave_t

/**
 *  TC Counter Value Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 842 
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint16_t cv       : 16; // counter value
        uint16_t reserved : 16;
    } bits;
} tc_cv_t;

/**
 *  TC Register A, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 842 
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint16_t ra        : 16; // register a
        uint16_t reserved  : 16;
    } bits;
} tc_ra_t;

/**
 *  TC Register B, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 843 
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint16_t rb        : 16; // register b
        uint16_t reserved  : 16;
    } bits;
} tc_rb_t;

/**
 *  TC Register C, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 843 
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint16_t rc        : 16; // register c
        uint16_t reserved  : 16;
    } bits;
} tc_rc_t;

/**
 *  TC Status Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 844
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t covfs      : 1; // counter overflow status
        uint8_t lovrs      : 1; // load overrun status
        uint8_t cpas       : 1; // ra compare status
        uint8_t cpbs       : 1; // rb compare status
        uint8_t cpcs       : 1; // rc compare status
        uint8_t ldras      : 1; // ra loading status
        uint8_t ldrbs      : 1; // rb loading status
        uint8_t etrgs      : 1; // external trigger status
        uint8_t reserved0  : 8;
        uint8_t clksta     : 1; // clock enable status
        uint8_t mtioa      : 1; // tioa mirror
        uint8_t mtiob      : 1; // tiob mirror
        uint8_t reserved1  : 5;
        uint8_t reserved2  : 8;
    } bits;
} tc_sr_t;

/**
 *  TC Interrupt Enable Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 846 
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t covfs      : 1; // counter overflow 
        uint8_t lovrs      : 1; // load overrun 
        uint8_t cpas       : 1; // ra compare 
        uint8_t cpbs       : 1; // rb compare 
        uint8_t cpcs       : 1; // rc compare 
        uint8_t ldras      : 1; // ra loading 
        uint8_t ldrbs      : 1; // rb loading 
        uint8_t etrgs      : 1; // external trigger 
        uint8_t reserved0  : 8;
        uint16_t reserved1 :16;
    } bits;
} tc_ier_t;

/**
 *  TC Interrupt Disable Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 847 
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t covfs      : 1; // counter overflow 
        uint8_t lovrs      : 1; // load overrun 
        uint8_t cpas       : 1; // ra compare 
        uint8_t cpbs       : 1; // rb compare 
        uint8_t cpcs       : 1; // rc compare 
        uint8_t ldras      : 1; // ra loading 
        uint8_t ldrbs      : 1; // rb loading 
        uint8_t etrgs      : 1; // external trigger 
        uint8_t reserved0  : 8;
        uint16_t reserved1 :16;
    } bits;
} tc_idr_t;

/**
 *  TC Interrupt Mask Register, AT91 ARM Cortex-M3 based Microcontrollers
 *  SAM3U Series, Preliminary 9/1/09, p. 848 
 */
typedef union
{
    uint32_t flat;
    struct
    {
        uint8_t covfs      : 1; // counter overflow 
        uint8_t lovrs      : 1; // load overrun 
        uint8_t cpas       : 1; // ra compare 
        uint8_t cpbs       : 1; // rb compare 
        uint8_t cpcs       : 1; // rc compare 
        uint8_t ldras      : 1; // ra loading 
        uint8_t ldrbs      : 1; // rb loading 
        uint8_t etrgs      : 1; // external trigger 
        uint8_t reserved0  : 8;
        uint16_t reserved1 :16;
    } bits;
} tc_imr_t;

/**
 * TC Register definitions, AT91 ARM Cortex-M3 based Microcontrollers SAM3U
 * Series, Preliminary 9/1/09, p. 827
 */
volatile uint32_t* TC_BASE = (volatile uint32_t*)   0x40080000;
// Channel 0
volatile tc_ccr_t*    TC_CCR0 = (volatile tc_ccr_t*)  0x40080000;
volatile tc_cmr_t*    TC_CMR0 = (volatile tc_cmr_t*)  0x40080004;
volatile tc_cv_t*     TC_CV0  = (volatile tc_cv_t*)   0x40080010;
volatile tc_ra_t*     TC_RA0  = (volatile tc_ra_t*)   0x40080014;
volatile tc_rb_t*     TC_RB0  = (volatile tc_rb_t*)   0x40080018;
volatile tc_rc_t*     TC_RC0  = (volatile tc_rc_t*)   0x4008001C;
volatile tc_sr_t*     TC_SR0  = (volatile tc_sr_t*)   0x40080020;
volatile tc_ier_t*    TC_IER0 = (volatile tc_ier_t*)  0x40080024;
volatile tc_idr_t*    TC_IDR0 = (volatile tc_idr_t*)  0x40080028;
volatile tc_imr_t*    TC_IMR0 = (volatile tc_imr_t*)  0x4008002C;
// Channel 1
volatile tc_ccr_t*    TC_CCR1 = (volatile tc_ccr_t*)  0x40080040;
volatile tc_cmr_t*    TC_CMR1 = (volatile tc_cmr_t*)  0x40080044;
volatile tc_cv_t*     TC_CV1  = (volatile tc_cv_t*)   0x40080050;
volatile tc_ra_t*     TC_RA1  = (volatile tc_ra_t*)   0x40080054;
volatile tc_rb_t*     TC_RB1  = (volatile tc_rb_t*)   0x40080058;
volatile tc_rc_t*     TC_RC1  = (volatile tc_rc_t*)   0x4008005C;
volatile tc_sr_t*     TC_SR1  = (volatile tc_sr_t*)   0x40080060;
volatile tc_ier_t*    TC_IER1 = (volatile tc_ier_t*)  0x40080064;
volatile tc_idr_t*    TC_IDR1 = (volatile tc_idr_t*)  0x40080068;
volatile tc_imr_t*    TC_IMR1 = (volatile tc_imr_t*)  0x4008006C;
// Channel 2
volatile tc_ccr_t*    TC_CCR2 = (volatile tc_ccr_t*)  0x40080080;
volatile tc_cmr_t*    TC_CMR2 = (volatile tc_cmr_t*)  0x40080084;
volatile tc_cv_t*     TC_CV2  = (volatile tc_cv_t*)   0x40080090;
volatile tc_ra_t*     TC_RA2  = (volatile tc_ra_t*)   0x40080094;
volatile tc_rb_t*     TC_RB2  = (volatile tc_rb_t*)   0x40080098;
volatile tc_rc_t*     TC_RC2  = (volatile tc_rc_t*)   0x4008009C;
volatile tc_sr_t*     TC_SR2  = (volatile tc_sr_t*)   0x400800A0;
volatile tc_ier_t*    TC_IER2 = (volatile tc_ier_t*)  0x400800A4;
volatile tc_idr_t*    TC_IDR2 = (volatile tc_idr_t*)  0x400800A8;
volatile tc_imr_t*    TC_IMR2 = (volatile tc_imr_t*)  0x400800AC;

volatile tc_bcr_t*    TC_BCR  = (volatile tc_bcr_t*)  0x400800C0;
volatile tc_bmr_t*    TC_BMR  = (volatile tc_bmr_t*)  0x400800C4;
volatile tc_qier_t*   TC_QIER = (volatile tc_qier_t*) 0x400800C8;
volatile tc_qidr_t*   TC_QIDR = (volatile tc_qidr_t*) 0x400800CC;
volatile tc_qimr_t*   TC_QIMR = (volatile tc_qimr_t*) 0x400800D0;
volatile tc_qisr_t*   TC_QISR = (volatile tc_qisr_t*) 0x400800D4;
#endif //SAM3UTCHARDWARE_H

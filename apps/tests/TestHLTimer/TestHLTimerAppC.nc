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
 * Basic application that tests the SAM3U SPI.
 *
 * @author Thomas Schmid
 **/

configuration TestHLTimerAppC
{
}
implementation
{
	components MainC, TestHLTimerC, LedsC;

	TestHLTimerC -> MainC.Boot;
	TestHLTimerC.Leds -> LedsC;

	components HilSam3uSpiC;
	TestHLTimerC.SpiControl -> HilSam3uSpiC;
	TestHLTimerC.SpiByte -> HilSam3uSpiC;
    TestHLTimerC.SpiPacket -> HilSam3uSpiC;

    components HplSam3uSpiC;
    TestHLTimerC.SpiConfig -> HplSam3uSpiC;

    components LcdC;
    TestHLTimerC.Lcd -> LcdC;
    TestHLTimerC.Draw -> LcdC;

    components new TimerMilliC() as T0;
    TestHLTimerC.TCHTimer -> T0;

    components HplSam3uGeneralIOC;
    TestHLTimerC.TCCRInterrupt -> HplSam3uGeneralIOC.InterruptPioA2;
}

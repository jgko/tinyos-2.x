/*
 * Copyright (c) 2009 Stanford University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the Stanford University nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL STANFORD
 * UNIVERSITY OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * HPL interface to the SAM3U MPU.
 *
 * @author wanja@cs.fau.de
 */

interface HplSam3uMpu
{
	async command void enableMpu();
	async command void disableMpu();

	async command void enableMpuDuringHardFaults();
	async command void disableMpuDuringHardFaults();

	async command void enableDefaultBackgroundRegion();
	async command void disableDefaultBackgroundRegion();

	async command error_t setupRegion(
		uint8_t regionNumber,
		void *baseAddress,
		uint32_t size, // in bytes (bug: 4 GB not possible with this interface)
		bool enableInstructionFetch,
		bool enableReadPrivileged,
		bool enableWritePrivileged,
		bool enableReadUnprivileged,
		bool enableWriteUnprivileged,
		bool cacheable, // should be turned off for periphery and sys control (definitive guide, p. 213)
		bool bufferable, // should be turned off for sys control to be strongly ordered (definitive guide, p. 213)
		uint8_t disabledSubregions // bit = 1: subregion disabled
		);

	// temporary test routines
	async command void writeProtect(void *pointer);
	async command void executeProtect(void *pointer);

	async event void mpuFault();
}
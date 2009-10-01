//$Id: TransformAlarmC.nc,v 1.5 2008/06/24 04:07:29 regehr Exp $

/* "Copyright (c) 2000-2003 The Regents of the University of California.  
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
 * TransformAlarmC decreases precision of an Alarm.
 * @param to_precision_tag A type indicating the precision of the transformed
 *   Alarm.
 * @param from_precision_tag A type indicating the precision of the original
 *   Alarm.
 * @param bit_shift_right Original time units will be 2 to the power 
 *   <code>bit_shift_right</code> larger than transformed time units.
 *
 * @author Cory Sharp <cssharp@eecs.berkeley.edu>
 */

generic module TransformAlarmSimpleC(
  typedef to_precision_tag,
  typedef from_precision_tag,
  uint8_t bit_shift_right) @safe()
{
  /**
   * The transformed Alarm.
   */
  provides interface Alarm<to_precision_tag, uint32_t>;

  /**
   * The original Alarm.
   */
  uses interface Alarm<from_precision_tag,uint32_t> as AlarmFrom;
}
implementation
{
  uint32_t m_t0;
  uint32_t m_dt;

  enum
  {
    MAX_DELAY_LOG2 = 8 * sizeof(uint32_t) - 1 - bit_shift_right,
    MAX_DELAY = ((uint32_t)1) << MAX_DELAY_LOG2,
  };

  async command uint32_t Alarm.getNow()
  {
    return call AlarmFrom.getNow() >> bit_shift_right;
  }

  async command uint32_t Alarm.getAlarm()
  {
    atomic return m_t0 + m_dt;
    //return m_t0 + m_dt;
  }

  async command bool Alarm.isRunning()
  {
    return call AlarmFrom.isRunning();
  }

  async command void Alarm.stop()
  {
    call AlarmFrom.stop();
  }

  void set_alarm()
  {
    uint32_t now = call Alarm.getNow(), expires, remaining;

    /* m_t0 is assumed to be in the past. If it's > now, we assume
       that time has wrapped around */

    expires = m_t0 + m_dt;

    /* The cast is necessary to get correct wrap-around arithmetic */
    remaining = (uint32_t)(expires - now);

    /* if (expires <= now) remaining = 0; in wrap-around arithmetic */
    if (m_t0 <= now)
      {
	if (expires >= m_t0 && // if it wraps, it's > now
	    expires <= now)
	  remaining = 0;
      }
    else
      {
	if (expires >= m_t0 || // didn't wrap so < now
	    expires <= now)
	  remaining = 0;
      }
    if (remaining > MAX_DELAY)
      {
	m_t0 = now + MAX_DELAY;
	m_dt = remaining - MAX_DELAY;
	remaining = MAX_DELAY;
      }
    else
      {
	m_t0 += m_dt;
	m_dt = 0;
      }
    call AlarmFrom.startAt((uint32_t)now << bit_shift_right,
			   (uint32_t)remaining << bit_shift_right);
  }

  async command void Alarm.startAt(uint32_t t0, uint32_t dt)
  {
    atomic
    {
      m_t0 = t0;
      m_dt = dt;
      set_alarm();
    }
  }

  async command void Alarm.start(uint32_t dt)
  {
    call Alarm.startAt(call Alarm.getNow(), dt);
  }

  async event void AlarmFrom.fired()
  {
    atomic
    {
      if(m_dt == 0)
      {
	signal Alarm.fired();
      }
      else
      {
	set_alarm();
      }
    }
  }

  default async event void Alarm.fired()
  {
  }
}

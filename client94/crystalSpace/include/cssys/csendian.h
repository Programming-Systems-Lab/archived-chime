/*
    Copyright (C) 1998 by Jorrit Tyberghein

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef __CSENDIAN_H__
#define __CSENDIAN_H__

#include <math.h>
#include "cstypes.h"
#include "qint.h"

/*
 * This is a bit of overkill but if you're sure your CPU doesn't require
 * strict alignment add your CPU to the !defined below to get slightly
 * smaller and faster code in some cases.
 */
#if !defined (PROC_X86)
#  define PROC_NEEDS_STRICT_ALIGNMENT
#endif

struct swap_4
{
  unsigned char b1, b2, b3, b4;
};

#ifdef CS_BIG_ENDIAN
#  define big_endian_long(x)  x
#  define big_endian_short(x) x
#  define big_endian_float(x) x
#else

/// Convert a long from big-endian to machine format
static inline uint32 big_endian_long (uint32 l)
{ return (l >> 24) | ((l >> 8) & 0xff00) | ((l << 8) & 0xff0000) | (l << 24); }

/// Convert a short from big-endian to machine format
static inline uint16 big_endian_short (uint16 s)
{ return (s >> 8) | (s << 8); }

/// Convert a big-endian floating-point number to machine format
//@@WARNING: Should be removed -- use float2long instead
static inline float big_endian_float (float f)
{
  unsigned char tmp;
  swap_4 *pf = (swap_4 *)&f;
  tmp = pf->b1; pf->b1 = pf->b4; pf->b4 = tmp;
  tmp = pf->b2; pf->b2 = pf->b3; pf->b3 = tmp;
  return f;
}

#endif // CS_BIG_ENDIAN

#ifdef CS_LITTLE_ENDIAN
#  define little_endian_long(x)  x
#  define little_endian_short(x) x
#  define little_endian_float(x) x
#else

/// Convert a long from little-endian to machine format
static inline uint32 little_endian_long (uint32 l)
{ return (l >> 24) | ((l >> 8) & 0xff00) | ((l << 8) & 0xff0000) | (l << 24); }

/// Convert a short from little-endian to machine format
static inline uint16 little_endian_short (uint16 s)
{ return (s >> 8) | (s << 8); }

/// Convert a little-endian floating-point number to machine format
static inline float little_endian_float (float f)
{
  unsigned char tmp;
  swap_4 *pf = (swap_4 *)&f;
  tmp = pf->b1; pf->b1 = pf->b4; pf->b4 = tmp;
  tmp = pf->b2; pf->b2 = pf->b3; pf->b3 = tmp;
  return f;
}

#endif // CS_LITTLE_ENDIAN

/*
    To be able to painlessly transfer files betwen platforms, we should
    avoid using native floating-point format. Here are a couple of routines
    that are guaranteed to work on all platforms.

    The floating point is converted to a fixed 1.7.25 bits format
    (one bit sign, 7 bits exponent, 25 bits mantissa) and back,
    so that we can binary store floating-point number without
    cross-platform problems. If you wonder why 1+7+25 = 33 while we
    only have 32 bits, we'll ommit the most significant bit of mantissa
    since it is always 1 (we use normalized numbers). This increases the
    precision twice.
*/

/// Convert a float to a cross-platform 32-bit format (no endianess adjustments!)
static inline long float2long (float f)
{
  int exp;
  long mant = QRound (frexp (f, &exp) * 0x1000000);
  long sign = mant & 0x80000000;
  if (mant < 0) mant = -mant;
  if (exp > 63) exp = 63; else if (exp < -64) exp = -64;
  return sign | ((exp & 0x7f) << 24) | (mant & 0xffffff);
}

/// Convert a 32-bit cross-platform float to native format (no endianess adjustments!)
static inline float long2float (long l)
{
  int exp = (l >> 24) & 0x7f;
  if (exp & 0x40) exp = exp | ~0x7f;
  float mant = float (l & 0x00ffffff) / 0x1000000;
  if (l & 0x80000000) mant = -mant;
  return (float) ldexp (mant, exp);
}

/**
 * The following routines are used for converting floating-point numbers
 * into 16-bit shorts and back. This is useful for low-precision data.
 * They use the 1.4.12 format. The range of numbers that can be represented
 * in this format is from 2^-8 to 2^7. The precision for numbers near to
 * 2^-8 (0.00390625) is near 0.000001, for numbers near 2^7 (128) is near 0.03.
 */

/// Convert a float to a cross-platform 16-bit format (no endianess adjustments!)
static inline short float2short (float f)
{
  int exp;
  long mant = QRound (frexp (f, &exp) * 0x1000);
  long sign = mant & 0x8000;
  if (mant < 0) mant = -mant;
  if (exp > 7) mant = 0x7ff, exp = 7; else if (exp < -8) mant = 0, exp = -8;
  return sign | ((exp & 0xf) << 11) | (mant & 0x7ff);
}

/// Convert a 16-bit cross-platform float to native format (no endianess adjustments!)
static inline float short2float (short s)
{
  int exp = (s >> 11) & 0xf;
  if (exp & 0x8) exp = exp | ~0xf;
  float mant = float ((s & 0x07ff) | 0x0800) / 0x1000;
  if (s & 0x8000) mant = -mant;
  return (float) ldexp (mant, exp);
}

/// Swap the bytes in a uint32 value.
static inline uint32 convert_endian (uint32 l)
{ return little_endian_long (l); }

/// Swap the bytes in a int32 value.
static inline int32 convert_endian (int32 l)
{ return little_endian_long (l); }

/// Swap the bytes in a int16 value.
static inline int16 convert_endian (int16 s)
{ return little_endian_short (s); }

/// Swap the bytes in a uint16 value.
static inline uint16 convert_endian (uint16 s)
{ return little_endian_short (s); }

/// Swap the bytes in a float value.
static inline float convert_endian (float f)
{ return little_endian_float (f); }

/// Read a little-endian short from address
inline uint16 get_le_short (void *buff)
{
#ifdef PROC_NEEDS_STRICT_ALIGNMENT
  uint16 s; memcpy (&s, buff, sizeof (s));
  return little_endian_short (s);
#else
  return little_endian_short (*(uint16 *)buff);
#endif
}

/// Read a little-endian long from address
inline uint32 get_le_long (void *buff)
{
#ifdef PROC_NEEDS_STRICT_ALIGNMENT
  uint32 l; memcpy (&l, buff, sizeof (l));
  return little_endian_long (l);
#else
  return little_endian_long (*(uint32 *)buff);
#endif
}

/// Read a little-endian 32-bit float from address
inline float get_le_float32 (void *buff)
{ uint32 l = get_le_long (buff); return long2float (l); }

/// Read a little-endian 16-bit float from address
inline float get_le_float16 (void *buff)
{ uint16 s = get_le_short (buff); return short2float (s); }

/// Set a little-endian short on a address
inline void set_le_short (void *buff, uint16 s)
{
#ifdef PROC_NEEDS_STRICT_ALIGNMENT
  s = little_endian_short (s);
  memcpy (buff, &s, sizeof (s));
#else
  *((uint16 *)buff) = little_endian_short (s);
#endif
}

/// Set a little-endian long on a address
inline void set_le_long (void *buff, uint32 l)
{
#ifdef PROC_NEEDS_STRICT_ALIGNMENT
  l = little_endian_long (l);
  memcpy (buff, &l, sizeof (l));
#else
  *((uint32 *)buff) = little_endian_long (l);
#endif
}

/// Set a little-endian 32-bit float on a address
inline void set_le_float32 (void *buff, float f)
{ set_le_long (buff, float2long (f)); }

/// Set a little-endian 16-bit float on a address
inline void set_le_float16 (void *buff, float f)
{ set_le_short (buff, float2short (f)); }

#endif // __CSENDIAN_H__

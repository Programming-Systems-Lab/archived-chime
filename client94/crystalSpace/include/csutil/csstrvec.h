/*
    Crystal Space: string vector class
    Copyright (C) 1998,1999,2000 by Andrew Zabolotny <bit@eltech.ru>

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

#ifndef __CS_CSSTRVEC_H__
#define __CS_CSSTRVEC_H__

#include "csutil/csvector.h"

/**
 * csStrVector is a version of csVector which assumes its components
 * were allocated with 'new char *[]'. FreeItem () deletes vector elements
 * using 'delete [] (char *)' operator.
 */
class csStrVector : public csVector
{
public:
  /**
   * Use these values as the Mode argument of QuickSort(), Compare(), and
   * CompareKey() in order to control case sensitivity during sorting and
   * comparison.  (See csVector for a description of QuickSort()).
   */
  enum { CASE_SENSITIVE, CASE_INSENSITIVE };

  /// Constructor just passes control to csVector's
  csStrVector (int ilimit = 64, int ithreshold = 64) :
    csVector (ilimit, ithreshold) {}

  /// Delete all inserted strings before deleting the object itself
  virtual ~csStrVector ();

  /// FreeItem deletes Item as if it was allocated by 'new char *[]'
  virtual bool FreeItem (csSome Item);

  /// Compare two array elements in given Mode
  virtual int Compare (csSome Item1, csSome Item2, int Mode) const;

  /// Compare two strings for equality (case-sensitive)
  virtual int CompareKey (csSome Item, csConstSome Key, int Mode) const;

  /// Overrided Get() to avoid type conversions
  inline char *Get (int n) const
  { return (char *)csVector::Get (n); }
};

#endif // __CS_CSSTRVEC_H__

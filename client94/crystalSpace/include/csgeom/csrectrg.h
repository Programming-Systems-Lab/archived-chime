/*
    Copyright (C) 2001 by Christopher Nelson

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

#ifndef __CS_CSRECTREGION_H__
#define __CS_CSRECTREGION_H__

#include "csgeom/csrect.h"

const int FRAGMENT_BUFFER_SIZE=64;

/**
 * A rect region is a class that implements splittable 2d rectangles.  The
 * region may be composed of one or more rectangles that do not need to occupy
 * the same area.  The idea being that you need to be able to have a number of
 * disparate rectangular regions for updates.  This class uses csRect for
 * nearly all rectangle operations.
 *<p>
 * To use you can Include and Exclude rectangles from this region.  When
 * finished, this class will have a list of optimal rectangles that occupy a
 * region.  If used properly, it will result in faster overall painting
 * performance, since several areas will not require overwriting.
 */
class csRectRegion
{
protected:
  /// The pointer the list of regions
  csRect* region;
  /// The number of regions currently stored
  int region_count;
  /// The size of the region buffer (in rects)
  int region_max;
  /// The fragment buffer, used for performing fragment operations
  csRect  fragment[FRAGMENT_BUFFER_SIZE];
  /// The gather marker
  int gather_mark;

  /// Pushes a new rect into the region, increases buffer if necessary
  void pushRect(csRect const &);
  /// Removes a rect from the region.
  void deleteRect(int);


  /// Controls fragmentContainedRect, used to perform all-side clipping and edge intersection.
  void fragmentRect(csRect&, csRect&, int mode);
  void nkSplit(csRect& r1, csRect& r2);
  /// Work method fragments rects properly when they intersect.
  void fragmentContainedRect(csRect &r1, csRect &r2);
  /// Marks the current region insertion point for gather.
  void markForGather();
  /// Gathers all regions since the mark into the fragment buffer.
  void gatherFragments();

public:
  /// Constructor.
  csRectRegion();
  /// Destructor
  ~csRectRegion();

  /// Add a rect to this region; may cause unions, but will not adjance (see csRect).
  void Include(csRect &rect);
  /// Exclude a rect from this region; may cause splitting. NOTE: broken!!!
  void Exclude(csRect &rect);
  /// Clips everything in the region to the borders given.
  void ClipTo(csRect &clip);

  /// Returns the number of rectangles in this region
  int Count() { return region_count; }
  /// Returns the rect at a specific index
  csRect& RectAt(int i) {  return region[i]; }
  /// Resets the region count to zero.
  void makeEmpty();
};

#endif //__CS_CSRECTREGION_H__

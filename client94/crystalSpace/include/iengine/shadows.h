/*
    Crystal Space 3D engine
    Copyright (C) 2001 by Jorrit Tyberghein

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

#ifndef __I_SHADOWS_H__
#define __I_SHADOWS_H__

#include "csutil/scf.h"

struct iShadowBlock;
struct iShadowBlockList;
struct iSector;
class csFrustum;
class csTransform;
class csPlane3;
class csVector3;

SCF_VERSION (iShadowIterator, 0, 0, 1);

/**
 * A shadow iterator allows someone to iterate over all shadows
 * in a iShadowBlock or iShadowBlockList.
 */

struct iShadowIterator : public iBase
{
  /// Reset the iterator to start again.
  virtual void Reset () = 0;
  /// Is there still an element in this iterator?
  virtual bool HasNext () = 0;
  /// Get the next shadow.
  virtual csFrustum* Next () = 0;
  /// Get the user data for the last shadow.
  virtual void* GetUserData () = 0;
  /// Return if the last shadow is relevant or not.
  virtual bool IsRelevant () = 0;
  /// Mark the last shadow as relevant.
  virtual void MarkRelevant (bool rel) = 0;
  /// Delete the last returned shadow.
  virtual void DeleteCurrent () = 0;
  /// Return the shadow list for the current element.
  virtual iShadowBlock* GetCurrentShadowBlock () = 0;
  /// Return the shadow list for the next element.
  virtual iShadowBlock* GetNextShadowBlock () = 0;
};

SCF_VERSION (iShadowBlock, 0, 0, 2);

/**
 * A block of shadows represent the shadows that are casted by
 * one iShadowCaster object.
 */
struct iShadowBlock : public iBase
{
  /// Get an iterator to iterate over all shadows in this block.
  virtual iShadowIterator* GetShadowIterator (bool reverse = false) = 0;
  /// Get a pointer to the sector in which this block was generated.
  virtual iSector* GetSector () = 0;
  /// Get the recursion level of this sector in our frustum check.
  virtual int GetRecLevel () = 0;
  /// Dereference all shadows in the list.
  virtual void DeleteShadows () = 0;

  /**
   * Copy all relevant shadow frustums from another shadow block
   * into this block. The frustums are not really copied but a new
   * reference is kept. However, if a transformation is given then
   * a copy is made and the shadows are transformed.
   */
  virtual void AddRelevantShadows (iShadowBlock* source,
  	csTransform* trans = NULL) = 0;

  /**
   * Copy all relevant shadow frustums from another shadow block list
   * into this block. The frustums are not really copied but a new
   * reference is kept.
   */
  virtual void AddRelevantShadows (iShadowBlockList* source) = 0;

  /**
   * Copy all shadow frustums from another shadow block list
   * into this block. The frustums are not really copied but a new
   * reference is kept.
   */
  virtual void AddAllShadows (iShadowBlockList* source) = 0;

  /**
   * Add unique shadows. Only add relevant shadow frustums that are not
   * already in the current list. The frustums are not really copied
   * but a new reference is kept.
   */
  virtual void AddUniqueRelevantShadows (iShadowBlockList* source) = 0;

  /**
   * Add a new frustum and return a reference.
   * The frustum will have the specified number of vertices but the
   * vertices still need to be initialized.
   */
  virtual csFrustum* AddShadow (const csVector3& origin, void* userData,
  	int num_verts, csPlane3& backplane) = 0;

  /// Unlink a shadow frustum from the list and dereference it.
  virtual void UnlinkShadow (int idx) = 0;

  /// Get the number of shadows in this list.
  virtual int GetShadowCount () = 0;

  /// Get the specified shadow.
  virtual csFrustum* GetShadow (int idx) = 0;

  /**
   * Apply a transformation to all frustums in this list.
   */
  virtual void Transform (csTransform* trans) = 0;
};

SCF_VERSION (iShadowBlockList, 0, 0, 2);

/**
 * This is a list of shadow blocks. An iShadowReceiver will get
 * such a list.
 */
struct iShadowBlockList : public iBase
{
  /// Get an iterator to iterate over all shadows in this list.
  virtual iShadowIterator* GetShadowIterator (bool reverse = false) = 0;

  /// Create a new shadow block and append to the list.
  virtual iShadowBlock* NewShadowBlock (iSector* sector, int draw_busy,
  	int num_shadows = 30) = 0;
  /// Create a new shadow block and append to the list.
  virtual iShadowBlock* NewShadowBlock () = 0;

  /// Get first shadow block in the list.
  virtual iShadowBlock* GetFirstShadowBlock () = 0;
  /// Get last shadow block in the list.
  virtual iShadowBlock* GetLastShadowBlock () = 0;
  /// Get next shadow block.
  virtual iShadowBlock* GetNextShadowBlock (iShadowBlock* s) = 0;
  /// Get previous shadow block.
  virtual iShadowBlock* GetPreviousShadowBlock (iShadowBlock* s) = 0;
  /// Remove the last shadow block from this list.
  virtual void RemoveLastShadowBlock () = 0;
  /// Destroy all shadow lists and shadows in the list.
  virtual void DeleteAllShadows () = 0;
};

#endif // __I_SHADOWS_H__


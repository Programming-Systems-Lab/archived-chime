/*
    Copyright (C) 1998-2001 by Jorrit Tyberghein
    Written by Alex Pfaffe.

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
#ifndef __CS_COLLIDER_H__
#define __CS_COLLIDER_H__

#include "csutil/csobject.h"
#include "csgeom/math3d.h"
#include "csgeom/matrix3.h"
#include "csgeom/vector3.h"

class csReversibleTransform;
struct iPolygonMesh;
struct iCollideSystem;
struct iCollider;
struct iObject;


SCF_VERSION (csColliderWrapper, 0, 0, 3);

/**
 * This is a conveniance object that you can use in your own
 * games to attach an iCollider object (from the CD plugin system)
 * to any other csObject (including CS entities). Use of this object
 * is optional (if you can assign your iCollider's to entities in
 * another manner then this is ok) and the engine will not use
 * this object itself.
 */
class csColliderWrapper : public csObject
{
private:
  iCollideSystem* collide_system;
  iCollider* collider;

public:
  /// Create a collider based on a mesh.
  csColliderWrapper (csObject& parent, iCollideSystem* collide_system,
  	iPolygonMesh* mesh);

  /// Create a collider based on a mesh.
  csColliderWrapper (iObject* parent, iCollideSystem* collide_system,
  	iPolygonMesh* mesh);

  /// Destroy the plugin collider object
  virtual ~csColliderWrapper ();

  /// Get the collider interface for this object.
  iCollider* GetCollider () { return collider; }

  /// Get the collide system.
  iCollideSystem* GetCollideSystem () { return collide_system; }

  /**
   * Check if this collider collides with pOtherCollider.
   * Returns true if collision detected and adds the pair to the collisions
   * hists vector.
   * This collider and pOtherCollider must be of comparable subclasses, if
   * not false is returned.
   */
  bool Collide (csColliderWrapper& pOtherCollider,
                csReversibleTransform* pThisTransform = NULL,
                csReversibleTransform* pOtherTransform = NULL);
  /**
   * Similar to Collide for csColliderWrapper. Calls GetColliderWrapper for
   * otherCollider.
   */
  bool Collide (csObject& otherObject,
                csReversibleTransform* pThisTransform = NULL,
                csReversibleTransform* pOtherTransform = NULL);
  /**
   * Similar to Collide for csColliderWrapper. Calls GetColliderWrapper for
   * otherCollider.
   */
  bool Collide (iObject* otherObject,
                csReversibleTransform* pThisTransform = NULL,
                csReversibleTransform* pOtherTransform = NULL);

  /**
   * If object has a child of type csColliderWrapper it is returned.
   * Otherwise 0 is returned.
   */
  static csColliderWrapper* GetColliderWrapper (csObject& object);

  /**
   * If object has a child of type csColliderWrapper it is returned.
   * Otherwise 0 is returned.
   */
  static csColliderWrapper* GetColliderWrapper (iObject* object);

  SCF_DECLARE_IBASE_EXT (csObject);
};

#endif // __CS_COLLIDER_H__

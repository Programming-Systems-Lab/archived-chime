/*
    Copyright (C) 2000 by Andrew Zabolotny

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

#ifndef __CS_CAMPOS_H__
#define __CS_CAMPOS_H__

#include "csutil/csobject.h"
#include "csutil/nobjvec.h"
#include "csgeom/vector3.h"
#include "csengine/camera.h"
#include "iengine/campos.h"

struct iEngine;
struct iCamera;
class csPlane3;

/**
 * A camera position. This object can be used to initialize a camera object to
 * a certain state.
 */
class csCameraPosition : public csObject
{
private:
  /// Destroy this object and free all associated memory
  virtual ~csCameraPosition ();

private:
  /// The sector this camera points to
  char* sector;
  /// The camera position
  csVector3 position;
  /// Camera orientation: forward vector
  csVector3 forward;
  /// Camera orientation: upward vector
  csVector3 upward;
  /**
   * Far plane. Negative side of this plane (as seen with Classify() function)
   * is invisible (which is different from how planes in CS usually
   * act). If this is NULL there is no far plane.
   */
  csPlane3* far_plane;

public:
  /// Initialize the camera position object
  csCameraPosition (const char *name, const char *sector,
    const csVector3 &position,
    const csVector3 &forward, const csVector3 &upward);

  /// Change camera position object
  void Set (const char *sector, const csVector3 &position,
    const csVector3 &forward, const csVector3 &upward);

  /// Load the camera position into a camera object
  bool Load (iCamera*, iEngine*);

  void SetFarPlane (csPlane3* pl);
  void ClearFarPlane ();

  SCF_DECLARE_IBASE_EXT (csObject);

  //--------------------- iCameraPosition implementation ----------------------
  struct CameraPosition : public iCameraPosition
  {
    SCF_DECLARE_EMBEDDED_IBASE(csCameraPosition);

    virtual iObject *QueryObject();
    virtual iCameraPosition *Clone () const;
    virtual const char *GetSector();
    virtual void SetSector(const char *Name);
    virtual const csVector3 &GetPosition();
    virtual void SetPosition (const csVector3 &v);
    virtual const csVector3 &GetUpwardVector();
    virtual void SetUpwardVector (const csVector3 &v);
    virtual const csVector3 &GetForwardVector();
    virtual void SetForwardVector (const csVector3 &v);
    virtual void Set (const char *sector, const csVector3 &pos,
      const csVector3 &forward, const csVector3 &upward);
    virtual bool Load (iCamera *c, iEngine *e);
    virtual void SetFarPlane (csPlane3* pl)
    {
      scfParent->SetFarPlane (pl);
    }
    virtual void ClearFarPlane ()
    {
      scfParent->ClearFarPlane ();
    }
    virtual csPlane3* GetFarPlane () const
    {
      return scfParent->far_plane;
    }
  } scfiCameraPosition;
  friend struct CameraPosition;
};

#endif // __CS_CAMPOS_H__

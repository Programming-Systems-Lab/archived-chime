/*
    Copyright (C) 1998-2001 by Jorrit Tyberghein

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

#ifndef __CS_RVIEW_H__
#define __CS_RVIEW_H__

#include "csgeom/math3d.h"
#include "csgeom/frustum.h"
#include "csengine/camera.h"
#include "csutil/csvector.h"
#include "iengine/rview.h"
#include "iengine/engine.h"

class csMatrix3;
class csVector3;
class csRenderView;
struct csFog;
struct iGraphics3D;
struct iGraphics2D;
struct iPolygon3D;
struct iSector;
struct iClipper2D;

/**
 * This structure represents all information needed for drawing
 * a scene. It is modified while rendering according to
 * portals/warping portals and such.
 */
class csRenderView : public iRenderView
{
private:
  /**
   * A structure to keep data with the render context. All data
   * that is attached to a render context will be automatically cleaned
   * up when the render context is deleted (i.e. when a recursion level
   * is closed).
   */
  struct csRenderContextData
  {
    /// Next data.
    csRenderContextData* next;

    /// The key is some value on which we want to retreive the data.
    void* key;
    /**
     * This is the data. When the render context is deleted it will DecRef()
     * this.
     */
    iBase* data;
  };

  /// The current render context.
  csRenderContext* ctxt;

  /// Engine handle.
  iEngine* iengine;
  /// The 3D graphics subsystem used for drawing.
  iGraphics3D* g3d;
  /// The 2D graphics subsystem used for drawing.
  iGraphics2D* g2d;
  /**
   * A copy to the original base camera before space warping.
   */
  iCamera* original_camera;

  /// The view frustum as defined at z=1.
  float leftx, rightx, topy, boty;
  /// The frustum corresponding with this.
  csRenderContextFrustum* top_frustum;

  /**
   * A callback function. If this is set then no drawing is done.
   * Instead the callback function is called.
   */
  iDrawFuncCallback* callback;

  /**
   * Delete all data on the given render context.
   */
  void DeleteRenderContextData (csRenderContext* rc);

  /**
   * Update the csRenderContextFrustum to the given clipper.
   */
  void UpdateFrustum (iClipper2D* clip, csRenderContextFrustum*
  	frust);

  /**
   * Given a csRenderContextFrustum and a bounding sphere calculate if
   * the sphere is fully inside and fully outside that frustum.
   */
  static void TestSphereFrustum (csRenderContextFrustum* frust,
  	const csVector3& center, float radius, bool& inside, bool& outside);

public:
  ///
  csRenderView ();
  ///
  csRenderView (iCamera* c);
  ///
  csRenderView (iCamera* c, iClipper2D* v, iGraphics3D* ig3d,
    iGraphics2D* ig2d);

  virtual ~csRenderView ();

  /// Set the engine.
  void SetEngine (iEngine* engine);
  /// Set the camera.
  void SetCamera (iCamera* camera);
  /// Set the original camera.
  void SetOriginalCamera (iCamera* camera);
  /// Get the original camera.
  virtual iCamera* GetOriginalCamera () const { return original_camera; }

  ///
  virtual void SetCallback (iDrawFuncCallback* cb)
  {
    if (cb) cb->IncRef ();
    if (callback) callback->DecRef ();
    callback = cb;
  }
  ///
  virtual iDrawFuncCallback* GetCallback ()
  {
    return callback;
  }

  /// Call callback.
  virtual void CallCallback (int type, void* data)
  {
    callback->DrawFunc (this, type, data);
  }

  SCF_DECLARE_IBASE;

  /// Get the current render context.
  virtual csRenderContext* GetRenderContext () { return ctxt; }

  /**
   * Create a new render context. This is typically used
   * when going through a portal. Note that you should remember
   * the old render context if you want to restore it later.
   * The render context will get all the values from the current context
   * (with SCF references properly incremented).
   */
  virtual void CreateRenderContext ();

  /**
   * Restore a render context. Use this to restore a previously overwritten
   * render context. This function will take care of properly cleaning
   * up the current render context.
   */
  virtual void RestoreRenderContext (csRenderContext* original);

  /**
   * Create a new camera in the current render context. This function
   * will create a new camera based on the current one. The new camera
   * reference is returned.
   */
  virtual iCamera* CreateNewCamera ();

  /// Get the engine.
  virtual iEngine* GetEngine () { return iengine; }
  /// Get the 2D graphics subsystem.
  virtual iGraphics2D* GetGraphics2D () { return g2d; }
  /// Get the 3D graphics subsystem.
  virtual iGraphics3D* GetGraphics3D () { return g3d; }
  /// Set the view frustum at z=1.
  virtual void SetFrustum (float lx, float rx, float ty, float by);
  /// Get the frustum.
  virtual void GetFrustum (float& lx, float& rx, float& ty, float& by)
  {
    lx = leftx;
    rx = rightx;
    ty = topy;
    by = boty;
  }
  /// Get the top level frustum (corresponding with SetFrustum()).
  virtual csRenderContextFrustum* GetTopFrustum ()
  {
    return top_frustum;
  }

  //-----------------------------------------------------------------
  // The following functions operate on the current render context.
  //-----------------------------------------------------------------

  /// Get the 2D clipper for this view.
  virtual iClipper2D* GetClipper () { return ctxt->iview; }
  /// Set the 2D clipper for this view.
  virtual void SetClipper (iClipper2D* clip);

  /**
   * If true then we have to clip all objects to the portal frustum
   * (returned with GetClipper()). Normally this is not needed but
   * some portals require this. If GetClipPlane() returns true then the
   * value of this function is also implied to be true.
   */
  virtual bool IsClipperRequired () { return ctxt->do_clip_frustum; }
  /**
   * Get the 3D clip plane that should be used to clip all geometry.
   * If this function returns false then this plane is invalid and should
   * not be used. Otherwise it must be used to clip the object before
   * drawing.
   */
  virtual bool GetClipPlane (csPlane3& pl)
  {
    pl = ctxt->clip_plane;
    return ctxt->do_clip_plane;
  }
  /// Get the clip plane.
  virtual csPlane3& GetClipPlane ()
  {
    return ctxt->clip_plane;
  }
  ///
  virtual void SetClipPlane (const csPlane3& p) { ctxt->clip_plane = p; }
  ///
  virtual void UseClipPlane (bool u) { ctxt->do_clip_plane = u; }
  ///
  virtual void UseClipFrustum (bool u) { ctxt->do_clip_frustum = u; }


  /**
   * Every fogged sector we encountered results in an extra structure in the
   * following list. This is only used if we are doing vertex based fog.
   * This function will return the first csFogInfo instance.
   */
  virtual csFogInfo* GetFirstFogInfo () { return ctxt->fog_info; }
  /**
   * Set the first fog info.
   */
  virtual void SetFirstFogInfo (csFogInfo* fi)
  {
    ctxt->fog_info = fi;
    ctxt->added_fog_info = true;
  }
  /**
   * Return true if fog info has been added.
   */
  virtual bool AddedFogInfo () { return ctxt->added_fog_info; }
  /**
   * Reset fog info.
   */
  virtual void ResetFogInfo () { ctxt->added_fog_info = false; }

  /**
   * Get the current camera.
   */
  virtual iCamera* GetCamera () { return ctxt->icamera; }
  /**
   * Calculate the fog information in the given G3DPolygonDP structure.
   */
  virtual void CalculateFogPolygon (G3DPolygonDP& poly);
  /**
   * Calculate the fog information in the given G3DPolygonDPFX structure.
   */
  virtual void CalculateFogPolygon (G3DPolygonDPFX& poly);
  /**
   * Calculate the fog information in the given G3DTriangleMesh
   * structure. This function assumes the fog array is already preallocated
   * and the rest of the structure should be filled in.
   * This function will take care of correctly enabling/disabling fog.
   */
  virtual void CalculateFogMesh (const csTransform& tr_o2c,
  	G3DTriangleMesh& mesh);

  /**
   * Calculate the fog information in the given G3DPolygonMesh
   * structure. This function assumes the fog array is already preallocated
   * and the rest of the structure should be filled in.
   * This function will take care of correctly enabling/disabling fog.
   */

  virtual void CalculateFogMesh (const csTransform &tr_o2c, 
    G3DPolygonMesh &mesh);



  /**
   * Test if the given bounding sphere (in object space coordinates)
   * is visibile in this render view. The transformation will
   * transform object to camera space.
   */
  virtual bool TestBSphere (const csReversibleTransform& o2c,
  	const csSphere& sphere);
  /**
   * Check if the given bounding sphere (in object space coordinates)
   * is visibile in this render view. The given transformation should
   * transform object to camera space. If the sphere is visible this
   * function will also initialize the clip_plane, clip_z_plane, and
   * clip_portal fields which can be used for DrawTriangleMesh or
   * DrawPolygonMesh.
   */
  virtual bool ClipBSphere (const csReversibleTransform& o2c,
  	const csSphere& sphere,
	int& clip_portal, int& clip_plane, int& clip_z_plane);
  /**
   * Check if the screen bounding box of an object is visible in
   * this render view. If true is returned (visible) then clip_plane,
   * clip_z_plane, and clip_portal will be set to the right value depending
   * on wether or not clipping is wanted. This function also does far
   * plane clipping.
   */
  virtual bool ClipBBox (const csBox2& sbox, const csBox3& cbox,
      	int& clip_portal, int& clip_plane, int& clip_z_plane);

  /**
   * Get current sector.
   */
  virtual iSector* GetThisSector () { return ctxt->this_sector; }

  /**
   * Set the current sector.
   */
  virtual void SetThisSector (iSector* s) { ctxt->this_sector = s; }

  /**
   * Get previous sector.
   */
  virtual iSector* GetPreviousSector () { return ctxt->previous_sector; }

  /**
   * Set the previous sector.
   */
  virtual void SetPreviousSector (iSector* s) { ctxt->previous_sector = s; }

  /// Get the portal polygon.
  virtual iPolygon3D* GetPortalPolygon () { return ctxt->portal_polygon; }
  /// Set the portal polygon.
  virtual void SetPortalPolygon (iPolygon3D* por)
  { ctxt->portal_polygon = por; }

  /**
   * Get render recursion level.
   */
  virtual int GetRenderRecursionLevel () { return ctxt->draw_rec_level; }
  /**
   * Set render recursion level.
   */
  virtual void SetRenderRecursionLevel (int rec)
  {
    ctxt->draw_rec_level = rec;
  }

  /**
   * Attach data to the current render context.
   */
  virtual void AttachRenderContextData (void* key, iBase* data);
  /**
   * Look for data on the current render context.
   */
  virtual iBase* FindRenderContextData (void* key);
  /**
   * Delete all data with the given key on the current render
   * context.
   */
  virtual void DeleteRenderContextData (void* key);
};

#endif // __CS_RVIEW_H__

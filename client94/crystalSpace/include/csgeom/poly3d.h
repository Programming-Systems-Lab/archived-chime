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

#ifndef __CS_POLY3D_H__
#define __CS_POLY3D_H__

#include "csgeom/math3d.h"

// Values returned by classify.
#define CS_POL_SAME_PLANE 0
#define CS_POL_FRONT 1
#define CS_POL_BACK 2
#define CS_POL_SPLIT_NEEDED 3

class csPoly2D;

/**
 * The following class represents a general 3D polygon.
 */
class csPoly3D
{
protected:
  /// The 3D vertices.
  csVector3* vertices;
  ///
  int num_vertices;
  ///
  int max_vertices;

public:
  /**
   * Make a new empty polygon.
   */
  csPoly3D (int start_size = 10);

  /// Copy constructor.
  csPoly3D (const csPoly3D& copy);

  /// Destructor.
  virtual ~csPoly3D ();

  /**
   * Initialize the polygon to empty.
   */
  void MakeEmpty ();

  /**
   * Get the number of vertices.
   */
  int GetVertexCount () const { return num_vertices; }

  /**
   * Get the array with all vertices.
   */
  csVector3* GetVertices () const { return vertices; }

  /**
   * Get the specified vertex.
   */
  csVector3* GetVertex (int i) const
  {
    if (i<0 || i>=num_vertices) return NULL;
    return &vertices[i];
  }

  /**
   * Get the specified vertex.
   */
  csVector3& operator[] (int i)
  {
    CS_ASSERT (i >= 0 && i < num_vertices);
    return vertices[i];
  }

  /**
   * Get the specified vertex.
   */
  csVector3& operator[] (int i) const
  {
    CS_ASSERT (i >= 0 && i < num_vertices);
    return vertices[i];
  }

  /**
   * Get the first vertex.
   */
  csVector3* GetFirst () const
  { if (num_vertices<=0) return NULL;  else return vertices; }

  /**
   * Get the last vertex.
   */
  csVector3* GetLast () const
  { if (num_vertices<=0) return NULL; else return &vertices[num_vertices-1]; }

  /**
   * Test if this vector is inside the polygon.
   */
  bool In (const csVector3& v) const;

  /**
   * Test if a vector is inside the given polygon.
   */
  static bool In (csVector3* poly, int num_poly, const csVector3& v);

  /**
   * Make room for at least the specified number of vertices.
   */
  void MakeRoom (int new_max);

  /**
   * Set the number of vertices.
   */
  void SetVertexCount (int n) { MakeRoom (n); num_vertices = n; }

  /**
   * Add a vertex (3D) to the polygon.
   * Return index of added vertex.
   */
  int AddVertex (const csVector3& v) { return AddVertex (v.x, v.y, v.z); }

  /**
   * Add a vertex (3D) to the polygon.
   * Return index of added vertex.
   */
  int AddVertex (float x, float y, float z);

  /**
   * Set all polygon vertices at once.  Copies the array.
   */
  void SetVertices (csVector3 const* v, int num)
  { MakeRoom (num); memcpy (vertices, v, (num_vertices = num) * sizeof (csVector3)); }

  /**
   * Project this polygon onto a X plane as seen from some
   * point in space. Fills the given 2D polygon with the projection
   * on the plane. This function assumes that there actually is
   * a projection. If the polygon to project comes on the same plane
   * as 'point' then it will return false (no valid projection).
   */
  bool ProjectXPlane (const csVector3& point, float plane_x,
  	csPoly2D* poly2d) const;

  /**
   * Project this polygon onto a Y plane as seen from some
   * point in space. Fills the given 2D polygon with the projection
   * on the plane. This function assumes that there actually is
   * a projection. If the polygon to project comes on the same plane
   * as 'point' then it will return false (no valid projection).
   */
  bool ProjectYPlane (const csVector3& point, float plane_y,
  	csPoly2D* poly2d) const;

  /**
   * Project this polygon onto a Z plane as seen from some
   * point in space. Fills the given 2D polygon with the projection
   * on the plane. This function assumes that there actually is
   * a projection. If the polygon to project comes on the same plane
   * as 'point' then it will return false (no valid projection).
   */
  bool ProjectZPlane (const csVector3& point, float plane_z,
  	csPoly2D* poly2d) const;

  /**
   * Project this polygon onto an axis-aligned plane as seen from some
   * point in space. Fills the given 2D polygon with the projection
   * on the plane. This function assumes that there actually is
   * a projection. Plane_nr is 0 for the X plane, 1 for Y, and 2 for Z.
   */
  bool ProjectAxisPlane (const csVector3& point, int plane_nr,
	float plane_pos, csPoly2D* poly2d) const
  {
    switch (plane_nr)
    {
      case 0: return ProjectXPlane (point, plane_pos, poly2d);
      case 1: return ProjectYPlane (point, plane_pos, poly2d);
      case 2: return ProjectZPlane (point, plane_pos, poly2d);
    }
    return false;
  }

  /**
   * Static function to classify a polygon with regards to a plane.
   * If this poly is on same plane it returns CS_POL_SAME_PLANE.
   * If this poly is completely in front of the given plane it returnes
   * CS_POL_FRONT. If this poly is completely back of the given plane it
   * returnes CS_POL_BACK. Otherwise it returns CS_POL_SPLIT_NEEDED.
   */
  static int Classify (const csPlane3& pl,
  	csVector3* vertices, int num_vertices);

  /**
   * Classify this polygon with regards to a plane.
   * If this poly is on same plane it returns CS_POL_SAME_PLANE. If this poly is
   * completely in front of the given plane it returnes CS_POL_FRONT. If this
   * poly is completely back of the given plane it returnes CS_POL_BACK.
   * Otherwise it returns CS_POL_SPLIT_NEEDED.
   */
  int Classify (const csPlane3& pl) const
  {
    return Classify (pl, vertices, num_vertices);
  }

  /// Same as Classify() but for X plane only.
  int ClassifyX (float x) const;

  /// Same as Classify() but for Y plane only.
  int ClassifyY (float y) const;

  /// Same as Classify() but for Z plane only.
  int ClassifyZ (float z) const;

  /// Cut this polygon with a plane and only keep the front side.
  void CutToPlane (const csPlane3& split_plane);

  /// Split this polygon with the given plane (A,B,C,D).
  void SplitWithPlane (csPoly3D& front, csPoly3D& back,
  	const csPlane3& split_plane) const;

  /// Split this polygon to the x-plane.
  void SplitWithPlaneX (csPoly3D& front, csPoly3D& back, float x) const;

  /// Split this polygon to the y-plane.
  void SplitWithPlaneY (csPoly3D& front, csPoly3D& back, float y) const;

  /// Split this polygon to the z-plane.
  void SplitWithPlaneZ (csPoly3D& front, csPoly3D& back, float z) const;

  /// Compute the normal of a polygon.
  static csVector3 ComputeNormal (csVector3* vertices, int num);

  /// Compute the normal of this polygon.
  csVector3 ComputeNormal () const
  {
    return ComputeNormal (vertices, num_vertices);
  }

  /// Compute the plane of a polygon.
  static csPlane3 ComputePlane (csVector3* vertices, int num);

  /// Compute the plane of this polygon.
  csPlane3 ComputePlane () const
  {
    return ComputePlane (vertices, num_vertices);
  }

  /**
   * Calculate the signed area of this polygon.
   */
  float GetSignedArea() const;

  /**
   * Compute and get the central vertex of this polygon.
   */
  csVector3 GetCenter () const;
};

/**
 * This is actually the same class as csPoly3D. But it has been
 * renamed to make it clear that it is for other uses. It also
 * adds some functionality specific to that use. In particular
 * this class is more used to hold an unordered collection of 3D vectors.
 */
class csVector3Array : public csPoly3D
{
public:
  csVector3Array (int start_size = 10) : csPoly3D (start_size) { }

  /**
   * Add a vertex but first check if it isn't already present
   * in the array. Return the index that the vertex was added too.
   */
  int AddVertexSmart (const csVector3& v)
  { return AddVertexSmart (v.x, v.y, v.z); }

  /**
   * Add a vertex but first check if it isn't already present
   * in the array. Return the index that the vertex was added too.
   */
  int AddVertexSmart (float x, float y, float z);
};

#endif // __CS_POLY3D_H__

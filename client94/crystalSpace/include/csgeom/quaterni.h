/*
    Copyright (C) 2000 by Norman Kramer

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

#ifndef __CS_QUATERNION_H__
#define __CS_QUATERNION_H__

#include "csgeom/math3d.h"
#include "qsqrt.h"

/**
 * Class for a quaternion.
 */
class csQuaternion
{
public:
  /// Initialize a quaternion with specific values.
  inline void Init (float theR, float theX, float theY, float theZ)
  { r = theR; x = theX; y = theY; z = theZ; }

  /// Construct a 0,0,0,0 quaternion.
  csQuaternion () { Init(0, 0, 0, 0 ); }
  /// Construct a quaternion with the given parameters.
  csQuaternion (float theR, float theX=0.0, float theY=0.0, float theZ=0.0)
  { Init (theR, theX, theY, theZ ); }
  /// Copy constructor.
  csQuaternion (const csQuaternion& q) { Init (q.r, q.x, q.y, q.z); }
  /// Construct quaternion from a vector.
  csQuaternion (const csVector3& q) { Init (0, q.x, q.y, q.z); }

  ///
  inline friend csQuaternion operator+ (const csQuaternion& q1, const csQuaternion& q2)
  { return csQuaternion (q1.r + q2.r, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z ); }
  ///
  inline friend csQuaternion operator- (const csQuaternion& q1, const csQuaternion& q2)
  { return csQuaternion (q1.r - q2.r, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z ); }
  ///
  inline friend csQuaternion operator* (const csQuaternion& q1, const csQuaternion& q2)
  { return csQuaternion (q1.r*q2.r -  q1.x*q2.x - q1.y*q2.y - q1.z*q2.z,
			 q1.y*q2.z -  q1.z*q2.y + q1.r*q2.x + q1.x*q2.r,
			 q1.z*q2.x -  q1.x*q2.z + q1.r*q2.y + q1.y*q2.r,
			 q1.x*q2.y -  q1.y*q2.x + q1.r*q2.z + q1.z*q2.r); }

  ///
  csQuaternion& operator*= (const csQuaternion& q2)
  {
    Init (r*q2.r -  x*q2.x - y*q2.y - z*q2.z,
	  y*q2.z -  z*q2.y + r*q2.x + x*q2.r,
	  z*q2.x -  x*q2.z + r*q2.y + y*q2.r,
	  x*q2.y -  y*q2.x + r*q2.z + z*q2.r);
    return *this;
  }

  ///
  void Conjugate () { Init (r, -x, -y, -z); }

	/// Negate all parameters of the quaternion
	void Negate () { Init(-r, -x, -y, -z); }

  /**
   * Prepare a rotation quaternion, we do a rotation around vec by
   * an angle of "angle". Note that vec needs to be a normalized
   * vector ( we don't check this ).
   */
  void PrepRotation (float angle, csVector3 vec)
  {
    double theSin = sin (angle / 2.0f);
    Init ((float) cos (angle / 2.0f), vec.x * theSin, vec.y * theSin, vec.z * theSin);
  }

  /// rotated = q * vec * qConj.
  csVector3 Rotate (csVector3 vec)
  {
    csQuaternion p (vec);
    csQuaternion qConj (r, -x, -y, -z);

    p = *this * p;
    p *= qConj;
    return csVector3 (p.x, p.y, p.z);
  }

  /// Normalize this quaternion.
  void Normalize ()
  {
    if(x*x + y*y + z*z > .999)
    {
      // Severe problems...
      float inverselen = 1.0f / (x*x + y*y + z*z);
      x *= inverselen;
      y *= inverselen;
      z *= inverselen;
      r = 0.0f;
    }
    else
    {
      r = qsqrt(1.0f - x*x - y*y - z*z);
    }
  }

  /**
   * Convert a set of Euler angles to a Quaternion
   * Takes a (X,Y,Z) rather than Yaw-Pitch-Roll (Y,X,Z)
   * The output is NOT Normalized, if you wish to do so, normalize it yourself.
   */
  void SetWithEuler(const csVector3 &rot);

  /**
   * Return an Axis Angle representation of this Quaternion
   */
  csQuaternion ToAxisAngle() const;

  /**
   * Spherical Linear Interpolation between two quaternions
   * Calculated between this class & the second quaternion by the slerp
   * factor and returned as a new quaternion
   */
  csQuaternion Slerp (const csQuaternion &quat2, float slerp) const;

//csQuaternion Lerp(const csQuaternion& quat2, float ratio) const;

  float r,x,y,z;
};


#endif // __CS_QUATERNION_H__

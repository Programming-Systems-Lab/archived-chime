/*
    Copyright (C) 2000 by Jorrit Tyberghein

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

#ifndef __IVIDEO_MATERIAL_H__
#define __IVIDEO_MATERIAL_H__

#include "csutil/scf.h"

/// Default material `diffuse' parameter
#define CS_DEFMAT_DIFFUSE	0.7f
/// Default material `ambient' parameter
#define CS_DEFMAT_AMBIENT	0.0f
/// Default material `reflection' parameter
#define CS_DEFMAT_REFLECTION	0.0f

struct iTextureHandle;
struct csRGBpixel;
struct csRGBcolor;

/**
 * This structure represents an extra texture
 * layer which is applied on top of the previous one.
 */
struct csTextureLayer
{
  iTextureHandle* txt_handle;
  uint mode;		// Mode: one of CS_FX_ADD ...
  float uscale, vscale;	// Txt mapping scale relative to parent texture
  float ushift, vshift;	// Txt mapping shift relative to parent texture
};

SCF_VERSION (iMaterial, 0, 0, 4);

/**
 * This class represents a material as seen from the engine
 * view. You need to register this to the texture manager to get
 * a handle to an internal compiled material. This interface
 * plays same role related to iMaterialHandle as iImage plays
 * related to iTextureHandle.
 */
struct iMaterial : public iBase
{
  /**
   * Get the base texture from the material.
   */
  virtual iTextureHandle *GetTexture () = 0;

  /**
   * Get the number of texture layers. The base
   * texture is not counted in this.
   */
  virtual int GetTextureLayerCount () = 0;

  /**
   * Get a texture layer.
   */
  virtual csTextureLayer* GetTextureLayer (int idx) = 0;

  /**
   * Get the flat color. If the material has a texture assigned, this
   * will return the mean texture color.
   */
  virtual void GetFlatColor (csRGBpixel &oColor) = 0;
  /**
   * Set the flat shading color.
   */
  virtual void SetFlatColor (const csRGBcolor& col) = 0;

  /**
   * Get light reflection parameters for this material.
   */
  virtual void GetReflection (
  	float &oDiffuse, float &oAmbient, float &oReflection) = 0;
  /**
   * Set the reflection parameters.
   */
  virtual void SetReflection (float oDiffuse, float oAmbient,
    float oReflection) = 0;
};

SCF_VERSION (iMaterialHandle, 0, 0, 2);

/**
 * This class represents a material handle (compiled material)
 * for the 3D rasterizer.
 */
struct iMaterialHandle : public iBase
{
  /**
   * Get a texture from the material.
   */
  virtual iTextureHandle *GetTexture () = 0;

  /**
   * Get the flat color. If the material has a texture assigned, this
   * will return the mean texture color.
   */
  virtual void GetFlatColor (csRGBpixel &oColor) = 0;

  /**
   * Get light reflection parameters for this material.
   */
  virtual void GetReflection (float &oDiffuse, float &oAmbient, float &oReflection) = 0;

  /**
   * Prepare this material. The material wrapper (remembered during
   * RegisterMaterial()) is queried again for material parameters
   * and a new material descriptor (internal to the texture manager)
   * is associated with given material handle.
   */
  virtual void Prepare () = 0;
};

#endif // __IVIDEO_MATERIAL_H__

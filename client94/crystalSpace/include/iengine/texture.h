/*
    Copyright (C) 1998, 2000 by Jorrit Tyberghein

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

#ifndef __IENGINE_TEXTURE_H__
#define __IENGINE_TEXTURE_H__

#include "csutil/scf.h"
#include "cstypes.h"

struct iImage;
struct iTextureHandle;
struct iTextureManager;
struct iTextureWrapper;
struct iObject;

SCF_VERSION (iTextureCallback, 0, 0, 1);

/**
 * A callback for when a iTextureWrapper is used.
 */
struct iTextureCallback : public iBase
{
  /// Get height.
  virtual void UseTexture (iTextureWrapper* wrap) = 0;
};

SCF_VERSION (iTextureWrapper, 0, 0, 4);

/**
 * A texture wrapper is an engine-level object that wraps around an actual
 * texture (iTextureHandle). Every texture in the engine is represented
 * by a texture wrapper, which keeps the pointer to the texture handle, its
 * name, and possibly the base image object.
 */
struct iTextureWrapper : public iBase
{
  /// Get the iObject for this texture
  virtual iObject *QueryObject() = 0;

  /// Create a clone this texture wrapper, using the same texture handle
  virtual iTextureWrapper *Clone () const = 0;

  /**
   * Change the base iImage. The changes will not be visible until the
   * texture is registered again.
   */
  virtual void SetImageFile (iImage *Image) = 0;
  /// Get the iImage.
  virtual iImage* GetImageFile () = 0;

  /**
   * Change the texture handle. The changes will immediatly be visible. This
   * will also change the key color and registration flags to those of
   * the new texture and the iImage to NULL.
   */
  virtual void SetTextureHandle (iTextureHandle *tex) = 0;
  /// Get the texture handle.
  virtual iTextureHandle* GetTextureHandle () = 0;

  /// Set the transparent color.
  virtual void SetKeyColor (int red, int green, int blue) = 0;
  /// Query the transparent color.
  virtual void GetKeyColor (int &red, int &green, int &blue) = 0;

  /// Set the flags which are used to register the texture
  virtual void SetFlags (int flags) = 0;
  /// Return the flags which are used to register the texture
  virtual int GetFlags () = 0;

  /// Register the texture with the texture manager
  virtual void Register (iTextureManager *txtmng) = 0;

  /**
   * Set a callback which is called just before the texture is used.
   * This is mainly useful for procedural textures which can then
   * choose to update their image.
   */
  virtual void SetUseCallback (iTextureCallback* callback) = 0;

  /**
   * Get the use callback. If there are multiple use callbacks you can
   * use this function to chain.
   */
  virtual iTextureCallback* GetUseCallback () = 0;

  /**
   * Visit this texture. This should be called by the engine right
   * before using the texture. It is responsible for calling the use
   * callback if there is one.
   */
  virtual void Visit () = 0;
};


SCF_VERSION (iTextureList, 0, 0, 1);

/**
 * This class represents a list of texture wrappers.
 */
struct iTextureList : public iBase
{
  /// Create a new texture.
  virtual iTextureWrapper *NewTexture (iImage *image) = 0;

  /**
   * Create a engine wrapper for a pre-prepared iTextureHandle
   * The handle will be IncRefed.
   */
  virtual iTextureWrapper *NewTexture (iTextureHandle *ith) = 0;

  /// Return the number of textures in this list.
  virtual int GetCount () const = 0;

  /// Return a texture by index.
  virtual iTextureWrapper *Get (int n) const = 0;

  /// Add a texture.
  virtual int Add (iTextureWrapper *obj) = 0;

  /// Remove a texture.
  virtual bool Remove (iTextureWrapper *obj) = 0;

  /// Remove the nth texture.
  virtual bool Remove (int n) = 0;

  /// Remove all textures.
  virtual void RemoveAll () = 0;

  /// Find a texture and return its index.
  virtual int Find (iTextureWrapper *obj) const = 0;

  /// Find a texture by name.
  virtual iTextureWrapper *FindByName (const char *Name) const = 0;
};

#endif // __IENGINE_TEXTURE_H__

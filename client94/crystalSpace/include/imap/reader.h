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

#ifndef __IMAP_LOADER_H__
#define __IMAP_LOADER_H__

#include "csutil/scf.h"

struct iLoaderContext;

SCF_VERSION (iLoaderPlugin, 0, 1, 0);

/**
 * This is a plugin for the loader.
 */
struct iLoaderPlugin : public iBase
{
  /// Parse a given string and return a new object for it.
  virtual iBase* Parse (const char* string, iLoaderContext* ldr_context,
  	iBase* context) = 0;
};

#endif


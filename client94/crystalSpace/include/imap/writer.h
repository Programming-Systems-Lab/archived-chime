/*
    Copyright (C) 2000-2002 by Jorrit Tyberghein
    Copyright (C) 2001 by W.C.A. Wijngaards

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

#ifndef __IMAP_SAVER_H__
#define __IMAP_SAVER_H__

#include "csutil/scf.h"

struct iFile;

SCF_VERSION (iSaverPlugin, 0, 2, 0);

/**
 * This is a plugin to save with.
 */
struct iSaverPlugin : public iBase
{
  /**
   * Take a given object and push description onto the given file.
   */
  virtual void WriteDown (iBase* obj, iFile* file) = 0;
};

#endif


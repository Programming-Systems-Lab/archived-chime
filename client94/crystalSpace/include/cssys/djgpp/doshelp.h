/*
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

#ifndef __WINHELP_H__
#define __WINHELP_H__

#include <stdarg.h>
#include "csutil/scf.h"

SCF_VERSION (iDosHelper, 0, 0, 1);

/**
 * This interface describes actions specific to the DOS platform.
 * An instance of this object will be registered to the object registry
 * with tag 'SystemHelper'. But it is recommended to query this from the
 * object registry using the iDosHelper interface.
 */
struct iDosHelper : public iBase
{
  /**
   * Set mouse position.
   */
  virtual void SetMousePosition (int x, int y) = 0;
  /**
   * Enable/disable printf.
   */
  virtual void DoEnablePrintf (bool en) = 0;
};

#endif // __WINHELP_H__


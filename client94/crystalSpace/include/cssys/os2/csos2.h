/*
    OS/2 support for Crystal Space 3D library
    Copyright (C) 1998 by Andrew Zabolotny <bit@eltech.ru>

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

#ifndef __CSOS2_H__
#define __CSOS2_H__

#include "csutil/csinput.h"
#include "cssys/system.h"
#include "cssys/os2/os2help.h"

class SysSystemDriver;
struct iObjectRegistry;

/**
 * Implementation class for iOs2Helper.
 */
class Os2Helper : public iOs2Helper
{
private:
  SysSystemDriver* sys;

public:
  Os2Helper (SysSystemDriver* sys);
  virtual ~Os2Helper ();

  SCF_DECLARE_IBASE;
  virtual void StartGUI ();
};

/**
 * This is the System driver for OS/2. It implements all required
 * functionality for standard csSystemDriver class.
 */
class SysSystemDriver : public csSystemDriver
{
  /// Window position in percents
  int WindowX, WindowY;
  /// Window width and height
  int WindowWidth, WindowHeight;
  /// Use system cursor if true; otherwise use builtin CSWS software cursors
  bool HardwareCursor;

public:
  /// Initialize system-dependent data
  SysSystemDriver (iObjectRegistry* object_reg);

  /// Perform extension function from Os2Helper.
  void StartGUI ();
};

#endif // __CSOS2_H__

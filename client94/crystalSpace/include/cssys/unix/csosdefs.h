/*
    Copyright (C) 1998 by Jorrit Tyberghein
    Written by Andrew Zabolotny <bit@eltech.ru>

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

#ifndef __CSOSDEFS_H__
#define __CSOSDEFS_H__

#include <math.h>

#ifdef CS_SYSDEF_PROVIDE_SOFTWARE2D
#  define CS_SOFTWARE_2D_DRIVER get_software_2d_driver ()
   static inline char* get_software_2d_driver ()
   {
     if (getenv ("GGI_DISPLAY"))
       return "crystalspace.graphics2d.ggi";
     else
#  if defined (OS_LINUX)
     if (getenv ("DISPLAY"))
#  endif
       return "crystalspace.graphics2d.x2d";
#  if defined (OS_LINUX)
     else
       return "crystalspace.graphics2d.svgalib";
#  endif
   }
#endif


#ifdef CS_SYSDEF_PROVIDE_HARDWARE_MMIO

// Defines that this platform supports hardware memory-mapped i/o
#define CS_HAS_MEMORY_MAPPED_IO 1

#include "cssys/unix/mmiounix.h"

#endif // memory-mapped I/O

// The 2D graphics driver used by OpenGL renderer
#define CS_OPENGL_2D_DRIVER "crystalspace.graphics2d.glx"

// The sound driver
#define CS_SOUND_DRIVER "crystalspace.sound.driver.oss"

#if defined (CS_SYSDEF_PROVIDE_DIR)
#  define __NEED_GENERIC_ISDIR
#endif

#if defined (CS_SYSDEF_PROVIDE_SOCKETS) && defined (OS_SOLARIS)
extern "C" unsigned long inet_addr(const char*);
#endif

#if defined (OS_SOLARIS)
extern "C" int usleep (unsigned);
#endif

#if !defined(CS_STATIC_LINKED) && defined(CS_UNIX_PLUGIN_REQUIRES_MAIN)
// Dummy main function required for plugin modules on some Unix platforms.
// Implementing this function ensures that global constructors in plugin
// modules are invoked.
#define CS_IMPLEMENT_PLATFORM_PLUGIN \
int main (int argc, char* argv[]) \
{ \
  (void)argc; (void)argv; \
  return 0; \
}
#endif // !CS_STATIC_LINKED && CS_UNIX_PLUGIN_REQUIRES_MAIN

#endif // __CSOSDEFS_H__

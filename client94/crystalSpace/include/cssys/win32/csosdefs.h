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

#if defined(COMP_VC)
  #pragma warning(disable:4291)   // no matching operator delete found
  #pragma warning(disable:4244)   // conversion from 'double' to 'float'
  #pragma warning(disable:4305)   // conversion from 'const double' to 'float'
  #pragma warning(disable:4018)   // Signed unsigned warnings
  #pragma warning(disable:4245)   // Signed unsigned warnings
  #pragma warning(disable:4805)   // unsafe mix of bool and int.
  #pragma warning(disable:4800)   // Forcing value to bool
  #pragma warning(disable:4514)   // Removal of unreferenced inline function
  #pragma warning(disable:4097)   // use of xxx as synonym for a classname
  #pragma warning(disable:4127)   // conditional expression is constant
  #pragma warning(disable:4189)   // local variable is intialized but not referenced
  #pragma warning(disable:4706)   // Assignment in conditional expression
  #pragma warning(disable:4611)   // interaction between _setjmp and C++ destructors not portable
  #pragma warning(disable:4710)   // function not inlined
  #pragma warning(disable:4201)   // structure/ union without name. (Only relevant on MSVC 5.0)
  #pragma warning(disable:4702)   // Unreachable Code
  #pragma warning(disable:4512)   // Could not generate assignment operator
  #pragma warning(disable:4100)   // Use of void* as a formal function parameter
  #pragma warning(disable:4390)   // Empty control statement

  #pragma inline_depth (255)
  #pragma inline_recursion (on)
  #pragma auto_inline (on)
#endif

// So many things require this. IF you have an issue with something defined
// in it then undef that def here.
#include <windows.h>
#include <malloc.h>

#if defined(COMP_VC)
  typedef __int64 int64_t;
#else
  typedef long long int64_t;
#endif

#define WIN32_LEAN_AND_MEAN

#undef min
#undef max
#undef GetCurrentTime
#undef DeleteFile

#ifdef _DEBUG
  #include <assert.h>
  #define ASSERT(expression) assert(expression)
  #define VERIFY_SUCCESS(expression) assert(SUCCEEDED(expression))
  #define VERIFY_RESULT(expression, result) assert(expression == result)
  #ifndef CS_DEBUG
    #define CS_DEBUG
  #endif

  #undef  DEBUG_BREAK
  #define DEBUG_BREAK ::DebugBreak()

#else
  #define ASSERT(expression)
  #define VERIFY_SUCCESS(expression) expression
  #define VERIFY_RESULT(expression, result) expression
#endif


#ifdef CS_SYSDEF_PROVIDE_HARDWARE_MMIO

// Defines that this platform supports hardware memory-mapped i/o
#define CS_HAS_MEMORY_MAPPED_IO 1

// Windows specific memory-mapped I/O stuff.
struct mmioInfo
{
    /// Handle to the mapped file 
    HANDLE hMappedFile;

    /// Handle to the mapping
    HANDLE hFileMapping;
  
    /// Base pointer to the data
    unsigned char *data;

    /// File size
    unsigned int file_size;
};

// Fills in the mmioInfo struct by mapping in filename.  Returns true on success, false otherwise.
inline 
bool
MemoryMapFile(mmioInfo *platform, char *filename)
{  
  if (
      (platform->hMappedFile=CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL))==INVALID_HANDLE_VALUE ||
      (platform->file_size=GetFileSize(platform->hMappedFile, NULL)) == 0xFFFFFFFF                                                    ||          
      (platform->hFileMapping = CreateFileMapping(platform->hMappedFile, NULL, PAGE_READONLY, 0, 0, NULL)) == NULL                              ||          
      (platform->data = (unsigned char *)MapViewOfFile(platform->hFileMapping, FILE_MAP_READ, 0, 0, platform->file_size))==NULL 
     )                                                                                              
  {                                                                                                 
    return false;                                                                        
  }                                                                                                 
  else                                                                                              
  {
    return true;                                                                         
  }
}

inline 
void
UnMemoryMapFile(mmioInfo *platform)
{
  if (platform->data!=NULL)
    UnmapViewOfFile(platform->data);

  if (platform->hMappedFile!=INVALID_HANDLE_VALUE)
    CloseHandle(platform->hMappedFile);

  if (platform->hFileMapping!=INVALID_HANDLE_VALUE)
    CloseHandle(platform->hFileMapping);
}

#endif

// The 2D graphics driver used by software renderer on this platform
#define CS_SOFTWARE_2D_DRIVER "crystalspace.graphics2d.directdraw"
#define CS_OPENGL_2D_DRIVER "crystalspace.graphics2d.glwin32"

// The sound driver
#define CS_SOUND_DRIVER "crystalspace.sound.driver.waveout"

// SCF symbol export facility.
#undef CS_EXPORTED_FUNCTION
#define CS_EXPORTED_FUNCTION extern "C" __declspec(dllexport)

#if defined (CS_SYSDEF_PROVIDE_DIR) || defined (CS_SYSDEF_PROVIDE_GETCWD) || defined (CS_SYSDEF_PROVIDE_MKDIR)
#  include <direct.h>
#  if defined(COMP_BC) || defined(COMP_GCC)
#    ifdef __CYGWIN32__
#	include <sys/dirent.h>
#    else
#    	include <dirent.h>
#    endif
#  endif
#endif

#if defined (COMP_BC)
#  define strcasecmp stricmp
#  define strncasecmp strnicmp
#endif

#if defined (COMP_VC)
#  define strcasecmp _stricmp
#  define strncasecmp _strnicmp
#endif

// Maximal path length
#ifdef CS_SYSDEF_PROVIDE_PATH
#  ifndef CS_MAXPATHLEN
#    ifdef _MAX_FNAME
#      define CS_MAXPATHLEN _MAX_FNAME
#    else
#      define CS_MAXPATHLEN 260 /* not 256 */
#    endif
#  endif
#endif

// Windows has built-in var "SystemRoot"
// (env var on NT, but not 9x; so we provide it this way)
// @@@ provide HOME(DIR) ??? ("My Docs" maybe?)
#ifdef CS_SYSDEF_VFS_PROVIDE_CHECK_VAR

char* __WindowsDirectory()
{
  static char lpWindowsDirectory[MAX_PATH+1] = {'\0'};

  if (!*lpWindowsDirectory) {
    GetWindowsDirectoryA(lpWindowsDirectory, MAX_PATH);
  }

  return lpWindowsDirectory;
}

#define CS_SYSDEF_VFS_CHECK_VAR(VarName) \
  if (!stricmp(VarName, "systemroot")) { \
    value = __WindowsDirectory(); \
  }
#endif

// COMP_GCC has generic opendir(), readdir(), closedir()

#if defined(CS_SYSDEF_PROVIDE_DIR) || defined(CS_SYSDEF_PROVIDE_PATH)
// Directory read functions
# if !defined(COMP_GCC)
#  if !defined(COMP_BC)
    #define __NEED_OPENDIR_PROTOTYPE
    #include <io.h>

    // Directory entry
    struct dirent
    {
      char d_name [CS_MAXPATHLEN + 1]; // File name, 0 terminated
      long d_size; // File size (bytes)
      unsigned d_attr; // File attributes (Windows-specific)
    };
    // Directory handle
    struct DIR
    {
      bool valid;
      long handle;
      dirent de;
      _finddata_t fd;
    };
    static inline bool isdir (const char *path, dirent *de)
    {
      (void)path;
      return !!(de->d_attr & _A_SUBDIR);
    }

    extern "C" DIR *opendir (const char *name);
    extern "C" dirent *readdir (DIR *dirp);
    extern "C" int closedir (DIR *dirp);
#  endif // end if !defined(COMP_BC)
# endif
#endif

#ifdef CS_SYSDEF_PROVIDE_PATH
#  if defined(COMP_BC) || defined(COMP_GCC)
#    define __NEED_GENERIC_ISDIR
#  else
#    define __NO_GENERIC_ISDIR
     static inline bool isdir (char *path, dirent *de)
     {
       (void)path;
       return !!(de->d_attr & _A_SUBDIR);
     }
#  endif
#endif

#ifdef CS_SYSDEF_PROVIDE_SOCKETS
#include <winsock.h>
#ifndef socklen_t
   typedef int socklen_t;
#endif
   typedef SOCKET csNetworkSocket;
#  define CS_NET_SOCKET_INVALID INVALID_SOCKET
#  define CS_IOCTLSOCKET ioctlsocket
#  define CS_CLOSESOCKET closesocket
#  define EWOULDBLOCK WSAEWOULDBLOCK
#  define CS_GETSOCKETERROR ::WSAGetLastError()
#  undef CS_SYSDEF_PROVIDE_SOCKETS
#endif

#ifdef CS_SYSDEF_PROVIDE_SELECT
#  undef CS_SYSDEF_PROVIDE_SELECT
#endif

#ifdef CS_SYSDEF_PROVIDE_ACCESS
#  include <io.h>
#endif

#ifdef COMP_BC
#  define GETPID() getpid()
#else
#  define GETPID() _getpid()
#endif

#ifdef CS_SYSDEF_PROVIDE_TEMP
#  include <process.h>
#  define TEMP_FILE "%x.cs", GETPID()
#  define TEMP_DIR win32_tempdir()
   // This is the function called by TEMP_DIR macro
   static inline char *win32_tempdir()
   {
     char *tmp;
     if ((tmp = getenv ("TMP")) != NULL)
       return tmp;
     if ((tmp = getenv ("TEMP")) != NULL)
       return tmp;
     return "";
   }
#endif // CS_SYSDEF_PROVIDE_TEMP

// Microsoft Visual C++ compiler includes a very in-efficient 'memcpy'.
// This also replaces the older 'better_memcpy',which was also not as
// efficient as it could be ergo...heres a better solution.
#ifdef COMP_VC
#define memcpy fast_mem_copy
static inline void* fast_mem_copy (void *dest, const void *src, int count)
{
    __asm
    {
      mov		eax, count
      mov		esi, src
      mov		edi, dest
      xor		ecx, ecx

      // Check for 'short' moves
      cmp		eax, 16
      jl		do_short
		
      // Move enough bytes to align 'dest'
      sub		ecx, edi
      and		ecx, 3
      je		skip
      sub		eax, ecx
      rep		movsb

      skip:
        mov		ecx, eax
        and		eax, 3
        shr		ecx, 2
        rep		movsd
        test	eax, eax
        je		end

      do_short:
        mov		ecx, eax
        rep		movsb

      end:
    }

    return dest;
}
#endif

#ifdef COMP_BC
// Major hack due to pow failures in CS for Borland, removing this
// causes millions of strings to print out -- Brandon Ehle
#define pow(arga, argb) ( (!arga && !argb)?0:pow(arga, argb) )
// Dunno why this is in CS -- Brandon Ehle
#define DEBUG_BREAK
#endif

#if defined (PROC_X86)
#  define CS_LITTLE_ENDIAN
#else
#  error "Please define a suitable CS_XXX_ENDIAN macro in win32/csosdefs.h!"
#endif

#if defined(COMP_BC)
  // The Borland C++ compiler does not accept a 'main' routine
  // in a program which already contains WinMain. This is a work-around.
  #undef main
  #define main csMain
#endif

#if defined(COMP_BC)
  #define CS_WIN32_ARGC _argc
  #define CS_WIN32_ARGV _argv
#else
  #define CS_WIN32_ARGC __argc
  #define CS_WIN32_ARGV __argv
#endif

#define CS_IMPLEMENT_PLATFORM_APPLICATION \
int main (int argc, char* argv[]); \
HINSTANCE ModuleHandle = NULL; \
int ApplicationShow = SW_SHOWNORMAL; \
int WINAPI WinMain (HINSTANCE hApp, HINSTANCE prev, LPSTR cmd, int show) \
{ \
  ModuleHandle = hApp; \
  ApplicationShow = show; \
  (void)prev; \
  (void)cmd; \
  return main(CS_WIN32_ARGC, CS_WIN32_ARGV); \
}

#if !defined(CS_STATIC_LINKED)

#define CS_IMPLEMENT_PLATFORM_PLUGIN \
HINSTANCE ModuleHandle = NULL; \
extern "C" BOOL WINAPI \
DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID /*lpvReserved*/) \
{ \
  if (fdwReason == DLL_PROCESS_ATTACH) \
    ModuleHandle = hinstDLL; \
  return TRUE; \
}

#endif // !CS_STATIC_LINKED

#endif // __CSOSDEFS_H__

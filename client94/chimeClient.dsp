# Microsoft Developer Studio Project File - Name="chimeClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=chimeClient - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "chimeClient.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "chimeClient.mak" CFG="chimeClient - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "chimeClient - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "chimeClient - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "chimeClient - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "WIN32_VOLATILE" /D "__CRYSTAL_SPACE__" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 Cache.lib urlmon.lib zlib.lib png.lib libjpeg.lib dinput.lib dxguid.lib winmm.lib libcsengine.lib libcsgeom.lib libcsgfx.lib csparser.lib libcssys.lib libcsutil.lib libcstool.lib libcsws.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "chimeClient - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "WIN32_VOLATILE" /D "___CRYSTAL_SPACE__" /D "CS_DEBUG" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Cache.lib urlmon.lib zlib.lib png.lib libjpeg.lib dinput.lib dxguid.lib winmm.lib libcsengine_d.lib libcsgeom_d.lib libcsgfx_d.lib csparser.lib libcssys_d.lib libcsutil_d.lib libcstool_d.lib libcsws_d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:windows /verbose /debug /machine:I386 /nodefaultlib:"libcmt.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "chimeClient - Win32 Release"
# Name "chimeClient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AICacheController.cpp
# End Source File
# Begin Source File

SOURCE=.\AICommController.cpp
# End Source File
# Begin Source File

SOURCE=.\AIDownloader.cpp
# End Source File
# Begin Source File

SOURCE=.\AISyncController.cpp
# End Source File
# Begin Source File

SOURCE=.\AITimeController.cpp
# End Source File
# Begin Source File

SOURCE=.\AIVideoFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\AIVideoFrameBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\AIVideoPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\AIVideoPlayerWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\AlwaysVisibleWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\ChimeApp.cpp
# End Source File
# Begin Source File

SOURCE=.\ChimeCollider.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ChimeComm.cpp
# End Source File
# Begin Source File

SOURCE=.\ChimeSector.cpp
# End Source File
# Begin Source File

SOURCE=.\ChimeSystemDriver.cpp
# End Source File
# Begin Source File

SOURCE=.\ChimeWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\ChimeWorldView.cpp
# End Source File
# Begin Source File

SOURCE=.\comm_client\ClientComm.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\GetObjectWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\HistoryWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoStorer.cpp
# End Source File
# Begin Source File

SOURCE=.\OverviewAWS.cpp
# End Source File
# Begin Source File

SOURCE=.\comm_client\SienaPublisher.cpp
# End Source File
# Begin Source File

SOURCE=.\comm_client\SienaSubscriber.cpp
# End Source File
# Begin Source File

SOURCE=.\SienaWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\comm_client\UDPClient.cpp
# End Source File
# Begin Source File

SOURCE=.\comm_client\UDPServer.cpp
# End Source File
# Begin Source File

SOURCE=.\VEMWindow.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AI2TVConstants.h
# End Source File
# Begin Source File

SOURCE=.\AICache.h
# End Source File
# Begin Source File

SOURCE=.\AICacheController.h
# End Source File
# Begin Source File

SOURCE=.\AICommController.h
# End Source File
# Begin Source File

SOURCE=.\AIDownloader.h
# End Source File
# Begin Source File

SOURCE=.\AISyncController.h
# End Source File
# Begin Source File

SOURCE=.\AITimeController.h
# End Source File
# Begin Source File

SOURCE=.\AIVideoFrame.h
# End Source File
# Begin Source File

SOURCE=.\AIVideoFrameBuffer.h
# End Source File
# Begin Source File

SOURCE=.\AIVideoPlayer.h
# End Source File
# Begin Source File

SOURCE=.\AIVideoPlayerWindow.h
# End Source File
# Begin Source File

SOURCE=.\ChimeApp.h
# End Source File
# Begin Source File

SOURCE=.\ChimeComm.h
# End Source File
# Begin Source File

SOURCE=.\ChimeInfoEvent.h
# End Source File
# Begin Source File

SOURCE=.\ChimeLabeling.h
# End Source File
# Begin Source File

SOURCE=.\ChimeSector.h
# End Source File
# Begin Source File

SOURCE=.\ChimeSystemDriver.h
# End Source File
# Begin Source File

SOURCE=.\ChimeWindow.h
# End Source File
# Begin Source File

SOURCE=.\ChimeWorldView.h
# End Source File
# Begin Source File

SOURCE=.\comm_client\ClientComm.h
# End Source File
# Begin Source File

SOURCE=.\InfoStorer.h
# End Source File
# Begin Source File

SOURCE=.\OverviewAWS.h
# End Source File
# Begin Source File

SOURCE=.\WindowToolkit.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\..\ai2tv\NextToFinal\bin\Cache.dll
# End Source File
# End Target
# End Project

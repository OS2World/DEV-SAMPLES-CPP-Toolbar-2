# IBM Developer's Workframe/2 Make File Creation run at 23:35:39 on 09/15/94

# Make File Creation run in directory:
#   E:\DEVEL\TOOLBAR;

.SUFFIXES:

.SUFFIXES: .c .cpp .cxx .rc

ALL: TOOLBAR.EXE \
     TOOLBAR.RES

TOOLBAR.EXE:  \
  AINFOA.OBJ \
  AMHLPHDR.OBJ \
  AMMVEHDR.OBJ \
  ATIMEHDR.OBJ \
  ATOOLBAR.OBJ \
  TOOLBAR.OBJ \
  TOOLBAR.RES \
  TOOLBAR.MAK
   ICC.EXE @<<
/Tl- /Tdp /Ti /Gm /Gd /G4  
 /B" /de /pmtype:pm"
 /Fe"TOOLBAR.EXE" DDE4CCI.LIB DDE4MBSI.LIB DDE4MUII.LIB TOOLBAR.DEF 
AINFOA.OBJ 
AMHLPHDR.OBJ 
AMMVEHDR.OBJ 
ATIMEHDR.OBJ 
ATOOLBAR.OBJ 
TOOLBAR.OBJ
<<
   RC TOOLBAR.RES TOOLBAR.EXE

{.}.rc.res:
   RC -r .\$*.RC

{.}.c.obj:
   ICC.EXE /Tl- /Ti /Gm /Gd /G4 /C   .\$*.c

{.}.cpp.obj:
   ICC.EXE /Tl- /Ti /Gm /Gd /G4 /C   .\$*.cpp

{.}.cxx.obj:
   ICC.EXE /Tl- /Ti /Gm /Gd /G4 /C   .\$*.cxx

!include TOOLBAR.DEP

:: %1: toolchain path

@echo off

SET CORE_NAME=%2
SET CLANG_DEFINE=__boot_%CORE_NAME%__

SET LIBS_DIR=libs
SET BOOTNAME=bootloader

SET TOOLCHAIN_BASE=%1
SET CLANG_BIN=%TOOLCHAIN_BASE%\bin\clang.exe
SET LD_BIN=%TOOLCHAIN_BASE%\bin\lld.exe

SET DRIVERLIB_DIR=..\%LIBS_DIR%\driverlib
SET CSRC_GLOBALVARIABLEDEFS=%DRIVERLIB_DIR%\globalvariabledefs.c
SET CSRC_MAIN=bootloadermain.c

SET OPTIMIZE_LEVEL=1
SET CLANG_FLAGS=-c -gdwarf-2 -target dsp -mcpu=qx320f049v2 -ffunction-sections -fdata-sections -O%OPTIMIZE_LEVEL% -std=c17 -D %CLANG_DEFINE% -D __CORE%CORE_NAME:~-1%__
SET CLANG_INCLUDE=-I%TOOLCHAIN_BASE%\include -I..\%LIBS_DIR%\device -I%DRIVERLIB_DIR% -I%DRIVERLIB_DIR%\bit_field
SET LD_LIB_PATH=-L..\%LIBS_DIR%\ldscript -Lldscript -L%TOOLCHAIN_BASE%\libv2

SET RELEASE_DIR=Release_%CORE_NAME%
SET LD_FLAGS=-T ldscript_BootLoader_%CORE_NAME%.ld -Map=%RELEASE_DIR%\%BOOTNAME%.map --no-check-sections --gc-sections -lqxboot
SET OBJ_GLOBALVARIABLEDEFS=%RELEASE_DIR%\globalvariabledefs.o
SET OBJ_MAIN=%RELEASE_DIR%\bootloadermain.o
SET OUT_EXECUTABLE=%RELEASE_DIR%\%BOOTNAME%.out

ECHO | SET /p dummyName=Building bootloader ... 
if NOT EXIST %RELEASE_DIR% (MKDIR %RELEASE_DIR%)
%CLANG_BIN% %CLANG_FLAGS% %CLANG_INCLUDE% %CSRC_GLOBALVARIABLEDEFS% -o %OBJ_GLOBALVARIABLEDEFS%
%CLANG_BIN% %CLANG_FLAGS% %CLANG_INCLUDE% %CSRC_MAIN% -o %OBJ_MAIN%
%LD_BIN% %LD_LIB_PATH% %LD_FLAGS% %OBJ_GLOBALVARIABLEDEFS% %OBJ_MAIN% -o %OUT_EXECUTABLE%
ECHO done.

cd %RELEASE_DIR%
%1\bin\gen_ram_image.exe --coretype bootloader --inputexec %BOOTNAME%.out --toolbinpath %1\bin
for /f "tokens=*" %%a in ('dir /b') do ren "%%a" "%CORE_NAME%.%%a"
cd ..

SET MERGED_RELEASE_DIR=Release
if NOT EXIST %MERGED_RELEASE_DIR% (MKDIR %MERGED_RELEASE_DIR%)
MOVE /Y %RELEASE_DIR%\* %MERGED_RELEASE_DIR% > nul
RMDIR %RELEASE_DIR%

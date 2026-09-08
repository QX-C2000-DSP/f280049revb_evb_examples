:: postbuild script for C2000 project
:: %1 - toolchain path
:: %2 - application project name
:: %3 - bootloader | core0 | core1
:: %4 - additional argument to gen_flash_image

@echo off

SET prjname=%2
SET fimgbase=%prjname:~0,-6%

%1\bin\gen_ram_image.exe --coretype %3 --inputexec %2.out --toolbinpath %1\bin

if NOT %3 == bootloader (
    cd ..\..\bootloader && .\buildbootloader.cmd %1 %3 && cd %cd%

    cd ..\..\ && %1\bin\gen_flash_image.exe %4 --dual-boot --dcsm && cd %cd%
    MOVE /Y ..\..\flash_image.hex ..\..\%fimgbase%.hex > nul
    MOVE /Y ..\..\flash_image.bin ..\..\%fimgbase%.bin > nul 2>&1
    %1\..\..\3rdparty\bin\srec_cat.exe ..\..\%fimgbase%.bin -binary -offset 0x30000000 -o ..\..\%fimgbase%.ihex -intel > nul 2>&1
    %1\..\..\3rdparty\bin\srec_cat.exe ..\..\%fimgbase%.bin -binary -crop 0x5000 0xFFFFFFFF -offset 0x30000000 -o ..\..\%fimgbase%.isp.srec -Motorola > nul 2>&1
)

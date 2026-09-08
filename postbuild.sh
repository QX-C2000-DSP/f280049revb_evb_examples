# postbuild script for C2000 project
# $1 - toolchain path
# $2 - application project name
# $3 - bootloader | core0 | core1
# $4 - additional argument to gen_flash_image

python3 $1/bin/gen_ram_image.py --coretype $3 --inputexec $2.out --toolbinpath $1/bin --linux

if [ $3 != "bootloader" ]; then
    # build bootloader if necessary
    chmod +x ../../bootloader/buildbootloader.sh
    cd ../../bootloader && ./buildbootloader.sh $1 $3 && cd - > /dev/null
    cd ../../ && python3 $1/bin/gen_flash_image.py $4 --dual-boot --dcsm && cd - > /dev/null

    fimgbase=`echo $2 | sed -e "s/_$3//g"`
    mv -f ../../flash_image.hex ../../$fimgbase.hex
    mv -f ../../flash_image.bin ../../$fimgbase.bin
fi

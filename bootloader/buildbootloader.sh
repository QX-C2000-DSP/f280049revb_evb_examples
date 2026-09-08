# $1: toolchain path

CORE_NAME=$2
CLANG_DEFINE=__boot_${CORE_NAME}__

LIBS_DIR=libs
BOOTNAME=bootloader

TOOLCHAIN_BASE=$1
CLANG_BIN=${TOOLCHAIN_BASE}/bin/clang.bin
LD_BIN=${TOOLCHAIN_BASE}/bin/lld.bin

DRIVERLIB_DIR=../${LIBS_DIR}/driverlib
CSRC_GLOBALVARIABLEDEFS=${DRIVERLIB_DIR}/globalvariabledefs.c
CSRC_MAIN=bootloadermain.c

OPTIMIZE_LEVEL=0
CLANG_FLAGS="-c -gdwarf-2 -target dsp -mcpu=qx320f049v2 -ffunction-sections -fdata-sections -O${OPTIMIZE_LEVEL} -std=c17 -D ${CLANG_DEFINE}"
CLANG_INCLUDE="-I${TOOLCHAIN_BASE}/include -I../${LIBS_DIR}/device -I${DRIVERLIB_DIR} -I${DRIVERLIB_DIR}/bit_field"
LD_LIB_PATH="-L../${LIBS_DIR}/ldscript -Lldscript -L${TOOLCHAIN_BASE}/libv2"

RELEASE_DIR=Release_${CORE_NAME}
LD_FLAGS="-T ldscript_BootLoader_${CORE_NAME}.ld -Map=${RELEASE_DIR}/${BOOTNAME}.map --no-check-sections --gc-sections -lqxboot"
OBJ_GLOBALVARIABLEDEFS=${RELEASE_DIR}/globalvariabledefs.o
OBJ_MAIN=${RELEASE_DIR}/bootloadermain.o
OUT_EXECUTABLE=${RELEASE_DIR}/${BOOTNAME}.out

echo Building bootloader ... 
[ ! -d ${RELEASE_DIR} ] && mkdir ${RELEASE_DIR}
${CLANG_BIN} ${CLANG_FLAGS} ${CLANG_INCLUDE} ${CSRC_GLOBALVARIABLEDEFS} -o ${OBJ_GLOBALVARIABLEDEFS}
${CLANG_BIN} ${CLANG_FLAGS} ${CLANG_INCLUDE} ${CSRC_MAIN} -o ${OBJ_MAIN}
${LD_BIN} ${LD_LIB_PATH} ${LD_FLAGS} ${OBJ_GLOBALVARIABLEDEFS} ${OBJ_MAIN} -o ${OUT_EXECUTABLE}
echo done.

cd ${RELEASE_DIR}
python3 $1/bin/gen_ram_image.py --coretype bootloader --inputexec ${BOOTNAME}.out --toolbinpath $1/bin --linux
for ff in *; do
  mv ${ff} ${CORE_NAME}.${ff}
done
cd - > /dev/null

MERGED_RELEASE_DIR=Release
[ ! -d ${MERGED_RELEASE_DIR} ] && mkdir ${MERGED_RELEASE_DIR}
mv ${RELEASE_DIR}/* ${MERGED_RELEASE_DIR}
rmdir ${RELEASE_DIR}

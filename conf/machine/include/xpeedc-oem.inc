# We know about rtc
include conf/machine/include/build-extras.inc

BRAND_OEM = "xpeedc"

MACHINE_NAME = "\
${@base_contains('MACHINEBUILD', 'xpeedlxcs2', 'XPEED LX CLASS S2' , '', d)}\
${@base_contains('MACHINEBUILD', 'xpeedlxcc', 'XPEED LX CLASS C' , '', d)}\
"

MACHINE_BRAND = "\
${@base_contains('MACHINEBUILD', 'xpeedlxcs2', 'GOLDEN INTERSTAR' , '', d)}\
${@base_contains('MACHINEBUILD', 'xpeedlxcc', 'GOLDEN INTERSTAR' , '', d)}\
"

IMAGEDIR ?= "\
${@base_contains('MACHINEBUILD', 'xpeedlxcs2', 'xpeedc' , '', d)}\
${@base_contains('MACHINEBUILD', 'xpeedlxcc', 'xpeedc' , '', d)}\
"

MTD_KERNEL = "\
${@base_contains('MACHINEBUILD', 'xpeedlxcs2', 'mtd1' , '', d)}\
${@base_contains('MACHINEBUILD', 'xpeedlxcc', 'mtd1' , '', d)}\
"

MTD_ROOTFS = "\
${@base_contains('MACHINEBUILD', 'xpeedlxcs2', 'mtd2' , '', d)}\
${@base_contains('MACHINEBUILD', 'xpeedlxcc', 'mtd2' , '', d)}\
"

MACHINE_DRIVER = "\
${@base_contains('MACHINEBUILD', 'xpeedlxcs2', 'xpeedc' , '', d)}\
${@base_contains('MACHINEBUILD', 'xpeedlxcc', 'xpeedc' , '', d)}\
"

KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.bin"

DVBPROVIDER = "kernel"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = "\
    xpeedc-dvb-modules-${MACHINE_DRIVER} \
    "

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = "\
    kernel-module-cdfs \
    "

MACHINE_EXTRA_RRECOMMENDS = " \
    gstreamer1.0-plugin-dvbmediasink \
    "

include conf/machine/include/autoload-filesystems.inc

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dtsdownmix"

TARGET_ARCH = "mipsel"
DEFAULTTUNE = "mips32el"

PREFERRED_PROVIDER_virtual/kernel = "linux-xpeedc"
PREFERRED_PROVIDER_virtual/blindscan-dvbc = "xpeedc-blindscan-utils"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "xpeedc-blindscan-utils"

PREFERRED_VERSION_nfs-utils ?= "1.2.8"

KERNEL_IMAGETYPE = "vmlinux"
KERNEL_OUTPUT = "${KERNEL_IMAGETYPE}"
KERNEL_CONSOLE = "ttyS0,115200n8"

IMAGE_FSTYPES ?= "ubi"

UBI_VOLNAME = "rootfs"
MKUBIFS_ARGS = "-m 2048 -e 126976 -c 4096"
UBINIZE_ARGS = "-m 2048 -p 128KiB"

IMAGE_CMD_ubi_prepend = " \
    rm -rf ${IMAGE_ROOTFS}/boot/*; \
    rm -rf ${IMAGE_ROOTFS}/tmp/*; \
    "

IMAGE_CMD_ubi_append = "; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    ${@base_contains("MACHINE_FEATURES", "bootsplash", "cp ${DEPLOY_DIR_IMAGE}/${BOOTLOGO_FILENAME} ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${BOOTLOGO_FILENAME};" , "", d)} \
    mv ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}_rootfs.rootfs.ubi ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${ROOTFS_FILE}; \
    gzip -9c ${DEPLOY_DIR_IMAGE}/vmlinux-${MACHINE}.bin > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
    echo ${DISTRO_NAME}-${DISTRO_VERSION}.${BUILD_VERSION} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
    echo "rename this file to 'force' to force an update without confirmation" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/noforce; \
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.ubi; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.ubifs; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.manifest; \
    rm -f ${DEPLOY_DIR_IMAGE}/.ubifs; \
    rm -f ${DEPLOY_DIR_IMAGE}/.manifest; \
    rm -Rf ${IMAGEDIR}; \
    "

MACHINE_FEATURES += "3dtv alsa hdmicec switchoff wifi bootsplash omb skins1080 \
    ${@base_contains('MACHINEBUILD', 'xpeedlxcc', 'dvb-c dvbc-only' , '', d)} \
    "

BOOTLOGO_FILENAME = "splash.bin"

require conf/machine/include/tune-mips32.inc

# add support for extra feeds
PACKAGE_ARCHS += " ${MACHINEBUILD}"


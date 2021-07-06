#!/bin/sh

rm *.asm
make cks6q32_fpga_defconfig
make CROSS_COMPILE=arm-linux-gnueabi- -j4
arm-linux-gnueabi-objdump -S u-boot > u-boot.asm
#arm-linux-gnueabi-objdump -S spl/u-boot-spl > u-boot-spl.asm
#make savedefconfig

if [ -f "spl/u-boot-spl.bin" ]; then
SPL_BASE=$(cat include/config/auto.conf | grep CONFIG_SPL_TEXT_BASE | awk -F '=' '{print $2}')
mkimage -A arm -O linux -T firmware -a $SPL_BASE -d spl/u-boot-spl.bin u-boot-spl.img
fi

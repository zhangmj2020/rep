#!/bin/sh
if [ -e u-boot.asm ]; then rm u-boot.asm; fi
if [ -e spl/u-boot-spl.asm ]; then rm spl/u-boot-spl.asm; fi

make CROSS_COMPILE=aarch64-linux-gnu- -j4
aarch64-linux-gnu-objdump -S u-boot > u-boot.asm
aarch64-linux-gnu-nm u-boot | sort $1 > u-boot.nm
make savedefconfig

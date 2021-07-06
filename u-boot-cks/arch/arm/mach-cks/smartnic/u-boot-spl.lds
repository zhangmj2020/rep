/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * (C) Copyright 2010
 * Texas Instruments, <www.ti.com>
 *	Aneesh V <aneesh@ti.com>
 */

MEMORY { .rom : ORIGIN = IMAGE_TEXT_BASE,
		LENGTH = IMAGE_MAX_SIZE }
MEMORY { .sram : ORIGIN = CONFIG_SPL_BSS_START_ADDR,
		LENGTH = CONFIG_SPL_BSS_MAX_SIZE }

OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
	.text : {
		. = ALIGN(8);
		*(.__image_copy_start)
		CPUDIR/start.o (.text*)
		*(.text*)
	} >.rom

	.rodata : {
		. = ALIGN(8);
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
	} >.rom

	.data : {
		. = ALIGN(8);
		*(.data*)
	} >.rom

	.u_boot_list : {
		. = ALIGN(8);
		KEEP(*(SORT(.u_boot_list*)));
	} >.rom

	.image_copy_end : {
		. = ALIGN(8);
		*(.__image_copy_end)
	} >.rom

	.end : {
		. = ALIGN(8);
		*(.__end)
	} >.rom

	_image_binary_end = .;

	.bss_start (NOLOAD) : {
		. = ALIGN(8);
		KEEP(*(.__bss_start));
	} >.sram

	.bss (NOLOAD) : {
		*(.bss*)
		 . = ALIGN(8);
	} >.sram

	.bss_end (NOLOAD) : {
		KEEP(*(.__bss_end));
	} >.sram

	/DISCARD/ : { *(.dynsym) }
	/DISCARD/ : { *(.dynstr*) }
	/DISCARD/ : { *(.dynamic*) }
	/DISCARD/ : { *(.plt*) }
	/DISCARD/ : { *(.interp*) }
	/DISCARD/ : { *(.gnu*) }
}

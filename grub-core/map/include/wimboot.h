 /*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2019  Free Software Foundation, Inc.
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef WIMBOOT_PRIVATE_DATA_H
#define WIMBOOT_PRIVATE_DATA_H

#include <grub/efi/api.h>
#include <grub/efi/efi.h>
#include <grub/misc.h>
#include <grub/disk.h>
#include <grub/file.h>

#include <maplib.h>
#include <efiapi.h>
#include <private.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <vfat.h>

#define PAGE_SIZE 4096

#define MBR_TYPE_PCAT 0x01
#define SIGNATURE_TYPE_MBR 0x01

struct grub_wimboot_component
{
  grub_file_t file;
  char *file_name;
};

struct grub_wimboot_context
{
  int nfiles;
  struct grub_wimboot_component *components;
};

struct wimboot_cmdline
{
  grub_efi_boolean_t gui;
  grub_efi_boolean_t rawbcd;
  grub_efi_boolean_t rawwim;
  unsigned int index;
  grub_efi_boolean_t pause;
  grub_efi_char16_t inject[256];
};

extern struct wimboot_cmdline wimboot_cmd;
extern struct vfat_file *bootmgfw;
extern vdisk_t wimboot_disk, wimboot_part;
/* efiboot */
void wimboot_boot (struct vfat_file *file);
/* efifile */
void
efi_read_file (struct vfat_file *vfile, void *data, size_t offset, size_t len);
void
mem_read_file (struct vfat_file *file, void *data, size_t offset, size_t len);
int
add_file (const char *name, void *data, size_t len,
    void (* read) (struct vfat_file *file, void *data, size_t offset, size_t len));
void grub_extract (struct grub_wimboot_context *wimboot_ctx);
/* efiinstall */
grub_efi_status_t wimboot_install (void);

#endif

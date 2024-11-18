/*++

Module Name:

    Public.h

Abstract:

    This file contains common definitions shared between driver and user applications.

Environment:

    Both kernel and user mode

--*/

#pragma once

#define IOCTL_KEYBOARD_GET_STATE      CTL_CODE(FILE_DEVICE_KEYBOARD, 0x800, METHOD_BUFFERED, FILE_READ_DATA)
#define IOCTL_KEYBOARD_SET_STATE      CTL_CODE(FILE_DEVICE_KEYBOARD, 0x801, METHOD_BUFFERED, FILE_WRITE_DATA)

#define IOCTL_PRINTER_PRINT_DATA      CTL_CODE(FILE_DEVICE_PRINTER, 0x800, METHOD_BUFFERED, FILE_WRITE_DATA)

#define IOCTL_STORAGE_READ_DATA       CTL_CODE(FILE_DEVICE_DISK, 0x800, METHOD_BUFFERED, FILE_READ_DATA)
#define IOCTL_STORAGE_WRITE_DATA      CTL_CODE(FILE_DEVICE_DISK, 0x801, METHOD_BUFFERED, FILE_WRITE_DATA)

#define IOCTL_DISPLAY_UPDATE_SCREEN   CTL_CODE(FILE_DEVICE_VIDEO, 0x800, METHOD_BUFFERED, FILE_WRITE_DATA)
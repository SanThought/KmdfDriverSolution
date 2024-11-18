/*++

Module Name:

    Keyboard.h

Abstract:

    This file contains the keyboard device definitions.

Environment:

    Kernel-mode Driver Framework

--*/

#pragma once

#include <ntddk.h>
#include <wdf.h>
#include "Public.h"
#include "Trace.h"

NTSTATUS
Keyboard_CreateDevice(
    _In_ WDFDRIVER Driver
);

EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL Keyboard_EvtIoDeviceControl;
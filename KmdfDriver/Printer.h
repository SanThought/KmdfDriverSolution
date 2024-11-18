/*++

Module Name:

    Printer.h

Abstract:

    This file contains the printer device definitions.

Environment:

    Kernel-mode Driver Framework

--*/

#pragma once

#include <ntddk.h>
#include <wdf.h>
#include "Public.h"
#include "Trace.h"

NTSTATUS
Printer_CreateDevice(
    _In_ WDFDRIVER Driver
);

EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL Printer_EvtIoDeviceControl;
/*++

Module Name:

    Driver.c

Abstract:

    This file contains the driver entry point and driver initialization.

Environment:

    Kernel-mode Driver Framework

--*/

#include "Driver.h"
#include "Driver.tmh" // Required for WPP tracing
#include "Keyboard.h"
#include "Printer.h"
#include "Storage.h"
#include "Display.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#endif

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    NTSTATUS            status;
    WDF_DRIVER_CONFIG   config;
    WDFDRIVER           hDriver;

    WPP_INIT_TRACING(DriverObject, RegistryPath);

    WDF_DRIVER_CONFIG_INIT(&config, WDF_NO_EVENT_CALLBACK);

    status = WdfDriverCreate(DriverObject,
        RegistryPath,
        WDF_NO_OBJECT_ATTRIBUTES,
        &config,
        &hDriver);

    if (!NT_SUCCESS(status)) {
        WPP_CLEANUP(DriverObject);
        return status;
    }

    // Create devices
    status = Keyboard_CreateDevice(hDriver);
    if (!NT_SUCCESS(status)) {
        WPP_CLEANUP(DriverObject);
        return status;
    }

    status = Printer_CreateDevice(hDriver);
    if (!NT_SUCCESS(status)) {
        WPP_CLEANUP(DriverObject);
        return status;
    }

    status = Storage_CreateDevice(hDriver);
    if (!NT_SUCCESS(status)) {
        WPP_CLEANUP(DriverObject);
        return status;
    }

    status = Display_CreateDevice(hDriver);
    if (!NT_SUCCESS(status)) {
        WPP_CLEANUP(DriverObject);
        return status;
    }

    return STATUS_SUCCESS;
}
/*++

Module Name:

    Printer.c

Abstract:

    This file contains the printer device implementation.

Environment:

    Kernel-mode Driver Framework

--*/

#include "Printer.h"
#include "Printer.tmh" // Required for WPP tracing

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, Printer_CreateDevice)
#endif

NTSTATUS
Printer_CreateDevice(
    _In_ WDFDRIVER Driver
)
{
    NTSTATUS                status;
    PWDFDEVICE_INIT         pDeviceInit = NULL;
    WDFDEVICE               device;
    WDF_IO_QUEUE_CONFIG     ioQueueConfig;
    WDF_OBJECT_ATTRIBUTES   attributes;
    UNICODE_STRING          deviceName;
    UNICODE_STRING          symbolicLinkName;

    PAGED_CODE();

    // Initialize the Security Descriptor
    UNICODE_STRING sddl = RTL_CONSTANT_STRING(L"D:(A;;GA;;;SY)(A;;GA;;;BA)");

    // Use the address of the SDDL variable
    pDeviceInit = WdfControlDeviceInitAllocate(Driver, &sddl);
    if (pDeviceInit == NULL) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    WdfDeviceInitSetDeviceType(pDeviceInit, FILE_DEVICE_PRINTER);

    // Set device name and symbolic link with UPTC branding
    RtlInitUnicodeString(&deviceName, L"\\Device\\UPTCPrinter");
    RtlInitUnicodeString(&symbolicLinkName, L"\\DosDevices\\UPTCPrinter");

    status = WdfDeviceInitAssignName(pDeviceInit, &deviceName);
    if (!NT_SUCCESS(status)) {
        WdfDeviceInitFree(pDeviceInit);
        return status;
    }

    WDF_OBJECT_ATTRIBUTES_INIT(&attributes);

    status = WdfDeviceCreate(&pDeviceInit,
        &attributes,
        &device);
    if (!NT_SUCCESS(status)) {
        return status;
    }

    status = WdfDeviceCreateSymbolicLink(device, &symbolicLinkName);
    if (!NT_SUCCESS(status)) {
        WdfObjectDelete(device);
        return status;
    }

    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&ioQueueConfig,
        WdfIoQueueDispatchSequential);

    ioQueueConfig.EvtIoDeviceControl = Printer_EvtIoDeviceControl;

    status = WdfIoQueueCreate(device,
        &ioQueueConfig,
        WDF_NO_OBJECT_ATTRIBUTES,
        NULL);
    if (!NT_SUCCESS(status)) {
        WdfObjectDelete(device);
        return status;
    }

    WdfControlFinishInitializing(device);

    return status;
}

VOID
Printer_EvtIoDeviceControl(
    _In_ WDFQUEUE      Queue,
    _In_ WDFREQUEST    Request,
    _In_ size_t        OutputBufferLength,
    _In_ size_t        InputBufferLength,
    _In_ ULONG         IoControlCode
)
{
    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(OutputBufferLength);
    UNREFERENCED_PARAMETER(InputBufferLength); // Suppress unused parameter warning

    NTSTATUS status = STATUS_SUCCESS;

    switch (IoControlCode) {
    case IOCTL_PRINTER_PRINT_DATA:
        // Handle printer print data
        TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "IOCTL_PRINTER_PRINT_DATA");
        break;
    default:
        status = STATUS_INVALID_DEVICE_REQUEST;
        break;
    }

    WdfRequestComplete(Request, status);
}
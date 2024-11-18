/*++

Module Name:

    Display.c

Abstract:

    This file contains the display device implementation.

Environment:

    Kernel-mode Driver Framework

--*/

#include "Display.h"
#include "Display.tmh" // Required for WPP tracing

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, Display_CreateDevice)
#endif

NTSTATUS
Display_CreateDevice(
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

    WdfDeviceInitSetDeviceType(pDeviceInit, FILE_DEVICE_VIDEO);

    // Set device name and symbolic link with UPTC branding
    RtlInitUnicodeString(&deviceName, L"\\Device\\UPTCDisplay");
    RtlInitUnicodeString(&symbolicLinkName, L"\\DosDevices\\UPTCDisplay");

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

    ioQueueConfig.EvtIoDeviceControl = Display_EvtIoDeviceControl;

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
Display_EvtIoDeviceControl(
    _In_ WDFQUEUE      Queue,
    _In_ WDFREQUEST    Request,
    _In_ size_t        OutputBufferLength,
    _In_ size_t        InputBufferLength,
    _In_ ULONG         IoControlCode
)
{
    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(OutputBufferLength); // Suppress unused parameter warning
    UNREFERENCED_PARAMETER(InputBufferLength);  // Suppress unused parameter warning

    NTSTATUS status = STATUS_SUCCESS;
    PVOID buffer;
    size_t bufferLength;

    switch (IoControlCode) {
    case IOCTL_DISPLAY_UPDATE_SCREEN:
        // Handle display update screen
        TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "IOCTL_DISPLAY_UPDATE_SCREEN");
        status = WdfRequestRetrieveInputBuffer(Request, sizeof(buffer), &buffer, &bufferLength);
        if (NT_SUCCESS(status)) {
            // Simulate updating screen
        }
        break;
    default:
        status = STATUS_INVALID_DEVICE_REQUEST;
        break;
    }

    WdfRequestComplete(Request, status);
}
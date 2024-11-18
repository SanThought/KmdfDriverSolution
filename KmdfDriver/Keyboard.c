/*++

Module Name:

    Keyboard.c

Abstract:

    This file contains the keyboard device implementation.

Environment:

    Kernel-mode Driver Framework

--*/

#include "Keyboard.h"
#include "Keyboard.tmh" // Required for WPP tracing

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, Keyboard_CreateDevice)
#endif

NTSTATUS
Keyboard_CreateDevice(
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
    UNICODE_STRING          sddl = RTL_CONSTANT_STRING(L"D:(A;;GA;;;SY)(A;;GA;;;BA)"); // Initialize SDDL variable directly

    PAGED_CODE();

    // Use the address of the SDDL variable
    pDeviceInit = WdfControlDeviceInitAllocate(Driver, &sddl);
    if (pDeviceInit == NULL) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    WdfDeviceInitSetDeviceType(pDeviceInit, FILE_DEVICE_KEYBOARD);

    // Set device name and symbolic link with UPTC branding
    RtlInitUnicodeString(&deviceName, L"\\Device\\UPTCKeyboard");
    RtlInitUnicodeString(&symbolicLinkName, L"\\DosDevices\\UPTCKeyboard");

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

    ioQueueConfig.EvtIoDeviceControl = Keyboard_EvtIoDeviceControl;

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
Keyboard_EvtIoDeviceControl(
    _In_ WDFQUEUE      Queue,
    _In_ WDFREQUEST    Request,
    _In_ size_t        OutputBufferLength,
    _In_ size_t        InputBufferLength,
    _In_ ULONG         IoControlCode
)
{
    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(OutputBufferLength);
    UNREFERENCED_PARAMETER(InputBufferLength);

    NTSTATUS status = STATUS_SUCCESS;

    switch (IoControlCode) {
    case IOCTL_KEYBOARD_GET_STATE:
        TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "IOCTL_KEYBOARD_GET_STATE");
        break;
    case IOCTL_KEYBOARD_SET_STATE:
        TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "IOCTL_KEYBOARD_SET_STATE");
        break;
    default:
        status = STATUS_INVALID_DEVICE_REQUEST;
        break;
    }

    WdfRequestComplete(Request, status);
}
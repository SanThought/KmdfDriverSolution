/*++

Module Name:

    Driver.h

Abstract:

    This file contains the driver definitions.

Environment:

    Kernel-mode Driver Framework

--*/

#pragma once

#include <ntddk.h>
#include <wdf.h>
#include "Trace.h"

// Function prototypes
DRIVER_INITIALIZE DriverEntry;
/*++

Module Name:

    Trace.h

Abstract:

    Header file for tracing definitions.

Environment:

    Kernel-mode Driver Framework

--*/

#pragma once

#include <evntrace.h> // For TRACE_LEVEL definitions

//
// Define the tracing flags.
//
#define WPP_CONTROL_GUIDS                                              \
    WPP_DEFINE_CONTROL_GUID(                                           \
        UPTCDriverTraceGuid, (B1A2B3C4,D5E6,47F8,ABCD,EF0123456789),   \
        WPP_DEFINE_BIT(TRACE_DRIVER)                                    \
        )

#define WPP_FLAG_LEVEL_LOGGER(flag, level)                             \
    WPP_LEVEL_LOGGER(flag)

#define WPP_FLAG_LEVEL_ENABLED(flag, level)                            \
    (WPP_LEVEL_ENABLED(flag) && WPP_CONTROL(WPP_BIT_ ## flag).Level >= level)

//
// This comment block is scanned by the trace preprocessor to define our
// Trace function.
//

// begin_wpp config
// FUNC TraceEvents(LEVEL, FLAGS, MSG, ...);
// end_wpp
//
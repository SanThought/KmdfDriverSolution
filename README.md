# UPTC Device Manager KMDF Driver Solution

## Overview

This project contains a Kernel-Mode Driver Framework (KMDF) solution for the UPTC Device Manager. It provides basic driver implementations for the following devices:
- **Keyboard**
- **Printer**
- **Storage**
- **Display**

Each driver is designed for modularity and simplicity, enabling integration with other OS components developed by the Operating Systems class at UPTC.

---

## Solution Structure

The solution consists of the following components:

### Directories and Files
- **`Driver.c`**: Contains the entry point for the driver and initialization logic.
- **`Keyboard.c` / `Keyboard.h`**: Implementation and definitions for the keyboard driver.
- **`Printer.c` / `Printer.h`**: Implementation and definitions for the printer driver.
- **`Storage.c` / `Storage.h`**: Implementation and definitions for the storage driver.
- **`Display.c` / `Display.h`**: Implementation and definitions for the display driver.
- **`Trace.h`**: WPP tracing definitions for logging and diagnostics.
- **`Public.h`**: Shared definitions between drivers and user applications.
- **`.inf` file**: Installation file for setting up the driver.
- **`.cat` file**: Catalog file for driver signing (to be generated).

---

## Installation

### Prerequisites
1. **Test Signing Mode**:
   - Open an elevated Command Prompt.
   - Run: `bcdedit /set testsigning on`.
   - Reboot the system.
2. **KMDF Environment**:
   - Install Windows Driver Kit (WDK) and ensure Visual Studio is configured for driver development.

### Steps
1. **Build the Driver**:
   - Open the solution in Visual Studio.
   - Select `x64` (or `x86` for 32-bit systems) as the target platform.
   - Build the solution.

2. **Copy Files**:
   - Copy `KmdfDriver.sys` and the `.inf` file to a folder on your test machine.

3. **Install the Driver**:
   - Open Device Manager.
   - Right-click on the device you want to install and choose `Update Driver`.
   - Select `Browse my computer for drivers` and point to the folder containing the `.inf` file.

4. **Verify Installation**:
   - Check Device Manager for the installed device under the **System** category.

---

## Testing the Drivers

### Testing Environment
- A physical test machine or a virtual machine with **Test Signing Mode** enabled.

### Tools
- **TraceView**: Use TraceView or DebugView to monitor WPP tracing logs.
- **Test Applications**: Use custom or generic test applications to send I/O requests (IRPs) to the drivers.

---

## Troubleshooting

### Common Issues
1. **Driver Installation Fails**:
   - Ensure `Test Signing Mode` is enabled.
   - Check the `.inf` file for errors.
2. **Driver Doesn't Load**:
   - Use Event Viewer to check for driver-related errors.
   - Ensure all dependencies are correctly included.

### Debugging
- Use **WinDbg** with a kernel debugging setup to step through driver code.
- Enable WPP tracing to capture detailed logs for troubleshooting.

---

## Customization

### Branding
The driver and devices are branded with "UPTC" in their names and symbolic links. Update the `.inf` file and source code if further customization is required.

### Modularity
Each device driver is implemented in a separate module, making it easy to extend or modify individual components without affecting the entire solution.

---

## Known Limitations

- This is a minimal viable product (MVP) designed for educational purposes.
- Advanced features, such as power management and PnP handling, are not implemented.

---

## Licensing

This project is developed as part of the UPTC Operating Systems class and is intended for educational use only.

---

## Contact

For questions or issues, contact the Repository owner (SanThought) or any UPTC Operating Systems Development Team member (collaborators).

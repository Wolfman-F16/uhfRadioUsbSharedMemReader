# uhfRadioUsbSharedMemReader
command line utility to interface Falcon 4.0 BMS 4.35 with UHF Radio

compiled on Windows 7 32bit with gcc

g++ (i686-posix-dwarf-rev1, Built by MinGW-W64 project) 4.9.2

Check `/bin` for pre-compiled executable.

# Installation

A libusb filter driver must be installed to enable interfacing with the UHF Radio firmware.

The software to do so is available at `http://sourceforge.net/projects/libusb-win32/`

Type `install-filter install -device=USBVid_16c0.Pid_27db.Rev_0100` on the commandline. Or use the `install-filter-gui.exe` to do the same.

**Note:**

Please follow the installation instructions provided in `libusb-win32-bin-README.txt`.
Most users will have a x64 architecture, so 
  - `x86\libusb0_x86.dll`: Must be renamed to `libusb0.dll`! and copied to `C:\Windows\syswow64\libusb0.dll.`
  - `amd64\libusb0.sys`: Must be copied to `C:\Windows\system32\drivers\libusb0.sys`
  - `amd64\libusb0.dll`: Must be copied to `C:\Windows\system32\libusb0.dll`

You can check on successfull installation with the libusb tool `testlibusb-win.exe`. It should display a long list of information about the USB device (device has to be connected of course).

# Details

`uhfRadio.exe` interfaces Falcon BMS shared memory with the UHF Radio via USB. The executable accepts one (optional) parameter.

`uhfRadio [<path and filename of pilot ini file>]`

Using the parameter, the pilots ini file residing in `<falcon bms path>/User/Config/` is parsed for UHF preset frequencies, which are loaded onto the UHF Radio after starting the executable (UHF Radio must be connected of course for this to work).
Only a successful parsing leads to the following written on the command line (example):
> found at UHF PRESET 1 Frequency 297500

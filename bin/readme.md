The following dlls are required to run uhfRadio.exe:

(included in dll.zip)

from gcc

0. libgcc_s_dw2-1.dll 
0. libstdc++-6.dll 
0. libwinpthread-1.dll

from libusb-win32 (http://sourceforge.net/projects/libusb-win32/)

0. libusb.dll

To be able to interface with the UHF Radio, a filter driver must be installed.
choose the appropriate architecture (`/amd64` for 64bit windows versions) and run the following command (or use the install-filter-win GUI)
`
install-filter install --device=USBVid_16c0.Pid_27db.Rev_0100`

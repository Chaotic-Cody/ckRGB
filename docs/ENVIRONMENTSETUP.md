# Setting up your ckRGB development environment 

## Linux/WSL

### Fork the [ckRGB repository](https://github.com/Chaotic-Cody/ckRGB) from GitHub.

Make sure to place it in an easy to access directory. I suggest using a neat cloud storage option that integrates with your file explorer, such as Microsoft OneDrive or Google Drive. I personally use the former.

### Install mingw 

sudo apt-get install mingw-w64

### Cross compile the application using mingw to build a Windows executable

Linux: 
gcc libusbtestsuite.c -o test.exe -lusb-1.0

Linux -> Windows Cross Compilation: 

Without pkg-config installed:

64-bit
x86_64-w64-mingw32-gcc -I./dependencies/libusb-1.0.22/include -o testusb.exe libusbtestsuite.c -L./dependencies/libusb-1.0.22/MinGW64/static -lusb-1.0 -D WINDOWS

32-bit
i686-w64-mingw32-gcc -I./dependencies/libusb-1.0.22/include -o testusb32.exe libusbtestsuite.c -L./dependencies/libusb-1.0.22/MinGW32/static -lusb-1.0 -D WINDOWS

With pkg-config installed:

64-bit
x86_64-w64-mingw32-gcc -I./dependencies/libusb-1.0.22/include -o testusb.exe libusbtestsuite.c -L./dependencies/libusb-1.0.22/MinGW64/static `pkg-config --libs libusb-1.0` -D WINDOWS

32-bit
i686-w64-mingw32-gcc -I./dependencies/libusb-1.0.22/include -o testusb32.exe libusbtestsuite.c -L./dependencies/libusb-1.0.22/MinGW32/static `pkg-config --libs libusb-1.0` -D WINDOWS




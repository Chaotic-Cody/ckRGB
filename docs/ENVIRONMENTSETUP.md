# Setting up your ckRGB development environment 

## Linux/WSL

### Fork the [ckRGB repository](https://github.com/Chaotic-Cody/ckRGB) from GitHub.

Make sure to place it in an easy to access directory. I suggest using a neat cloud storage option that integrates with your file explorer, such as Microsoft OneDrive or Google Drive. I personally use the former.

### Install mingw 

sudo apt-get install mingw-w64

### Install make

sudo apt-get install make

### Cross compile the application using mingw to build a Windows executable

Linux: 

gcc libusbtestsuite.c -o test.exe -lusb-1.0

Linux -> Windows Cross Compilation: 

1. cd into ckRGB directory
2. Run 'make main'

# In Progress Instructions

Statically link jsmn with -ljsmn
Compile jsmn example: 
gcc -I../ simple.c -L../ -ljsmn
gcc -I../ jsondump.c -L../ -ljsmn -o jsondump.out

x86_64-w64-mingw32-gcc -I./dependencies/libusb-1.0.22/include -o testusb.exe libusbtestsuite.c -L./dependencies/libusb-1.0.22/MinGW64/static -lusb-1.0 -D WINDOWS
# Setting up your ckRGB development environment 

## Linux/WSL

### Fork the [ckRGB repository](https://github.com/Chaotic-Cody/ckRGB) from GitHub.

Make sure to place it in an easy to access directory. I suggest using a neat cloud storage option that integrates with your file explorer, such as Microsoft OneDrive or Google Drive. I personally use the former.

### Install mingw 

sudo apt-get install mingw-w64

### Install make

sudo apt-get install make

### Cross compile the application using mingw to build a Windows executable

Linux -> Windows Cross Compilation: 

1. cd into ckRGB/src
2. Run 'make main'

This will cross-compile the program with libusb1.0, Lua5.2, and Jsmn as statically linked libraries into a Windows executable using minGW.

### Running the application

TODO: Get ckRGB application functionality implemented.
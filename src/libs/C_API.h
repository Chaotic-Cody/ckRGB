#include <stdio.h>
#include <string.h>
#include "libusb-1.0/libusb.h"
//#include "libusb.h"
#ifdef WINDOWS
#include <windows.h>
#endif
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

void pushKey(char* scriptName);
void pushKeys(char* scriptName);
void pushAll(char* scriptName);
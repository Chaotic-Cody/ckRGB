#include <stdio.h>
#include <string.h>
#include "hidapi.h"
#ifdef WINDOWS
#include <windows.h>
#endif
/*
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
*/

#define MAX_STR 255

int main(int argc, char **argv) {

	int r;
	hid_device *handle;
	wchar_t wstr[MAX_STR];

	// Device info variables
	// Information for these will be loaded from a JSON file using jsmn, but are hardcoded for now (very easy to swap out)
	char keyboard_name[100] = "Corsair K95 RGB Platinum"; 
	wint_t productID = 0x1B2D;
	wint_t vendorID = 0x1B1C;

	// init hidapi library
	r = hid_init();

	// open device 
	handle = hid_open(vendorID, productID, NULL);

	// print out manufacturer string for testing
	r = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	printf("Manufacturer: %s\n", wstr);

	// close device
	hid_close(handle);

	// finalize hidapi
	r = hid_exit();

	return 0;
}
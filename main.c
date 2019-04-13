#include <stdio.h>
#include <string.h>
#include "libusb-1.0/libusb.h"
//#include "libusb.h"
#ifdef WINDOWS
#include <windows.h>
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define snprintf _snprintf
#endif

libusb_device *get_device(libusb_device **devs, uint16_t productID, uint16_t vendorID) {

	struct libusb_device_descriptor desc;
	int ret;

	for (int i = 0; devs[i]; i++) {
		
		ret = libusb_get_device_descriptor(devs[i], &desc);
		if (ret < 0) {
			fprintf(stderr, "failed to get device descriptor");
			return EXIT_FAILURE;
		}

		printf("%04X - %04X\n", desc.idVendor, desc.idProduct);

		if (desc.idVendor == vendorID && desc.idProduct == productID) {
			return devs[i];
		}

	}

	return NULL;

}

int main (int argc, char **argv) {

	libusb_device **devs;
	ssize_t cnt;
	int r, i;

	// Device info variables
	// Information for these will be loaded from a JSON file using jsmn, but are hardcoded for now (very easy to swap out)
	char keyboard_name[100] = "Corsair K95 RGB Platinum"; 
	uint16_t productID = 0x1B2D;
	uint16_t vendorID = 0x1B1C;

	// Device we'll br working with
	libusb_device *dev;

	// Initialize libusb library and get an array of connected devices
	r = libusb_init(NULL);
	if (r < 0) {
		return r;
	}

	cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0) {
		return (int)cnt;
	}

	dev = get_device(devs, productID, vendorID);

	// Print whether or not we found a connected device
	printf((dev != NULL) ? "Device found :)\n" : "Device not found :(\n");

	libusb_free_device_list(devs, 1);
	libusb_exit(NULL);

	return EXIT_SUCCESS;

}
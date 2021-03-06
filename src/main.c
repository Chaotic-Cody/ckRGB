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

libusb_device *get_device(libusb_device **devs, uint16_t productID, uint16_t vendorID) {

	struct libusb_device_descriptor desc;
	int ret;

	for (int i = 0; devs[i]; i++) {
		
		ret = libusb_get_device_descriptor(devs[i], &desc);
		if (ret < 0) {
			fprintf(stderr, "failed to get device descriptor");
			exit(EXIT_FAILURE);
		}

		#ifdef DEBUG
		printf("%04X - %04X\n", desc.idVendor, desc.idProduct);
		#endif

		if (desc.idVendor == vendorID && desc.idProduct == productID) {

			#ifdef DEBUG
			uint8_t address = libusb_get_device_address(devs[i]);
			printf("Keyboard address: %d\n", address);
			#endif

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

	// Device we'll be working with
	libusb_device *dev;
	libusb_device_handle *dev_handle;

	// Initialize libusb library and get an array of connected devices
	r = libusb_init(NULL);
	if (r < 0) {
		fprintf(stderr, "failed to initialize libusb");
		exit(EXIT_FAILURE);
	}

	cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0) {
		fprintf(stderr, "no connected devices");
		exit(EXIT_FAILURE);
	}

	dev = get_device(devs, productID, vendorID);

	// Print whether or not we found a connected device
	printf((dev != NULL) ? "Device found :)\n" : "Device not found :(\n");

	if (dev == NULL) {
		fprintf(stderr, "Corsair K95 RGB Platinum not found");
		exit(EXIT_FAILURE);
	}

	// Open the device
	r = libusb_open(dev, &dev_handle);
	if (r != 0) {
		fprintf(stderr, "%s: failed to connect to device", libusb_strerror(r));
		exit(EXIT_FAILURE);
	}

	// Now we have a handle and can perform IO on the device
	r = libusb_claim_interface(dev_handle, 0); // unsure which interface we should be claiming, but only 0 and 1 don't error
	//r = libusb_detach_kernel_driver(dev_handle, 3);
	if (r != 0) {
		fprintf(stderr, "%s: failed to claim interface", libusb_strerror(r));
		exit(EXIT_FAILURE);
	}



	libusb_release_interface(dev_handle, 3);
	libusb_close(dev_handle);
	libusb_free_device_list(devs, 1);
	libusb_exit(NULL);

	return EXIT_SUCCESS;

}
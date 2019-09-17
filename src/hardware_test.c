#include <stdio.h>
#include <string.h>
#include "libusb-1.0/libusb.h"
//#include "libusb.h"
#ifdef WINDOWS
#include <windows.h>
#endif

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
	productID = 0x1B2D;
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
	r = libusb_claim_interface(dev_handle, 1); // unsure which interface we should be claiming, but only 0 and 1 don't error
	//r = libusb_detach_kernel_driver(dev_handle, 0);
	if (r != 0) {
		fprintf(stderr, "%s: failed to claim interface", libusb_strerror(r));
		exit(EXIT_FAILURE);
	} else {
/*
		unsigned char data_pkt[5][64] = {0};

		data_pkt[0][0] = 0x7F;
		data_pkt[0][1] = 0x01;
		data_pkt[0][2] = 0x3C;

		data_pkt[1][0] = 0x7F;
		data_pkt[1][1] = 0x02;
		data_pkt[1][2] = 0x3C;

		data_pkt[2][0] = 0x7F;
		data_pkt[2][1] = 0x03;
		data_pkt[2][2] = 0x3C;

		data_pkt[3][0] = 0x7F;
		data_pkt[3][1] = 0x04;
		data_pkt[3][2] = 0x24;

		data_pkt[4][0] = 0x07;
		data_pkt[4][1] = 0x27;
		data_pkt[4][4] = 0xD8;

		for(int i = 0; i < 60; i++) {
			data_pkt[0][i+4] = 1 << 4;
		}

		for(int i = 0; i < 12; i++) {
			data_pkt[1][i+4] = 1 << 4;
		}

		for(int i = 0; i < 48; i++) {
			data_pkt[1][i+16] = 1 << 4;
		}

		for(int i = 0; i < 24; i++) {
			data_pkt[2][i+4] = 1 << 4;
		}

		for(int i = 0; i < 36; i++) {
			data_pkt[2][i+28] = 1 << 4;
		}

		for(int i = 0; i < 36; i++) {
			data_pkt[3][i+4] = 1 << 4;
		}

		int transferred = 0;

		printf("%d\n", libusb_bulk_transfer(dev_handle, 0x82, data_pkt[0], 64, &transferred, 1000));
		printf("%d\n", transferred);
		printf("%d\n", libusb_bulk_transfer(dev_handle, 0x82, data_pkt[1], 64, &transferred, 1000));
		printf("%d\n", transferred);
		printf("%d\n", libusb_bulk_transfer(dev_handle, 0x82, data_pkt[2], 64, &transferred, 1000));
		printf("%d\n", transferred);
		printf("%d\n", libusb_bulk_transfer(dev_handle, 0x82, data_pkt[3], 64, &transferred, 1000));
		printf("%d\n", transferred);
		printf("%d\n", libusb_bulk_transfer(dev_handle, 0x82, data_pkt[4], 64, &transferred, 1000));
		printf("%d\n", transferred);

*/

		static char data_pkt_0[] =
		  { 0x07,   0x27,   0x00,   0x00,   0xD8,   0x00,   0x00,   0x00,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00 };
		 
		static char wht_pkt_1[] =
		  { 0x7F,   0x01,   0x3C,   0x00,   0x00,   0x00,   0x00,   0x00,
			0x07,   0x77,   0x00,   0x00,   0x07,   0x70,   0x00,   0x77,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x77,   0x00,   0x00,
			0x70,   0x00,   0x70,   0x77,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x77,   0x00,   0x00,   0x70,   0x00,   0x00,   0x77,
			0x00,   0x00,   0x70,   0x00,   0x00,   0x77,   0x00,   0x00,
			0x00,   0x00,   0x00,   0x77,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x77,   0x00,   0x00,   0x00,   0x07,   0x00,   0x77 };
		 
		static char wht_pkt_2[] =
		  { 0x7F,   0x02,   0x3C,   0x00,   0x00,   0x00,   0x70,   0x00,
			0x00,   0x77,   0x00,   0x00,   0x00,   0x07,   0x00,   0x77,
			0x00,   0x00,   0x00,   0x00,   0x07,   0x77,   0x00,   0x00,
			0x07,   0x70,   0x00,   0x77,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x77,   0x00,   0x00,   0x70,   0x00,   0x70,   0x77,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x77,   0x00,   0x00,
			0x70,   0x00,   0x00,   0x77,   0x00,   0x00,   0x70,   0x00,
			0x00,   0x77,   0x00,   0x00,   0x00,   0x00,   0x00,   0x77 };
		 
		static char wht_pkt_3[] =
		  { 0x7F,   0x03,   0x3C,   0x00,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x77,   0x00,   0x00,   0x00,   0x07,   0x00,   0x77,
			0x00,   0x00,   0x70,   0x00,   0x00,   0x77,   0x00,   0x00,
			0x00,   0x07,   0x00,   0x77,   0x00,   0x00,   0x00,   0x00,
			0x07,   0x77,   0x00,   0x00,   0x07,   0x70,   0x00,   0x77,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x77,   0x00,   0x00,
			0x70,   0x00,   0x70,   0x77,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x77,   0x00,   0x00,   0x70,   0x00,   0x00,   0x77 };
		 
		static char wht_pkt_4[] =
		  { 0x7F,   0x04,   0x24,   0x00,   0x00,   0x00,   0x70,   0x00,
			0x00,   0x77,   0x00,   0x00,   0x00,   0x00,   0x00,   0x77,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x77,   0x00,   0x00,
			0x00,   0x07,   0x00,   0x77,   0x00,   0x00,   0x70,   0x00,
			0x00,   0x77,   0x00,   0x00,   0x00,   0x07,   0x00,   0x77,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,
			0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00 };

		while (1) {

			int bytes_written = 0;
			
			bytes_written = libusb_control_transfer(dev_handle, 0x21, 0x09, 0x0300, 0x03, data_pkt_0, 64, 1000);
			printf("%d\n", bytes_written);

			bytes_written = libusb_control_transfer(dev_handle, 0x21, 0x09, 0x0300, 0x03, wht_pkt_1, 64, 1000);
			printf("%d\n", bytes_written);
			bytes_written = libusb_control_transfer(dev_handle, 0x21, 0x09, 0x0300, 0x03, wht_pkt_2, 64, 1000);
			printf("%d\n", bytes_written);
			bytes_written = libusb_control_transfer(dev_handle, 0x21, 0x09, 0x0300, 0x03, wht_pkt_3, 64, 1000);
			printf("%d\n", bytes_written);
			bytes_written = libusb_control_transfer(dev_handle, 0x21, 0x09, 0x0300, 0x03, wht_pkt_4, 64, 1000);
			printf("%d\n", bytes_written);
			
			Sleep(1);

		}

		//printf("%s\n", libusb_strerror(bytes_written));

	}



	libusb_release_interface(dev_handle, 1);
	libusb_close(dev_handle);
	libusb_free_device_list(devs, 1);
	libusb_exit(NULL);

	return EXIT_SUCCESS;

}
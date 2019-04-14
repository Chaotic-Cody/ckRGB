# build an executable named main.exe from main.c with statically linked libraries
main: main.c
	x86_64-w64-mingw32-gcc -I./dependencies/libusb-1.0.22/include -I./dependencies/jsmn -o main.exe main.c -L./dependencies/libusb-1.0.22/MinGW64/static -L./dependencies/jsmn -lusb-1.0 -ljsmn -D WINDOWS

debug: main.c
	x86_64-w64-mingw32-gcc -I./dependencies/libusb-1.0.22/include -I./dependencies/jsmn -o main.exe main.c -L./dependencies/libusb-1.0.22/MinGW64/static -L./dependencies/jsmn -lusb-1.0 -ljsmn -D WINDOWS -D DEBUG

clean: 
	$(RM) main.exe

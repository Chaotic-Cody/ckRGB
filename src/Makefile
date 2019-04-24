# build an executable named main.exe from main.c with statically linked libraries

main: main.c
	x86_64-w64-mingw32-gcc -I./dependencies/libusb-1.0.22/include -I./dependencies/jsmn -I./dependencies/lua-5.2.4/install/include/ -o main.exe main.c -L./dependencies/libusb-1.0.22/MinGW64/static -L./dependencies/jsmn -L./dependencies/lua-5.2.4/install/lib -lusb-1.0 -ljsmn -llua -D WINDOWS

debug: main.c
	x86_64-w64-mingw32-gcc -I./dependencies/libusb-1.0.22/include -I./dependencies/jsmn -I./dependencies/lua-5.2.4/install/include/ -o main.exe main.c -L./dependencies/libusb-1.0.22/MinGW64/static -L./dependencies/jsmn -L./dependencies/lua-5.2.4/install/lib -lusb-1.0 -ljsmn -llua -D WINDOWS -D DEBUG

test: hardware_test.c
	x86_64-w64-mingw32-gcc -I./dependencies/libusb-1.0.22/include -I./dependencies/jsmn -I./dependencies/lua-5.2.4/install/include/ -o hardware_test.exe hardware_test.c -L./dependencies/libusb-1.0.22/MinGW64/static -L./dependencies/jsmn -L./dependencies/lua-5.2.4/install/lib -lusb-1.0 -ljsmn -llua -D WINDOWS -D DEBUG

clean: 
	$(RM) main.exe
	$(RM) test.exe

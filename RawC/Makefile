main: main.c
	gcc entry.c -o Raw --entry=main -ffreestanding -nostartfiles  -nodefaultlibs  -nolibc  -nostdlib -static
	mv Raw ../bin/
	ls -alh ../bin/Raw
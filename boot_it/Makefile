all:
	nasm -f win64 efi_main.s -o main.obj
	ld -nostdlib -znocombreloc -Ttext=0 -entry efi_main -o BOOTX64.efi main.obj
~
#! /bin/bash
all:
	echo 'Now assembling, compiling, and linking the kernel:'
	nasm -f aout -o multiboot_header.o multiboot_header.asm 
	# rem Remember this spot here: We will add 'gcc' commands here to compile C sources
	gcc -ffreestanding -O2 -nostdlib -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./Include -c -o initialize.o initialize.c
	
	# rem This links all your files. Remember that as you add *.o files, you need to
	# rem add them after start.o. If you don't add them at all, they won't be in your kernel!
	ld -T link.ld -o kernel.bin multiboot_header.o initialize.o
	echo 'Done!'

clean:
	mv *.o ./output
	mv *.bin ./output
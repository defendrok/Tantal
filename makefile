OFiles = multiboot_header.o Initialize.o Screen.o
GCCFlags = -ffreestanding -O2 -nostdlib -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./Include -c -o

all:
	nasm -f aout -o multiboot_header.o multiboot_header.asm 
## Kernel part 
	gcc $(GCCFlags) Initialize.o Initialize.c
	gcc $(GCCFlags) Screen.o Screen.c
	
## Linking all together
	ld -T link.ld -o Kernel.bin $(OFiles)
	
## Cleaning kernel
	objcopy -S -R .eh_frame -O binary Kernel.bin
	
	make clean
clean:
	mv *.o ./output
	mv *.bin ./output
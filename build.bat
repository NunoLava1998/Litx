@echo off

i686-elf-as boot.S -o boot.o
pause
i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wpedantic -Wshadow -s
pause
i686-elf-gcc -c stdio/stdio.c -o stdio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wpedantic -Wshadow -s
pause
i686-elf-gcc -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib boot.o kernel.o stdio.o -lgcc -s

pause

qemu-system-i386 -kernel os.bin -d int

pause
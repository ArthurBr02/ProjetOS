nasm -f elf32 loader.s
ld -T link.ld -melf_i386 loader.o -o kernel.elf
cp kernel.elf iso/boot/kernel.elf
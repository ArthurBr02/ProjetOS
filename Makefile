OBJECTS = build/loader.o build/kmain.o build/io.o build/iolib.o build/strlib.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: build/kernel.elf

build/kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o build/kernel.elf

build/os.iso: build/kernel.elf
	cp build/kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o build/os.iso                 \
				iso

run: build/os.iso
	./start_qemu.sh

build/%.o: src/%.c
	$(CC) $(CFLAGS)  $< -o $@

build/%.o: src/%.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf build/*.o build/kernel.elf build/os.iso
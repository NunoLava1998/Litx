.section .multiboot
.align 4
.long 0x1BADB002 					# MAGIC
.long (1<<0 | 1<<1) 				# FLAGS
.long -(0x1BADB002 + (1<<0 | 1<<1))	# CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _boot
.type _boot, @function
_boot:

	# Our ELF bootloader has loaded us into _boot.
	# We are in 32 bit mode. Interrupts are disabled.
	# We're running in little-endian and we're booting
	# this from a x86 processor in 32bit or 64bit mode.
	# The state of the CPU is defined as in the multiboot
	# standard. We have complete control of the CPU.
	
	# Let's set up a stack. Many languages, including C
	# and C++ will need a stack.
	
	mov $stack_top, %esp
	
	# Let's for now enter our high-level kernel.
	
	call kmain
	
	# In case our kmain exits for whatever reason,
	# we'll make a loop for it to not execute garbage.
	
	cli
1:
	hlt
	jmp 1 # In case somehow the systems stops halting...
	
# Set the size of the _boot symbol.
.size _boot, . - _boot
	
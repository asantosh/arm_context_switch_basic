ENTRY(vectors_start)
SECTIONS
{
 . = 0x10000;
 .text : {
 start.o
 *(.text .rodata)
 }
 .data : { *(.data) }
 .bss : { *(.bss) }
 . = ALIGN(8);
 . = . + 0x2000;
 svc_stack = .;
 . = . + 0x2000;
 irq_stack = .;
}
 














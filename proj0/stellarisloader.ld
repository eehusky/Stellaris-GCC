MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    .data : AT(ADDR(.text) + SIZEOF(.text))
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > SRAM

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM

    . = ALIGN(32);           /*Not sure if this needs to be done, but why not.*/
    _stack_bottom = .;       /*Address of the bottom of the stack.*/
    . = . + 0x1000;          /*Allocate 4K for the Stack.*/
    _stack_top = .;          /*Address of the top of the stack.*/
    _heap_bottom = .;        /*Address of the bottom of the heap.*/
    _heap_top = 0x20008000;  /*Address of the top of the heap, also end of RAM.*/
}

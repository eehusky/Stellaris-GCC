#include <stdio.h>

#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

void PrintMemoryLayout();
char *GetSP();

int main(void)
{
    PrintMemoryLayout();

    MAP_SysCtlSleep();

    return 0;
}


char* GetSP()
{
    char *stack_ptr;
    __asm (
        "mov %[stack_ptr], sp \n"
        : [stack_ptr] "=r" (stack_ptr)
        :
    );
    return stack_ptr;
}


void PrintMemoryLayout()
{
    extern unsigned long _text;
    extern unsigned long _etext;
    extern unsigned long _data;
    extern unsigned long _edata;
    extern unsigned long _bss;
    extern unsigned long _ebss;
    extern unsigned long _stack_bottom;
    extern unsigned long _stack_top;
    extern unsigned long _heap_bottom;
    extern char *heap_end;
    extern unsigned long _heap_top;

    printf("_text          = 0x%X\n",      (unsigned int) &_text);
    printf("_etext         = 0x%X\n",      (unsigned int) &_etext);
    printf("Sizeof(.text)  = %d bytes\n",  (&_etext - &_text) * 4);
    printf("---------------------------\n");
    printf("_data          = 0x%X\n",      (unsigned int) &_data);
    printf("_edata         = 0x%X\n",      (unsigned int) &_edata);
    printf("Sizeof(.data)  = %d bytes\n",  (&_edata - &_data) * 4);
    printf("---------------------------\n");
    printf("_bss           = 0x%X\n",      (unsigned int) &_bss);
    printf("_ebss          = 0x%X\n",      (unsigned int) &_ebss);
    printf("Sizeof(.bss)   = %d bytes\n",  (&_ebss - &_bss) * 4);
    printf("---------------------------\n");
    printf("_heap_bottom   = 0x%X\n",      (unsigned int) &_heap_bottom);
    printf("_heap_end      = 0x%X",        (unsigned int) heap_end);
    printf(" : usage: %d\n",               (heap_end - (char *) &_heap_bottom));
    printf("_heap_top      = 0x%X\n",      (unsigned int) &_heap_top);
    printf("Sizeof(heap)   = %d bytes\n",  (&_heap_top - &_heap_bottom) * 4);
    printf("---------------------------\n");
    printf("_stack_bottom  = 0x%X\n",      (unsigned int) &_stack_bottom);
    printf("StackPointer   = 0x%X",        (unsigned int) GetSP());
    printf(" : usage: %d\n",               ( (char *) &_stack_top - GetSP()));
    printf("_stack_top     = 0x%X\n",      (unsigned int) &_stack_top);
    printf("Sizeof(stack)  = %d bytes\n",  (&_stack_top - &_stack_bottom) * 4);
    printf("---------------------------\n");
}

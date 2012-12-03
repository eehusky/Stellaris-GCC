#include <sys/types.h>
#include <sys/stat.h>

#include "inc/hw_memmap.h"      //Needed for GPIO Pins
#include "inc/hw_types.h"       //Needed for SysTick Types
#include "inc/hw_uart.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/uart.h"
#include <string.h>

static char *heap_end = 0;
extern unsigned long _heap_bottom;
extern unsigned long _heap_top;
extern unsigned long g_ulBase;

caddr_t _sbrk(unsigned int incr)
{
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = (caddr_t)&_heap_bottom;
    }

    prev_heap_end = heap_end;

    if (heap_end + incr > (caddr_t)&_heap_top) {
        return (caddr_t)0;
    }

    heap_end += incr;

    return (caddr_t) prev_heap_end;
}

int _close(int file)
{
    return -1;
}

int _fstat(int file)
{
    return 0;
}

int _isatty(int file)
{
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _open(const char *name, int flags, int mode)
{
    return -1;
}

int _read(int file, char *ptr, int len)
{
    return 0;
}

int _write(int file, char *ptr, unsigned int len)
{
    unsigned int uIdx;
    for(uIdx = 0; uIdx < len; uIdx++)
    {
        MAP_UARTCharPut(g_ulBase, ptr[uIdx]);
    }
    return(uIdx);
}

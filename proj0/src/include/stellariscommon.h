#ifndef _STELLARIS_COMMON_H_
#define _STELLARIS_COMMON_H_

#include <stdio.h>

#define TRACE    printf("TRACE %s:%d: %s\n",__FILE__,__LINE__,__FUNCTION__)
#define VAL_I(x) printf(#x ": %d\n", x);
#define VAL_X(x) printf(#x ": 0x%X\n", (unsigned int)x);
#define VAL_S(x) printf(#x ": %s\n", x);

#define CLK80 1
#define CLK50 2
#define CLK16 3

void SetupFPU(void);

void SetupClock(int clk);

void SetupStdio(void);

void SetupSysTick(void);

#endif

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "StellarisCommon.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LED_RED     GPIO_PIN_1
#define LED_BLUE    GPIO_PIN_2
#define LED_GREEN   GPIO_PIN_3

unsigned long* GetSP()
{
    unsigned long *stack_ptr;
    __asm(
        "mov %[stack_ptr], sp \n"
        : [stack_ptr] "=r" (stack_ptr)
        :
        );
        return stack_ptr;
}

int main(void)
{
    //Enable Floating Point Unit
    SetupFPU();
    //Set Clock rate
    SetupClock(CLK80);
    //Setup STDIO, Needs to be done after setting the clock
    SetupStdio();

    printf("Hello %f\n",9.82);

    // Enable PORT F GPIO
    MAP_SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF );
    // set LED pins as outputs
    MAP_GPIOPinTypeGPIOOutput( GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN );
    // loop forever
    for (;;) {
        // set the red LED pin high, others low
        MAP_GPIOPinWrite( GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN, LED_RED );
        // delay
        MAP_SysCtlDelay( 2000000 );
        // set the green LED pin high, others low
        MAP_GPIOPinWrite( GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN, LED_GREEN );
        // delay
        MAP_SysCtlDelay( 2000000 );
        // set the blue LED pin high, others low
        MAP_GPIOPinWrite( GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN, LED_BLUE );
        // delay
        MAP_SysCtlDelay( 2000000 );
    }

    return 0;
}

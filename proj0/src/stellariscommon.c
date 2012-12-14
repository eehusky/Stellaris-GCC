#include "inc/hw_memmap.h"  //Needed for GPIO Pins
#include "inc/hw_types.h"   //Needed for SysTick Types
#include "inc/hw_uart.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/uart.h"

#include "stellariscommon.h"

void SetupFPU(void)
{
    MAP_FPUEnable();
    MAP_FPULazyStackingEnable();
}

void SetupClock(int clk)
{
    switch (clk) {
        case CLK80:
            MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL |
                       SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
            break;
        case CLK50:
            MAP_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL |
                       SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
            break;
        case CLK16:
            MAP_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC |
                       SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
            break;
        default:
            MAP_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC |
                       SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
            break;
    }
}

void SetupStdio(void)
{
    //Put these into variables because passing macros to macros isnt fun.
    const unsigned long srcClock = MAP_SysCtlClockGet();
    const unsigned long baud = 115200;

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    MAP_UARTConfigSetExpClk(UART0_BASE, srcClock, baud,
                (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                 UART_CONFIG_WLEN_8));
    MAP_UARTEnable(UART0_BASE);
}

void SetupSysTick(void)
{
    MAP_SysTickPeriodSet(MAP_SysCtlClockGet());
    MAP_SysTickIntEnable();
    MAP_SysTickEnable();
}

#ifndef TIMER_H_
#define	TIMER_H_

#include <stdint.h>

#define UART0_BASE_ADDR 0x101f1000
#define UART0_DR (*((volatile uint32_t *)(UART0_BASE_ADDR + 0x000)))
#define VIC_BASE_ADDR 0x10140000		//start address of PIC for arm926ej-s versatilepb
#define VIC_INTENABLE (*((volatile uint32_t *)(VIC_BASE_ADDR + 0x010)))    //Enable the interrupt line
#define VIC_INTENCLEAR (*((volatile uint32_t *)(VIC_BASE_ADDR + 0x014)))    //clears the bits of VIC_INTENABLE register
#define CONFIG_SYS_TIMERBASE 0x101E2000  // base address for timer 0

extern int sched_var; 

#endif //TIMER_H_
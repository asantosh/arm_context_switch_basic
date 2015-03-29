#include "timer.h"
int timer_init(void)
{
    unsigned long timer_ctrl_val;
    VIC_INTENABLE = 3<<4; //enable timer0 and timer 1 in VIC
    timer_ctrl_val = 1 << 7; // enable the timer
    //timer_ctrl_val &= ~(1 << 6); // free running
    timer_ctrl_val |= 1 << 6; // periodic running
    timer_ctrl_val |= 1 << 5; // enable the interrupt

    *(volatile unsigned long *)(CONFIG_SYS_TIMERBASE) = 0x3E8 ; //1ms	//0xF4240 *2 ; // set the load register for 2 second
    *(volatile unsigned long *)(CONFIG_SYS_TIMERBASE + 0x8) = timer_ctrl_val; //write to control register

    return 0;
}


void print(const char* s)
{
    /* Print Hello World to UART */
    while(*s != '\0') { /* Loop until end of string */
	UART0_DR = (unsigned int)(*s); /* Transmit char */
	s++; /* Next char */
    }
}

/*IRQ Handler*/
void __attribute__((interrupt)) do_irq()
{
    task2();
    *(volatile unsigned long *)(CONFIG_SYS_TIMERBASE + 0x0C) = 1; // clear the timer interrupt
}

/* all other handlers are infinite loops */
void __attribute__((interrupt)) undef_handler(void) { for(;;); }
void __attribute__((interrupt)) swi_handler(void) { for(;;); }
void __attribute__((interrupt)) prefetch_abort_handler(void) { for(;;); }
void __attribute__((interrupt)) data_abort_handler(void) { for(;;); }
void __attribute__((interrupt)) fiq_handler(void) { for(;;); }


/*Copy the vector table to 0th address*/
void copy_vectors(void) 
{
    extern uint32_t vectors_start;
    extern uint32_t vectors_end;
    uint32_t *vectors_src = &vectors_start;
    uint32_t *vectors_dst = (uint32_t *)0;

    while(vectors_src < &vectors_end)
	*vectors_dst++ = *vectors_src++;
}

void timer_start(void)
{
    timer_init();
}


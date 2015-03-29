.text
     .code 32
 
     .global vectors_start
     .global vectors_end
 
vectors_start:
     LDR PC, reset_handler_addr
     LDR PC, undef_handler_addr
     LDR PC, swi_handler_addr
     LDR PC, prefetch_abort_handler_addr
     LDR PC, data_abort_handler_addr
     B .
     LDR PC, irq_handler_addr
     LDR PC, fiq_handler_addr
 
reset_handler_addr:		.word reset_handler
undef_handler_addr: 		.word undef_handler
swi_handler_addr: 		.word swi_handler
prefetch_abort_handler_addr:	.word prefetch_abort_handler
data_abort_handler_addr: 	.word data_abort_handler
irq_handler_addr: 		.word irq_handler
fiq_handler_addr: 		.word fiq_handler
 
vectors_end:
 
reset_handler:
     /* set Supervisor stack */
     LDR sp, =svc_stack

     /* copy vector table to address 0 */
     BL copy_vectors

     /* get Program Status Register */
     MRS r0, cpsr
    
     /* go in IRQ mode */
     BIC r1, r0, #0x1F
     ORR r1, r1, #0x12
     MSR cpsr, r1

     /* set IRQ stack */
     LDR sp, =irq_stack

     /* Enable IRQs */
     BIC r0, r0, #0x80

     /* go back in Supervisor mode */
     MSR cpsr, r0

     /* jump to main */
     BL main
     B .

/*
 * use irq_save_user_regs / irq_restore_user_regs for IRQ/FIQ handling
 */
.macro	irq_save_user_regs
    ldr	sp, =irq_stack	
    stmia	sp!, {r0 - r12}		@ store to stack r0-r12
.endm

.macro	irq_restore_user_regs
    mrs	r0,   spsr
    msr	cpsr, r0
    ldmia   sp!, {r0 - r12}		@ restore r0 - r12
    sub	    lr, lr, #4			@ lr = lr - 4
    mov	    pc, lr  		
.endm


/*
 * exception handlers
 */

irq_handler:
	
    irq_save_user_regs
    bl 	do_irq
    irq_restore_user_regs

.end

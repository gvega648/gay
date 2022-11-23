.section .text 
.align 2 
.globl UART_write 

#include "memoryMap.inc" 
#include "UART.inc" 

UART_write: 
    addi sp, sp, -16 
    # allocate a stack frame, moves the stack up by 16 bits 
    sw ra, 12(sp)

    li t0, UART_CTRL_ADDR
    sw a0, UART_txdata(t0)
    
    loop:
        li t0, UART_CTRL_ADDR
        lw t1, UART_txdata(t0)
        li t2, 0x80000000
        and t3,t3,t1
        bnez t3, loop
        sb a0, UART_txdata(t0)
        //lw ra, 12(sp)
        //addi sp,sp,16
    //ret
    
    lw ra, 12(sp) # load the return address 
    addi sp, sp, 16 # deallocate the stack 
    ret 
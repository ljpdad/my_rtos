    AREA    MY_CODE, CODE, READONLY
 
    EXPORT  my_rtos_task_switch
    EXPORT  taskYield

    EXTERN pxCurrentTcb
    EXTERN vTaskSwitchContext

taskYield
    ldr r0, =0xE000ED04    ; NVIC中断控制寄存器地址
    ldr r1, =0x10000000    ; PendSV触发位
    str r1, [r0]           ; 触发PendSV
    bx lr                  ; 返回

PendSV_Handler
    mrs r0, psp
    isb

    ldr r3, =pxCurrentTcb  ; Get the location of the current TCB
    ldr r2, [r3]

    stmdb r0!, {r4-r11}    ; Save the remaining registers
    str r0, [r2]           ; Save the new top of stack into the first member of the TCB

    stmdb sp!, {r3, r14}
    ; mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
    ; msr basepri, r0
    ; dsb
    isb
    bl vTaskSwitchContext
    ; mov r0, #0
    ; msr basepri, r0
    ldmia sp!, {r3, r14}

    ldr r1, [r3]
    ldr r0, [r1]           ; The first item in pxCurrentTcb is the task top of stack
    ldmia r0!, {r4-r11}    ; Pop the registers and the critical nesting count
    msr psp, r0
    isb
    bx r14

my_rtos_task_switch
    bx lr  

    END
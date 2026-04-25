#ifndef __TYPE_H
#define __TYPE_H


#ifndef NULL
#define NULL ((void*)0)
#endif
#define TASK_READY      1
#define TASK_RUNNING    2
#define TASK_SUSPENDED  3
#define TASK_DELETED    4
#define TASK_BLOCKED    5

typedef unsigned int uint32_t;
typedef struct Tcb {
    uint32_t *pxTopOfStack;  // 必须放在第一个！
    uint32_t status;
    uint32_t taskPriority;    // 优先级
    struct Tcb *taskNext;
    struct Tcb *taskPrev;
} Tcb_t;




extern void taskYield(void);



#endif
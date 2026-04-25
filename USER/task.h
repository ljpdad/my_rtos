
#ifndef __TASK_H
#define __TASK_H

#include"type.h"


extern uint32_t taskNumber;
// 全局指针变量
extern Tcb_t *pxCurrentTcb;
extern Tcb_t *taskReadyList;
extern Tcb_t *taskWaitList;




void taskListAdd(Tcb_t *task,Tcb_t ** taskList);
void vListRemoveTask(Tcb_t *task,Tcb_t ** taskList);
Tcb_t *findTaskHighest(Tcb_t *taskList);
void vTaskSwitchContext(void);
Tcb_t *taskCreate(Tcb_t *tcb, uint32_t priority, uint32_t *stackArray, uint32_t size, void (*taskFunc)(void));
void startScheduler(void);


#endif
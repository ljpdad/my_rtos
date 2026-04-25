#include"task.h"
Tcb_t *taskReadyList = NULL;
uint32_t taskNumber = 0;
// 全局指针变量
Tcb_t *pxCurrentTcb = NULL;
Tcb_t *taskWaitList = NULL;


void taskListAdd(Tcb_t *task,Tcb_t ** taskList) {
    task->taskNext = NULL;
    task->taskPrev = NULL;
																										//把任务加到链表
    if (*taskList == NULL) {
        *taskList = task;
    } else {
        Tcb_t *current = *taskList;
        while (current->taskNext != NULL) {
            current = current->taskNext;
        }
        current->taskNext = task;
        task->taskPrev = current;
    }
    taskNumber++;
}

void vListRemoveTask(Tcb_t *task,Tcb_t ** taskList) {										//任务从链表中删除
    if (task->taskPrev != NULL) {
        task->taskPrev->taskNext = task->taskNext;
    } else {
        // 删除的是头节点
        *taskList = task->taskNext;
    }
    
    if (task->taskNext != NULL) {
        task->taskNext->taskPrev = task->taskPrev;
    }
    
    task->taskNext = NULL;
    task->taskPrev = NULL;
    taskNumber--;
}

Tcb_t *findTaskHighest(Tcb_t *taskList) {  
     Tcb_t *highest = taskList;
    Tcb_t *current = taskList;  
	if (taskList == NULL) {
        return NULL;
    }
    

    
    while (current != NULL) {
        if (current->taskPriority < highest->taskPriority) {
            highest = current;
        }
        current = current->taskNext;
    }
    
    return highest;
}







void vTaskSwitchContext(void) {
    // 如果当前任务还在运行，放回就绪链表
    if (pxCurrentTcb != NULL && pxCurrentTcb->status == TASK_RUNNING) {
        pxCurrentTcb->status = TASK_READY;
        taskListAdd(pxCurrentTcb,&taskReadyList);
    }
    
    // 选择优先级最高的任务
    pxCurrentTcb = findTaskHighest(taskReadyList);
    
    if (pxCurrentTcb != NULL) {
        vListRemoveTask(pxCurrentTcb,&taskReadyList);
        pxCurrentTcb->status = TASK_RUNNING;
    }
}

Tcb_t *taskCreate(Tcb_t *tcb, uint32_t priority, uint32_t *stackArray, uint32_t size, void (*taskFunc)(void)) {
    uint32_t *sp = stackArray + size;
    
    // 异常自动压栈部分（由CPU自动压入）
    *(--sp) = 0x01000000;              // xPSR (Thumb模式，第24位=1)
    *(--sp) = (uint32_t)taskFunc;      // PC (任务入口函数)
    *(--sp) = 0xFFFFFFFD;              // LR (异常返回地址)
    *(--sp) = 0x12121212;              // R12 (临时寄存器，随便填)
    *(--sp) = 0x00000003;              // R3
    *(--sp) = 0x00000002;              // R2
    *(--sp) = 0x00000001;              // R1
    *(--sp) = 0x00000000;              // R0 (通常作为参数，这里为0)
    
    // 软件手动保存的部分（R4-R11）
    *(--sp) = 0x11111111;              // R11
    *(--sp) = 0x10101010;              // R10
    *(--sp) = 0x09090909;              // R9
    *(--sp) = 0x08080808;              // R8
    *(--sp) = 0x07070707;              // R7
    *(--sp) = 0x06060606;              // R6
    *(--sp) = 0x05050505;              // R5
    *(--sp) = 0x04040404;              // R4
    
    // 保存栈顶指针到TCB
    tcb->pxTopOfStack = sp;
    tcb->status = TASK_READY;
    tcb->taskPriority = priority;
    tcb->taskNext = NULL;
    tcb->taskPrev = NULL;
    
    taskListAdd(tcb,&taskReadyList);
    return tcb;
}

void startScheduler(void) {
	
    // 选择优先级最高的任务作为当前任务
    pxCurrentTcb = findTaskHighest(taskReadyList);
    
    if (pxCurrentTcb != NULL) {
        // 从就绪链表中移除
        vListRemoveTask(pxCurrentTcb,&taskReadyList);
        pxCurrentTcb->status = TASK_RUNNING;
        
        taskYield();
    }
}



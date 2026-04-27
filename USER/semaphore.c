#include"Semaphore.h"
#include"task.h"
extern Tcb_t* pxCurrentTcb;
void SemaphoreGive(Semaphore_t *sem)
{
	Tcb_t* task;
	sem->count++;
	if(sem->wait_list)
	{
		 task=sem->wait_list;
		sem->wait_list=task->taskNext;
		task->status=TASK_READY;
		taskListAdd(task,&taskReadyList[task->taskPriority]);
	}
	
}


void semaphore_init(Semaphore_t *sem, uint32_t initial_count) {
    sem->count = initial_count;
    sem->wait_list = NULL;
}


uint32_t SemaphoreTake(Semaphore_t *sem)
{
	 // 1. 关中断（保护临界区）
		//	uint32_t primask = __get_PRIMASK();
   // __disable_irq();
		// 2. 如果有可用资源，直接获取
    if (sem->count > 0) {
        sem->count--;
       // __set_PRIMASK(primask);  // 恢复中断
        return 1;  // 成功
    }
	// 4. 当前任务从就绪列表移除
    vListRemoveTask(pxCurrentTcb,&taskReadyList[pxCurrentTcb->taskPriority]);
    
    // 5. 设置任务状态为阻塞
    pxCurrentTcb->status = TASK_BLOCKED;
    
    // 6. 保存超时时间（用于超时唤醒）
  //  pxCurrentTCB->wait_timeout = timeout;
    
    // 7. 加入信号量的等待队列
    // 注意：通常按优先级排序，这里简化：加到队尾
    //add_to_waiting_list(&sem->wait_list, pxCurrentTCB);
   // taskListAdd(Tcb_t *task,taskWaitList);
		taskListAdd(pxCurrentTcb,&sem->wait_list);
    // 8. 触发调度，切换到其他任务
  //  __set_PRIMASK(primask);  // 先恢复中断（PendSV会重新关闭）
    taskYield();  // 触发 PendSV
    
    // ========== 从这里恢复执行 ==========
    // 任务被唤醒后，会继续执行这里
    
    // 9. 检查是被事件唤醒还是超时唤醒
    
    
    // 正常唤醒，已经获取到信号量（sem->count已被give函数减1）
    return 1;
}

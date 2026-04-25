#include"task.h"
#include"semaphore.h"

uint32_t myTask1Array[255];
uint32_t myTask2Array[255];
Tcb_t task1Tcb;
Tcb_t task2Tcb;
Semaphore_t sema_task1;

void myTask1(void) {
	semaphore_init(&sema_task1, 0);
	while(1)
	{
		if(SemaphoreTake(&sema_task1)==1)
		{
			
		}
	}
	
    // 任务代码
}

void myTask2(void) {
    // 任务代码
	
	while(1)
	{
		
		SemaphoreGive(&sema_task1);
	}
	
	
}



int main(void) {
    taskCreate(&task1Tcb, 1, myTask1Array, 255, myTask1);
    taskCreate(&task2Tcb, 2, myTask2Array, 255, myTask2);
    startScheduler();
	while(1)
	{
		
	}
	
	
    
    return 0;  // 理论上不会执行到这里
}
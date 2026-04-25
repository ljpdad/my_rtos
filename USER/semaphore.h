#include"type.h"
#ifndef __Semaphone__H
#define __Semaphone__H


typedef struct 
{
	uint32_t count;
	Tcb_t *wait_list;
	
}Semaphore_t;

void SemaphoreGive(Semaphore_t *sem);
uint32_t SemaphoreTake(Semaphore_t *sem);
void semaphore_init(Semaphore_t *sem, uint32_t initial_count);






#endif
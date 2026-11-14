/**
 * @file app_main.c
 * @author Aiden O'Leary (aidenoleary2004@gmail.com)
 * @brief Source for the main loop of the application
 * @version 0.1
 * @date 2026-11-14
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "FreeRTOS.h"
#include "task.h"
#include "blink_tasks.h"
#include "can_tasks.h"

void app_main(void)
{
	/* Initialize the tasks */
	init_blink_tasks();
	//init_can_tasks();

	// Start the FreeRTOS scheduler
	vTaskStartScheduler();

	// The program should never reach here
	for (;;);
}

static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

/* This function is automatically called by the kernel on startup */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
									StackType_t **ppxIdleTaskStackBuffer,
									uint32_t *pulIdleTaskStackSize )
{
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}


#if (configUSE_TIMERS == 1)
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
									 StackType_t **ppxTimerTaskStackBuffer,
									 uint32_t *pulTimerTaskStackSize )
{
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
#endif
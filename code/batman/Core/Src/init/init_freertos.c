/**
 * @file init_freertos.c
 * @brief initializes the freertos threads
 *
 *
 * @author Aiden O'Leary'
 * @version 1.0
 * @date 2026-06-06
 */

#include "init_freertos.h"
#include "FreeRTOS.h"
#include "task.h"

#define STACK_SIZE 256

static StaticTask_t s_placeholder_buffer;
static StackType_t s_placeholder_stack[ STACK_SIZE ];
TaskHandle_t placeholder_task_handle;


void placeholder_thread(void *PvParameters)
{
	for (;;) {
		// Do nothing
	}
}

void init_threads()
{
	placeholder_task_handle = xTaskCreateStatic(
		placeholder_thread,
		"StaticTask",
		STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY + 1,
		s_placeholder_stack,
		&s_placeholder_buffer
	);
	return;
}

void init_freertos()
{
	init_threads();
	vTaskStartScheduler();
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
    /* If the buffers are provided as static/global variables,
       this function must return pointers to them */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/**
 * @file blink_tasks.c
 * @author Aiden O'Leary (aidenoleary2004@gmail.com)
 * @brief Collection of tasks for blinking LEDs on the STM32F103 Bluepull board using FreeRTOS.
 * @version 0.1
 * @date 2026-09-29
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "blink_tasks.h"
#include "FreeRTOS.h"
#include "task.h"

#define STACK_SIZE 256

static StaticTask_t s_blink1_buffer;
static StackType_t s_blink1_stack[ STACK_SIZE ];
TaskHandle_t blink1_task_handle;

static StaticTask_t s_blink2_buffer;
static StackType_t s_blink2_stack[ STACK_SIZE ];
TaskHandle_t blink2_task_handle;



void tbike_blink1_thread(void *PvParameters)
{
	for (;;) {
		// Do nothing
	}
}

void tbike_blink2_thread(void *PvParameters)
{
	for (;;) {
		// Do nothing
	}
}

void init_blink_tasks(void)
{
    blink1_task_handle = xTaskCreateStatic(
        tbike_blink1_thread,
        "Blink1Task",
        STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1,
        s_blink1_stack,
        &s_blink1_buffer
    );

    blink2_task_handle = xTaskCreateStatic(
        tbike_blink2_thread,
        "Blink2Task",
        STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1,
        s_blink2_stack,
        &s_blink2_buffer
    );
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
/**
 * @file can_tasks.c
 * @author Charlie Drysdale (cmcharlie@shaw.com)
 * @brief CAN taks to test the CANBUS functionality of the the DEV board. Blinks LED for recieve using FreeRTOS.
 * @version 0.1
 * @date 2026-10-31
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "stm32f2xx_hal.h"
#include "can_tasks.h"
#include "FreeRTOS.h"
#include "task.h"

// will probably have to change just picked arbitrary value
#define STACK_SIZE 256

static StaticTask_t s_can_recv_buffer;
static StackType_t s_can_recv_stack[ STACK_SIZE ];
TaskHandle_t can_recv_task_handle;

static StaticTask_t s_can_send_buffer;
static StackType_t s_can_send_stack[ STACK_SIZE ];
TaskHandle_t can_send_task_handle;


void tbike_can_recv_thread(void *PvParameters)
{
	for (;;) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
        vTaskDelay(500);
	}
}

void tbike_can_send_thread(void *PvParameters)
{
	for (;;) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
        vTaskDelay(333);
	}
}

void init_can_tasks(void)
{
    can_recv_task_handle = xTaskCreateStatic(
        tbike_can_recv_thread,
        "Blink1Task",
        STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1,
        s_blink1_stack,
        &s_blink1_buffer
    );

    can_send_task_handle = xTaskCreateStatic(
        tbike_can_send_thread,
        "Blink2Task",
        STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1,
        s_blink2_stack,
        &s_blink2_buffer
    );
}
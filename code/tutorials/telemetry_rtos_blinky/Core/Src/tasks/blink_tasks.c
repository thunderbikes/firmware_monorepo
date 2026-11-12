#include "blink_tasks.h"
#include "main.h" //for hal
#include "FreeRTOS.h" //kernel config, defines common types and settings  (data types, hanlde type)
#include "task.h" //task creation, Function definitions(API)
#define STACK_SIZE 256 

//is a structure defined by freertos. it holds one task's internal control block. 
//this include ssaved stack pointer, priority, stack location (where in memory), Task Name, Notification Data, state information 
static StaticTask_t s_blink1_buffer; //holds tasks datastructures 
static StackType_t blink1_stack[STACK_SIZE]; 
TaskHandle_t blink1_task_handle; //type by which tasks are referenced, return type of taskcreate

static StaticTask_t s_blink2_buffer;
static StackType_t blink2_stack[STACK_SIZE]; 
TaskHandle_t blink2_task_handle;


// void parameter allwos passing of different tata to a task without the kernel knowing types. 
void blink1_thread(void *pvParameters){
    
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(500);
    TickType_t xPeriodsElapsed;

    xLastWakeTime = xTaskGetTickCount(); 
    
    for(;;){

        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin); 
        xTaskPeriodicDelay(&xLastWakeTime, xFrequency); 

    }
}

void blink2_thread(void *pvParameters){

    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(500);
    TickType_t xPeriodsElapsed;

    xLastWakeTime = xTaskGetTickCount(); 
    
    for(;;){

        HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin); 
        xTaskPeriodicDelay(&xLastWakeTime, xFrequency); 
        
    }
}


void init_blink_tasks(void){
    blink1_task_handle = xTaskCreateStatic(
        blink1_thread,
        "blink LED1", 
        STACK_SIZE, 
        NULL, 
        tskIDLE_PRIORITY + 1, 
        blink1_stack, 
        &s_blink1_buffer
    ); 

    blink2_task_handle = xTaskCreateStatic(
        blink2_thread, 
        "blink LED1", 
        STACK_SIZE, 
        NULL, 
        tskIDLE_PRIORITY + 1, 
        blink2_stack, 
        &s_blink2_buffer
    ); 
}
   

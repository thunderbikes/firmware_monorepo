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

    for(;;){


    }
}

void blink2_thread(void *pvParameters){

    for(;;){

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
   
//the functions below literally just assign the timer and idle tasks memory since we disabled dynamic task creation 
static StaticTask_t idle_task_buffer 
static StaticType_t idle_task_stack

// **indicates pointer to pointer.  
// you pass in a pointer to your pointer. the function creates a local copy of the outermost pointer 
// that copied adress in turn points to another adress
//to change the value of the pointer, not the local copy, the double pointer is dereferenced once
// that modifies teh value of the middle pointer, telling it to point to our variable. 
//*pointer means acess the object at the adress stored at p 
//&means adress of the variable 
/* This function is automatically called by the kernel on startup, sets up idle task's memory  */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
    *ppxIdleTaskTCBBuffer = &idle_task_buffer;
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
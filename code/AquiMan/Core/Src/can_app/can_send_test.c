#include "main.h"
#include "FreeRTOS.h"
#include "task.h"



#define STACK_SIZE 256

extern CAN_HandleTypeDef hcan; 

static StaticTask_t can_test_buffer; 
static StackType_t can_test_stack[STACK_SIZE]; 
TaskHandle_t can_test_handle; 


void CANTestThread(void *pv_parameters){
    TickType_t last_wake_time; 
    const TickType_t frequency = pdMS_TO_TICKS(1000); 

    xTaskPeriodicDelay(&last_wake_time, frequency); 
    
    CAN_TxHeaderTypeDef tx_header; 

    tx_header.StdId = 0x0000; 
    tx_header.IDE = CAN_ID_STD; 
    tx_header.RTR = CAN_RTR_DATA; 
    tx_header.DLC = 8; 
    tx_header.TransmitGlobalTime = DISABLE; 
    
    uint8_t tx_data[8] = {0}; 
    
    uint32_t tx_mailbox; /* The number of the mail box that transmitted the Tx message */

    for(;;){

        if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan) != 0){

            if(HAL_CAN_AddTxMessage(&hcan, &tx_header, tx_data, &tx_mailbox) != HAL_OK){
                Error_Handler(); 
            }
            
        }

    }


}


void InitCANTestTask(){
    can_test_handle = xTaskCreateStatic(
        CANTestThread, 
        "can loopback transmit test", 
        STACK_SIZE, 
        NULL, 
        tskIDLE_PRIORITY + 1, 
        can_test_stack, 
        &can_test_buffer 
    ); 
}








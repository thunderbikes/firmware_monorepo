
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "can_app.h"


void CanAppInit(CAN_HandleTypeDef *hcan) {
    //define can filter bank to filter for last 3 bits. 
    CAN_FilterTypeDef can_filter_config; 
    can_filter_config.FilterActivation = CAN_FILTER_ENABLE; 
    can_filter_config.FilterBank = 0; 
    can_filter_config.FilterFIFOAssignment = CAN_FILTER_FIFO0; 
    can_filter_config.FilterIdHigh = 0x000 << 5; //only check the top 8 bits, make sure they are equal to 1 
    can_filter_config.FilterIdLow = 0x0000; 
    can_filter_config.FilterMaskIdHigh = 0x000 << 5;   //set to 11111111 as the top 8 bits that identify a message bound for the telem board 
    can_filter_config.FilterMaskIdLow = 0x0006;  //RTR and IDE bits must be 0 
    can_filter_config.FilterMode = CAN_FILTERMODE_IDMASK; 
    can_filter_config.FilterScale = CAN_FILTERSCALE_32BIT; 

    //slave start filter bank not needed, only one controller 

    
    // startup functions for can peripheral 
    if(HAL_CAN_ConfigFilter(hcan, &can_filter_config) != HAL_OK){
        Error_Handler(); 
        return; 
    }


    if(HAL_CAN_Start(hcan) != HAL_OK){
        Error_Handler(); 
        return; 
    }

    if(HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
        Error_Handler(); 
        return; 
    }

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {

    //debug watch vars 
    uint8_t bms_indicator = 0; 
    uint8_t motcon_indicator = 0; 
    uint8_t vcu_indicator = 0; 

    while (HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO0)) {
        CanQueueEntry_t message_package; 

        CAN_RxHeaderTypeDef rx_header; 

        if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, message_package.data_payload) != HAL_OK) {

            Error_Handler();  //will likely customize this 

        }

        message_package.message_id = rx_header.StdId; 
        message_package.timestamp_ms = HAL_GetTick(); 

        switch (rx_header.StdId) {
            case BMS_MSG:
                bms_indicator = 1; 
                break; 
            case VCU_MSG:
                vcu_indicator = 1; 
                break; 
            case MOTCON_MSG: 
                motcon_indicator = 1; 
                break; 

        }
    }

}




#ifndef CAN_APP
#define CAN_APP
#include "can_init.h"
#define DEBUG_MODE 1
enum MESSAGE_TYPE {
    BMS_MSG, 
    MOTCON_MSG, 
    VCU_MSG, 
};




typedef struct CanQueueEntry_t {
    uint8_t data_payload[8]; 
    uint32_t  message_id; 
    uint32_t timestamp_ms; 
} CanQueueEntry_t; 

#endif 
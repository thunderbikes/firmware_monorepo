/**
 * @file can_tasks.h
 * @author Charlie Drysdale (cmcharlie@shaw.com)
 * @brief 
 * @version 0.1
 * @date 2026-10-31
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef CAN_TASKS_H
#define CAN_TASKS_H

/*============ PROTOTYPES ============*/

 /**
  * @brief Initializes the CAN tasks for the STM32F205 Dev board using FreeRTOS.
  * 
  */
void init_can_tasks(void);

/**
 * @brief Blink task for the first LED on the STM32F103 Bluepill board.
 * 
 * @param PvParameters 
 */
void tbike_can_recv_thread(void *PvParameters);

/**
 * @brief Blink task for the second LED on the STM32F103 Bluepill board.
 * 
 * @param PvParameters 
 */
void tbike_can_send_thread(void *PvParameters);

#endif /* BLINK_TASKS_H */
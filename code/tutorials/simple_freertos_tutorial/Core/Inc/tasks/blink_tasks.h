/**
 * @file blink_tasks.h
 * @author Aiden O'Leary (aidenoleary2004@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-09-29
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#IFNDEF BLINK_TASKS_H
#define BLINK_TASKS_H

 /*============ PROTOTYPES ============*/

 /**
  * @brief Initializes the blink tasks for the STM32F103 Bluepill board using FreeRTOS.
  * 
  */
void init_blink_tasks(void);

/**
 * @brief Blink task for the first LED on the STM32F103 Bluepill board.
 * 
 * @param PvParameters 
 */
void tbike_blink1_thread(void *PvParameters);

/**
 * @brief Blink task for the second LED on the STM32F103 Bluepill board.
 * 
 * @param PvParameters 
 */
void tbike_blink2_thread(void *PvParameters);

#endif /* BLINK_TASKS_H */
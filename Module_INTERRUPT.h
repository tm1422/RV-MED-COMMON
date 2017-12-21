/**
  ******************************************************************************
  * @file    Module_INTERRUPT.h
  * @author  Toni Malovrh, Template from MCD Application Team
  * @version V1.0.0
  * @date    16-August-2017
  * @last    16-August-2017
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_IT_H
#define __STM32F0XX_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "main.h"
#include <Module_TIM.h>
#include <Module_CAN.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern uint16_t TIM2_Alarm_Timer_HIGH;
extern uint16_t TIM2_Alarm_Timer_LOW;
extern uint16_t BEEP_STATUS;
extern uint16_t ALARM_STATUS;


void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void Disable_Interrupts();
void Enable_Interrupts();

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_IT_H */
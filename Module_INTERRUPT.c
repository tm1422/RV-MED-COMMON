/**
  ******************************************************************************
  * @file    Module_INTERRUPT.c
  * @author  Toni Malovrh, Template from MCD Application Team
  * @version V1.0.0
  * @date    16-August-2017
  * @last    13-December-2017
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <Module_INTERRUPT.h>

/** @addtogroup STM32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_TimeBase
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t capture = 0;
extern __IO uint16_t CCR1_Val;
extern __IO uint16_t CCR2_Val;
extern __IO uint16_t CCR3_Val;
extern __IO uint16_t CCR4_Val;

extern uint16_t TIM3_Interrupt_Flags;
//extern uint16_t TIM2_Interrupt_Flags;
extern uint16_t TIM2_Beep_Timer;
extern uint16_t TIM2_Alarm_Timer;

extern uint16_t ALARM_periode;
extern uint16_t ALARM_duty;
extern uint16_t ALARM_calculated_time_HIGH;
extern uint16_t ALARM_calculated_time_LOW;



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function enables interrupts.
  * @param  None
  * @retval None
  */
void Enable_Interrupts(){
  
  /* Enable CAN massage received interrupts */
  NVIC_IntEnable(IVT_INT_CEC_CAN);
  
  /* Enable TIM3 interrupts */
  NVIC_IntEnable(IVT_INT_TIM3);
  
  /* Enable TIM2 interrupts */
  NVIC_IntEnable(IVT_INT_TIM2);
}

/**
  * @brief  This function disables interrupts.
  * @param  None
  * @retval None
  */
void Disable_Interrupts(){
  
  /* Disable CAN massage received interrupts */
  NVIC_IntDisable(IVT_INT_CEC_CAN);
  
  /* Disable TIM3 interrupts */
  NVIC_IntDisable(IVT_INT_TIM3);
  
  /* Disable TIM2 interrupts */
  NVIC_IntDisable(IVT_INT_TIM2);
}


/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}


/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/******************************************************************************/
/**
  * @brief  This function handles TIM3 global interrupt request used for CAN TIMINGS.
  * @param  None
  * @retval None
  */

void TIM3_IRQHandler() iv IVT_INT_TIM3 ics ICS_AUTO{

  /* Check TIM3 capture-compare 1 interrupt flag used for CAN TIMING 1 */
  if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET){
    
    /* Write TIM3 CC1 pending interrupt in buffer for later use */
    TIM3_Interrupt_Flags |= 0B0000000000000001;
    
    /* Clear TIM3 CC1 interrupt flag */
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);

    /* Save time that has passed between last interrupt and now */
    capture = TIM_GetCapture1(TIM3);
    
    /* Set TIM3 Compare 1 with incalculated time above for higher precission timings */
    TIM_SetCompare1(TIM3, capture + CCR1_Val);
  }
  
  /* Check TIM3 capture-compare 2 interrupt flag used for CAN TIMING 2 */
  else if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET){
    
    /* Write TIM3 CC2 pending interrupt in buffer for later use */
    TIM3_Interrupt_Flags |= 0B0000000000000010;
    
    /* Clear TIM3 CC2 interrupt flag */
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);

    /* Save time that has passed between last interrupt and now */
    capture = TIM_GetCapture2(TIM3);
    
    /* Set TIM3 Compare 2 with incalculated time above for higher precission timings */
    TIM_SetCompare2(TIM3, capture + CCR2_Val);
  }
  
  /* Check TIM3 capture-compare 3 interrupt flag used for CAN TIMING 3 */
  else if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET){
    
    /* Write TIM3 CC3 pending interrupt in buffer for later use */
    TIM3_Interrupt_Flags |= 0B0000000000000100;
    
    /* Clear TIM3 CC3 interrupt flag */
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);

    /* Save time that has passed between last interrupt and now */
    capture = TIM_GetCapture3(TIM3);
    
    /* Set TIM3 Compare 3 with incalculated time above for higher precission timings */
    TIM_SetCompare3(TIM3, capture + CCR3_Val);
  }
  
  /* Check TIM3 capture-compare 4 interrupt flag used for CAN TIMING 4 */
  else if(TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET){
    
    /* Write TIM3 CC4 pending interrupt in buffer for later use */
    TIM3_Interrupt_Flags |= 0B0000000000001000;
    
    /* Clear TIM3 CC4 interrupt flag */
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);

    /* Save time that has passed between last interrupt and now */
    capture = TIM_GetCapture4(TIM3);
    
    /* Set TIM3 Compare 4 with incalculated time above for higher precission timings */
    TIM_SetCompare4(TIM3, capture + CCR4_Val);
  }
}


/**
  * @brief  This function handles TIM2 CC1 request used for SOUND PROCESSING.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler() iv IVT_INT_TIM2 ics ICS_AUTO{

  /* Check TIM2 capture-compare 1 interrupt flag.
     This interrupt / timer is used for timings in
     sound processing routines
  */
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET){
    
    /* Check if "beep" sound is active */
    if(BEEP_STATUS){
    
      /* Increase timer for "beep" sound */
      TIM2_Beep_Timer++;
      
      /* If timer is larger than value defined in configuration tabble
         stop playing "beep" sound
       */
      if(TIM2_Beep_Timer > (Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_PERIODE_DUTY] & 0B1111000000000000)>>12){
        Module_Sound_Beep_Stop();
      }
    }

    /* Check if sound alarm is active */
    if(ALARM_STATUS & 0B0000000000000001){
      
      /* Check if higher pitch part of sound alarm is playing and increase its timer */
      if(ALARM_STATUS & 0B0000000000000010) TIM2_Alarm_Timer_HIGH++;
      
      /* Otherwise increase time for lower pitch part of sound alarm */
      else TIM2_Alarm_Timer_LOW++;

      /* Check high pitch alarm time and switch to lower pitch if larger than calculated value */
      if(TIM2_Alarm_Timer_HIGH > ALARM_calculated_time_HIGH){ SOUND_ALARM_Switch(0);              UART1_Write_Text("switch to low");}
      
      /* Check low pitch alarm time and switch to higher pitch if larger than calculated value */
      else if(TIM2_Alarm_Timer_LOW > ALARM_calculated_time_LOW){ SOUND_ALARM_Switch(1);           UART1_Write_Text("switch to high");}
    }

    /* Clear TIM2 CC1 interrupt flag */
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);

    /* Save time that has passed between interrupt and now */
    capture = TIM_GetCapture1(TIM2);
    
    /* Set TIM2 Compare 1 with incalculated time above for higher precission timings */
    TIM_SetCompare1(TIM2, capture + CCR1_Val);
  }
}


/**
  * @brief  This function handles CAN1 RX0 request.
  * @param  None
  * @retval None
  */
void CAN_IRQHandler() iv IVT_INT_CEC_CAN ics ICS_AUTO {

  /* Check CAN receive interrupt flag */
  if(FMP00_bit || FMP01_bit){

    /* Save CAN data in CAN receive software buffer */
    CAN_GET();
  }
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */
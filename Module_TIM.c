/**
  ******************************************************************************
  * @file    Module_TIM.c
  * @author  Toni Malovrh, Template from MCD Application Team
  * @version V1.0.0
  * @date    16-August-2017
  * @last    13-December-2017
  * @brief   Timers configuration functions
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <Module_TIM.h>

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
__IO uint16_t CCR1_Val = 40961;
__IO uint16_t CCR2_Val = 27309;
__IO uint16_t CCR3_Val = 13654;
__IO uint16_t CCR4_Val = 6826;
uint16_t PrescalerValue = 0;
uint16_t PrescalerValueDiv = 0;


/**
  * @brief  This function configures TIM3 and belonging interrupts.
  * @param  None
  * @retval None
  */
void TIM_Config_CAN(void)
{
  /* Initialize structures used for timer and interrupt configuration */
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /*  If statements below chackes for selected mode in configuration table and
      calculates CC1 to CC4 prescaller values for 4 different CAN timings
      based on values written in configuration table

      Configuration table mode selection:
        * B0 = 1 : SLOW MODE   (usable range : 100ms - 100s)
        * B1 = 1 : MEDIUM MODE (usable range : 10ms - 10s)
        * B2 = 1 : FAST MODE   (usable range : 1ms - 1s)

      Prescaller examples for SLOW MODE:
        Prescaller = (Sysclock / X) - 1
          * X = 60.000 : CCR_Val = 100s
          * X = 6.000  : CCR_Val = 10s
          * X = 600    : CCR_Val = 1s
          * X = 60     : CCR_Val = 100ms

      Prescaller examples for MEDIUM MODE:
        Prescaller = (Sysclock / X) - 1
          * X = 60.000 : CCR_Val = 10s
          * X = 6.000  : CCR_Val = 1s
          * X = 600    : CCR_Val = 100ms
          * X = 60     : CCR_Val = 10ms

      Prescaller examples for SLOW MODE:
        Prescaller = (Sysclock / X) - 1
          * X = 60.000 : CCR_Val = 1s
          * X = 6.000  : CCR_Val = 100ms
          * X = 600    : CCR_Val = 10ms
          * X = 60     : CCR_Val = 1ms
  */
  if(Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_MODE] & 0B0000000000000001){ 
    PrescalerValueDiv = 600; // SLOW MODE

    CCR1_Val = (6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_1])/10;
    CCR2_Val = (6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_2])/10;
    CCR3_Val = (6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_3])/10;
    CCR4_Val = (6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_4])/10;
  }
  else if(Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_MODE] & 0B0000000000000010){
    PrescalerValueDiv = 6000; // MEDIUM MODE

    CCR1_Val = 6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_1];
    CCR2_Val = 6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_2];
    CCR3_Val = 6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_3];
    CCR4_Val = 6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_4];
  }
  else if(Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_MODE] & 0B0000000000000100){
    PrescalerValueDiv = 60000; // FAST MODE

    CCR1_Val = 60 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_1];
    CCR2_Val = 60 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_2];
    CCR3_Val = 60 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_3];
    CCR4_Val = 60 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_4];
  }
  else{
    PrescalerValueDiv = 6000; // MEDIUM MODE

    CCR1_Val = 6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_1];
    CCR2_Val = 6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_2];
    CCR3_Val = 6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_3];
    CCR4_Val = 6 * Configuration_Table[CONF_TABLE_CAN_TIMING][CONF_TABLE_CAN_TIMING_4];
  }
  

  /* Enable the TIM3 gloabal Interrupt in NVIC init structure */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);


  /***** TIM3 INTERRUPT CONFIGURATION *****/

  /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  
  /* Set priority for TIM3 interrupt request to 3 (higher priority) in NVIC init structure */
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
  
   /* Set enable flag for TIM2 interrupt in NVIC init structure */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  
  /* Initialize NVIC interrupt controller for TIM2 according to NVIC init structure */
  NVIC_Init(&NVIC_InitStructure);
  
  
  /***** TIM3 TIME BASE CONFIGURATION *****/

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock  / PrescalerValueDiv) - 1;
                                                                                
  /* Set basic TIM2 periode to full timer range in TIM2 time base structure */
  TIM_TimeBaseStructure.TIM_Period = 65535;
  
  /* Set TIM3 timer prescaller to 0 in TIM3 time base structure */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  
  /* Set TIM3 clock division to 0 in TIM3 time base structure */
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  
  /* Set TIM3 counter mode - up counter in TIM3 time base structure */
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  /* Set Output Compare Mode to timing mode in TIM3 output compare init structure */
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);
  

  /***** TIM3 CCP COMMON CONFIGURATION *****/
                                                                                
  /* Output Compare Timing Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  
  
  /***** TIM3 CCP 1 CONFIGURATION *****/
  
  /* Write TIM3 output state enable flag in TIM3 output compare init structure */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  
  /* Write TIM3 CC3 value in TIM3 output compare init structure */
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  
  /* Set high polarity in TIM3 output compare init structure */
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  /* Initialize TIM3 OC1 output compare */
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  /* Disable TIM3 CC1 output compare preload */
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);


  /***** TIM3 CCP 2 CONFIGURATION *****/

  /* Write TIM3 output state enable flag in TIM3 output compare init structure */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  
  /* Write TIM3 CC2 value in TIM3 output compare init structure */
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

  /* Initialize TIM3 OC2 output compare */
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

  /* Disable TIM3 CC2 output compare preload */
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);


  /***** TIM3 CCP 3 CONFIGURATION *****/
  
  /* Write TIM3 output state enable flag in TIM3 output compare init structure */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  
  /* Write TIM3 CC3 value in TIM3 output compare init structure */
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  /* Initialize TIM3 OC3 output compare */
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

  /* Disable TIM3 CC3 output compare preload */
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);


  /***** TIM3 CCP 4 CONFIGURATION *****/
  
  /* Write TIM3 output state enable flag in TIM3 output compare init structure */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  
  /* Write TIM3 CC4 value in TIM3 output compare init structure */
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  /* Initialize TIM3 OC4 output compare */
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

  /* Disable TIM3 CC4 output compare preload */
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);


  /* TIM3 Interrupts enable */
  TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
}


/**
  * @brief  This function configures TIM2 and belonging interrupts.
  * @param  None
  * @retval None
  */
void TIM2_Config(void){
  
  /* Initialize structures used for timer and interrupt configuration */
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Set prescaller and CC1 timing value to match 10ms interrupt rate on TIM2 capture compare 1 */
  PrescalerValueDiv = 60000;
  CCR1_Val = 600;


  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);


  /***** TIM2 INTERRUPT CONFIGURATION *****/
  
  /* Enable the TIM2 gloabal Interrupt in NVIC init structure */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  
  /* Set priority for TIM2 interrupt request to 10 (lower priority) in NVIC init structure */
  NVIC_InitStructure.NVIC_IRQChannelPriority = 10;

  /* Set enable flag for TIM2 interrupt in NVIC init structure */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  /* Initialize NVIC interrupt controller for TIM2 according to NVIC init structure */
  NVIC_Init(&NVIC_InitStructure);


  /***** TIM2 TIME BASE CONFIGURATION *****/
  
  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock  / PrescalerValueDiv) - 1;

  /* Set basic TIM2 periode to full timer range in TIM2 time base structure */
  TIM_TimeBaseStructure.TIM_Period = 65535;
  
  /* Set TIM2 timer prescaller to 0 in TIM2 time base structure */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  
  /* Set TIM2 clock division to 0 in TIM2 time base structure */
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  
  /* Set TIM2 counter mode - up counter in TIM2 time base structure */
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  /* Initialize time base fot TIM2 according to time base init structure */
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Prescaler configuration based on prescaller 
     value and set immediate prescaller reload mode
  */
  TIM_PrescalerConfig(TIM2, PrescalerValue, TIM_PSCReloadMode_Immediate);


  /***** TIM2 CCP COMMON CONFIGURATION *****/
  
  /* Set Output Compare Mode to timing mode in TIM2 output compare init structure */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  
  
  /***** TIM2 CCP 1 CONFIGURATION *****/
  
  /* Write TIM2 output state enable flag in TIM2 output compare init structure */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  
  /* Write TIM2 CC1 value in TIM2 output compare init structure */
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  
  /* Set high polarity in TIM2 output compare init structure */
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  /* Initialize TIM2 OC1 output compare */
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);

  /* Disable TIM2 output compare preload */
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);



  /* TIM Interrupts enable */
  TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);

  /* TIM2 enable counter */
//  TIM2_Enable();
                                                                                
}

/**
  * @brief  This function disables TIM2.
  * @param  None
  * @retval None
  */
void TIM2_Disable(void){

  /* Disable TIM2 counter */
  TIM_Cmd(TIM2, DISABLE);
}

/**
  * @brief  This function enables TIM2.
  * @param  None
  * @retval None
  */
void TIM2_Enable(void){
  
  /* Enable TIM2 counter */
  TIM_Cmd(TIM2, ENABLE);
}
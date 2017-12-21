#ifndef MODULE_TIM_H
#define MODULE_TIM_H

/**
  ******************************************************************************
  * @file    Module_COMP.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    16-August-2017
  * @last    14-December-2017
  * @brief   Functions prototypes for the COMP used in Medicop
             STM32F072 CAN modules
  ******************************************************************************
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>                                                           //
#include <Defines.h>                                                          //
#include <stm32f0xx_tim.h>                                                    //
#include <stm32f0xx_misc.h>                                                   //
#include <stm32f0xx_rcc.h>                                                    //
                                                                              //

/* External ------------------------------------------------------------------*/
/* MUST be defined externally!                                                */
                                                                              //
extern uint32_t SystemCoreClock;                                              //
extern uint16_t Configuration_Table[12][16];                                  //
                                                                              //

/* Function prototypes - MAINS -----------------------------------------------*/
                                                                              //
void TIM_Config_CAN(void);                                                    //
void TIM2_Config(void);                                                       //
void TIM2_Enable(void);                                                       //
void TIM2_Disable(void);                                                      //
                                                                              //

/* Function prototypes - SUBS ------------------------------------------------*/
                                                                              //
                                                                              
                                                                              
#endif
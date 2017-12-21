#ifndef MODULE_PWM_H
#define MODULE_PWM_H

/**
  ******************************************************************************
  * @file    Module_ADC.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    16-August-2017
  * @last    13-December-2017
  * @brief   Functions prototypes for the PWM used in
             Medicop STM32F072 CAN modules
  ******************************************************************************
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
                                                                              //
#include <stdint.h>                                                           //
#include <Defines.h>                                                          //
#include <Module_DEBUG.h>                                                     //
                                                                              //
                                                                              
                                                                              
/* External ------------------------------------------------------------------*/
/* MUST be defined externally!                                                */
                                                                              //
extern uint8_t CAN_Buffer[32][8];                                             //
extern uint16_t Configuration_Table[12][16];                                  //
                                                                              //
                                                                              

/* Function prototypes - MAINS -----------------------------------------------*/
                                                                              //
void PWM_SET();                                                               //
void PWM_SET_OUTPUT();                                                        //
void PWM_UPDATE();                                                            //
                                                                              //


/* Function prototypes - SUBS ------------------------------------------------*/
                                                                              //
void Module_PWM_Start(uint8_t Timer_nr, uint32_t channel);                    //
void Module_PWM_Stop(uint8_t Timer_nr, uint32_t channel);                     //
void Module_PWM_Update_Duty(uint8_t Timer_nr, uint32_t duty, uint8_t inverted, uint8_t channel);//
void PWM_Get_Flags();                                                         //
void PWM_Calculate_Duty();                                                    //
                                                                              //
                                                                              
                                                                              
/* Debug ---------------------------------------------------------------------*/
                                                                              //
uint8_t PWM_Debug_Mode();                                                     //
                                   
                                   
#endif
#ifndef MODULE_ADC_H
#define MODULE_ADC_H

/**
  ******************************************************************************
  * @file    Module_ADC.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    16-August-2017
  * @last    13-December-2017
  * @brief   Functions prototypes for the ADC used in
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
void ADC_GET();                                                               //
void ADC_SET();                                                               //
                                                                              //
                                                                              

/* Function prototypes - SUBS ------------------------------------------------*/
                                                                              //
void Module_ADC_Init(uint16_t input_mask);                                    //
void Module_ADC_Read(uint16_t input, uint16_t hysteresis);                    //
                                                                              //
                                                                              

/* Debug ---------------------------------------------------------------------*/
                                                                              //
uint8_t ADC_Debug_Mode();                                                     //
                                                                              //
                                                                              
#endif
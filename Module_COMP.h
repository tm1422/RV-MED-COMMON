#ifndef MODULE_COMP_H
#define MODULE_COMP_H

/**
  ******************************************************************************
  * @file    Module_COMP.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    16-August-2017
  * @last    13-December-2017
  * @brief   Functions prototypes for the COMP used in Medicop
             STM32F072 CAN modules
  ******************************************************************************
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include <stm32f0xx_comp.h>                                                   //
#include <stm32f0xx_rcc.h>                                                    //
#include <Defines.h>                                                          //
#include <stdint.h>                                                           //
#include <Module_DEBUG.h>                                                     //


/* External ------------------------------------------------------------------*/
/* MUST be defined externally!                                                */
                                                                              //
extern uint8_t CAN_Buffer[32][8];                                             //
extern uint16_t Configuration_Table[12][16];                                  //
                                                                              //
                                                                              
                                                                              
/* Function prototypes - MAINS -----------------------------------------------*/
                                                                              //
void COMP_GET();                                                              //
void COMP_SET();                                                              //
                                                                              //
                                                                              

/* Function prototypes - SUBS ------------------------------------------------*/
                                                                              //
void Module_COMPx_Init(uint32_t Comp_Select, uint32_t Invert_Input_Select,    //
                       uint32_t Comp_Output, uint32_t Comp_Output_Pol,        //
                       uint32_t Comp_Hysteresis, uint32_t Comp_Mode);         //
                                                                              //
uint32_t Module_COMP_GetOutput(uint32_t Comp_Select);                         //
void COMP_Get_Flags();                                                        //
void Module_COMP_Window_Mode_Enable(uint8_t State);                           //
uint32_t COMP_Get_Output_Selection(uint16_t tmp);                             //
uint32_t COMP_Get_Mode(uint16_t tmp);                                         //
uint32_t COMP_Get_Hysteresis(uint16_t tmp);                                   //
uint32_t COMP_Get_Inverting_Input(uint16_t tmp);                              //
                                                                              //
                                                                              

/* Debug ---------------------------------------------------------------------*/
                                                                              //
uint8_t COMP_Debug_Mode();                                                    //
                                                                              //
                                                                              
#endif
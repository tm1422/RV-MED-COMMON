#ifndef MODULE_RTC_H
#define MODULE_RTC_H
/**
  ******************************************************************************
  * @file    Module_RTC.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    07-September-2017
  * @brief   Functions prototypes for the hardware RTC used in
             Medicop STM32F072 CAN modules
  ******************************************************************************
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
                                                                              //
#include <stdint.h>                                                           //
#include <stm32f0xx_rtc.h>                                                    //
#include <stm32f0xx_rcc.h>                                                    //
#include <stm32f0xx_pwr.h>                                                    //
#include <Defines.h>                                                          //
#include <Module_DEBUG.h>                                                     //
#include <Defines.h>                                                          //
                                                                              //

/* External ------------------------------------------------------------------*/
/* MUST be defined externally!                                                */
                                                                              //
extern uint8_t CAN_Buffer[32][8];                                             //
extern uint16_t Configuration_Table[12][16];                                  //
                                                                              //
                                                                              
/* Function prototypes - MAINS -----------------------------------------------*/

void RTCC_Process();                                                                              //
void RTC_SET_UART(void);                                                      //
void RTC_SET_CLOCK(uint8_t Hours, uint8_t Minutes, uint8_t Seconds);          //
void RTC_SET_DATE(uint8_t WeekDay, uint8_t Day, uint8_t Month, uint8_t Year); //
void RTC_WRITE_CAN_BUFFER();                                                  //
                                                                              //



/* Function prototypes - SUBS ------------------------------------------------*/
                                                                              //
void RTC_TimeRegulate(void);                                                  //
void RTC_TimeShow(void);                                                      //
void RTC_DateShow(void);                                                      //
//void RTC_AlarmShow(void);                                                   //
uint8_t USART_Scanf(uint32_t value);        

#endif                                  //
/**
  ******************************************************************************
  * @file    Module_ADC.c
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    07-September-2017
  * @last    13-December-2017
  * @brief   This file provides functions to manage the following
  *          functionalities of the PWM on Medicop STM32F072 CAN Modules:
  *           + PWM INITialization via external configuration table mask
  *           + SET PWM results vai external configuration table mask
  *           + UPDATE PWM on-the-fly
  *           + PWM debug mode
  *
*/

/* Includes ------------------------------------------------------------------*/
#include "Module_PWM.h"                                                       //
                                                                              //

/* Declarations --------------------------------------------------------------*/
                                                                              //
// Enabled flags                                                              //
uint8_t _MODULE_PWM_TIM15_CH1_ENABLED = 0;                                    //
uint8_t _MODULE_PWM_TIM15_CH2_ENABLED = 0;                                    //
uint8_t _MODULE_PWM_TIM16_ENABLED = 0;                                        //
uint8_t _MODULE_PWM_TIM17_ENABLED = 0;                                        //
                                                                              //
// Inverted flags                                                             //
uint8_t _MODULE_PWM_TIM15_CH1_INVERTED = 0;                                   //
uint8_t _MODULE_PWM_TIM15_CH2_INVERTED = 0;                                   //
uint8_t _MODULE_PWM_TIM16_INVERTED = 0;                                       //
uint8_t _MODULE_PWM_TIM17_INVERTED = 0;                                       //
                                                                              //
// Duty Cycles                                                                //
uint32_t _MODULE_PWM_TIM15_CH1_DUTY_CYCLE = 0;                                //
uint32_t _MODULE_PWM_TIM15_CH2_DUTY_CYCLE = 0;                                //
uint32_t _MODULE_PWM_TIM16_DUTY_CYCLE = 0;                                    //
uint32_t _MODULE_PWM_TIM17_DUTY_CYCLE = 0;                                    //
                                                                              //
// Temporary buffer for ADC results                                           //
uint32_t period15 = 0;                                                        //
uint32_t period16 = 0;                                                        //
uint32_t period17 = 0;                                                        //
                                                                              //
// ADC debug txt                                                              //
const uint8_t txt_pwm_new_line[] = "\r\n";                                    //
const uint8_t txt_pwm_Module_PWM_Init[] = "Module_PWM_Init();";               //
const uint8_t txt_pwm_Frequency[] = "Frequency = ";                           //
const uint8_t txt_pwm_Duty_ratio[] = "Duty ratio = ";                         //
const uint8_t txt_pwm_Inverted[] = "Inverted = ";                             //
const uint8_t txt_pwm_Channel[] = "Channel = ";                               //
const uint8_t txt_pwm_Module_PWM_Start[] = "Module_PWM_Start();";             //
const uint8_t txt_pwm_PWM_SET[] = "PWM_SET();";                               //
const uint8_t txt_pwm_TIM15_CH1_Init_Done[] = "TIM15 CH1 Init... Done";       //
const uint8_t txt_pwm_TIM15_CH2_Init_Done[] = "TIM15 CH2 Init... Done";       //
const uint8_t txt_pwm_TIM16_Init_Done[] = "TIM16 Init... Done";               //
const uint8_t txt_pwm_TIM17_Init_Done[] = "TIM17 Init... Done";               //
const uint8_t txt_pwm_PWM_UPDATE[] = "PWM_UPDATE();";                         //
const uint8_t txt_pwm_PWM_SET_OUTPUT[] = "PWM_SET_OUTPUT();";                 //
const uint8_t txt_pwm_TIM15_CH1_Start[] = "TIM15 CH1 Start";                  //
const uint8_t txt_pwm_TIM15_CH1_Stop[] = "TIM15 CH1 Stop";                    //
const uint8_t txt_pwm_TIM15_CH2_Start[] = "TIM15 CH2 Start";                  //
const uint8_t txt_pwm_TIM15_CH2_Stop[] = "TIM15 CH2 Stop";                    //
const uint8_t txt_pwm_TIM16_Start[] = "TIM16 Start";                          //
const uint8_t txt_pwm_TIM16_Stop[] = "TIM16 Stop";                            //
const uint8_t txt_pwm_TIM17_Start[] = "TIM17 Start";                          //
const uint8_t txt_pwm_TIM17_Stop[] = "TIM17 Stop";                            //
const uint8_t txt_pwm_TIM15_CH1_Duty_Update[] = "TIM15 CH1 Duty Update";      //
const uint8_t txt_pwm_TIM15_CH2_Duty_Update[] = "TIM15 CH2 Duty Update";      //
const uint8_t txt_pwm_TIM16_Duty_Update[] = "TIM16 Duty Update";              //
const uint8_t txt_pwm_TIM17_Duty_Update[] = "TIM17 Duty Update";              //
 
 

/*____________________________________________________________________________*/
/*                            Functions - MAINS                               */
/*____________________________________________________________________________*/


/******************************************************************************/
/*******************************  PWM SET  ************************************/
/******************************************************************************/
/* PWM_SET -------------------------------------------------------------------*/
/*                                                                            //
    Initialises PWM channels enabled in Configuration_Table.                  //
    Available chanels:                                                        //
      + PWM TIM15 CHANNEL 1                                                   //
      + PWM TIM15 CHANNEL 2                                                   //
      + PWM TIM16 CHANNEL 1                                                   //
      + PWM TIM17 CHANNEL 1                                                   //
                                                                              //
      PWM outputs:                                                            //
                                                                              //
           _GPIO_MODULE_TIM15_CH1_PF9                                         //
           _GPIO_MODULE_TIM15_CH2_PF10                                        //
           _GPIO_MODULE_TIM16_CH1_PA6                                         //
           _GPIO_MODULE_TIM17_CH1_PA7                                         //
                                                                              //
    Uses MIkroC build-in libs                                                 //
    ______________________________________                                    //
                                                                              //
    MAX/RECOMMENDED VALUES:                                                   //
                                                                              //
      + PWM FREQ vs DUTY CYCLE:                                               //
        - dividable with clock                                                //
          (et. ..., 2.4k, 4.8k, ... , 2.4M , 4.8M for 48 MHz clock)           //
        - maximum of 4.8MHz @ 48MHz input clock                               //
        - higher pwm freq. results in duty cicle resolution dropS < 100       //
                                                                              //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //

                                                                                  /********** DEBUG ****************************/
void PWM_SET(){
  uint32_t tmp;
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_PWM_SET);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

  /* Get PWM enable and invert flags for all PWM channels */
  PWM_Get_Flags();

  /* Check if PWM TIM15 channel 1 is enabled */
  if(_MODULE_PWM_TIM15_CH1_ENABLED){
  
    /* Get PWM TIM 15 channle 1 32-bit frequency from configuration table */
    tmp = Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T15_CH1_FREQ_L] | Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T15_CH1_FREQ_H] << 16;

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_Frequency);
                                                                                    Debug_LongToStr((uint32_t) tmp);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                    UART1_Write_Text(txt_pwm_Duty_ratio);
                                                                                    Debug_WordToStr(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T15_CH1_DUTY]);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

    /* Initialise PWM TIM15 and store return value in
       periode15 which is used for duty cycle value calculation 
    */
    period15 = PWM_TIM15_Init(tmp);
    
    /* calculate duty cycle values */
    PWM_Calculate_Duty();
    
    /* Set PWM TIM15 channel 1 duty cycle */
    PWM_TIM15_Set_Duty(_MODULE_PWM_TIM15_CH1_DUTY_CYCLE,_MODULE_PWM_TIM15_CH1_INVERTED, _PWM_CHANNEL1);

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM15_CH1_Init_Done);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

  }

  /* Check if PWM TIM15 channel 2 is enabled */
  if(_MODULE_PWM_TIM15_CH2_ENABLED){  // IF TIM15 CH2 ENABLE
    
    /* Get PWM TIM 15 channle 2 32-bit frequency from configuration table */
    tmp = Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T15_CH2_FREQ_L] | Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T15_CH2_FREQ_H] << 16;

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_Frequency);
                                                                                    Debug_LongToStr((uint32_t) tmp);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                    UART1_Write_Text(txt_pwm_Duty_ratio);
                                                                                    Debug_WordToStr(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T15_CH2_DUTY]);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

    /* Initialise PWM TIM15 and store return value in
       periode15 which is used for duty cycle value calculation
    */
    period15 = PWM_TIM15_Init(tmp);
    
    /* calculate duty cycle values */
    PWM_Calculate_Duty();

    /* Set PWM TIM15 channel 2 duty cycle */
    PWM_TIM15_Set_Duty(_MODULE_PWM_TIM15_CH2_DUTY_CYCLE,_MODULE_PWM_TIM15_CH2_INVERTED, _PWM_CHANNEL2);

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM15_CH2_Init_Done);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

  }

  /* Check if PWM TIM16 is enabled */
  if(_MODULE_PWM_TIM16_ENABLED){  // IF TIM16 ENABLE
    
    /* Get PWM TIM 16 32-bit frequency from configuration table */
    tmp = Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T16_FREQ_L] | Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T16_FREQ_H] << 16;

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_Frequency);
                                                                                    Debug_LongToStr((uint32_t) tmp);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                    UART1_Write_Text(txt_pwm_Duty_ratio);
                                                                                    Debug_WordToStr(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T16_DUTY]);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                   }

    /* Initialise PWM TIM16 and store return value in
       periode16 which is used for duty cycle value calculation
    */
    period16 = PWM_TIM16_Init(tmp);
    
    /* calculate duty cycle values */
    PWM_Calculate_Duty();

    /* Set PWM TIM16 duty cycle */
    PWM_TIM16_Set_Duty(_MODULE_PWM_TIM16_DUTY_CYCLE,_MODULE_PWM_TIM16_INVERTED, _PWM_CHANNEL1);

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM16_Init_Done);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

  }

  /* Check if PWM TIM17 is enabled */
  if(_MODULE_PWM_TIM16_ENABLED){  // IF TIM17 ENABLE
    
    /* Get PWM TIM 17 32-bit frequency from configuration table */
    tmp = Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T17_FREQ_L] | Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T17_FREQ_H] << 16;

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_Frequency);
                                                                                    Debug_LongToStr((uint32_t) tmp);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                    UART1_Write_Text(txt_pwm_Duty_ratio);
                                                                                    Debug_WordToStr(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T17_DUTY]);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                   }

    /* Initialise PWM TIM17 and store return value in
       periode17 which is used for duty cycle value calculation
    */
    period17 = PWM_TIM17_Init(tmp);
    
    /* calculate duty cycle values */
    PWM_Calculate_Duty();

    /* Set PWM TIM17 duty cycle */
    PWM_TIM17_Set_Duty(_MODULE_PWM_TIM17_DUTY_CYCLE,_MODULE_PWM_TIM17_INVERTED, _PWM_CHANNEL1);

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM17_Init_Done);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

  }

                                                                                  if(PWM_Debug_Mode()) UART1_Write_Text(txt_pwm_new_line);
}


/******************************************************************************/
/***************************  PWM SET OUTPUT **********************************/
/******************************************************************************/
/* PWM_SET_OUTPUT ------------------------------------------------------------*/
/*                                                                            //
    Starts/stops PWM channels enabled in Configuration_Table                  //
    according start/stop bits in configuration table.                         //
    Uses MIkroC build-in libs                                                 //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + none                                                                  //
                                                                              //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //


void PWM_SET_OUTPUT(){

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_PWM_SET_OUTPUT);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

  /* Check if PWM TIM15 channel 1 is enabled in configuration table */
  if(_MODULE_PWM_TIM15_CH1_ENABLED){
  
    /* Check if start bit for PWM TIM15 channel 1 is set */
    if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_START] & 0B0000000000001000){
      
      /* Start PWM TIM15 channel 1 */
      Module_PWM_Start(15, 0);
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM15_CH1_Start);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

    }
    else {
      
      /* Stop PWM TIM15 channel 1 */
      Module_PWM_Stop(15, 0);
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM15_CH1_Stop);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

    }
  }
  
  /* Check if PWM TIM15 channel 2 is enabled in configuration table */
  if(_MODULE_PWM_TIM15_CH2_ENABLED){
    
    /* Check if start bit for PWM TIM15 channel 2 is set */
    if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_START] & 0B0000000000001000){
    
      /* Start PWM TIM15 channel 2 */
      Module_PWM_Start(15, 1);
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM15_CH2_Start);
                                                                                    UART1_Write_Text(txt_pwm_new_line);

                                                                                  }
    }
    else {
      
      /* Stop PWM TIM15 channel 2 */
      Module_PWM_Stop(15, 1);
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM15_CH2_Stop);
                                                                                    UART1_Write_Text(txt_pwm_new_line);

                                                                                  }
    }
  }
  
  /* Check if PWM TIM16 is enabled in configuration table */
  if(_MODULE_PWM_TIM16_ENABLED){
    
    /* Check if start bit for PWM TIM16 is set */
    if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_START] & 0B0000000000000100){
      
      /* Start PWM TIM16 */
      Module_PWM_Start(16, 0);
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM16_Start);
                                                                                    UART1_Write_Text(txt_pwm_new_line);

                                                                                  }
    }
    else {
      
      /* Stop PWM TIM16 */
      Module_PWM_Stop(16, 0);
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM16_Stop);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

    }
  }
  
  /* Check if PWM TIM17 is enabled in configuration table */
  if(_MODULE_PWM_TIM17_ENABLED){
    
    /* Check if start bit for PWM TIM17 is set */
    if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_START] & 0B0000000000001000){
      
      /* Start PWM TIM17 */
      Module_PWM_Start(17, 0);
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM17_Start);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

    }
    else {
      
      /* Stop PWM TIM17 */
      Module_PWM_Stop(17, 0);
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM17_Stop);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

    }
  }
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

}



/******************************************************************************/
/******************************  PWM UPDATE ***********************************/
/******************************************************************************/
/* PWM_UPDATE ----------------------------------------------------------------*/
/*                                                                            //
    Updates PWM duty cycle if channel enabled in Configuration_Table          //
    Uses values defined in Configuration table.                               //
                                                                              //
    Uses MIkroC build-in libs                                                 //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + none                                                                  //
                                                                              //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //



void PWM_UPDATE(){

  if(_MODULE_PWM_TIM15_CH1_ENABLED){  // IF TIM15 CH1 ENABLE

    /* Calculate duty value for PWM TIM15 channel 1 */
    PWM_Calculate_Duty();
    
    /* Update PWM TIM15 channel 1 duty cycle */
    Module_PWM_Update_Duty(15, Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T15_CH1_DUTY],_MODULE_PWM_TIM15_CH1_INVERTED, 0);

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM15_CH1_Duty_Update);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

  }

  if(_MODULE_PWM_TIM15_CH2_ENABLED){  // IF TIM15 CH2 ENABLE

    /* Calculate duty value for PWM TIM15 channel 2 */
    PWM_Calculate_Duty();

    /* Update PWM TIM15 channel 2 duty cycle */
    Module_PWM_Update_Duty(15, Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T15_CH2_DUTY], _MODULE_PWM_TIM15_CH2_INVERTED, 1);

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM15_CH2_Duty_Update);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

  }

  if(_MODULE_PWM_TIM16_ENABLED){  // IF TIM16 ENABLE

    /* Calculate duty value for PWM TIM16 */
    PWM_Calculate_Duty();

    /* Update PWM TIM16 duty cycle */
    Module_PWM_Update_Duty(16, Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T16_DUTY], _MODULE_PWM_TIM16_INVERTED, 0);

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM16_Duty_Update);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

  }

  if(_MODULE_PWM_TIM17_ENABLED){  // IF TIM17 ENABLE

    /* Calculate duty value for PWM TIM17 */
    PWM_Calculate_Duty();

    /* Update PWM TIM17 duty cycle */
    Module_PWM_Update_Duty(17, Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T17_DUTY], _MODULE_PWM_TIM17_INVERTED, 0);

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_TIM17_Duty_Update);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

  }

                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }

}





/*____________________________________________________________________________*/
/*                            Functions - SUBS                                */
/*____________________________________________________________________________*/


/******************************************************************************/
/**************************  PWM CALCULATE DUTY  ******************************/
/******************************************************************************/
/* PWM_Calculate_Duty() ------------------------------------------------------*/
/*                                                                            //
    Read duty cycle from configuration table and calculate value              //
    for PWM functions.                                                        //
    period15/16/17 MUST be defined as return value of PWM_Init() function     //
    before calling this function                                              //
                                                                              //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + none                                                                  //
                                                                              //
    RETURN VALUES:                                                            //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //

void PWM_Calculate_Duty(){

  /* calculate duty cycle value for PWM TIM15 channel 1 */
  _MODULE_PWM_TIM15_CH1_DUTY_CYCLE = period15*Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T15_CH1_DUTY]/100;
  
  /* calculate duty cycle value for PWM TIM15 channel 2 */
  _MODULE_PWM_TIM15_CH2_DUTY_CYCLE = period15*Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T15_CH2_DUTY]/100;
  
  /* calculate duty cycle value for PWM TIM16 */
  _MODULE_PWM_TIM16_DUTY_CYCLE = period16*Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T16_DUTY]/100;
  
  /* calculate duty cycle value for PWM TIM17 */
  _MODULE_PWM_TIM17_DUTY_CYCLE = period17*Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_T17_DUTY]/100;
}


/******************************************************************************/
/**************************  PWM GET FLAGS  ***********************************/
/******************************************************************************/
/* PWM_Get_Flags() -----------------------------------------------------------*/
/*                                                                            //
    Checks configuration table for enabled PWMs and inverted outputs          //
    and writes flags                                                          //
                                                                              //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + none                                                                  //
                                                                              //
    RETURN VALUES:                                                            //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //

void PWM_Get_Flags(){

  /* Check if PWM TIM15 channel 1 is enabled) */
  if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_SETT] & 0B0000000000000001){
    
    /* Write PWM TIM15 channel 1 enable flag */
    _MODULE_PWM_TIM15_CH1_ENABLED = 1;
  }
  else _MODULE_PWM_TIM15_CH1_ENABLED = 0;
  
  /* Check if PWM TIM15 channel 2 is enabled) */
  if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_SETT] & 0B0000000000000010){
    
    /* Write PWM TIM15 channel 2 enable flag */
    _MODULE_PWM_TIM15_CH2_ENABLED = 1;
  }
  else _MODULE_PWM_TIM15_CH2_ENABLED = 0;
  
  /* Check if PWM TIM16 is enabled) */
  if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_SETT] & 0B0000000000000100){
    
    /* Write PWM TIM16 enable flag */
    _MODULE_PWM_TIM16_ENABLED = 1;
  }
  else _MODULE_PWM_TIM16_ENABLED = 0;
  
  /* Check if PWM TIM17 is enabled) */
  if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_SETT] & 0B0000000000001000){
    
    /* Write PWM TIM17 enable flag */
    _MODULE_PWM_TIM17_ENABLED = 1;
  }
  else _MODULE_PWM_TIM17_ENABLED = 0;
  
  /* Check if PWM TIM15 channel 1 is inverted) */
  if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_SETT] & 0B0000000000010000){
    
    /* Write PWM TIM15 channel 1 inverted flag */
    _MODULE_PWM_TIM15_CH1_INVERTED = 1;
  }
  else _MODULE_PWM_TIM15_CH1_INVERTED = 0;
  
  /* Check if PWM TIM15 channel 2 is inverted) */
  if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_SETT] & 0B0000000000100000){
    
    /* Write PWM TIM15 channel 2 inverted flag */
    _MODULE_PWM_TIM15_CH2_INVERTED = 1;
  }
  else _MODULE_PWM_TIM15_CH2_INVERTED = 0;
  
  /* Check if PWM TIM16 is inverted) */
  if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_SETT] & 0B0000000001000000){
    
    /* Write PWM TIM16 inverted flag */
    _MODULE_PWM_TIM16_INVERTED = 1;
  }
  else _MODULE_PWM_TIM16_INVERTED = 0;
  
  /* Check if PWM TIM17 is inverted) */
  if(Configuration_Table[CONF_TABLE_PWM][CONF_TABLE_PWM_SETT] & 0B0000000010000000){
    
    /* Write PWM TIM17 inverted flag */
    _MODULE_PWM_TIM17_INVERTED = 1;
  }
  else _MODULE_PWM_TIM17_INVERTED = 0;
}



/******************************************************************************/
/**************************  MODULE PWM START  ********************************/
/******************************************************************************/
/* Module_PWM_Start() --------------------------------------------------------*/
/*                                                                            //
    Starts desired PWM channel                                                //
                                                                              //
    Uses MIkroC build-in libs                                                 //
                                                                              //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + uint8_t Timer_nr:                                                     //
        - 15 / 16 / 17                                                        //
                                                                              //
      + uint32_t channel:                                                     //
        - _PWM_CHANNEL1                                                       //
        - _PWM_CHANNEL2 (PWM TIM 15 ONLY)                                     //
                                                                              //
    RETURN VALUES:                                                            //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //



void Module_PWM_Start(uint8_t Timer_nr, uint32_t channel){
  
  /* Check input parameters for channel */
  if(Timer_nr==15){
    
    /* Start PWM channel on PF9 (channel 1) */
    if(channel==_PWM_CHANNEL1)PWM_TIM15_Start(channel, &_GPIO_MODULE_TIM15_CH1_PF9);
    
    /* Start PWM channel on PF10 (channel 2) */
    else if(channel==_PWM_CHANNEL2)PWM_TIM15_Start(channel, &_GPIO_MODULE_TIM15_CH2_PF10);
  }
  
  /* Check input parameters for channel */
  else if(Timer_nr==16){

    /* Start PWM channel on PA6 */
    PWM_TIM16_Start(channel, &_GPIO_MODULE_TIM16_CH1_PA6);
  }
  
  /* Check input parameters for channel */
  else if(Timer_nr==17){
  
    /* Start PWM channel on PA7 */
    PWM_TIM17_Start(channel, &_GPIO_MODULE_TIM17_CH1_PA7);
 
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_Module_PWM_Start);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                    UART1_Write_Text(txt_pwm_Channel);
                                                                                    Debug_WordToStr(channel);
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }
                                                                                    
  }
  
                                                                                  if(PWM_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_pwm_new_line);
                                                                                  }
                                                                                    
}



/******************************************************************************/
/**************************  MODULE PWM STOP  *********************************/
/******************************************************************************/
/* Module_PWM_Stop() ---------------------------------------------------------*/
/*                                                                            //
    Stops desired PWM channel                                                 //
                                                                              //
    Uses MIkroC build-in libs                                                 //
                                                                              //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + uint8_t Timer_nr:                                                     //
        - 15 / 16 / 17                                                        //
                                                                              //
      + uint32_t channel:                                                     //
        - _PWM_CHANNEL1                                                       //
        - _PWM_CHANNEL2 (PWM TIM 15 ONLY)                                     //
                                                                              //
    RETURN VALUES:                                                            //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //


void Module_PWM_Stop(uint8_t Timer_nr, uint32_t channel){
  
  /* Check input parameters for channel */
  if(Timer_nr==15){
  
    /* Stop PWM TIM 15 */
    PWM_TIM15_Stop(channel);
  }
  
  /* Check input parameters for channel */
  else if(Timer_nr==16){
    
    /* Stop PWM TIM 16 */
    PWM_TIM16_Stop(channel);
  }
  
  /* Check input parameters for channel */
  else if(Timer_nr==17){
  
    /* Stop PWM TIM 17 */
    PWM_TIM17_Stop(channel);
  }
}



/******************************************************************************/
/**********************  MODULE PWM UPDADE DUTY  ******************************/
/******************************************************************************/
/* Module_PWM_Update_Duty() --------------------------------------------------*/
/*                                                                            //
    Updates desired PWM channel duty cycle                                    //
                                                                              //
    Uses MIkroC build-in libs                                                 //
                                                                              //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + uint8_t Timer_nr:                                                     //
        - 15 / 16 / 17                                                        //
                                                                              //
      + uint32_t duty:                                                        //
        - 1-100                                                               //
                                                                              //
      + uint8_t invertet:                                                     //
        - _PWM_INVERTED                                                       //
        - _PWM_NON_INVERTED                                                   //
                                                                              //
      + uint32_t channel:                                                     //
        - _PWM_CHANNEL1                                                       //
        - _PWM_CHANNEL2 (PWM TIM 15 ONLY)                                     //
                                                                              //
    RETURN VALUES:                                                            //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //



void Module_PWM_Update_Duty(uint8_t Timer_nr, uint32_t duty, uint8_t inverted, uint8_t channel){
  
  /* Check input parameters for channel */
  if(Timer_nr==15 && channel == _PWM_CHANNEL1){

    /* Update duty cycle on PWM TIM 15 Channel 1 */
    PWM_TIM15_Set_Duty(_MODULE_PWM_TIM15_CH1_DUTY_CYCLE,_MODULE_PWM_TIM15_CH1_INVERTED, channel);

  }
  
  /* Check input parameters for channel */
  else if(Timer_nr==15 && channel == _PWM_CHANNEL2){

    /* Update duty cycle on PWM TIM 15 Channel 2 */
    PWM_TIM15_Set_Duty(_MODULE_PWM_TIM15_CH2_DUTY_CYCLE,_MODULE_PWM_TIM15_CH2_INVERTED, channel);

  }
  
  /* Check input parameters for channel */
  else if(Timer_nr==16){

    /* Update duty cycle on PWM TIM 16 */
    PWM_TIM16_Set_Duty(_MODULE_PWM_TIM16_DUTY_CYCLE,_MODULE_PWM_TIM16_INVERTED, channel);

  }
  
  /* Check input parameters for channel */
  else if(Timer_nr==17){

    /* Update duty cycle on PWM TIM 17 */
    PWM_TIM17_Set_Duty(_MODULE_PWM_TIM17_DUTY_CYCLE,_MODULE_PWM_TIM17_INVERTED, channel);
    
  }
}





/******************************************************************************/
/**************************  PWM DEBUG MODE  **********************************/
/******************************************************************************/
/* PWM_Debug_Mode() ----------------------------------------------------------*/
/*                                                                            //
    Checks if debug mode is enabled                                           //
                                                                              //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + none                                                                  //
                                                                              //
    RETURN VALUES:                                                            //
                                                                              //
      1: Debug mode is enabled                                                //
      0: Debug mode is disabled                                               //
    ______________________________________                                    //
*/                                                                            //


uint8_t PWM_Debug_Mode(){

  /* Check if PWM UART debugging is enabled */
  if(Configuration_Table[CONF_TABLE_DEBUG][CONF_TABLE_DEBUG_MASK1] & 0B0000000000001000) return 1;
  else return 0;
}
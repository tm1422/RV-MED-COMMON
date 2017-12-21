/**
  ******************************************************************************
  * @file    Module_ADC.c
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    16-August-2017
  * @last    13-December-2017
  * @brief   This file provides functions to manage the following
  *          functionalities of the ADC on Medicop STM32F072 CAN Modules:
  *           + ADC initialization via external configuration table mask
  *           + get ADC results vai external configuration table mask
  *           + ADC debug mode
  *
*/


/* Includes ------------------------------------------------------------------*/
#include <Module_ADC.h>                                                       //
                                                                              //


/* Declarations --------------------------------------------------------------*/
                                                                              //
// Temporary buffer for ADC results                                           //
uint16_t ADC_Buffer[8];                                                       //
                                                                              //
// ADC debug txt                                                              //
const uint8_t txt_adc_new_line[] = "\r\n";                                    //
const uint8_t txt_adc_adc_set[] = "ADC_SET();";                               //
const uint8_t txt_adc_adc_init_mask[] = "ADC Init MASK: ";                    //
const uint8_t txt_adc_adc_get[] = "ADC_GET();";                               //
const uint8_t txt_adc_conf_table_adc[] = "Configuration_Table[CONF_TABLE_ADC][";//
const uint8_t txt_adc_bracket[] = "] = ";                                     //
const uint8_t txt_adc_hyst[] = "HYST =";                                      //
const uint8_t txt_adc_can_buffer_adc[] = "CAN_Buffer[CAN_BUFFER_TABLE_ADC]["; //
const uint8_t txt_adc_adc_init[] = "ADC_Init();";                             //
const uint8_t txt_adc_read[] = "Module_ADC_Read();";                          //
const uint8_t txt_adc_result[] = "ADC Result;";                               //
const uint8_t txt_adc_buffer[] = "ADC_Buffer[";                               //
                                                                              //


/*____________________________________________________________________________*/
/*                            Functions - MAINS                               */
/*____________________________________________________________________________*/


/******************************************************************************/
/*******************************  ADC SET  ************************************/
/******************************************************************************/
/* ADC_SET -------------------------------------------------------------------*/
/*                                                                            //
    Sets ADC channels enabled in Configuration_Table:                         //
      + if config byte is 0xFF, ADC channel in disabled                       //
        otherwise channel is enabled and value is interpreted as              //
       hysteresis - propotional to full range                                 //
      + Ref+ = AVdd pin                                                       //
      + Ref- = AVss pin                                                       //
                                                                              //
    ADC available inputs:                                                     //
      + PA0: ADC_IN0                                                          //
      + PA1: ADC_IN1                                                          //
      + PA2: ADC_IN2                                                          //
      + PA3: ADC_IN3                                                          //
      + PA4: ADC_IN4                                                          //
      + PA5: ADC_IN5                                                          //
      + PA6: ADC_IN6                                                          //
      + PA7: ADC_IN7                                                          //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + none                                                                  //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //

                                                                                  /********** DEBUG ****************************/
void ADC_SET(){
  uint16_t MASK = 0;
  uint8_t i = 0;

  /* Check which ADC channels are enabled and write MASK */
  for(i=0; i<8; i++){
    if(Configuration_Table[CONF_TABLE_ADC][i] < 255) MASK = MASK | (1<<i);
  }
                                                                                  if(ADC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_adc_adc_set);
                                                                                    UART1_Write_Text(txt_adc_new_line);
                                                                                    UART1_Write_Text(txt_adc_adc_init_mask);
                                                                                    Debug_WordToStr(MASK);
                                                                                    UART1_Write_Text(txt_adc_new_line);
                                                                                    UART1_Write_Text(txt_adc_new_line);
                                                                                  }
  /* Initialize ADC channels based on MASK */
  Module_ADC_Init(MASK);
}


/******************************************************************************/
/*******************************  ADC GET  ************************************/
/******************************************************************************/
/* ADC_GET() -----------------------------------------------------------------*/
/*                                                                            //
    Gets results from enabled ADC module (see ADC_SET) and writes them        //
    in to CAN_Buffer:                                                         //
      + encalculates hysteresis - if change in ADC result is lower than       //
        hysteresis result is not updated                                      //
      + ADC_Buffer stores 12 bit results, while CAN_Buffer stores             //
        higher 8 bits                                                         //
      + hysteresis is based on range of CAN_Buffer 8-bit values               //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + none                                                                  //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //

void ADC_GET(){
  uint16_t HYST = 0;
  uint8_t i;
  uint16_t tmp;

                                                                                  if(ADC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_adc_adc_get);
                                                                                    UART1_Write_Text(txt_adc_new_line);
                                                                                  }
  
  for(i=0; i<8; i++){
    
    /* Check if appropriate ADC channel is enabled (not 255) */
    if(Configuration_Table[CONF_TABLE_ADC][i] < 255){

      /* Get hysteresis from configuration table and shift to match 12 bit result */
      HYST = Configuration_Table[CONF_TABLE_ADC][i]<<4;
      
      /* Update ADC result if ADC sample is larger than HYST */
      Module_ADC_Read(i, HYST);

      /* Shift ADC result to match 8 bit CAN buffer */
      tmp = ADC_Buffer[i] >> 4;
      
      /* Write 8 bit ADC value to CAN buffer */
      CAN_Buffer[CAN_TX_BUFFER_TABLE_ADC][i] = (uint8_t)tmp;

                                                                                  if(ADC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_adc_conf_table_adc);
                                                                                    Debug_WordToStr(i);
                                                                                    UART1_Write_Text(txt_adc_bracket);
                                                                                    Debug_WordToStr(Configuration_Table[CONF_TABLE_ADC][i]);
                                                                                    UART1_Write_Text(txt_adc_new_line);

                                                                                    UART1_Write_Text(txt_adc_hyst);
                                                                                    Debug_WordToStr(HYST);
                                                                                    UART1_Write_Text(txt_adc_new_line);

                                                                                    UART1_Write_Text(txt_adc_can_buffer_adc);
                                                                                    Debug_WordToStr(i);
                                                                                    UART1_Write_Text(txt_adc_bracket);
                                                                                    Debug_WordToStr(CAN_Buffer[CAN_TX_BUFFER_TABLE_ADC][i]);
                                                                                    UART1_Write_Text(txt_adc_new_line);
                                                                                    UART1_Write_Text(txt_adc_new_line);
                                                                                  }
    }
  }

                                                                                  if(ADC_Debug_Mode()) UART1_Write_Text(txt_adc_new_line);
}

/*____________________________________________________________________________*/
/*                            Functions - SUBS                                */
/*____________________________________________________________________________*/


/******************************************************************************/
/*************************  MODULE ADC INIT  **********************************/
/******************************************************************************/
/* Module_ADC_Init(uint16_t input_mask) --------------------------------------*/
/*                                                                            //
    Initialize ADC module:                                                    //
      + uses MikroC build-in libs                                             //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + uint16_t input_mask :                                                 //
        - ADC inputs enable mask:                                             //
          > B0: ADC input channel 0                                           //
          > ...                                                               //
          > B15: ADC input channel 15                                         //
        - 1 : channel enabled                                                 //
        - 0 : channel disabled                                                //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //

void Module_ADC_Init(uint16_t input_mask){
 
  /* Configure ADC inputs */
  ADC_Set_Input_Channel(input_mask);
  
  /* Initialize ADC periph. */
  ADC1_Init();
                                                                                 if(ADC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_adc_adc_init);
                                                                                    UART1_Write_Text(txt_adc_new_line);
                                                                                  }
}


/******************************************************************************/
/*************************  MODULE ADC READ  **********************************/
/******************************************************************************/
/* Module_ADC_Read(uint16_t input, uint16_t hysteresis) ----------------------*/
/*                                                                            //
    Reads 12-bit ADC results:                                                 //
      + uses MikroC build-in libs                                             //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + uint16_t input :                                                      //
        - channel number:                                                     //
          > 0: ADC input channel 0                                            //
          > ...                                                               //
          > B15: ADC input channel 15                                         //
                                                                              //
      + uint16_t hysteresis :
        - 12-bit hysteresis                                                   //
        - if difference between prev. ADC_Buffer[x] result and new on is      //
          smaller than hysteresis, ADC_Buffer[x] is not updated               //
          and vice versa                                                      //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //

void Module_ADC_Read(uint16_t input, uint16_t hysteresis){
  uint16_t ADC_Read_Result = 0;
  uint16_t i=0;

  /* Get sample from AD input */
  ADC_Read_Result = ADC1_Get_Sample(input);

  /* Calculate difference for hysteresis */
  if(ADC_Read_Result<=ADC_Buffer[input])i = ADC_Buffer[input] - ADC_Read_Result;
  else i = ADC_Read_Result - ADC_Buffer[input];

  /* if ADC result > hysteresis -> update ADC_Buffer */
  if(i > hysteresis) ADC_Buffer[input] = ADC_Read_Result;

                                                                                  if(ADC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_adc_read);
                                                                                    UART1_Write_Text(txt_adc_new_line);

                                                                                    UART1_Write_Text(txt_adc_result);
                                                                                    Debug_WordToStr(ADC_Read_Result);
                                                                                    UART1_Write_Text(txt_adc_new_line);

                                                                                    UART1_Write_Text(txt_adc_buffer);
                                                                                    Debug_WordToStr(input);
                                                                                    UART1_Write_Text(txt_adc_bracket);
                                                                                    Debug_WordToStr(ADC_Buffer[input]);
                                                                                    UART1_Write_Text(txt_adc_new_line);
                                                                                  }
}


/******************************************************************************/
/**************************  ADC DEBUG MODE  **********************************/
/******************************************************************************/
/* ADC_Debug_Mode() ----------------------------------------------------------*/
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

uint8_t ADC_Debug_Mode(){

  /* Check if ADC UART debugging is enabled */
  if(Configuration_Table[CONF_TABLE_DEBUG][CONF_TABLE_DEBUG_MASK1] & 0B0000000000000001) return 1;
  else return 0;
}
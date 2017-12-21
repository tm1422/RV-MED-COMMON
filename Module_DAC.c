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
#include <Module_DAC.h>                                                       //
                                                                              //
                                                                              
/* Declarations --------------------------------------------------------------*/
                                                                              //
// Enabled flags                                                              //
uint8_t _MODULE_DAC1_ENABLED = 0;                                             //
uint8_t _MODULE_DAC2_ENABLED = 0;                                             //
uint8_t _MODULE_DAC_DUAL_MODE_ENABLED = 0;                                    //
                                                                              //
// ADC debug txt                                                              //
const uint8_t txt_dac_new_line[] = "\r\n";                                    //
const uint8_t txt_dac_DAC_SET[] = "DAC_SET();";                               //
const uint8_t txt_dac_DAC_DUAL_MODE_ENABLE[] = "_DAC_DUAL_MODE_ENABLE";       //
const uint8_t txt_dac_DAC_CH1_ENABLE[] = "_DAC_CH1_ENABLE";                   //
const uint8_t txt_dac_DAC_CH2_ENABLE[] = "_DAC_CH2_ENABLE";                   //
const uint8_t txt_dac_DAC_SET_OUTPUT[] = "DAC_SET_OUTPUT();";                 //
const uint8_t txt_dac_h1[] = "h1 = ";                                         //
const uint8_t txt_dac_h2[] = "h2 = ";                                         //
const uint8_t txt_dac_l1[] = "l1 = ";                                         //
const uint8_t txt_dac_l2[] = "l2 = ";                                         //
const uint8_t txt_dac_r1[] = "r1 = ";                                         //
const uint8_t txt_dac_r2[] = "r2 = ";                                         //
const uint8_t txt_dac_DAC_DUAL_MODE_output_set[] = "_DAC_DUAL_MODE output set";//
const uint8_t txt_dac_DAC_CH1_output_set[] = "_DAC_CH1 output set";           //
const uint8_t txt_dac_DAC_CH2_output_set[] = "_DAC_CH2 output set";           //
                                                                              //
                                                                              


/*____________________________________________________________________________*/
/*                            Functions - MAINS                               */
/*____________________________________________________________________________*/


/******************************************************************************/
/*******************************  DAC SET  ************************************/
/******************************************************************************/
/* DAC_SET -------------------------------------------------------------------*/
/*                                                                            //
    Initialises DAC channels enabled in Configuration_Table.                  //
    Available chanels:                                                        //
      + DAC 1 CHANNEL 1                                                       //
      + DAC 1 CHANNEL 2                                                       //
      + DUAL CHANNEL MODE                                                     //
                                                                              //
      Ref+ = AVdd pin                                                         //
      Ref- = AVss pin                                                         //
                                                                              //
      DAC outputs:                                                            //
                                                                              //
      PA4: DAC_OUT1                                                           //
      PA5: DAC_OUT2                                                           //
                                                                              //
    Uses MIkroC build-in libs                                                 //
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



void DAC_SET(){                                                                   
                                                                                  if(DAC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_dac_DAC_SET);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                  }
  
  /* Get enable flags for use in DAC library */
  DAC_Get_Enabled_DACs();

  /* Check if DAC dual Mode is enabled) */
  if(_MODULE_DAC_DUAL_MODE_ENABLED){
    
    /* Initialise DAC dual mode
       _DAC_12_BIT : 12-bit DAC mode
       _DAC_TRIGGER_SW : DAC triggered by software
       _DAC_RIGHT_ALIGN : 12-bit data for DAC is right alligned
    */
    DAC1_Init(_DAC_DUAL_MODE_ENABLE);
                                                                                  if(DAC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_dac_DAC_DUAL_MODE_ENABLE);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                  }
  }
  
  /* Check if DAC1 is enabled) */
  if(_MODULE_DAC1_ENABLED){

    /* Initialise DAC channel 1 */
    DAC1_Init(_DAC_CH1_ENABLE);
                                                                                  if(DAC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_dac_DAC_CH1_ENABLE);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                  }
  }
  
  /* Check if DAC2 is enabled) */
  if(_MODULE_DAC2_ENABLED) {
    
    /* Initialise DAC channel 2 */
    DAC1_Init(_DAC_CH2_ENABLE);
                                                                                  if(DAC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_dac_DAC_CH2_ENABLE);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                  }
  }
                                                                                  if(DAC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                  }
}


/******************************************************************************/
/**************************  DAC SET OUTPUT ***********************************/
/******************************************************************************/
/* DAC SET OUTPUT ------------------------------------------------------------*/
/*                                                                            //
    Sets DAC channels enabled in Configuration_Table. Available chanels:      //
      + DAC 1 CHANNEL 1                                                       //
      + DAC 1 CHANNEL 2                                                       //
      + DUAL CHANNEL MODE                                                     //
                                                                              //
      Ref+ = AVdd pin                                                         //
      Ref- = AVss pin                                                         //
                                                                              //
      DAC outputs:                                                            //
                                                                              //
      PA4: DAC_OUT1                                                           //
      PA5: DAC_OUT2                                                           //
                                                                              //
    Uses MIkroC build-in libs                                                 //
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

void DAC_SET_OUTPUT(){
  uint32_t h1, h2, l1, l2, r1, r2;

    /* Get higher 4 bits from configuration table */
    h1 = Configuration_Table[CONF_TABLE_DAC][CONF_TABLE_DAC_CH1_H];
    
    /* Get lower 8 bits from configuration table */
    l1 = Configuration_Table[CONF_TABLE_DAC][CONF_TABLE_DAC_CH1_L];
    
    /* Get higher 4 bits from configuration table */
    h2 = Configuration_Table[CONF_TABLE_DAC][CONF_TABLE_DAC_CH2_H];
    
    /* Get lower 8 bits from configuration table */
    l2 = Configuration_Table[CONF_TABLE_DAC][CONF_TABLE_DAC_CH2_L];
    
    /* Calculate 12-bit ADC value for channel 1 from above data */
    r1 = h1<<8 | l1;
    
    /* Calculate 12-bit ADC value for channel 2 from above data */
    r2 = h2<<8 | l2;
                                                                                  if(DAC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_dac_DAC_SET);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                    UART1_Write_Text(txt_dac_h1);
                                                                                    Debug_WordToStr(h1);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                    UART1_Write_Text(txt_dac_l1);
                                                                                    Debug_WordToStr(l1);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                    UART1_Write_Text(txt_dac_h2);
                                                                                    Debug_WordToStr(h2);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                    UART1_Write_Text(txt_dac_l2);
                                                                                    Debug_WordToStr(l2);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                    UART1_Write_Text(txt_dac_r1);
                                                                                    Debug_WordToStr(r1);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                    UART1_Write_Text(txt_dac_r2);
                                                                                    Debug_WordToStr(r2);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                  }

  /* Check if DAC dual Mode is enabled) */
  if(_MODULE_DAC_DUAL_MODE_ENABLED){

    /* Initialise DAC dual mode outputs
       _DAC_12_BIT : 12-bit DAC mode
       _DAC_TRIGGER_SW : DAC triggered by software
       _DAC_RIGHT_ALIGN : 12-bit data for DAC is right alligned
    */
    DAC1_Dual_Output(r1, r2, _DAC_12_BIT | _DAC_TRIGGER_SW | _DAC_RIGHT_ALIGN, _DAC_12_BIT | _DAC_TRIGGER_SW | _DAC_RIGHT_ALIGN);
    
                                                                                  if(DAC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_dac_DAC_DUAL_MODE_output_set);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                  }
    
  }
    
  /* Check if DAC channel 1 is enabled) */
  if(_MODULE_DAC1_ENABLED) {
    
    /* Initialise DAC channel 1 output
       _DAC_12_BIT : 12-bit DAC mode
       _DAC_TRIGGER_SW : DAC triggered by software
       _DAC_RIGHT_ALIGN : 12-bit data for DAC is right alligned
    */
    DAC1_Advanced_Ch1_Output(r1, _DAC_12_BIT | _DAC_TRIGGER_SW | _DAC_RIGHT_ALIGN);
    
                                                                                  if(DAC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_dac_DAC_CH1_output_set);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                  }
    
  }
  
  /* Check if DAC channel 2 is enabled) */
  if(_MODULE_DAC2_ENABLED) {
    
    /* Initialise DAC channel 2 output
       _DAC_12_BIT : 12-bit DAC mode
       _DAC_TRIGGER_SW : DAC triggered by software
       _DAC_RIGHT_ALIGN : 12-bit data for DAC is right alligned
    */
    DAC1_Advanced_Ch2_Output(r2, _DAC_12_BIT | _DAC_TRIGGER_SW | _DAC_RIGHT_ALIGN);
    
                                                                                  if(DAC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_dac_DAC_CH2_output_set);
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                  }
    
  }
                                                                                  if(DAC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_dac_new_line);
                                                                                  }
}




/*____________________________________________________________________________*/
/*                            Functions - SUBS                                */
/*____________________________________________________________________________*/


/******************************************************************************/
/**************************  DAC GET ENABLED DACs  ****************************/
/******************************************************************************/
/* DAC_Get_Enabled_DACs() ----------------------------------------------------*/
/*                                                                            //
    Checks configuration table for enabled DACs and store "flags" to          //
    _DACx_ENABLED ints                                                         //
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

void DAC_Get_Enabled_DACs(){
  
  /* Check if DAC dual Mode is enabled) */
  if((Configuration_Table[CONF_TABLE_DAC][CONF_TABLE_DAC_ENABLE] & 0B0000000000001000) ||
     ((Configuration_Table[CONF_TABLE_DAC][CONF_TABLE_DAC_ENABLE] & 0B0000000000000001) &&
     Configuration_Table[CONF_TABLE_DAC][CONF_TABLE_DAC_ENABLE] & 0B0000000000000010)){

     /* Write dual mode enable flag */
     _MODULE_DAC_DUAL_MODE_ENABLED = 1;
     
     /* Clear flags if dual mode is enabled */
     _MODULE_DAC1_ENABLED = 0;
     _MODULE_DAC2_ENABLED = 0;
  }
  else{

    /* Check if DAC channel 1 is enabled) */
    if(Configuration_Table[CONF_TABLE_DAC][CONF_TABLE_DAC_ENABLE] & 0B0000000000000001) {

      /* Write DAC1 enable flag */
      _MODULE_DAC1_ENABLED = 1;
    }

    /* Check if DAC channel 2 is enabled) */
    if(Configuration_Table[CONF_TABLE_DAC][CONF_TABLE_DAC_ENABLE] & 0B0000000000000010) {

      /* Write DAC2 enable flag */
      _MODULE_DAC2_ENABLED = 1;
    }
    
    /* Clear dual mode flag */
    _MODULE_DAC_DUAL_MODE_ENABLED = 0;
  }
}

/******************************************************************************/
/**************************  DAC DEBUG MODE  **********************************/
/******************************************************************************/
/* DAC_Debug_Mode() ----------------------------------------------------------*/
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

uint8_t DAC_Debug_Mode(){
  
  /* Check if DAC UART debugging is enabled */
  if(Configuration_Table[CONF_TABLE_DEBUG][CONF_TABLE_DEBUG_MASK1] & 0B0000000000000100) return 1;
  else return 0;
}
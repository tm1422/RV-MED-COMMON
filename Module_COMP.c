/**
  ******************************************************************************
  * @file    Module_ADC.c
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    16-August-2017
  * @last    13-December-2017
  * @brief   This file provides functions to manage the following
  *          functionalities of the COMP on Medicop STM32F072 CAN Modules:
  *           + ADC initialization via external configuration table mask
  *           + get ADC results vai external configuration table mask
  *           + ADC debug mode
  *
*/


/* Includes ------------------------------------------------------------------*/
#include <Module_COMP.h>

/* Declarations --------------------------------------------------------------*/
                                                                              //
// Enabled flags                                                              //
uint8_t _MODULE_COMP1_ENABLED = 0;                                            //
uint8_t _MODULE_COMP2_ENABLED = 0;                                            //
uint8_t _MODULE_WINDOW_MODE_ENABLED = 0;                                      //
uint8_t _MODULE_COMP1_OUTPUT_POLARITY = 0;                                    //
uint8_t _MODULE_COMP2_OUTPUT_POLARITY = 0;                                    //
                                                                              //
// COMP Structure                                                             //
COMP_InitTypeDef Module_COMP_Init_Struct;                                     //
                                                                              //
// COMP debug txt                                                             //
const uint8_t txt_comp_new_line[] = "\r\n";                                   //
                                                                              //
const uint8_t txt_comp_COMP_SET[] = "COMP_SET();";                            //
const uint8_t txt_comp_Enable_COMP1[] = "Enable COMP1";                       //
const uint8_t txt_comp_COMP1_output_select[] = "COMP1 output select: ";       //
const uint8_t txt_comp_COMP2_output_select[] = "COMP2 output select: ";       //
const uint8_t txt_comp_COMP_Output_TIM3OCREFCLR[] = "COMP_Output_TIM3OCREFCLR";//
const uint8_t txt_comp_COMP_Output_TIM3IC1[] = "COMP_Output_TIM3IC1";         //
const uint8_t txt_comp_COMP_Output_TIM2OCREFCLR[] = "COMP_Output_TIM2OCREFCLR";//
const uint8_t txt_comp_COMP_Output_TIM2IC4[] = "COMP_Output_TIM2IC4";         //
const uint8_t txt_comp_COMP_Output_TIM1OCREFCLR[] = "COMP_Output_TIM1OCREFCLR";//
const uint8_t txt_comp_COMP_Output_TIM1IC1[] = "OMP_Output_TIM1IC1";          //
const uint8_t txt_comp_COMP_Output_TIM1BKIN[] = "COMP_Output_TIM1BKIN";       //
const uint8_t txt_comp_COMP_Output_None[] = "COMP_Output_None";               //
const uint8_t txt_comp_COMP1_mode_select[] = "COMP1 mode select: ";           //
const uint8_t txt_comp_COMP2_mode_select[] = "COMP2 mode select: ";           //
const uint8_t txt_comp_COMP_Mode_UltraLowPower[] = "COMP_Mode_UltraLowPower"; //
const uint8_t txt_comp_COMP_Mode_LowPower[] = "COMP_Mode_LowPower";           //
const uint8_t txt_comp_COMP_Mode_MediumSpeed[] = "COMP_Mode_MediumSpeed";     //
const uint8_t txt_comp_COMP_Mode_HighSpeed[] = "COMP_Mode_HighSpeed";         //
const uint8_t txt_comp_COMP1_hysteresis[] = "COMP1 hysteresis: ";             //
const uint8_t txt_comp_COMP_Hysteresis_High[] = "COMP_Hysteresis_High";       //
const uint8_t txt_comp_COMP_Hysteresis_Medium[] = "COMP_Hysteresis_Medium";   //
const uint8_t txt_comp_COMP_Hysteresis_Low[] = "COMP_Hysteresis_Low";         //
const uint8_t txt_comp_COMP_Hysteresis_No[] = "COMP_Hysteresis_No";           //
const uint8_t txt_comp_COMP1_inverting_input_select[] = "COMP1 inverting input select: ";//
const uint8_t txt_comp_COMP_InvertingInput_IO[] = "COMP_InvertingInput_IO";   //
const uint8_t txt_comp_COMP_InvertingInput_DAC2[] = "COMP_InvertingInput_DAC2";//
const uint8_t txt_comp_COMP_InvertingInput_DAC1[] = "COMP_InvertingInput_DAC1";//
const uint8_t txt_comp_COMP_InvertingInput_VREFINT[] = "COMP_InvertingInput_VREFINT";//
const uint8_t txt_comp_COMP_InvertingInput_3_4VREFINT[] = "COMP_InvertingInput_3_4VREFINT";//
const uint8_t txt_comp_COMP_InvertingInput_1_2VREFINT[] = "COMP_InvertingInput_1_2VREFINT";//
const uint8_t txt_comp_COMP_InvertingInput_1_4VREFINT[] = "COMP_InvertingInput_1_4VREFINT";//
const uint8_t txt_comp_Enable_COMP2[] = "Enable COMP2";                       //
const uint8_t txt_comp_COMP2_hysteresis[] = "COMP2 hysteresis: ";             //
const uint8_t txt_comp_COMP2_inverting_input_select[] = "COMP2 inverting input select: ";//
const uint8_t txt_comp_Window_mode_enabled[] = "Window mode enabled";         //
                                                                              //
const uint8_t txt_comp_COMP_GetOutput[] = "COMP_GetOutput();";                //
const uint8_t txt_comp_Result[] = "Result = ";                                //
                                                                              //
const uint8_t txt_comp_COMP_GET[] = "COMP_GET();";                            //
const uint8_t txt_comp_CAN_Buffer[] = "CAN_Buffer[CAN_BUFFER_TABLE_COMP][";   //
const uint8_t txt_comp_bracket[] = "] = ";                                    //
const uint8_t txt_comp_1[] = "1";                                             //
const uint8_t txt_comp_0[] = "0";                                             //
                                                                              //




/*____________________________________________________________________________*/
/*                            Functions - MAINS                               */
/*____________________________________________________________________________*/


/******************************************************************************/
/*******************************  COMP SET  ***********************************/
/******************************************************************************/
/* COMP_SET() ----------------------------------------------------------------*/
/*                                                                            //
    Initialize COMP module as defined in Configuration Table:                 //
                                                                              //
                                                                              //
      CONF_TABLE_COMP_SETT:                                                   //
        B0: COMP1 ENABLE                                                      //
        B1: COMP2 ENABLE                                                      //
        B3: WINDOWS MODE ENABLE                                               //
        B4: COMP1_OUT_POL                                                     //
        B5: COMP2_OUT_POL                                                     //
                                                                              //
      CONF_TABLE_COMP1_SETT1:                                                 //
        bit<3:0> = Comp_Output                                                //
        bit<7:4> = Comp_Mode                                                  //
                                                                              //
      CONF_TABLE_COMP1_SETT2:                                                 //
        bit<3:0> = Comp_Hysteresis                                            //
        bit<7:4> = Invert_Input_Select                                        //
                                                                              //
      CONF_TABLE_COMP2_SETT1:                                                 //
        bit<3:0> = Comp_Output                                                //
        bit<7:4> = Comp_Mode                                                  //
                                                                              //
      CONF_TABLE_COMP2_SETT2:                                                 //
        bit<3:0> = Comp_Hysteresis                                            //
        bit<7:4> = Invert_Input_Select                                        //
                                                                              //
                                                                              //
    Values:                                                                   //
                                                                              //
       OOMPx OUTPUT POLARITY                                                  //
        0: OUTPUT IS NON INVERTED                                             //
        1: OUTPUT IS INVERTED                                                 //
                                                                              //
       OOMPx HISTERESYS                                                       //
        0: NO HISTERESYS                                                      //
        1: LOW HISTERESYS                                                     //
        2: MEDIUM HISTERESYS                                                  //
        3: HIGH HISTERESYS                                                    //
                                                                              //
       COMPx MODE                                                             //
        0: HIGH SPEED                                                         //
        1: MEDIUM SPEED                                                       //
        2: LOW SPEED                                                          //
        3: VERY LOW SPEED                                                     //
                                                                              //
       COMPx ENABLE                                                           //
        0: DISABLED                                                           //
        1: ENABLED                                                            //
                                                                              //
       COMP WINDOWS MODE ENABLE                                               //
        0: DISABLED                                                           //
        1: ENABLED                                                            //
                                                                              //
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
void COMP_SET(){
  uint32_t _out_pol, _out, _mode, _hys, _inv_in;
                                                                                  if(COMP_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_comp_COMP_SET);
                                                                                    UART1_Write_Text(txt_comp_new_line);
                                                                                  }
  /* Check COMP1 enable flag */
  if(_MODULE_COMP1_ENABLED){

                                                                                  if(COMP_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_comp_Enable_COMP1);
                                                                                    UART1_Write_Text(txt_comp_new_line);
                                                                                  }
      /* Get COMP1 Output polarity from configuration table */
      if(Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP_SETT] & 0B0000000000010000) _out_pol = COMP_OutputPol_Inverted;
      else _out_pol = COMP_OutputPol_NonInverted;

                                                                                  if(COMP_Debug_Mode()) UART1_Write_Text(txt_comp_COMP1_output_select);

      /* Get COMP1 Output from configuration table */
      _out = COMP_Get_Output_Selection(Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP1_SETT1] & 0B0000000000001111);

                                                                                  if(COMP_Debug_Mode()) UART1_Write_Text(txt_comp_COMP1_mode_select);

      /* Get COMP1 Mode from configuration table */
      _mode = COMP_Get_Mode((Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP1_SETT1] & 0B0000000011110000) >> 4);
      
                                                                                  if(COMP_Debug_Mode()) UART1_Write_Text(txt_comp_COMP1_hysteresis);
      
      /* Get COMP1 Hysteresis from configuration table */
      _hys = COMP_Get_Hysteresis(Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP1_SETT2] & 0B0000000000001111);

                                                                                  if(COMP_Debug_Mode()) UART1_Write_Text(txt_comp_COMP1_inverting_input_select);

      /* Get COMP1 Inverting Input from configuration table */
      _inv_in = COMP_Get_Inverting_Input((Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP1_SETT2] & 0B0000000011110000) >> 4);

   /* Initialize COMP2 based on data from configuration table */
   Module_COMPx_Init(COMP_Selection_COMP1, _inv_in, _out, _out_pol, _hys, _mode);
  }

  /* Check COMP1 enable flag */
  if(_MODULE_COMP2_ENABLED){

                                                                                  if(COMP_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_comp_Enable_COMP2);
                                                                                    UART1_Write_Text(txt_comp_new_line);
                                                                                  }

      /* Get COMP2 Output polarity from configuration table */
      if(Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP_SETT] & 0B0000000000100000) _out_pol = COMP_OutputPol_Inverted;
      else _out_pol = COMP_OutputPol_NonInverted;

                                                                                  if(COMP_Debug_Mode()) UART1_Write_Text(txt_comp_COMP2_output_select);

      /* Get COMP2 Output from configuration table */
      _out = COMP_Get_Output_Selection(Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP2_SETT1] & 0B0000000000001111);

                                                                                  if(COMP_Debug_Mode()) UART1_Write_Text(txt_comp_COMP2_mode_select);

      /* Get COMP2 Mode from configuration table */
      _mode = COMP_Get_Mode((Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP2_SETT1] & 0B0000000011110000) >> 4);

                                                                                  if(COMP_Debug_Mode()) UART1_Write_Text(txt_comp_COMP2_hysteresis);
      
      /* Get COMP2 Hysteresis from configuration table */
      _hys = COMP_Get_Hysteresis(Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP2_SETT2] & 0B0000000000001111);

                                                                                  if(COMP_Debug_Mode()) UART1_Write_Text(txt_comp_COMP2_inverting_input_select);
      
      /* Get COMP2 Inverting Input from configuration table */
      _inv_in = COMP_Get_Inverting_Input((Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP2_SETT2] & 0B0000000011110000) >> 4);

   /* Initialize COMP2 based on data from configuration table */
   Module_COMPx_Init(COMP_Selection_COMP2, _inv_in, _out, _out_pol, _hys, _mode);
  }

  if(_MODULE_WINDOW_MODE_ENABLED){
    
    /* Enable comparator window mode */
    Module_COMP_Window_Mode_Enable(1);

                                                                                  if(COMP_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_comp_Window_mode_enabled);
                                                                                    UART1_Write_Text(txt_comp_new_line);
                                                                                  }

  }
                                                                                  if(COMP_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_comp_new_line);
                                                                                  }
}


/******************************************************************************/
/*******************************  COMP GET  ***********************************/
/******************************************************************************/
/* COMP_GET() ----------------------------------------------------------------*/
/*                                                                            //
    Gets results from enabled COMP modules (see COMP_SET) and writes them     //
    in to CAN_Buffer                                                          //
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

void COMP_GET(){

                                                                                  if(COMP_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_comp_COMP_GET);
                                                                                    UART1_Write_Text(txt_comp_new_line);
                                                                                  }

  /* Check if COMP1 is enabled */
  if(_MODULE_COMP1_ENABLED) {
    
    /* Get comparator 1 output and store it in CAN buffer */
    if(Module_COMP_GetOutput(COMP_Selection_COMP1)) CAN_Buffer[CAN_TX_BUFFER_TABLE_COMP][0] = 0B00000001;
    else CAN_Buffer[CAN_TX_BUFFER_TABLE_COMP][0] = 0;
                                                                                  if(COMP_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_comp_CAN_Buffer);
                                                                                    UART1_Write_Text(txt_comp_0);
                                                                                    UART1_Write_Text(txt_comp_bracket);
                                                                                    Debug_WordToStr(CAN_Buffer[CAN_TX_BUFFER_TABLE_COMP][0]);
                                                                                    UART1_Write_Text(txt_comp_new_line);
                                                                                  }
  }
  if(_MODULE_COMP2_ENABLED) {
    
    /* Get comparator 2 output and store it in CAN buffer */
    if(Module_COMP_GetOutput(COMP_Selection_COMP2)) CAN_Buffer[CAN_TX_BUFFER_TABLE_COMP][1] = 0B00000001;
    else CAN_Buffer[CAN_TX_BUFFER_TABLE_COMP][1] = 0;
                                                                                  if(COMP_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_comp_CAN_Buffer);
                                                                                    UART1_Write_Text(txt_comp_1);
                                                                                    UART1_Write_Text(txt_comp_bracket);
                                                                                    Debug_WordToStr(CAN_Buffer[CAN_TX_BUFFER_TABLE_COMP][1]);
                                                                                    UART1_Write_Text(txt_comp_new_line);
                                                                                  }
  }
                                                                                  if(COMP_Debug_Mode()) UART1_Write_Text(txt_comp_new_line);
}



/*____________________________________________________________________________*/
/*                            Functions - SUBS                                */
/*____________________________________________________________________________*/


/******************************************************************************/
/*********************** COMP GET OUTPUT SELECTION ****************************/
/******************************************************************************/
/* COMP_Get_Output_Selection() -----------------------------------------------*/
/*                                                                            //
    Checks input for selected output                                          //
    and returns value defined in STM SPL comp Lib                             //
                                                                              //
       COMPx OUTPUT SELECTION                                                 //
        0: No output                                                          //
        1: TIM1BKIN                                                           //
        2: TIM1IC1                                                            //
        3: TIM1OCREFCLR                                                       //
        4: TIM2IC4                                                            //
        5: TIM2OCREFCLR                                                       //
        6: TIM3IC1                                                            //
        7: TIM3OCREFCLR                                                       //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + input variable (0-7)                                                  //
                                                                              //
    RETURN VALUES:                                                            //
                                                                              //
      + Output selection                                                      //
        - COMP_Output_None                                                    //
        - COMP_Output_TIM1BKIN                                                //
        - COMP_Output_TIM1IC1                                                 //
        - COMP_Output_TIM1OCREFCLR                                            //
        - COMP_Output_TIM2IC4                                                 //
        - COMP_Output_TIM2OCREFCLR                                            //
        - COMP_Output_TIM3IC1                                                 //
        - COMP_Output_TIM3OCREFCLR                                            //
    ______________________________________                                    //
*/

uint32_t COMP_Get_Output_Selection(uint16_t tmp){
  uint32_t _out = 0;
  
  switch(tmp){
    case 7: _out = COMP_Output_TIM3OCREFCLR;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Output_TIM3OCREFCLR);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
            break;
    case 6: _out = COMP_Output_TIM3IC1;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Output_TIM3IC1);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
            break;
    case 5: _out = COMP_Output_TIM2OCREFCLR;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Output_TIM2OCREFCLR);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
            break;
    case 4: _out = COMP_Output_TIM2IC4;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Output_TIM2IC4);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
            break;
    case 3: _out = COMP_Output_TIM1OCREFCLR;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Output_TIM1OCREFCLR);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
            break;
    case 2: _out = COMP_Output_TIM1IC1;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Output_TIM1IC1);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
            break;
    case 1: _out = COMP_Output_TIM1BKIN;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Output_TIM1BKIN);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
            break;
    case 0: _out = COMP_Output_None;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Output_None);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
            break;
    default: _out = COMP_Output_None; break;
  }
  
  return _out;
}


/******************************************************************************/
/*********************** COMP GET MODE ****************************************/
/******************************************************************************/
/* COMP_Get_Mode() -----------------------------------------------------------*/
/*                                                                            //
    Checks input for selected mode                                            //
    and returns value defined in STM SPL comp Lib                             //
                                                                              //
       COMPx MODE                                                             //
        0: HIGH SPEED                                                         //
        1: MEDIUM SPEED                                                       //
        2: LOW SPEED                                                          //
        3: VERY LOW SPEED                                                     //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + input variable (0-3)                                                  //
                                                                              //
    RETURN VALUES:                                                            //
                                                                              //
      + Mode selection                                                  //
        - COMP_Mode_HighSpeed                                                 //
        - COMP_Mode_MediumSpeed                                               //
        - COMP_Mode_LowPower                                                  //
        - COMP_Mode_UltraLowPower                                             //
    ______________________________________                                    //
*/

uint32_t COMP_Get_Mode(uint16_t tmp){
  uint32_t _mode = 0;
  
  switch(tmp){
    case 3: _mode = COMP_Mode_UltraLowPower;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Mode_UltraLowPower);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 2: _mode = COMP_Mode_LowPower;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Mode_LowPower);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 1: _mode = COMP_Mode_MediumSpeed;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Mode_MediumSpeed);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 0: _mode = COMP_Mode_HighSpeed;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Mode_HighSpeed);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    default: _mode = COMP_Mode_HighSpeed;
  }
  
  return _mode;
}


/******************************************************************************/
/*********************** COMP GET HYHSTERESIS *********************************/
/******************************************************************************/
/* COMP_Get_Hysteresis() -----------------------------------------------------*/
/*                                                                            //
    Checks input for selected hysteresis                                      //
    and returns value defined in STM SPL comp Lib                             //
                                                                              //
       OOMPx HISTERESYS                                                       //
        0: NO HISTERESYS                                                      //
        1: LOW HISTERESYS                                                     //
        2: MEDIUM HISTERESYS                                                  //
        3: HIGH HISTERESYS                                                    //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + input variable (0-3)                                                  //
                                                                              //
    RETURN VALUES:                                                            //
                                                                              //
      + Hysteresis selection                                                  //
        - COMP_Hysteresis_No                                                  //
        - COMP_Hysteresis_Low                                                 //
        - COMP_Hysteresis_Medium                                              //
        - COMP_Hysteresis_High                                                //
    ______________________________________                                    //
*/

uint32_t COMP_Get_Hysteresis(uint16_t tmp){
  uint32_t _hys = 0;
  
  switch(tmp){
    case 3: _hys = COMP_Hysteresis_High;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Hysteresis_High);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 2: _hys = COMP_Hysteresis_Medium;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Hysteresis_Medium);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 1: _hys = COMP_Hysteresis_Low;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Hysteresis_Low);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 0: _hys = COMP_Hysteresis_No;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_Hysteresis_No);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    default: _hys = COMP_Hysteresis_No; break;
  }
  
  return _hys;
}


/******************************************************************************/
/*********************** COMP GET INVERTING INPUT *****************************/
/******************************************************************************/
/* COMP_Get_Inverting_Input() ------------------------------------------------*/
/*                                                                            //
    Checks input for selected inverting input                                 //
    and returns value defined in STM SPL comp Lib                             //
                                                                              //
       COMPx AIN-:                                                            //
        0: Vrefint 1/4                                                        //
        1: Vrefint 1/2                                                        //
        2: Vrefint 3/4                                                        //
        3: Vrefint                                                            //
        4: PA4 - DAC_OUT1                                                     //
        5: PA5 - DAC_OUT2                                                     //
        6: PA2                                                                //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + input variable (0-6)                                                  //
                                                                              //
    RETURN VALUES:                                                            //
                                                                              //
      + Inverting input selection                                             //
        - COMP_InvertingInput_1_4VREFINT                                      //
        - COMP_InvertingInput_1_2VREFINT                                      //
        - COMP_InvertingInput_3_4VREFINT                                      //
        - COMP_InvertingInput_VREFINT                                         //
        - COMP_InvertingInput_DAC1                                            //
        - COMP_InvertingInput_DAC2                                            //
        - COMP_InvertingInput_IO                                              //
    ______________________________________                                    //
*/                                                                            //

uint32_t COMP_Get_Inverting_Input(uint16_t tmp){
  uint32_t _inv_in = 0;
  
  switch(tmp){
    case 6: _inv_in = COMP_InvertingInput_IO;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_InvertingInput_IO);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 5: _inv_in = COMP_InvertingInput_DAC2;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_InvertingInput_DAC2);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 4: _inv_in = COMP_InvertingInput_DAC1;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_InvertingInput_DAC1);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 3: _inv_in = COMP_InvertingInput_VREFINT;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_InvertingInput_VREFINT);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 2: _inv_in = COMP_InvertingInput_3_4VREFINT;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_InvertingInput_3_4VREFINT);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 1: _inv_in = COMP_InvertingInput_1_2VREFINT;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_InvertingInput_1_2VREFINT);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    case 0: _inv_in = COMP_InvertingInput_1_4VREFINT;
                                                                              if(COMP_Debug_Mode()){
                                                                                UART1_Write_Text(txt_comp_COMP_InvertingInput_1_4VREFINT);
                                                                                UART1_Write_Text(txt_comp_new_line);
                                                                              }
    break;
    default: _inv_in = COMP_InvertingInput_1_4VREFINT; break;
  }
  
  return _inv_in;
}


/******************************************************************************/
/**************************  COMP GET FLAGS  ***********************************/
/******************************************************************************/
/* COMP_Get_Flags() -----------------------------------------------------------*/
/*                                                                            //
    Checks configuration table for enabled comparators and inverted outputs   //
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

void COMP_Get_Flags(){

  /* Check if COMP1 is enabled) */
  if(Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP_SETT] & 0B0000000000000001){

    /* Write COMP1 enable flag */
    _MODULE_COMP1_ENABLED = 1;
  }
  else _MODULE_COMP1_ENABLED = 0;

  /* Check COMP2 is enabled) */
  if(Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP_SETT] & 0B0000000000000010){

    /* Write COMP2 enable flag */
    _MODULE_COMP2_ENABLED = 1;
  }
  else _MODULE_COMP2_ENABLED = 0;

  /* COMP WINDOW MODE is enabled) */
  if(Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP_SETT] & 0B0000000000000100){

    /* Write window mode enable flag */
    _MODULE_WINDOW_MODE_ENABLED = 1;
  }
  else _MODULE_WINDOW_MODE_ENABLED = 0;

  /* Check if COMP1 output is invertes) */
  if(Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP_SETT] & 0B0000000000001000){

    /* Write COMP1 output inverted flag */
    _MODULE_COMP1_OUTPUT_POLARITY = 1;
  }
  else _MODULE_COMP1_OUTPUT_POLARITY = 0;

  /* Check if COMP2 output is inverted) */
  if(Configuration_Table[CONF_TABLE_COMP][CONF_TABLE_COMP_SETT] & 0B0000000000010000){

    /* Write COMP2 output inverted flag */
    _MODULE_COMP2_OUTPUT_POLARITY = 1;
  }
  else _MODULE_COMP2_OUTPUT_POLARITY = 0;
}


/******************************************************************************/
/***************************  MODULE COMP INIT  *******************************/
/******************************************************************************/
/* Module_COMPx_Init ---------------------------------------------------------*/
/*                                                                            //
    Initialize comparator module(s).                                          //
    Uses STM SPL.                                                             //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + Comp_Select:                                                          //
        - COMP_Selection_COMP1                                                //
        - COMP_Selection_COMP2                                                //
                                                                              //
      + Invert_Input_Select:                                                  //
        - COMP_InvertingInput_1_4VREFINT                                      //
        - COMP_InvertingInput_1_2VREFINT                                      //
        - COMP_InvertingInput_3_4VREFINT                                      //
        - COMP_InvertingInput_VREFINT                                         //
        - COMP_InvertingInput_DAC1                                            //
        - COMP_InvertingInput_DAC2                                            //
        - COMP_InvertingInput_IO                                              //
                                                                              //
      + Comp_Output:                                                          //
        - COMP_Output_None                                                    //
        - COMP_Output_TIM1BKIN                                                //
        - COMP_Output_TIM1IC1                                                 //
        - COMP_Output_TIM1OCREFCLR                                            //
        - COMP_Output_TIM2IC4                                                 //
        - COMP_Output_TIM2OCREFCLR                                            //
        - COMP_Output_TIM3IC1                                                 //
        - COMP_Output_TIM3OCREFCLR                                            //
                                                                              //
      + Comp_Output_Pol:                                                      //
        - COMP_OutputPol_NonInverted                                          //
        - COMP_OutputPol_Inverted                                             //
                                                                              //
      + Comp_Hysteresis:                                                      //
        - COMP_Hysteresis_No                                                  //
        - COMP_Hysteresis_Low                                                 //
        - COMP_Hysteresis_Medium                                              //
        - COMP_Hysteresis_High                                                //
                                                                              //
      + Comp_Mode:                                                            //
        - COMP_Mode_HighSpeed                                                 //
        - COMP_Mode_MediumSpeed                                               //
        - COMP_Mode_LowPower                                                  //
        - COMP_Mode_UltraLowPower                                             //
                                                                              //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //


void Module_COMPx_Init(uint32_t Comp_Select, uint32_t Invert_Input_Select, uint32_t Comp_Output,
                       uint32_t Comp_Output_Pol, uint32_t Comp_Hysteresis, uint32_t Comp_Mode){

  /* Enable APB2 peripherial clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Check input data: comparator selection = COMP1 */
  if(Comp_Select == COMP_Selection_COMP1){
  
    /* Configure GPIOs for COMP1: 
         - Analog input enable
         - Alternate function enable
         - 50MHz speed limit
         - push-pull type GPIO
    
    */
    GPIO_Config(&GPIOA_BASE , _GPIO_PINMASK_1, _GPIO_CFG_ANALOG_INPUT);
    GPIO_Config(&GPIOA_BASE , _GPIO_PINMASK_0, _GPIO_CFG_MODE_ALT_FUNCTION | _GPIO_CFG_SPEED_50MHZ | _GPIO_CFG_OTYPE_PP);
    GPIO_Alternate_Function_Enable(&_GPIO_MODULE_COMP1_PA0);
  }
  
  /* Check input data: comparator selection = COMP2 */
  else if(Comp_Select == COMP_Selection_COMP2){
 
    /* Configure GPIOs for COMP2:
         - Analog input enable
         - Alternate function enable
         - 50MHz speed limit
         - push-pull type GPIO

    */
    GPIO_Config(&GPIOA_BASE , _GPIO_PINMASK_3, _GPIO_CFG_ANALOG_INPUT);
    GPIO_Config(&GPIOA_BASE , _GPIO_PINMASK_2, _GPIO_CFG_MODE_ALT_FUNCTION | _GPIO_CFG_SPEED_50MHZ | _GPIO_CFG_OTYPE_PP);
    GPIO_Alternate_Function_Enable(&_GPIO_MODULE_COMP2_PA2);
  }
  
  /* Write input data to comparator structure that is used by STM SPL comp Lib*/
  Module_COMP_Init_Struct.COMP_InvertingInput = Invert_Input_Select;
  Module_COMP_Init_Struct.COMP_Output = Comp_Output;
  Module_COMP_Init_Struct.COMP_OutputPol = Comp_Output_Pol;
  Module_COMP_Init_Struct.COMP_Hysteresis = Comp_Hysteresis;
  Module_COMP_Init_Struct.COMP_Mode = Comp_Mode;

  /* Initialize comparator based od input data and comparator structure */
  COMP_Init(Comp_Select, &Module_COMP_Init_Struct);

  /* Enable selected comparator */
  COMP_Cmd(Comp_Select, ENABLE);
                       
}



/******************************************************************************/
/*************************  MODULE COMP GET OUTPUT  ***************************/
/******************************************************************************/
/* Module_COMP_GetOutput(uint32_t Comp_Select) -------------------------------*/
/*                                                                            //
    Gets result of appropriate ADC channel                                    //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + Comp_Select:                                                          //
        COMP_Selection_COMP1:  comparator 1 selected                          //
        COMP_Selection_COMP2:  comparator 2 selected                          //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + COMP Result                                                           //
    ______________________________________                                    //
*/                                                                            //
uint32_t Module_COMP_GetOutput(uint32_t Comp_Select){
  uint32_t Result;
  
  /* Read COMP output level */
  Result = COMP_GetOutputLevel(Comp_Select);
                                                                                  if(COMP_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_comp_COMP_GetOutput);
                                                                                    UART1_Write_Text(txt_comp_new_line);
                                                                                    UART1_Write_Text(txt_comp_Result);
                                                                                    Debug_WordToStr(Result);
                                                                                    UART1_Write_Text(txt_comp_new_line);
                                                                                  }
  
  /* Return COMP output level '0' or '1' */
  return Result;
                                                                                  if(COMP_Debug_Mode()) UART1_Write_Text(txt_comp_new_line);
}


/******************************************************************************/
/***********************  MODULE COMP WINDOWS MODE ENABLE  ********************/
/******************************************************************************/
/* COMP_Debug_Mode() ---------------------------------------------------------*/
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

void Module_COMP_Window_Mode_Enable(uint8_t State){
  
  /* Check "State" and enable comparator dual mode if '1' */
  if(State) COMP_WindowCmd(ENABLE);
  
  /* Check "State" and disable comparator dual mode if '0' */
  else COMP_WindowCmd(DISABLE);
}


/******************************************************************************/
/**************************  COMP DEBUG MODE  *********************************/
/******************************************************************************/
/* COMP_Debug_Mode() ---------------------------------------------------------*/
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

uint8_t COMP_Debug_Mode(){
  
  /* Check if COMP UART debugging is enabled */
  if(Configuration_Table[CONF_TABLE_DEBUG][CONF_TABLE_DEBUG_MASK1] & 0B0000000000000010) return 1;
  else return 0;
}
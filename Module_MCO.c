/**
  ******************************************************************************
  * @file    Module_MCO.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    07-September-2017
  * @last    13-December-2017
  * @brief   This file provides functions to manage the following
  *          functionalities of the MCO on Medicop STM32F072 CAN Modules:
  *           + MCO configuration via external configuration table mask
  *           + SET MCO via external configuration table mask
  *
*/


/* Includes ------------------------------------------------------------------*/
#include <Module_MCO.h>                                                       //
                                                                              //


/*____________________________________________________________________________*/
/*                            Functions - MAINS                               */
/*____________________________________________________________________________*/


/******************************************************************************/
/*******************************  MCO SET  ************************************/
/******************************************************************************/
/* MCO_SET -------------------------------------------------------------------*/
/*                                                                            //
    Initialises MCO if enabled in configuration table and enables it on PA8.  //
    Prescaller is defined in configuration table.                             //
                                                                              //
    Uses ST SPL libs                                                          //
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



void MCO_SET(){
  uint8_t tmp1;
  uint32_t tmp2;

  /* check if MCO is enabled in configuration table*/
  if(Configuration_Table[CONF_TABLE_MCO][CONF_TABLE_MCO_ENABLE]==1){

      /* Get MCO Source from configuration table and store it in tmp1 */
      switch(Configuration_Table[CONF_TABLE_MCO][CONF_TABLE_MCO_SETT]){
        case 0: tmp1 = RCC_MCOSource_NoClock; break;
        case 1: tmp1 = RCC_MCOSource_HSI14; break;
        case 2: tmp1 = RCC_MCOSource_LSI; break;
        case 3: tmp1 = RCC_MCOSource_LSE; break;
        case 4: tmp1 = RCC_MCOSource_SYSCLK; break;
        case 5: tmp1 = RCC_MCOSource_HSI; break;
        case 6: tmp1 = RCC_MCOSource_HSE; break;
        case 7: tmp1 = RCC_MCOSource_PLLCLK_Div2; break;
        case 8: tmp1 = RCC_MCOSource_PLLCLK; break;
        case 9: tmp1 = RCC_MCOSource_HSI48; break;
        default: tmp1 = RCC_MCOSource_NoClock; break;
      }

      /* Get MCO Prescaller from configuration table and store it in tmp2 */
      switch(Configuration_Table[CONF_TABLE_MCO][CONF_TABLE_MCO_PRESC]){
        case 1: tmp2 = RCC_MCOPrescaler_1; break;
        case 2: tmp2 = RCC_MCOPrescaler_2; break;
        case 4: tmp2 = RCC_MCOPrescaler_4; break;
        case 8: tmp2 = RCC_MCOPrescaler_8; break;
        case 16: tmp2 = RCC_MCOPrescaler_16; break;
        case 32: tmp2 = RCC_MCOPrescaler_32; break;
        case 64: tmp2 = RCC_MCOPrescaler_64; break;
        case 128: tmp2 = RCC_MCOPrescaler_128; break;
        default: tmp2 = RCC_MCOPrescaler_1; break;
      }
    
    /* Configure MCO module based on above data */
    Module_MCO_Config(tmp1, tmp2);
  }
}




/*____________________________________________________________________________*/
/*                            Functions - SUBS                                */
/*____________________________________________________________________________*/


/******************************************************************************/
/*******************************  MCO CONFIG  *********************************/
/******************************************************************************/
/* Module_MCO_Config() -------------------------------------------------------*/
/*                                                                            //
    Configures MCO acording to configuration table                            //
                                                                              //
    Uses ST SPL libs                                                          //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
        + RCC_MCOSource: specifies the clock source to output.                //
          *          This parameter can be one of the following values:       //
          *            @arg RCC_MCOSource_NoClock: No clock selected.         //
          *            @arg RCC_MCOSource_HSI14: HSI14 oscillator clock       //
                        selected.                                             //
          *            @arg RCC_MCOSource_LSI: LSI oscillator clock selected. //
          *            @arg RCC_MCOSource_LSE: LSE oscillator clock selected. //
          *            @arg RCC_MCOSource_SYSCLK: System clock selected.      //
          *            @arg RCC_MCOSource_HSI: HSI oscillator clock selected. //
          *            @arg RCC_MCOSource_HSE: HSE oscillator clock selected. //
          *            @arg RCC_MCOSource_PLLCLK_Div2: PLL clock divided by 2 //
                        selected.                                             //
          *            @arg RCC_MCOSource_PLLCLK: PLL clock selected.         //
          *            @arg RCC_MCOSource_HSI48: HSI48 clock selected.        //
                                                                              //
        + RCC_MCOPrescaler: specifies the prescaler on MCO pin.               //
          *          This parameter can be one of the following values:       //
          *            @arg RCC_MCOPrescaler_1: MCO clock is divided by 1.    //
          *            @arg RCC_MCOPrescaler_2: MCO clock is divided by 2.    //
          *            @arg RCC_MCOPrescaler_4: MCO clock is divided by 4.    //
          *            @arg RCC_MCOPrescaler_8: MCO clock is divided by 8.    //
          *            @arg RCC_MCOPrescaler_16: MCO clock is divided by 16.  //
          *            @arg RCC_MCOPrescaler_32: MCO clock is divided by 32.  //
          *            @arg RCC_MCOPrescaler_64: MCO clock is divided by 64.  //
          *            @arg RCC_MCOPrescaler_128: MCO clock is divided by 128.//
                                                                              //
                                                                              //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //

void Module_MCO_Config(uint8_t RCC_MCOSource, uint32_t RCC_MCOPrescaler){

  /* Enable clock for GPIOA */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* Configure PA8 as MCO output 
       - alternate function
       - no speed limit on PA8 pin
       - push-pull type output
       - pull-up enabled
  */
  GPIO_Config(&GPIOA_BASE , _GPIO_PINMASK_8, _GPIO_CFG_MODE_ALT_FUNCTION | _GPIO_CFG_SPEED_MAX | _GPIO_CFG_OTYPE_PP  | _GPIO_CFG_PULL_UP);
  GPIO_Alternate_Function_Enable(&_GPIO_MODULE_MCO_PA8);
  
  /* Configure MCO based on input clock source and prescaller */
  RCC_MCOConfig(RCC_MCOSource, RCC_MCOPrescaler);
}
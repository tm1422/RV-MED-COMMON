/**
  ******************************************************************************
  * @file    Module_GPIO.c
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    08-September-2017
  * @last    13-December-2017
  * @brief   This file provides functions to manage the following
  *          functionalities of the GPIO on Medicop STM32F072 CAN Modules:
  *           + GPIO SET - set GPIO as defined in configuration table
  *           + UPDATE DOUT STATES - updates appropriate digital outputs
  *              to values as defined in configuration table
  *           + GPIO debug mode
  *
*/




/* Includes ------------------------------------------------------------------*/
                                                                              //
#include <Module_GPIO.h>                                                      //
                                                                              //
                                                                              


/* Declarations --------------------------------------------------------------*/
                                                                              //
// ADC debug txt                                                              //
const uint8_t txt_gpio_new_line[] = "\r\n";                                   //
const uint8_t txt_gpio_AIN[] = "AIN:";                                        //
const uint8_t txt_gpio_DIN[] = "DIN:";                                        //
const uint8_t txt_gpio_DOUT[] = "DOUT:";                                      //
const uint8_t txt_gpio_PULL_UP[] = "PULL-UP:";                                //
const uint8_t txt_gpio_PULL_DOWN[] = "PULL-DOWN:";                            //
const uint8_t txt_gpio_DOUT_STATE[] = "DOUT STATE:";                          //
                                                                              //
                                                                              //
                                                                              
                                                                              


/*____________________________________________________________________________*/
/*                            Functions - MAINS                               */
/*____________________________________________________________________________*/


/******************************************************************************/
/*******************************  GPIO SET  ***********************************/
/******************************************************************************/
/* GPIO_SET ------------------------------------------------------------------*/
/*                                                                            //
    Sets GPIO by prioritis as defined in Configuration_Table:                 //
                                                                              //
                                                                              //
      _GPIO_CFG_SPEED_MAX         - ASSINGED TO ALL                           //
      _GPIO_CFG_DIGITAL_INPUT     - PRIORITY : A2                             //
      _GPIO_CFG_DIGITAL_OUTPUT    - PRIORITI : A3                             //
      _GPIO_CFG_ANALOG_INPUT      - PRIORITI : A1                             //
      _GPIO_CFG_PULL_DOWN         - PRIORITY : B2                             //
      _GPIO_CFG_PULL_NO           - PRIORITY : - not implemented              //
      _GPIO_CFG_PULL_UP           - PRIORITY : B1                             //
      GPIOA_ODR                                                               //
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


                                                                              
// Configuration_Table MUST be loaded before!
void GPIO_SET(){
  uint16_t MASK[6] = {0,0,0,0,0,0};
  uint8_t i = 0;
  
  /* Set max speed on all available GPIOs */
  GPIO_Config(&GPIOA_BASE, _GPIO_PINMASK_ALL, _GPIO_CFG_SPEED_MAX);
  GPIO_Config(&GPIOB_BASE, _GPIO_PINMASK_ALL, _GPIO_CFG_SPEED_MAX);
  GPIO_Config(&GPIOC_BASE, _GPIO_PINMASK_ALL, _GPIO_CFG_SPEED_MAX);
  GPIO_Config(&GPIOD_BASE, _GPIO_PINMASK_ALL, _GPIO_CFG_SPEED_MAX);
  GPIO_Config(&GPIOE_BASE, _GPIO_PINMASK_ALL, _GPIO_CFG_SPEED_MAX);
  GPIO_Config(&GPIOF_BASE, _GPIO_PINMASK_ALL, _GPIO_CFG_SPEED_MAX);


                                                                                                              if(GPIO_Debug_Mode()){
                                                                                                                UART1_Write_Text(txt_gpio_AIN);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_A]);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_B]);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_C]);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_D]);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_E]);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_F]);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                              }
                                                                                                                
  /* Configure analog inputs based on configuration table */
  GPIO_Config(&GPIOA_BASE, Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_A], _GPIO_CFG_ANALOG_INPUT);
  GPIO_Config(&GPIOB_BASE, Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_B], _GPIO_CFG_ANALOG_INPUT);
  GPIO_Config(&GPIOC_BASE, Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_C], _GPIO_CFG_ANALOG_INPUT);
  GPIO_Config(&GPIOD_BASE, Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_D], _GPIO_CFG_ANALOG_INPUT);
  GPIO_Config(&GPIOE_BASE, Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_E], _GPIO_CFG_ANALOG_INPUT);
  GPIO_Config(&GPIOF_BASE, Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_F], _GPIO_CFG_ANALOG_INPUT);
  
  /* Configure digital inputs based on configuration table (*NOT* AIN *AND* DIN) */
  MASK[0] = ~Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_A] & Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_A];
  GPIO_Config(&GPIOA_BASE, MASK, _GPIO_CFG_DIGITAL_INPUT);
  MASK[1] = ~Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_B] & Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_B];
  GPIO_Config(&GPIOB_BASE, MASK, _GPIO_CFG_DIGITAL_INPUT);
  MASK[2] = ~Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_C] & Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_C];
  GPIO_Config(&GPIOC_BASE, MASK, _GPIO_CFG_DIGITAL_INPUT);
  MASK[3] = ~Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_D] & Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_D];
  GPIO_Config(&GPIOD_BASE, MASK, _GPIO_CFG_DIGITAL_INPUT);
  MASK[4] = ~Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_E] & Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_E];
  GPIO_Config(&GPIOE_BASE, MASK, _GPIO_CFG_DIGITAL_INPUT);
  MASK[5] = ~Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_F] & Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_F];
  GPIO_Config(&GPIOF_BASE, MASK, _GPIO_CFG_DIGITAL_INPUT);
                                                                                                              if(GPIO_Debug_Mode()){
                                                                                                                UART1_Write_Text(txt_gpio_DIN);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                                for(i=0; i<6; i++){
                                                                                                                  Debug_WordToStr_no_trim(MASK[i]);
                                                                                                                }
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                              }

  /* Configure digital inputs based on configuration table (*NOT* AIN *OR* DIN *AND* DOUT) */
  MASK[0] = ~(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_A] | Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_A]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_A];
  GPIO_Config(&GPIOA_BASE, MASK, _GPIO_CFG_DIGITAL_OUTPUT);
  MASK[1] = ~(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_B] | Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_B]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_B];
  GPIO_Config(&GPIOB_BASE, MASK, _GPIO_CFG_DIGITAL_OUTPUT);
  MASK[2] = ~(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_C] | Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_C]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_C];
  GPIO_Config(&GPIOC_BASE, MASK, _GPIO_CFG_DIGITAL_OUTPUT);
  MASK[3] = ~(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_D] | Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_D]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_D];
  GPIO_Config(&GPIOD_BASE, MASK, _GPIO_CFG_DIGITAL_OUTPUT);
  MASK[4] = ~(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_E] | Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_E]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_E];
  GPIO_Config(&GPIOE_BASE, MASK, _GPIO_CFG_DIGITAL_OUTPUT);
  MASK[5] = ~(Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_AIN_F] | Configuration_Table[CONF_TABLE_GPIO1_IN][CONF_TABLE_DIN_F]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_F];
  GPIO_Config(&GPIOF_BASE, MASK, _GPIO_CFG_DIGITAL_OUTPUT);

                                                                                                              if(GPIO_Debug_Mode()){
                                                                                                                UART1_Write_Text(txt_gpio_DOUT);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                                for(i=0; i<6; i++){
                                                                                                                  Debug_WordToStr_no_trim(MASK[i]);
                                                                                                                }
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                              }
                                                                                                                
                                                                                                              if(GPIO_Debug_Mode()){
                                                                                                                UART1_Write_Text(txt_gpio_PULL_UP);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_A_PULL_UP]);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_B_PULL_UP]);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_C_PULL_UP]);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_D_PULL_UP]);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_E_PULL_UP]);
                                                                                                                Debug_WordToStr_no_trim(Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_F_PULL_UP]);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                              }
  
  /* Set pull-ups based on configuration table */
  GPIO_Config(&GPIOA_BASE, Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_A_PULL_UP], _GPIO_CFG_PULL_UP);
  GPIO_Config(&GPIOB_BASE, Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_B_PULL_UP], _GPIO_CFG_PULL_UP);
  GPIO_Config(&GPIOC_BASE, Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_C_PULL_UP], _GPIO_CFG_PULL_UP);
  GPIO_Config(&GPIOD_BASE, Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_D_PULL_UP], _GPIO_CFG_PULL_UP);
  GPIO_Config(&GPIOE_BASE, Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_E_PULL_UP], _GPIO_CFG_PULL_UP);
  GPIO_Config(&GPIOF_BASE, Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_F_PULL_UP], _GPIO_CFG_PULL_UP);

  /* Set pull-downs based on configuration table (*NOT* PULL-UP *AND* PULL-DOWN)*/
  MASK[0] = ~Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_A_PULL_UP] & Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_A_PULL_DOWN];
  GPIO_Config(&GPIOA_BASE, MASK, _GPIO_CFG_PULL_DOWN);
  MASK[1] = ~Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_B_PULL_UP] & Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_B_PULL_DOWN];
  GPIO_Config(&GPIOB_BASE, MASK, _GPIO_CFG_PULL_DOWN);
  MASK[2] = ~Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_C_PULL_UP] & Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_C_PULL_DOWN];
  GPIO_Config(&GPIOC_BASE, MASK, _GPIO_CFG_PULL_DOWN);
  MASK[3] = ~Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_D_PULL_UP] & Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_D_PULL_DOWN];
  GPIO_Config(&GPIOD_BASE, MASK, _GPIO_CFG_PULL_DOWN);
  MASK[4] = ~Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_E_PULL_UP] & Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_E_PULL_DOWN];
  GPIO_Config(&GPIOE_BASE, MASK, _GPIO_CFG_PULL_DOWN);
  MASK[5] = ~Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_F_PULL_UP] & Configuration_Table[CONF_TABLE_GPIO2_PULL_UP_DOWN][CONF_TABLE_DIN_F_PULL_DOWN];
  GPIO_Config(&GPIOF_BASE, MASK, _GPIO_CFG_PULL_DOWN);

                                                                                                              if(GPIO_Debug_Mode()){
                                                                                                                UART1_Write_Text(txt_gpio_PULL_DOWN);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                                for(i=0; i<6; i++){
                                                                                                                  Debug_WordToStr_no_trim(MASK[i]);
                                                                                                                }
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                              }
                                                                                                                
                                                                                                              if(GPIO_Debug_Mode()){
                                                                                                                UART1_Write_Text(txt_gpio_DOUT_STATE);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                                Debug_WordToStr_no_trim(GPIOA_ODR);
                                                                                                                Debug_WordToStr_no_trim(GPIOB_ODR);
                                                                                                                Debug_WordToStr_no_trim(GPIOC_ODR);
                                                                                                                Debug_WordToStr_no_trim(GPIOD_ODR);
                                                                                                                Debug_WordToStr_no_trim(GPIOE_ODR);
                                                                                                                Debug_WordToStr_no_trim(GPIOF_ODR);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                              }
  
  /* Configure digital outputs states if GPIO is configured as digital output */
  GPIOA_ODR = GPIOA_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_A] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_A]);                                                                                   // WRITES 1's TO ODR
  GPIOA_ODR = GPIOA_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_A] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_A]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_A]));            // WRITES 0's TO ODR
  GPIOB_ODR = GPIOB_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_B] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_B]);                                                                                   // WRITES 1's TO ODR
  GPIOB_ODR = GPIOB_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_B] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_B]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_B]));            // WRITES 0's TO ODR
  GPIOC_ODR = GPIOC_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_C] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_C]);                                                                                   // WRITES 1's TO ODR
  GPIOC_ODR = GPIOC_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_C] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_C]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_C]));            // WRITES 0's TO ODR
  GPIOD_ODR = GPIOD_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_D] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_D]);                                                                                   // WRITES 1's TO ODR
  GPIOD_ODR = GPIOD_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_D] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_D]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_D]));            // WRITES 0's TO ODR
  GPIOE_ODR = GPIOE_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_E] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_E]);                                                                                   // WRITES 1's TO ODR
  GPIOE_ODR = GPIOE_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_E] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_E]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_E]));            // WRITES 0's TO ODR
  GPIOF_ODR = GPIOF_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_F] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_F]);                                                                                   // WRITES 1's TO ODR
  GPIOF_ODR = GPIOF_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_F] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_F]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_F]));            // WRITES 0's TO ODR
}


/******************************************************************************/
/**************************  GPIO UPDATE DOUT STATES  *************************/
/******************************************************************************/
/* GPIO_UPDATE_DOUT_STATES() -------------------------------------------------*/
/*                                                                            //
    Updates GPIO output states defined in Configuration_Table.                //
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

void GPIO_UPDATE_DOUT_STATES(){

                                                                                                              if(GPIO_Debug_Mode()){
                                                                                                                UART1_Write_Text(txt_gpio_DOUT_STATE);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                                Debug_WordToStr_no_trim(GPIOA_ODR);
                                                                                                                Debug_WordToStr_no_trim(GPIOB_ODR);
                                                                                                                Debug_WordToStr_no_trim(GPIOC_ODR);
                                                                                                                Debug_WordToStr_no_trim(GPIOD_ODR);
                                                                                                                Debug_WordToStr_no_trim(GPIOE_ODR);
                                                                                                                Debug_WordToStr_no_trim(GPIOF_ODR);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                                UART1_Write_Text(txt_gpio_new_line);
                                                                                                              }

  /* Update digital outputs states if GPIO is configured as digital output */
  GPIOA_ODR = GPIOA_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_A] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_A]);                                                                                   // WRITES 1's TO ODR
  GPIOA_ODR = GPIOA_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_A] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_A]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_A]));            // WRITES 0's TO ODR
  GPIOB_ODR = GPIOB_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_B] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_B]);                                                                                   // WRITES 1's TO ODR
  GPIOB_ODR = GPIOB_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_B] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_B]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_B]));            // WRITES 0's TO ODR
  GPIOC_ODR = GPIOC_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_C] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_C]);                                                                                   // WRITES 1's TO ODR
  GPIOC_ODR = GPIOC_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_C] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_C]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_C]));            // WRITES 0's TO ODR
  GPIOD_ODR = GPIOD_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_D] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_D]);                                                                                   // WRITES 1's TO ODR
  GPIOD_ODR = GPIOD_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_D] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_D]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_D]));            // WRITES 0's TO ODR
  GPIOE_ODR = GPIOE_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_E] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_E]);                                                                                   // WRITES 1's TO ODR
  GPIOE_ODR = GPIOE_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_E] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_E]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_E]));            // WRITES 0's TO ODR
  GPIOF_ODR = GPIOF_ODR | (Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_F] & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_F]);                                                                                   // WRITES 1's TO ODR
  GPIOF_ODR = GPIOF_ODR & (~((Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_F] ^ Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_STATE_F]) & Configuration_Table[CONF_TABLE_GPIO3_OUTPUT][CONF_TABLE_DOUT_F]));            // WRITES 0's TO ODR
}






/*____________________________________________________________________________*/
/*                            Functions - SUBS                                */
/*____________________________________________________________________________*/




/******************************************************************************/
/**************************  GPIO DEBUG MODE  *********************************/
/******************************************************************************/
/* GPIO_Debug_Mode() ---------------------------------------------------------*/
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

uint8_t GPIO_Debug_Mode(){
  if(Configuration_Table[CONF_TABLE_DEBUG][CONF_TABLE_DEBUG_MASK1] & 0B0000000000100000) return 1;
  else return 0;
}
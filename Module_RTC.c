/**
  ******************************************************************************
  * @file    Module_RTC.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    07-September-2017
  * @brief   This file provides functions to manage the following
  *          functionalities of the RTC on Medicop STM32F072 CAN Modules:
               + configures RTCC
               + sets clock
               + sets calendar
               + writes and reads to/from clock buffer in CAN table buffer            // not fully implemented
               + provides functionalities to sets and reads RTCC via UART
               + reads time and data from CAN and saves it in CAN buffer              // not implemented
  ******************************************************************************
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
                                                                              //
#include <Module_RTC.h>                                                       //
                                                                              //
                                                                              


/* Declarations --------------------------------------------------------------*/
#define RTC_CLOCK_SOURCE_LSE   /* LSE used as RTC source clock */             //
#define BKP_VALUE    0x32F0                                                   //
                                                                              //
                                                                              //
__IO uint32_t AsynchPrediv = 0, SynchPrediv = 0;                              //
static void RTC_Config(void);                                                 //
uint8_t RTC_Config_Flag = 0;                                                  //
                                                                              //
                                                                              //
// RTC UART & DEBUG txt                                                       //
                                                                              //
const uint8_t txt_rtc_new_line[] = "\r\n";                                    //
const uint8_t txt_rtc_RTC_Hardware_Example[] = "*********************** RTC Hardware Calendar Example ***********************";//
const uint8_t txt_rtc_RTC_Prescaler_Failed[] = "        /!\\***** RTC Prescaler Config failed ********/!\\";//
const uint8_t txt_rtc_Power_on_Reset[] = "Power On Reset occurred....";       //
const uint8_t txt_rtc_External_Reset[] = "External Reset occurred....";       //
const uint8_t txt_rtc_No_Need[] = "No need to configure RTC....";             //
const uint8_t txt_rtc_Time_Settings[] = "==============Time Settings=====================================";//
const uint8_t txt_rtc_Set_Hours[] = "  Please Set Hours:";                    //
const uint8_t txt_rtc_Set_Minutes[] = "  Please Set Minutes:";                //
const uint8_t txt_rtc_Set_Seconds[] = "  Please Set Seconds:";                //
const uint8_t txt_rtc_Time_Success[] = ">> !! RTC Set Time success. !! <<";   //
const uint8_t txt_rtc_Time_Failed[] = ">> !! RTC Set Time failed. !! <<";     //
const uint8_t txt_rtc_Current_Time[] = "  The current time is : ";            //
const uint8_t txt_rtc_Current_Date[] = "\r\n  The current date is : ";        //
const uint8_t txt_rtc_Mon[] = "Monday, ";                                     //
const uint8_t txt_rtc_Tue[] = "Tuesday, ";                                    //
const uint8_t txt_rtc_Wed[] = "Wednesday, ";                                  //
const uint8_t txt_rtc_Thu[] = "Thursday, ";                                   //
const uint8_t txt_rtc_Fri[] = "Friday, ";                                     //
const uint8_t txt_rtc_Sat[] = "Saturday, ";                                   //
const uint8_t txt_rtc_Sun[] = "Sunday, ";                                     //
const uint8_t txt_rtc_0[] = "0";                                              //
const uint8_t txt_rtc_dot[] = ".";                                            //
const uint8_t txt_rtc_equ[] = ":";                                            //
const uint8_t txt_rtc_20[] = "20";                                            //
const uint8_t txt_rtc_space[] = " ";                                          //
const uint8_t txt_rtc_Valid_Number_0_9[] = " Please enter valid number between 0 and 9";//
const uint8_t txt_rtc_Valid_Number_0_[] = " Please enter valid number between 0 and ";//
                                                                              //





void RTCC_Process(){
  if(Configuration_Table[CONF_TABLE_RTCC][CONF_TABLE_RTCC_OUT_CAN_ADDR] & 0B1000000000000000){      // if CAN RTCC OUT
    RTC_WRITE_CAN_BUFFER();
  }
}




/*____________________________________________________________________________*/
/*                            Functions - MAINS                               */
/*____________________________________________________________________________*/


/******************************************************************************/
/***************************  RTC SET CLOCK  **********************************/
/******************************************************************************/
/* RTC_SET_CLOCK -------------------------------------------------------------*/
/*                                                                            //
    Enables and sets internal RTC clock.                                      //
      + uses separate external oscillator for RTCC                            //
                                                                              //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + uint8_t Hours: 0 - 23                                                 //
      + uint8_t Minutes: 0 - 59                                               //
      + uint8_t Seconds: 0 - 59                                               //
                                                                              //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //

                                                                              

void RTC_SET_CLOCK(uint8_t Hours, uint8_t Minutes, uint8_t Seconds){
 
  RTC_InitTypeDef RTC_InitStructure;
  RTC_TimeTypeDef RTC_TimeStructure;

    /* RTC configuration  */
    if(!RTC_Config_Flag){
      RTC_Config();
      RTC_Config_Flag = 1;
      
    /* Configure the RTC data register and RTC prescaler */
      RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
      RTC_InitStructure.RTC_SynchPrediv = SynchPrediv;
      RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
    }

    /* Check on RTC init */
//    if (RTC_Init(&RTC_InitStructure) == ERROR){
//      UART1_Write_Text("\r\n        /!\\***** RTC Prescaler Config failed ********/!\\ \r\n");
//    }

  RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
  RTC_TimeStructure.RTC_Hours = Hours;
  RTC_TimeStructure.RTC_Minutes = Minutes;
  RTC_TimeStructure.RTC_Seconds = Seconds;

  /* Configure the RTC time register */
  if(RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure) != ST_SPL_ERROR) RTC_WriteBackupRegister(RTC_BKP_DR0, BKP_VALUE);
  
}




/******************************************************************************/
/***************************  RTC SET DATE  ***********************************/
/******************************************************************************/
/* RTC_SET_DATE --------------------------------------------------------------*/
/*                                                                            //
    Enables internal RTC and sets date.                                       //
      + uses separate external oscillator for RTCC                            //
                                                                              //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
      + uint8_t WeekDay: 1 - 7                                                //
      + uint8_t Day: 1 - 31                                                   //
      + uint8_t Month: 1 - 12                                                 //
      + uint8_t Year: 0 - 99                                                  //
                                                                              //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/                                                                            //



void RTC_SET_DATE(uint8_t WeekDay, uint8_t Day, uint8_t Month, uint8_t Year){

  RTC_InitTypeDef RTC_InitStructure;
  RTC_DateTypeDef RTC_DateStructure;

    /* RTC configuration  */
    if(!RTC_Config_Flag){
      RTC_Config();
      RTC_Config_Flag = 1;

    /* Configure the RTC data register and RTC prescaler */
      RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
      RTC_InitStructure.RTC_SynchPrediv = SynchPrediv;
      RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
    }
    
  RTC_DateStructure.RTC_Date = Day;
  RTC_DateStructure.RTC_Month = Month;
  RTC_DateStructure.RTC_Year = Year;
  RTC_DateStructure.RTC_WeekDay = WeekDay;

  /* Configure the RTC time register */
  if(RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure) != ST_SPL_ERROR) RTC_WriteBackupRegister(RTC_BKP_DR0, BKP_VALUE);
}



/******************************************************************************/
/**********************  RTC WRITE CAN BUFFER  ********************************/
/******************************************************************************/
/* RTC_WRITE_CAN_BUFFER ------------------------------------------------------*/
/*                                                                            //
    Writes RTCC clock and date to CAN Buffer                                  //
    CAN buffer data structure:                                                //
      1 hours,                                                                //
      2 minutes,                                                              //
      3 seconds,                                                              //
      4 weekday,                                                              //
      5 day,                                                                  //
      6 month,                                                                //
      7 year                                                                  //
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



void RTC_WRITE_CAN_BUFFER(){
  uint8_t tmp= 0xFF;

  RTC_TimeTypeDef RTC_TimeStructure;
  /* Get the current Time */

  RTC_DateTypeDef RTC_DateStructure;
  /* Get the current Time */

  RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);

    CAN_Buffer[CAN_TX_BUFFER_TABLE_RTCC][CAN_TX_BUFFER_TABLE_RTCC_HOURS] = RTC_TimeStructure.RTC_Hours;
    CAN_Buffer[CAN_TX_BUFFER_TABLE_RTCC][CAN_TX_BUFFER_TABLE_RTCC_MINUTES] = RTC_TimeStructure.RTC_Minutes;
    CAN_Buffer[CAN_TX_BUFFER_TABLE_RTCC][CAN_TX_BUFFER_TABLE_RTCC_SECONDS] = RTC_TimeStructure.RTC_Seconds;
    CAN_Buffer[CAN_TX_BUFFER_TABLE_RTCC][CAN_TX_BUFFER_TABLE_RTCC_WEEKDAY]  = RTC_DateStructure.RTC_WeekDay;
    CAN_Buffer[CAN_TX_BUFFER_TABLE_RTCC][CAN_TX_BUFFER_TABLE_RTCC_DAY]  = RTC_DateStructure.RTC_Date;
    CAN_Buffer[CAN_TX_BUFFER_TABLE_RTCC][CAN_TX_BUFFER_TABLE_RTCC_MONTH]  = RTC_DateStructure.RTC_Month;
    CAN_Buffer[CAN_TX_BUFFER_TABLE_RTCC][CAN_TX_BUFFER_TABLE_RTCC_YEAR]  = RTC_DateStructure.RTC_Year;
}



/******************************************************************************/
/***************************  RTC SET UART  ***********************************/
/******************************************************************************/
/* RTC_SET_UART --------------------------------------------------------------*/
/*                                                                            //
  !< At this stage the microcontroller clock setting is already configured,   //
       this is done through SystemInit() function which is called from startup//
       file (startup_stm32f0xx.s) before to branch to application main.       //
       To reconfigure the default setting of SystemInit() function, refer to  //
       system_stm32f0xx.c file                                                //
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
                                                                              //
                                                                              

                                              /********** RTC UART *****************/

void RTC_SET_UART(void){

  RTC_InitTypeDef RTC_InitStructure;
//  NVIC_InitTypeDef  NVIC_InitStructure;
//  EXTI_InitTypeDef  EXTI_InitStructure;

//  STM_EVAL_COMInit(COM1, &USART_InitStructure);

  /* Output a message on Hyperterminal using printf function */
                                              
                                              UART1_Write_Text(txt_rtc_new_line);
                                              UART1_Write_Text(txt_rtc_RTC_Hardware_Example);
                                              UART1_Write_Text(txt_rtc_new_line);

  if (RTC_ReadBackupRegister(RTC_BKP_DR0) != BKP_VALUE){
    /* RTC configuration  */
    RTC_Config();

    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
    RTC_InitStructure.RTC_SynchPrediv = SynchPrediv;
    RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;

    /* Check on RTC init */
    if (RTC_Init(&RTC_InitStructure) == ST_SPL_ERROR){
                                              
                                              UART1_Write_Text(txt_rtc_new_line);
                                              UART1_Write_Text(txt_rtc_RTC_Prescaler_Failed);
                                              UART1_Write_Text(txt_rtc_new_line);
    }

    /* Configure the time register */
    RTC_TimeRegulate();
  }
  else
  {
    /* Check if the Power On Reset flag is set */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET){
    
                                              UART1_Write_Text(txt_rtc_new_line);
                                              UART1_Write_Text(txt_rtc_Power_on_Reset);
                                              UART1_Write_Text(txt_rtc_new_line);
    }
    /* Check if the Pin Reset flag is set */
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET){
    
                                              UART1_Write_Text(txt_rtc_new_line);
                                              UART1_Write_Text(txt_rtc_External_Reset);
                                              UART1_Write_Text(txt_rtc_new_line);
    }
                                              UART1_Write_Text(txt_rtc_new_line);
                                              UART1_Write_Text(txt_rtc_No_Need);
                                              UART1_Write_Text(txt_rtc_new_line);

    /* Enable the PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);

 #ifdef RTC_CLOCK_SOURCE_LSI
    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);
 #endif /* RTC_CLOCK_SOURCE_LSI */

    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();

    /* Clear the RTC Alarm Flag */
    RTC_ClearFlag(RTC_FLAG_ALRAF);

    /* Clear the EXTI Line 17 Pending bit (Connected internally to RTC Alarm) */
//    EXTI_ClearITPendingBit(EXTI_Line17);

    /* Display the RTC Time and Alarm */
    RTC_TimeShow();
//    RTC_AlarmShow();
  }

  /* Configure the external interrupt "KEY", "SEL" and "UP" buttons */
//  STM_EVAL_PBInit(BUTTON_TAMPER, BUTTON_MODE_EXTI);
//  STM_EVAL_PBInit(BUTTON_SEL, BUTTON_MODE_EXTI);
//  STM_EVAL_PBInit(BUTTON_UP, BUTTON_MODE_EXTI);

  /* Configure LEDs */
//  STM_EVAL_LEDInit(LED1);
//  STM_EVAL_LEDInit(LED2);

  /* Turn LED2 ON */
//  STM_EVAL_LEDOn(LED2);

  /* RTC Alarm A Interrupt Configuration */
  /* EXTI configuration *********************************************************/
/*  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
*/
  /* Enable the RTC Alarm Interrupt */
/*  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
*/
}

/*____________________________________________________________________________*/
/*                            Functions - MAINS                               */
/*____________________________________________________________________________*/



/******************************************************************************/
/****************************  RTC CONFIG  ************************************/
/******************************************************************************/
/* RTC_Config ----------------------------------------------------------------*/
/*                                                                            //
    Configures RTC.                                                           //
                                                                              //
  * @brief  Configure the RTC peripheral by selecting the clock source.       //
  * @param  None                                                              //
  * @retval None                                                              //
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
                                                                              //


static void RTC_Config(void)
{
  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);

  /* Enable the LSE OSC */
  RCC_LSEConfig(RCC_LSE_ON);

  /* Wait till LSE is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  SynchPrediv = 0xFF;
  AsynchPrediv = 0x7F;

  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
}

/**
  * @brief  Returns the time entered by user, using Hyperterminal.
  * @param  None
  * @retval None
  */






/*____________________________________________________________________________*/
/*                            Functions - SUBS                                */
/*____________________________________________________________________________*/



/******************************************************************************/
/***************************  RTC TIME REGULATE  ******************************/
/******************************************************************************/
/* RTC_TimeRegulate ----------------------------------------------------------*/
/*                                                                            //
    Regulates time via UART                                                   //
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
                                                                              //



void RTC_TimeRegulate(void){

  RTC_TimeTypeDef RTC_TimeStructure;
//  RTC_AlarmTypeDef  RTC_AlarmStructure;
  uint32_t tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;

                                              UART1_Write_Text(txt_rtc_new_line);
                                              UART1_Write_Text(txt_rtc_Time_Settings);
                                              UART1_Write_Text(txt_rtc_new_line);
                                              
  RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
  
                                              UART1_Write_Text(txt_rtc_Set_Hours);
                                              UART1_Write_Text(txt_rtc_new_line);
  
  while (tmp_hh == 0xFF)
  {
    tmp_hh = USART_Scanf(23);
    RTC_TimeStructure.RTC_Hours = tmp_hh;
  }
  
                                              UART1_Write_Text(txt_rtc_space);
                                              Debug_IntToStr(tmp_hh);
                                              UART1_Write_Text(txt_rtc_new_line);

                                              UART1_Write_Text(txt_rtc_Set_Minutes);
                                              UART1_Write_Text(txt_rtc_new_line);
  while (tmp_mm == 0xFF)
  {
    tmp_mm = USART_Scanf(59);
    RTC_TimeStructure.RTC_Minutes = tmp_mm;
  }

                                              UART1_Write_Text(txt_rtc_space);
                                              Debug_IntToStr(tmp_mm);
                                              UART1_Write_Text(txt_rtc_new_line);

                                              UART1_Write_Text(txt_rtc_Set_Seconds);
                                              UART1_Write_Text(txt_rtc_new_line);
  while (tmp_ss == 0xFF)
  {
    tmp_ss = USART_Scanf(59);
    RTC_TimeStructure.RTC_Seconds = tmp_ss;
  }
  
                                              UART1_Write_Text(txt_rtc_space);
                                              Debug_IntToStr(tmp_ss);
                                              UART1_Write_Text(txt_rtc_new_line);

  /* Configure the RTC time register */
  if(RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure) == ST_SPL_ERROR)
  {
                                              UART1_Write_Text(txt_rtc_new_line);
                                              UART1_Write_Text(txt_rtc_Time_Failed);
                                              UART1_Write_Text(txt_rtc_new_line);
  }
  else
  {
                                              UART1_Write_Text(txt_rtc_new_line);
                                              UART1_Write_Text(txt_rtc_Time_Success);
                                              UART1_Write_Text(txt_rtc_new_line);
    RTC_TimeShow();
    /* Indicator for the RTC configuration */
    RTC_WriteBackupRegister(RTC_BKP_DR0, BKP_VALUE);
  }

  tmp_hh = 0xFF;
  tmp_mm = 0xFF;
  tmp_ss = 0xFF;

}

/**
  * @brief  Display the current time on the Hyperterminal.
  * @param  None
  * @retval None
  */





/******************************************************************************/
/***************************  RTC TIME SHOW  **********************************/
/******************************************************************************/
/* RTC_TimeShow --------------------------------------------------------------*/
/*                                                                            //
    Show time on UART                                                         //
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
                                                                              //



void RTC_TimeShow(void){
  
  RTC_TimeTypeDef RTC_TimeStructure;
  /* Get the current Time */
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
  
                                             UART1_Write_Text(txt_rtc_new_line);
                                             UART1_Write_Text(txt_rtc_Current_Time);

  if(RTC_TimeStructure.RTC_Hours < 10)       UART1_Write_Text(txt_rtc_0);
                                             Debug_IntToStr(RTC_TimeStructure.RTC_Hours);
                                             UART1_Write_Text(txt_rtc_equ);
  
  if(RTC_TimeStructure.RTC_Minutes < 10)     UART1_Write_Text(txt_rtc_0);
                                             Debug_IntToStr(RTC_TimeStructure.RTC_Minutes);
                                             UART1_Write_Text(txt_rtc_equ);
  
  if(RTC_TimeStructure.RTC_Seconds < 10)     UART1_Write_Text(txt_rtc_0);
                                             Debug_IntToStr(RTC_TimeStructure.RTC_Seconds);
                                             UART1_Write_Text(txt_rtc_new_line);
}



/******************************************************************************/
/***************************  RTC DATE SHOW  **********************************/
/******************************************************************************/
/* RTC_DateShow --------------------------------------------------------------*/
/*                                                                            //
    Show date on UART                                                         //
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
                                                                              //


void RTC_DateShow(void){
  uint8_t i = 0;

  RTC_DateTypeDef RTC_DateStructure;
  /* Get the current Time */
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);

                                             UART1_Write_Text(txt_rtc_new_line);
                                             UART1_Write_Text(txt_rtc_Current_Date);

  i = RTC_DateStructure.RTC_WeekDay;
  switch(i){
    case 1:                                  UART1_Write_Text(txt_rtc_Mon);
            break;
    case 2:                                  UART1_Write_Text(txt_rtc_Tue);
            break;
    case 3:                                  UART1_Write_Text(txt_rtc_Wed);
            break;
    case 4:                                  UART1_Write_Text(txt_rtc_Thu);
            break;
    case 5:                                  UART1_Write_Text(txt_rtc_Fri);
            break;
    case 6:                                  UART1_Write_Text(txt_rtc_Sat);
            break;
    case 7:                                  UART1_Write_Text(txt_rtc_Sun);
            break;
    default: break;
  }

  if(RTC_DateStructure.RTC_Date < 10)        UART1_Write_Text(txt_rtc_0);
                                             Debug_IntToStr(RTC_DateStructure.RTC_Date);
                                             UART1_Write_Text(txt_rtc_dot);

  if(RTC_DateStructure.RTC_Month < 10)       UART1_Write_Text(txt_rtc_0);
                                             Debug_IntToStr(RTC_DateStructure.RTC_Month);
                                             UART1_Write_Text(txt_rtc_dot);

                                             UART1_Write_Text(txt_rtc_20);
  if(RTC_DateStructure.RTC_Year < 10)        UART1_Write_Text(txt_rtc_0);
                                             Debug_IntToStr(RTC_DateStructure.RTC_Year);
                                             UART1_Write_Text(txt_rtc_new_line);
}


/******************************************************************************/
/***************************  USART SCANF  ************************************/
/******************************************************************************/
/* USART_Scanf ---------------------------------------------------------------*/
/*                                                                            //
  * @brief  Gets numeric values from the hyperterminal.                       //
  * @param  None                                                              //
  * @retval None                                                              //
                                                                              //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + unit32_t value                                                        //
        - UART input value limit                                              //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + 0xFF if entered value is larger than "value"                          //
        otherwise returns entered value                                       //
    ______________________________________                                    //
*/                                                                            //
                                                                              //



uint8_t USART_Scanf(uint32_t value){
  uint32_t index = 0;
  uint32_t tmp[2] = {0, 0};

  while (index < 2)
  {
    /* Loop until RXNE = 1 */
    while (!UART1_Data_Ready());
    tmp[index++] = UART1_Read();
    if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
    {
                                             UART1_Write_Text(txt_rtc_new_line);
                                             UART1_Write_Text(txt_rtc_Valid_Number_0_9);
                                             UART1_Write_Text(txt_rtc_new_line);
      index--;
    }
  }
  /* Calculate the Corresponding value */
  index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10);
  /* Checks */
  if (index > value)
  {
                                             UART1_Write_Text(txt_rtc_new_line);
                                             UART1_Write_Text(txt_rtc_Valid_Number_0_);
                                             Debug_IntToStr(value);
                                             UART1_Write_Text(txt_rtc_new_line);
    
    return 0xFF;
  }
  return index;
}
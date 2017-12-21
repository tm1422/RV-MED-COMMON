/**
  ******************************************************************************
  * @file    Module_CRC.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    16-August-2017
  * @brief   This file provides functions to manage the following
  *          functionalities of the CRC on Medicop STM32F072 CAN Modules:
               + CRC polynom configuration
               + CRC calculation of a configuration table
  ******************************************************************************
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include <Module_CRC.h>                                                       //



/* Declarations --------------------------------------------------------------*/
  // Temporary buffer for ADC results                                         //
uint16_t CRC_Buffer[8];                                                       //
                                                                              //
/*// ADC debug txt                                                              //
const uint8_t txt_crc_new_line[] = "\r\n";                                    //
                                                                              //
const uint8_t txt_crc_Calculate_Table[] = "CRC_Calculate_Table(uint8_t Table_Nr)";//
const uint8_t txt_crc_remote_received_calculation[] = "Remote Received Configuration Table CRC calculation...";//
const uint8_t txt_crc_ram_calculation[] = "RAM Configuration Table CRC calculation...";//
const uint8_t txt_crc_default_calculation[] = "Default Configuration Table CRC calculation...";//
const uint8_t txt_crc_working_calculation[] = "Working Configuration Table CRC calculation...";//
const uint8_t txt_crc_SD_Card_calculation[] = "SD Card Configuration Table CRC calculation...";//*/
                                                                              //



/*____________________________________________________________________________*/
/*                            Functions - MAINS                               */
/*____________________________________________________________________________*/


/******************************************************************************/
/****************************  CRC CALCULATE  *********************************/
/******************************************************************************/
/* CRC_Calculate_Table() -----------------------------------------------------*/
/*                                                                            //
    calculate CRC of a choosen Configuration_Table                            //
                                                                              //
                                                                              //
    Uses ST SPL libs                                                          //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + uint8_t Table_Nr:                                                     //
        0: Default_Configuration_Table                                        //
        1: Working_Configuration_Table                                        //
        2: REMOTE_RECEIVED_Configuration_Table                                //
        3: SD_Card_Configuration_Table                                        //
        4: RAM Configuration Table                                            //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + uint32_t CRC calculation result                                       //
                                                                              //
    ______________________________________                                    //
*/                                                                            //



                                                                                  /********** DEBUG ****************************/
uint32_t CRC_Calculate_Table(uint8_t Table_Nr){
  uint32_t tmp_table[96];
  uint32_t tmp=0;
  uint8_t i=0, j=0, k=0;
  uint32_t l = 0, m = 0;
  int16_t rfhand=0;
  uint32_t size=0;
  char rdbuf[6] = {' ', ' ', ' ', ' ', ' ', ' '};
                                                                                  /*if(CRC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_crc_Calculate_Table);
                                                                                    UART1_Write_Text(txt_crc_new_line);
                                                                                  }*/

  /* Configure the CRC peripheral to use the polynomial X32 + X26 + X23 + X22 +
                          X16 + X12 + X11 + X10 +X8 + X7 + X5 + X4 + X2+ X +1 */
  CRC_Config(0x04C11DB7);
  
  
  if(Table_Nr==0){
                                                                                  /*if(CRC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_crc_default_calculation);
                                                                                    UART1_Write_Text(txt_crc_new_line);
                                                                                  }*/

  _FLASH_Unlock();
  _EE_Init();

    for(i=0; i<12; i++){
      for(j=0; j<16; j+=2){
       EE_ReadVariable(EE_INTERNAL_DEFAULT_TABLE_BASE_ADDRESS + i*16 + j, &l);
       EE_ReadVariable(EE_INTERNAL_DEFAULT_TABLE_BASE_ADDRESS + i*16 + j +1, &m);

       tmp_table[(i*8) + (j>>1)] = (l<<16) | m;
      }
    }
    tmp = CRC_CalcBlockCRC((uint32_t *)tmp_table, 96);
  }
  
  else if(Table_Nr==1){
                                                                                  /*if(CRC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_crc_working_calculation);
                                                                                    UART1_Write_Text(txt_crc_new_line);
                                                                                  }*/

  _FLASH_Unlock();
  _EE_Init();

    for(i=0; i<12; i++){
      for(j=0; j<16; j+=2){
       EE_ReadVariable(EE_INTERNAL_WORKING_TABLE_BASE_ADDRESS + i*16 + j, &l);
       EE_ReadVariable(EE_INTERNAL_WORKING_TABLE_BASE_ADDRESS + i*16 + j +1, &m);

       tmp_table[(i*8) + (j>>1)] = (l<<16) | m;
      }
    }
    tmp = CRC_CalcBlockCRC((uint32_t *)tmp_table, 96);
  }
  
  else if(Table_Nr==2){

                                                                                  /*if(CRC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_crc_remote_received_calculation);
                                                                                    UART1_Write_Text(txt_crc_new_line);
                                                                                  }*/
  
    for(i=0; i<12; i++){
      for(j=0; j<16; j+=2){
       l = REMOTE_RECEIVED_Configuration_Table[i][j];
       m = REMOTE_RECEIVED_Configuration_Table[i][j+1];

       tmp_table[(i*8) + (j>>1)] = (l<<16) | m;
      }
    }
    tmp = CRC_CalcBlockCRC((uint32_t *)tmp_table, 96);
  }
  
/*
  else if(Table_Nr==3){

                                                                                  if(CRC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_crc_SD_Card_calculation);
                                                                                    UART1_Write_Text(txt_crc_new_line);
                                                                                  }


      SPI_Set_Active(SPI2_Read, SPI2_Write);
      if(!FAT32_ChangeDir("\\")){
        rfhand = FAT32_Open("Config.TXT", 0x01); // READ
        if(rfhand > -1){
          FAT32_Size("Config.TXT", &size);

          if(size==2689){
            for(i = 0; i < 12; i++){
              for(j=0; j<16; j++){
                FAT32_Seek(rfhand, 6+14*(i*16+j));
                if(!FAT32_Read(rfhand, &rdbuf, 6)){

                  if(j%2==0){
                    l = atoi(rdbuf);
                    tmp_table[(i*8) + (j>>1)] = (l<<16) | m;
                  }
                  else m = atoi(rdbuf);

                }
              }
            }
          }

          FAT32_Close(rfhand);
        }
      }
      
      tmp = CRC_CalcBlockCRC((uint32_t *)tmp_table, 96);
  }*/
  
  
  else if(Table_Nr==4){

                                                                                  /*if(CRC_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_crc_ram_calculation);
                                                                                    UART1_Write_Text(txt_crc_new_line);
                                                                                  }*/

    for(i=0; i<12; i++){
      for(j=0; j<16; j+=2){
       l = Configuration_Table[i][j];
       m = Configuration_Table[i][j+1];

       tmp_table[(i*8) + (j>>1)] = (l<<16) | m;
      }
    }
    tmp = CRC_CalcBlockCRC((uint32_t *)tmp_table, 96);
  }


  return tmp;
}


/*____________________________________________________________________________*/
/*                            Functions - SUBS                                */
/*____________________________________________________________________________*/


/******************************************************************************/
/****************************  CRC CONFIG  ************************************/
/******************************************************************************/
/* CRC_Config() --------------------------------------------------------------*/
/*                                                                            //
    Enables CRC an sets polynom for CRC calculations                          //
                                                                              //
                                                                              //
    Uses ST SPL libs                                                          //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + uint32_t poly:                                                        //
          Configure the CRC peripheral to use the polynomial X32 + X31 +      //
          X30 + ... + X2+ X +1                                                //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
                                                                              //
    ______________________________________                                    //
*/                                                                            //


void CRC_Config(uint32_t poly){
  /* Enable CRC AHB clock interface */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

  CRC_INIT = 0xFFFFFFFF;
  CRC_CR = 0;
  CRC->POL = poly;
  CRC->IDR = 0x00;
  CRC_CR = 1; // RESET
}



/******************************************************************************/
/**************************  CRC DEBUG MODE  **********************************/
/******************************************************************************/
/* CRC_Debug_Mode() ----------------------------------------------------------*/
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

uint8_t CRC_Debug_Mode(){
  if(Configuration_Table[CONF_TABLE_DEBUG][CONF_TABLE_DEBUG_MASK1] & 0B0000000000010000) return 1;
  else return 0;
}
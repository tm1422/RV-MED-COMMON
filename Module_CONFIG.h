#ifndef MODULE_CONFIG_H
#define MODULE_CONFIG_H

#include <stdint.h>
#include <eeprom.h>
#include <Defines.h>
#include "__Lib_FAT32.h"
#include <Module_DEBUG.h>
#include <stm32f0xx_rcc.h>

/*
#include <built_in.h>
#include <Module_CRC.h>
#include "__Lib_FAT32.h"
#include <stm32f0xx_flash.h>*/


extern uint32_t EE_Init_State;
extern uint32_t FLASH_Unlock_State;
extern int16_t rfHandle;
extern uint8_t* rfName;
extern uint32_t rfStartSect;
extern uint16_t Configuration_Table[12][16];
extern uint16_t VirtAddVarTab[NB_OF_VAR];

void Configuration_Table_Hand_Write();


void Write_Virtual_Addresses_For_EEPROM();

uint16_t Internal_Working_Configuration_Flag();
uint16_t Internal_Default_Configuration_Flag();
uint16_t SD_Card_Working_Configuration_Flag();
void Get_Load_Internal_Working_Configuration();
void Get_Load_Internal_Default_Configuration();
void Get_Load_SD_Card_Working_Configuration();
unsigned int Get_Load_Working_Configuration();
unsigned int Init_Ext_Mem();

void Erase_FLASH_EEPROM_Page_Default();

void Erase_FLASH_EEPROM_Page_Working();

void Export_Working_Table();  // exports config and makes backup of old one if any
void Export_Default_Table();  // exports config and makes backup of old one if any


void Config_Table_Write_Rand();
void Config_Table_Write_To_Working();
void Config_Table_Write_To_Default();

uint16_t Write_Flag_To_Default_Config_Table();
uint16_t Write_Flag_To_Working_Config_Table();

void Clear_Default_Config_Table_Flag();
void Clear_Working_Config_Table_Flag();
void Write_Clear_SD_Card_Configuration_Flag(uint8_t Flag);


void Write_Config_Table_To_UART();

void _EE_Init();
void _FLASH_Unlock();

uint8_t Config_Debug_Mode();



#endif
#ifndef MODULE_LED_H
#define MODULE_LED_H

#include <stdint.h>
#include <Defines.h>
#include <Module_INTERRUPT.h>

extern uint16_t Configuration_Table[12][16];

void LED_Init();

void LED_Set_15();

void LED_Set_14();

void LED_Clear();

void LED_Set();

void LED_OE_Toggle();

void Manual_SPI2_Write(uint16_t RX_Data);

#endif
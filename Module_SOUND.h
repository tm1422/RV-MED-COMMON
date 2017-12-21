#ifndef MODULE_SOUND_H
#define MODULE_SOUND_H

#include <stdint.h>                                                             //
#include <Module_TIM.h>                                                         //
#include <Module_DEBUG.h>

extern uint16_t TIM2_Beep_Timer;
extern uint16_t ALARM_STATUS;
extern uint16_t BEEP_STATUS;
extern uint16_t FT810_IS_PLAYING;

extern uint16_t ALARM_periode;
extern uint16_t ALARM_duty;
extern uint16_t ALARM_calculated_time_HIGH;
extern uint16_t ALARM_calculated_time_LOW;
extern uint16_t TIM2_Alarm_Timer_HIGH;
extern uint16_t TIM2_Alarm_Timer_LOW;


void Module_SOUND_Init();

void Module_Test_Sound(char sound, char volume);
void Module_Sound_Beep_Start();
void Module_Sound_Beep_Stop();
void SOUND_ALARM_Process();
void SOUND_ALARM_Switch(uint8_t switch_to);
void Module_Sound_Alarm_Start();
void Module_Sound_Alarm_Stop();
void Module_FT810_Get_GPIO_Struct();
void Module_FT810_Send_GPIO_Struct();
void Module_FT810_Sound_Disable();
void Module_FT810_Sound_Enable();


#endif
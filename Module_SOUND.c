#include "FT810_Types.h"
#include <Module_SOUND.h>

uint8_t prev_effect = 0;
uint8_t prev_pitch = 0;
uint8_t prev_vol = 0;

uint16_t sound, pitch, vol;

TFT810GPIO  Sound_GPIO_Struct;


void Module_FT810_Get_GPIO_Struct(){
  FT810_GPIO_GetConfig(&Sound_GPIO_Struct);
                                                                                UART1_Write_Text("Module_FT810_Get_GPIO_Struct: \r\n");
                                                                                UART1_Write_Text("   - GET GPIODIR: ");
                                                                                Debug_LongToStr(Sound_GPIO_Struct.GPIODIR);
                                                                                UART1_Write_Text("\r\n");
                                                                                UART1_Write_Text("   - GET GPIO: ");
                                                                                Debug_LongToStr(Sound_GPIO_Struct.GPIO);
                                                                                UART1_Write_Text("\r\n");
}

void Module_FT810_Send_GPIO_Struct(){
  FT810_GPIO_SetConfig(&Sound_GPIO_Struct);
                                                                                UART1_Write_Text("Module_FT810_Sound_Enable: \r\n");
                                                                                UART1_Write_Text("   - SEND GPIODIR: ");
                                                                                Debug_LongToStr(Sound_GPIO_Struct.GPIODIR);
                                                                                UART1_Write_Text("\r\n");
                                                                                UART1_Write_Text("   - SEND GPIO: ");
                                                                                Debug_LongToStr(Sound_GPIO_Struct.GPIO);
                                                                                UART1_Write_Text("\r\n");
  
}

void Module_FT810_Sound_Enable(){
  Module_FT810_Get_GPIO_Struct();
  
  Sound_GPIO_Struct.GPIO |= 2;
  
  Module_FT810_Send_GPIO_Struct();
}

void Module_FT810_Sound_Disable(){
  Module_FT810_Get_GPIO_Struct();
  
  Sound_GPIO_Struct.GPIO &= -3;
  Module_FT810_Send_GPIO_Struct();
}

void Module_SOUND_Init(){
  
//  SPI1_Init_Advanced(_SPI_FPCLK_DIV2, _SPI_8_BIT | _SPI_MASTER | _SPI_CLK_IDLE_LOW | _SPI_FIRST_CLK_EDGE_TRANSITION | _SPI_MSB_FIRST | _SPI_SSM_DISABLE | _SPI_SS_ENABLE | _SPI_SSI_1, &_GPIO_MODULE_SPI1_PB345);
  SPI_Set_Active(SPI1_Read, SPI1_Write);
//  FT810_Init();

//  FT810_Core_ClockSource(_FT810_CLK_SOURCE_EXTERNAL);
//  FT810_Core_SetFrequency(VTFT_FT810_CONFIG_DISPLAY.Frequency);

  // Internal modules setup

//  FT810_Display_SetConfig(&VTFT_FT810_CONFIG_DISPLAY);

//  FT810_Audio_SetConfig(&VTFT_FT810_CONFIG_AUDIO);

//  FT810_Sound_SetConfig(&VTFT_FT810_CONFIG_SOUND);
  
//  FT810_Interrupt_SetConfig(&VTFT_FT810_CONFIG_INTERRUPT);

//  FT810_PWM_SetConfig(&VTFT_FT810_CONFIG_PWM);

//  FT810_GPIO_SetConfig(&VTFT_FT810_CONFIG_GPIO);

//  FT810_Touch_SetConfig(&VTFT_FT810_CONFIG_TOUCH);
  
//  FT810_Touch_Calibrate(_FT810_FONT_ROBOTO_SIZE_10, "Touch blinking point on the screen!", 400, 300);

  Module_FT810_Get_GPIO_Struct();
  Sound_GPIO_Struct.GPIODIR |= 2;
  Sound_GPIO_Struct.GPIO &= -3;
  Module_FT810_Send_GPIO_Struct();
  
  TIM2_Config();
  FT810_Sound_Stop();
}




void Module_Test_Sound(char sound, char volume){
  char i = 0;

  SPI_Set_Active(SPI1_Read, SPI1_Write);

  Module_FT810_Sound_Enable();
//  Delay_ms(1);
  
  for(i=0; i<2; i++){
    FT810_Sound_SetAndPlay(sound, _FT810_SOUND_PITCH_A5, volume);
    Delay_ms(500);
    FT810_Sound_SetAndPlay(sound, _FT810_SOUND_PITCH_A4, volume);
    Delay_ms(500);
  }
  FT810_Sound_Stop();
  Module_FT810_Sound_Disable();
  
}

void Module_Sound_Beep_Start(){
  BEEP_STATUS = 1;
  SPI_Set_Active(SPI1_Read, SPI1_Write);
  if(ALARM_STATUS & 0B0000000000000001){
    Module_FT810_Sound_Enable();
    TIM2_Enable();
  }
  FT810_Sound_SetAndPlay(_FT810_SOUND_SINE_WAVE, _FT810_SOUND_PITCH_C6, Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000000011111111);
  TIM2_Beep_Timer = 0;
}

void Module_Sound_Beep_Stop(){
  BEEP_STATUS = 0;
  if(!(ALARM_STATUS & 0B0000000000000001)){
//                                                       UART1_Write_Text("Beep stop: stop\r\n");
//                                                       UART1_Write_Text("TIM2 Disable\r\n");
    TIM2_Disable();
    Module_FT810_Sound_Disable();
  }
  FT810_Sound_Stop();
}

void Module_Sound_Alarm_Stop(){
                                                       UART1_Write_Text("TIM2 Disable\r\n");
    TIM2_Disable();
    NVIC_IntDisable(IVT_INT_TIM2);                                                                            UART1_Write_Text("TIM2 Interrupt Disabled");
    
  FT810_Sound_Stop();
  Module_FT810_Sound_Disable();
}

void Module_Sound_Alarm_Start(){
  
  if(Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000010000000000) sound = _FT810_SOUND_SQUARE_WAVE;
  else if(Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000001000000000) sound = _FT810_SOUND_TRIANGLE_WAVE;
  else if(Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000000100000000) sound = _FT810_SOUND_SINE_WAVE;
                                                                                                               
                                                                                                               UART1_Write_Text("Sound: ");
                                                                                                               Debug_WordToStr(sound);
                                                                                                               UART1_Write_Text("\r\n");
                                                                                                               
  pitch = (Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_PITCH] & 0B1111111100000000)>>8;
  
                                                                                                               UART1_Write_Text("Pitch: ");
                                                                                                               Debug_WordToStr(pitch);
                                                                                                               UART1_Write_Text("\r\n");
  
  vol = Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000000011111111;
  
                                                                                                               UART1_Write_Text("Vol: ");
                                                                                                               Debug_WordToStr(vol);
                                                                                                               UART1_Write_Text("\r\n");
  
  SPI_Set_Active(SPI1_Read, SPI1_Write);
  Module_FT810_Sound_Enable();
  FT810_Sound_SetAndPlay((uint8_t)sound, (uint8_t)pitch, (uint8_t)vol);
  TIM2_Alarm_Timer_HIGH = 0;
  TIM2_Alarm_Timer_LOW = 0;
  ALARM_STATUS |= 0B0000000000000010;                                                                           // ALARM_STATUS = 2
  
      ALARM_periode = Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_PERIODE_DUTY] & 0B0000000011111111; // get periode
      
                                                                                                               UART1_Write_Text("ALARM_Periode: ");
                                                                                                               Debug_WordToStr(10*ALARM_periode);
                                                                                                               UART1_Write_Text(" ms\r\n");
      
      ALARM_duty = 10*((Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_PERIODE_DUTY] & 0B0000111100000000)>>8);
      
                                                                                                               UART1_Write_Text("ALARM_duty: ");
                                                                                                               Debug_WordToStr(ALARM_duty);
                                                                                                               UART1_Write_Text("\r\n");

      ALARM_calculated_time_HIGH = (ALARM_duty * ALARM_periode)/100;
      
                                                                                                               UART1_Write_Text("ALARM_calculated_time_HIGH: ");
                                                                                                               Debug_WordToStr(ALARM_calculated_time_HIGH);
                                                                                                               UART1_Write_Text("\r\n");
      
      ALARM_calculated_time_LOW = ((100-ALARM_duty) * ALARM_periode)/100;
      
                                                                                                               UART1_Write_Text("ALARM_calculated_time_LOW: ");
                                                                                                               Debug_WordToStr(ALARM_calculated_time_LOW);
                                                                                                               UART1_Write_Text("\r\n");
                                                              // STATUS "HIGH"
  TIM2_Enable();
  NVIC_IntEnable(IVT_INT_TIM2);                                                                                UART1_Write_Text("TIM2 Interrupt Enabled");
}

void SOUND_ALARM_Switch(uint8_t switch_to){
  if(switch_to==1){


                              if(Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000010000000000) sound = _FT810_SOUND_SQUARE_WAVE;
                              else if(Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000001000000000) sound = _FT810_SOUND_TRIANGLE_WAVE;
                              else if(Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000000100000000) sound = _FT810_SOUND_SINE_WAVE;
                              vol = Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000000011111111;




    pitch = (Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_PITCH] & 0B1111111100000000)>>8;
    
                                                                                                               UART1_Write_Text("Switch To High. New pitch: ");
                                                                                                               Debug_WordToStr(pitch);
                                                                                                               UART1_Write_Text("\r\n");
    
    TIM2_Alarm_Timer_HIGH = 0;
    TIM2_Alarm_Timer_LOW = 0;
    ALARM_STATUS |= 0B0000000000000010;
  }
  else if(switch_to==0){


                              if(Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000010000000000) sound = _FT810_SOUND_SQUARE_WAVE;
                              else if(Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000001000000000) sound = _FT810_SOUND_TRIANGLE_WAVE;
                              else if(Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000000100000000) sound = _FT810_SOUND_SINE_WAVE;
                              vol = Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B0000000011111111;




    pitch = Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_PITCH] & 0B0000000011111111;
    
                                                                                                               UART1_Write_Text("Switch To Low. New pitch: ");
                                                                                                               Debug_WordToStr(pitch);
                                                                                                               UART1_Write_Text("\r\n");
    
    TIM2_Alarm_Timer_LOW = 0;
    TIM2_Alarm_Timer_HIGH = 0;
    ALARM_STATUS &= 0B1111111111111101;
  }
  if(!BEEP_STATUS)FT810_Sound_SetAndPlay(sound, pitch, vol);
}

void SOUND_ALARM_Process(){
  if(Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B1000000000000000){
    
    UART1_Write_Text("Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B1000000000000000 == 1 \r\n");
    UART1_Write_Text("ALARM_STATUS: \r\n");
    Debug_IntToStr(ALARM_STATUS);
    UART1_Write_Text("\r\n");
    
    if(!(ALARM_STATUS & 0B0000000000000001)){
      ALARM_STATUS |= 0B0000000000000001;                 UART1_Write_Text("Write: ALARM_STATUS & 1 \r\n}");
      Module_Sound_Alarm_Start();
    }
  }
  else{
    
    UART1_Write_Text("Configuration_Table[CONF_TABLE_SOUND][CONF_TABLE_SOUND_ALARM_SETTINGS] & 0B1000000000000000 == 0 \r\n");
    UART1_Write_Text("ALARM_STATUS: \r\n");
    Debug_IntToStr(ALARM_STATUS);
    UART1_Write_Text("\r\n");
    
    if(ALARM_STATUS & 0B0000000000000001){
      Module_Sound_Alarm_Stop();                         UART1_Write_Text("Write: ALARM_STATUS & 0 \r\n}");
      ALARM_STATUS &= 0B1111111111111110;
    }
  }
}
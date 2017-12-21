#include <Module_KEYPAD.h>

uint8_t Keypad_READ_Process(){
  uint16_t i,j;
  Keypad_Get_Keys();
  while(Keypad_events_stack[0]){
    if(Keypad_events_stack[0] & 0B10000000){
      UART1_Write_Text("Key pressed: ");
      Debug_IntToStr(Keypad_events_stack[0] & 0B01111111);
      UART1_Write_Text("\r\n");

      for(i=8, j=0; i<129; i+=8, j++){
        if((Keypad_events_stack[0] & 0B01111111) < i){
          if(j<8){
            CAN_Buffer[CAN_TX_BUFFER_TABLE_KEYS1][j] |= 0B00000001<<((Keypad_events_stack[0] & 0B01111111) - (i-8));
          }
          else{
            CAN_Buffer[CAN_TX_BUFFER_TABLE_KEYS2][j-8] |= 0B00000001<<((Keypad_events_stack[0] & 0B01111111) - (i-8));
          }
        }
      }
    }
    else{
      UART1_Write_Text("Key released: ");
      Debug_IntToStr(Keypad_events_stack[0] & 0B01111111);
      UART1_Write_Text("\r\n");

      for(i=8, j=0; i<129; i+=8, j++){
        if((Keypad_events_stack[0] & 0B01111111) < i){
          if(j<8){
            CAN_Buffer[CAN_TX_BUFFER_TABLE_KEYS1][j] &= ~(0B00000001<<((Keypad_events_stack[0] & 0B01111111) - (i-8)));
          }
          else{
            CAN_Buffer[CAN_TX_BUFFER_TABLE_KEYS2][j-8] &= ~(0B00000001<<((Keypad_events_stack[0] & 0B01111111) - (i-8)));
          }
        }
      }
    }
    
    for(i=0; i<9; i++){
      Keypad_events_stack[i] = Keypad_events_stack[i+1];
    }
    Keypad_events_stack[9] = 0;
  }
}

uint8_t Keypad_Write(uint8_t Reg_Name, uint8_t reg_write_value){
  uint8_t I2C1_Data_Buffer[2];
  uint8_t _return = 0;
                                                                                                            //UART1_Write_Text("-> Keypad WRITE()\r\n");

  I2C1_Data_Buffer[0] = Reg_Name;
  I2C1_Data_Buffer[1] = reg_write_value;
  if(I2C1_Start() == 0){                                                                                    //UART1_Write_Text("-> I2C WRITE...\r\n");
    I2C1_Write(TCA8414, I2C1_Data_Buffer, 2, END_MODE_STOP);                                                //UART1_Write_Text("-> DONE\r\n");
    _return = 1;
  }
  else _return = 0;
  
  return _return;
}

uint8_t Keypad_Read(uint8_t Reg_Name){
  uint8_t I2C1_Data_Buffer[2] = {0,0};


  I2C1_Data_Buffer[0] = Reg_Name;
  if(I2C1_Start() == 0){
    I2C1_Write(TCA8414, I2C1_Data_Buffer, 1, END_MODE_RESTART);
    I2C1_Read(TCA8414, I2C1_Data_Buffer ,1, END_MODE_STOP);  
    
//    UART1_Write_Text("I2C1_Write(0x34, I2C1_Data_Buffer, 2, END_MODE_STOP); REG_CFG\r\n");
  }

  return I2C1_Data_Buffer[0];
}

uint8_t Keypad_Get_Keys(){
  uint8_t event_count = 0;
  uint8_t i=0;
  if(Keypad_Read(REG_INT_STAT) & REG_INT_STAT_KEY_EVENTS_INTERRUPT_FLAG){
    while(Keypad_Read(REG_KEY_LCK_EC) & REG_KEY_LCK_EC_KEY_EVENT_COUNT){
      for(i=0; i<10; i++){
        if(Keypad_events_stack[i]==0){                            // write to first free space
          Keypad_events_stack[i] = Keypad_Read(REG_KEY_EVENT_A);
          i=11;
        }
      }
      if(i==10) Keypad_Read(REG_KEY_EVENT_A); // stack overflow
    }
    Keypad_Write(REG_INT_STAT, 0x1F); // clear interrupts
  }
}


                                                           // REG_INT_STAT
                                                           // clear interrupts
                                                           // B4: CTRL-ALT-DEL key sequence status. Requires writing a 1 to clear interrupts. 0 = interrupt not detected 1 = interrupt detected
                                                           // B3: Overflow interrupt status. Requires writing a 1 to clear interrupts. 0 = interrupt not detected 1 = interrupt detected
                                                           // B2: Keypad lock interrupt status. This is the interrupt to the processor when the keypad lock sequence is started. Requires writing a 1 to clear interrupts. 0 = interrupt not detected 1 = interrupt detected
                                                           // B1: GPI interrupt status. Requires writing a 1 to clear interrupts. 0 = interrupt not detected 1 = interrupt detected Can be used to mask interrupts
                                                           // B0: Key events interrupt status. Requires writing a 1 to clear interrupts. 0 = interrupt not detected 1 = interrupt detected

                                                           // REG_KEY_LCK_EC
                                                           // B6: Key lock enable 0 = disabled; Write a 0 to this bit to unlock the keypad manually 1 = enabled; Write a 1 to this bit to lock the keypad
                                                           // B5: Keypad lock status 0 = unlock (if LCK1 is 0 too) 1 = locked (if LCK1 is 1 too)
                                                           // B4: Keypad lock status 0 = unlock (if LCK2 is 0 too) 1 = locked (if LCK2 is 1 too)
                                                           // KEC[3:0] : indicates how many key events are in the FIFO
                                                           
uint8_t Keypad_Init(){
  uint8_t _return = 1;                                                                              //UART1_Write_Text("Keypad_Init()\r\n");
  // Initialize the I2C1 module with 100Kbps speed on PORTB
  
  
  I2C1_Init();
                                                                                                    //UART1_Write_Text("-> I2C2 INIT\r\n");
//  Delay_ms(10);
  
  if(!Keypad_Write(REG_CFG, REG_CFG_AUTO_INCREMENT_DISABLE |             // CONFIG
                        REG_CFG_GPI_INTERRUPT_DISABLE |
                        REG_CFG_INTERRUPT_CLEAR_ALLOWED_IF_PENDING_KEY |
                        REG_CFG_KEY_EVENTS_INTERRUPT_ENABLE |
                        REG_CFG_KEYPAD_LOCK_INTERRUPT_DISABLE |
                        REG_CFG_OVERFLOW_DATA_LIFO |
                        REG_CFG_OVERFLOW_INTERRUPT_DISABLE |
                        REG_CFG_TRACK_EVENTS_WHEN_LOCKED_DISABLE
                        )) _return = 0;

  if(!Keypad_Write(REG_INT_STAT, 0x1F)) _return = 0;                        // CLEAR FLAGS
  
  if(!Keypad_Write(REG_KEY_LCK_EC, 0)) _return = 0;                      // CLEAR KEY LOCK STATUS, EVENTS COUNTER

  if(!Keypad_Write(REG_KP_GPIO1, 0B11111111)) _return = 0;               // KP ROWs 0-3

  if(!Keypad_Write(REG_KP_GPIO2, 0B11111111)) _return = 0;               // KP COLs 0-3

  return _return;
}
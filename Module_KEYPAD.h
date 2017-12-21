#ifndef MODULE_KEYPAD_H
#define MODULE_KEYPAD_H

#include <stdint.h>                                                           //
#include <Defines.h>                                                          //
#include <Module_DEBUG.h>
//#include <stm32f0xx_i2c.h>
//#include <stm32f0xx_rcc.h>

/* TCA8418 I2C ADDRESS*/

#define TCA8414                        0x34

/* TCA8418 register offsets */

#define REG_CFG                        0x01
#define REG_INT_STAT                   0x02
#define REG_KEY_LCK_EC                 0x03
#define REG_KEY_EVENT_A                0x04
#define REG_KEY_EVENT_B                0x05
#define REG_KEY_EVENT_C                0x06
#define REG_KEY_EVENT_D                0x07
#define REG_KEY_EVENT_E                0x08
#define REG_KEY_EVENT_F                0x09
#define REG_KEY_EVENT_G                0x0A
#define REG_KEY_EVENT_H                0x0B
#define REG_KEY_EVENT_I                0x0C
#define REG_KEY_EVENT_J                0x0D
#define REG_KP_LCK_TIMER               0x0E
#define REG_UNLOCK1                    0x0F
#define REG_UNLOCK2                    0x10
#define REG_GPIO_INT_STAT1             0x11
#define REG_GPIO_INT_STAT2             0x12
#define REG_GPIO_INT_STAT3             0x13
#define REG_GPIO_DAT_STAT1             0x14
#define REG_GPIO_DAT_STAT2             0x15
#define REG_GPIO_DAT_STAT3             0x16
#define REG_GPIO_DAT_OUT1              0x17
#define REG_GPIO_DAT_OUT2              0x18
#define REG_GPIO_DAT_OUT3              0x19
#define REG_GPIO_INT_EN1               0x1A
#define REG_GPIO_INT_EN2               0x1B
#define REG_GPIO_INT_EN3               0x1C
#define REG_KP_GPIO1                   0x1D
#define REG_KP_GPIO2                   0x1E
#define REG_KP_GPIO3                   0x1F
#define REG_GPI_EM1                    0x20
#define REG_GPI_EM2                    0x21
#define REG_GPI_EM3                    0x22
#define REG_GPIO_DIR1                  0x23
#define REG_GPIO_DIR2                  0x24
#define REG_GPIO_DIR3                  0x25
#define REG_GPIO_INT_LVL1              0x26
#define REG_GPIO_INT_LVL2              0x27
#define REG_GPIO_INT_LVL3              0x28
#define REG_DEBOUNCE_DIS1              0x29
#define REG_DEBOUNCE_DIS2              0x2A
#define REG_DEBOUNCE_DIS3              0x2B
#define REG_GPIO_PULL1                 0x2C
#define REG_GPIO_PULL2                 0x2D
#define REG_GPIO_PULL3                 0x2E

/* TCA8418 bit definitions */

// Configuration Register
                                                              // OR-ing
#define REG_CFG_AUTO_INCREMENT_ENABLE                         0B10000000
#define REG_CFG_AUTO_INCREMENT_DISABLE                        0
#define REG_CFG_TRACK_EVENTS_WHEN_LOCKED_ENABLE               0
#define REG_CFG_TRACK_EVENTS_WHEN_LOCKED_DISABLE              0B01000000
#define REG_CFG_OVERFLOW_DATA_LOST                            0
#define REG_CFG_OVERFLOW_DATA_LIFO                            0B00100000
#define REG_CFG_INTERRUPT_CLEAR_NOT_ALLOWED_IF_PENDING_KEY    0
#define REG_CFG_INTERRUPT_CLEAR_ALLOWED_IF_PENDING_KEY        0B00010000
#define REG_CFG_OVERFLOW_INTERRUPT_ENABLE                     0B00001000
#define REG_CFG_OVERFLOW_INTERRUPT_DISABLE                    0
#define REG_CFG_KEYPAD_LOCK_INTERRUPT_ENABLE                  0B00000100
#define REG_CFG_KEYPAD_LOCK_INTERRUPT_DISABLE                 0
#define REG_CFG_GPI_INTERRUPT_ENABLE                          0B00000010
#define REG_CFG_GPI_INTERRUPT_DISABLE                         0
#define REG_CFG_KEY_EVENTS_INTERRUPT_ENABLE                   0B00000001
#define REG_CFG_KEY_EVENTS_INTERRUPT_DISABLE                  0

// Interrupt Status Register
                                                              // OR-ing
#define REG_INT_STAT_CAD_INTERRUPT_FLAG                       0B00010000
#define REG_INT_STAT_OVR_FLOW_INTERRUPT_FLAG                  0B00001000
#define REG_INT_STAT_K_LCK_INTERRUPT_FLAG                     0B00000100
#define REG_INT_STAT_GPI_INTERRUPT_FLAG                       0B00000010
#define REG_INT_STAT_KEY_EVENTS_INTERRUPT_FLAG                0B00000001

// Key Lock and Event Counter Register
                                                              // OR-ing
#define REG_KEY_LCK_EC_KEY_LOCK_ENABLED                       0B01000000
#define REG_KEY_LCK_EC_KEY_LOCK_2_STATUS                      0B00100000
#define REG_KEY_LCK_EC_KEY_LOCK_1_STATUS                      0B00010000
#define REG_KEY_LCK_EC_KEY_EVENT_COUNT                        0B00001111

// Keypad Lock1 to Lock2 Timer Register
/*
  KL[2:0] are for the Lock1 to Lock2 timer
  KL[7:3] are for the interrupt mask timer
  Lock1 to Lock2 timer must be non-zero for keylock to be enabled. The lock1 to
  lock2 bits ( KL[2:0] ) define the time in seconds the user has to press unlock
  key 2 after unlock key 1 before the key lock sequence times out. For more
  information, please see Keypad Lock/Unlock.
  If the keypad lock interrupt mask timer is non-zero, a key event interrupt
  (K_INT) will be generated on any first key press. The second interrupt
  (K_LCK_IN) will only be generated when the correct unlock sequence has been
  completed. If either timer expires, the keylock state machine will reset.
  When the interrupt mask timer is disabled (‘0’), a key lock interrupt will
  trigger only when the correct unlock sequence is completed.
  The interrupt mask timer should be set for the time it takes for the LCD to dim
  or turn off. For more information, please see Keypad Lock Interrupt Mask Timer.
*/
                                                              // OR-ing
#define REG_KP_LCK_TIMER_LOCK1_TO_LOCK2_TIMER                 0B00000111
#define REG_KP_LCK_TIMER_KEYPAD_LOCK_INTERRUPT_MASK_TIMER     0B11111000

extern uint8_t Keypad_events_stack[10];
extern uint8_t CAN_Buffer[32][8];

uint8_t Keypad_READ_Process();
uint8_t Keypad_Write(uint8_t Reg_Name, uint8_t reg_write_value);
uint8_t Keypad_Read(uint8_t Reg_Name);
uint8_t Keypad_Init();
uint8_t Keypad_Get_Keys();

/*void Keypad_READ_Process();
uint8_t Keypad_READ();
void Keypad_Write_Reg(uint8_t register_name, uint8_t register_data);
uint8_t Keypad_Read_Reg(uint8_t register_name);         */


#endif
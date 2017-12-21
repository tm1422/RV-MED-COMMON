// LED DRIVER**********************************************

// END OF LED DRIVER***************************************

#include <Module_LED.h>

 sbit LED_LE at GPIOA_ODR.B5;
 sbit LED_OE1 at GPIOA_ODR.B7;
 sbit LED_OE2 at GPIOA_ODR.B6;
 sbit LED_CLK at GPIOB_ODR.B13;
 sbit LED_MOSI at GPIOB_ODR.B15;




void LED_Init(){

/*    SPI2_Init_Advanced(_SPI_FPCLK_DIV64, _SPI_MASTER | _SPI_8_BIT |
                       _SPI_CLK_IDLE_LOW | _SPI_FIRST_CLK_EDGE_TRANSITION |
                       _SPI_MSB_FIRST | _SPI_SS_DISABLE | _SPI_SSM_ENABLE | _SPI_SSI_1,
                       &_GPIO_MODULE_SPI2_PB13_14_15); */
/*    SPI2_Init_Advanced(_SPI_FPCLK_DIV2, _SPI_8_BIT | _SPI_MASTER | _SPI_CLK_IDLE_LOW
                                         | _SPI_FIRST_CLK_EDGE_TRANSITION | _SPI_MSB_FIRST
                                         | _SPI_SSM_ENABLE | _SPI_SS_DISABLE | _SPI_SSI_1,
                                         &_GPIO_MODULE_SPI2_PB13_14_15);                       */


//    GPIO_Config(&GPIOA_BASE, _GPIO_PINMASK_ALL, _GPIO_CFG_SPEED_MAX);
/*    GPIO_Config(&GPIOA_BASE, _GPIO_PINMASK_7, _GPIO_CFG_DIGITAL_OUTPUT); // OE1
    GPIO_Config(&GPIOA_BASE, _GPIO_PINMASK_6, _GPIO_CFG_DIGITAL_OUTPUT); // OE2  */
    GPIO_Config(&GPIOA_BASE, _GPIO_PINMASK_5, _GPIO_CFG_DIGITAL_OUTPUT); // LE
    GPIO_Config(&GPIOB_BASE, _GPIO_PINMASK_13, _GPIO_CFG_DIGITAL_OUTPUT); // CLK
    GPIO_Config(&GPIOB_BASE, _GPIO_PINMASK_15, _GPIO_CFG_DIGITAL_OUTPUT); // MOSI

//    SPI_Set_Active(SPI2_Read, SPI2_Write);
    
/*    LED_OE1 = 1;
    LED_OE2 = 1;  */

}

void LED_Process(){
    
    Manual_SPI2_Write(Configuration_Table[CONF_TABLE_LED][CONF_TABLE_LED_STATUS_33_48]);
    Manual_SPI2_Write(Configuration_Table[CONF_TABLE_LED][CONF_TABLE_LED_STATUS_17_32]);
    Manual_SPI2_Write(Configuration_Table[CONF_TABLE_LED][CONF_TABLE_LED_STATUS_1_16]);
    
    LED_LE = 1;
//    Delay_us(1);
    LED_LE = 0;  // Latch data
/*    LED_OE1 = 0;
    LED_OE2 = 0;  */
}
      

void Manual_SPI2_Write(uint16_t RX_Data){
  uint16_t i;
  
  for(i = 0; i < 16; i++){
    if(RX_Data & (0B0000000000000001<<i) ) LED_MOSI = 1;
    else LED_MOSI = 0;
    
//    Delay_us(1);
  
    LED_CLK = 1;
//    Delay_us(1);
    LED_CLK = 0;
  
  }
}

void LED_Set_15(){

    Manual_SPI2_Write(43690);
    Manual_SPI2_Write(32769);
    LED_LE = 1;
//    Delay_us(1);
    LED_LE = 0;  // Latch data
    LED_OE1 = 0;
    LED_OE2 = 0;
}

void LED_Set_14(){

    Manual_SPI2_Write(43690);
    Manual_SPI2_Write(16386);
    LED_LE = 1;
//    Delay_us(1);
    LED_LE = 0;  // Latch data
    LED_OE1 = 0;
    LED_OE2 = 0;

}

void LED_Clear(){

    Manual_SPI2_Write(0);
    Manual_SPI2_Write(0);
    LED_LE = 1;
//    Delay_us(1);
    LED_LE = 0;  // Latch data
    LED_OE1 = 0;
    LED_OE2 = 0;

}

void LED_Set(){

    Manual_SPI2_Write(0);
    Manual_SPI2_Write(32768);
    LED_LE = 1;
//    Delay_us(1);
    LED_LE = 0;  // Latch data
    LED_OE1 = 0;
    LED_OE2 = 0;

}

void LED_OE_Toggle(){

    LED_OE1 = ~LED_OE1;
    LED_OE2 = ~LED_OE2;
}

#include <Module_CONFIG.h>
#define MANUAL_WRITE_CONFIG_TABLE 1

/* Declarations --------------------------------------------------------------*/
  // Temporary buffer for ADC results                                         //
                                                                              //
// CONFIG debug txt                                                           //
                                                                              //
const uint8_t txt_config_new_line[] = "\r\n";
const uint8_t txt_config_space[] = " ";
const uint8_t txt_config_Erase_Default[] = "Erase_FLASH_EEPROM_Page_Default();";
const uint8_t txt_config_Error[] = "ERROR!";
const uint8_t txt_config_Flag_Cleared[] = "SD Card Configuration flag cleared!";
const uint8_t txt_config_SD_Flag_Written[] = "SD Card Configuration flag set!";
const uint8_t txt_config_FLASH_WRP[] = "FLASH WRP!";
const uint8_t txt_config_PAGE_62[] = "PAGE_62 ERASED!";
const uint8_t txt_config_Error_Timeout[] = "ERROR: Timeout!";
const uint8_t txt_config_Erase_Working[] = "Erase_FLASH_EEPROM_Page_Working();";
const uint8_t txt_config_PAGE_63[] = "PAGE_63 ERASED!";
const uint8_t txt_config_Internal_Working_Flag[] = "Internal Working Config Flag...:";
const uint8_t txt_config_EE_ReadVariable[] = "EE_ReadVariable return:";
const uint8_t txt_config_No_Valid_page[] = "No valid Page found!";
const uint8_t txt_config_Variable_Found[] = "Variable found!";
const uint8_t txt_config_Variable_Not_Found[] = "Variable NOT found!";
const uint8_t txt_config_i[] = "i:";
const uint8_t txt_config_Internal_Default_Flag[] = "Internal Default Config Flag...:";
const uint8_t txt_config_ii[] = "ii:";
const uint8_t txt_config_EE_Write_FLASH_COMPLETE[] = "EE_Write Default Flag: FLASH_COMPLETE!";
const uint8_t txt_config_EE_Write_PAGE_FULL[] = "EE_Write Default Flag: PAGE_FULL!";
const uint8_t txt_config_EE_Write_NO_VALID_PAGE[] = "EE_Write Default Flag: NO_VALID_PAGE!";
const uint8_t txt_config_EE_Write_FLASH_ERROR[] = "EE_Write Default Flag: Flash error!";
const uint8_t txt_config_Get_SD_Flag[] = "Get SD Card Configuration Flag";
const uint8_t txt_config_File_Opened[] = "File Opened: Config.TXT";
const uint8_t txt_config_File_size[] = "File size = 2689";
const uint8_t txt_config_Seek_Error[] = "Seek ERROR!";
const uint8_t txt_config_Read_Error[] = "Read ERROR!";
const uint8_t txt_config_FileSize_over[] = "File size > 2689";
const uint8_t txt_config_FileSize_under[] = "File size < 2689";
const uint8_t txt_config_File_closed[] = "File closed";
const uint8_t txt_config_File_Not_Found[] = "File NOT Found: Config.TXT";
const uint8_t txt_config_Change_Dir[] = "Change Dir: root... ERROR!";
const uint8_t txt_config_Flag_1[] = "Flag: 1";
const uint8_t txt_config_Flag_0[] = "Flag: 0 or not found!";
const uint8_t txt_config_Get_Load_Working[] = "Get_Load_Internal_Working_Configuration();";
const uint8_t txt_config_Get_Load_Default[] = "Get_Load_Internal_Default_Configuration();";
const uint8_t txt_config_Internal_Default_Table[] = "Internal Default Configuration Table:";
const uint8_t txt_config_Get_Load_SD_Card[] = "Get & Load SD Card Configuration";
const uint8_t txt_config_Internal_Working_Loaded[] = "Internal working table loaded!";
const uint8_t txt_config_SD_Card_Loaded[] = "SD Card table loaded!";
const uint8_t txt_config_internal_Default_Loaded[] = "Internal default table loaded!";
const uint8_t txt_config_Init_Ext_Mem[] = "Init_Ext_Mem();";
const uint8_t txt_config_SD_Card_Detect[] = "SD Card detected and initialized.";
const uint8_t txt_config_Error_SD_Card[] = "ERROR: SD CARD NOT DETECTED!";
const uint8_t txt_config_Config_Already[] = "Config.TXT already exists.";
const uint8_t txt_config_Creating_backup[] = "Creating backup...";
const uint8_t txt_config_Config_OLD_Already[] = "Config_OLD.TXT already exists.";
const uint8_t txt_config_Deleting[] = "Deleting...";
const uint8_t txt_config_Done[] = "Done!";
const uint8_t txt_config_New_File_Created[] = "New file created: Config.TXT!";
const uint8_t txt_config_Config_Exported[] = "Config.TXT exported to SD Card!";
const uint8_t txt_config_New_File_Failed[] = "New file creation FAILED: Config.TXT!";
const uint8_t txt_config_Config_Default_Already[] = "Config_DEFAULT.TXT already exists.";
const uint8_t txt_config_Config_Default_OLD_Already[] = "Config_DEFAULT_OLD.TXT already exists.";
const uint8_t txt_config_Backup_Created[] = "Backup created: Config_DEFAULT_OLD.TXT!";
const uint8_t txt_config_New_File_Created_Default[] = "New file created: Config_DEFAULT.TXT!";
const uint8_t txt_config_New_File_Failed_Default[] = "New file creation FAILED: Config_DEFAULT.TXT!";
const uint8_t txt_config_Config_Write_Rand[] = "Config_Table_Write_Rand();";
const uint8_t txt_config_Config_Write_To_Working[] = "Config_Table_Write_To_Working();";
const uint8_t txt_config_Config_Write_To_Default[] = "Config_Table_Write_To_Default();";
const uint8_t txt_config_EE_Init_Return[] = "EE_Init return:";
const uint8_t txt_config_EEPROM_Init_OK[] = "EEPROM emulator Init OK!";
const uint8_t txt_config_EEPROM_Init_ERROR[] = "EEPROM emulator Init ERROR!";
const uint8_t txt_config_FLASH_Unlocked[] = "FLASH Unlocked!";



void Write_Virtual_Addresses_For_EEPROM(){
unsigned int i;

  for(i=0; i<192; i++){
    VirtAddVarTab[i] = i;
  }
  for(i=192; i<384; i++){
    VirtAddVarTab[i] = i + 0x1000;
  }
  VirtAddVarTab[384] = 0x0FFF;
  VirtAddVarTab[385] = 0x1FFF;
/*

// Virtual EEPROM Addrs
uint16_t VirtAddVarTab[NB_OF_VAR] = {                                                                                           // default config table addresses
0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F, // CONF_TABLE_GPIO1_IN
0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F, // CONF_TABLE_GPIO2_PULL_UP_DOWN
0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F, // CONF_TABLE_GPIO3_OUTPUT
0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F,
0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 0x008E, 0x008F,
0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F,
0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
                                                                                                                                 // working config table addresses
0x1000, 0x1001, 0x1002, 0x1003, 0x1004, 0x1005, 0x1006, 0x1007, 0x1008, 0x1009, 0x100A, 0x100B, 0x100C, 0x100D, 0x100E, 0x100F,  // CONF_TABLE_GPIO1_IN
0x1010, 0x1011, 0x1012, 0x1013, 0x1014, 0x1015, 0x1016, 0x1017, 0x1018, 0x1019, 0x101A, 0x101B, 0x101C, 0x101D, 0x101E, 0x101F,  // CONF_TABLE_GPIO2_PULL_UP_DOWN
0x1020, 0x1021, 0x1022, 0x1023, 0x1024, 0x1025, 0x1026, 0x1027, 0x1028, 0x1029, 0x102A, 0x102B, 0x102C, 0x102D, 0x102E, 0x102F,  // CONF_TABLE_GPIO3_OUTPUT
0x1030, 0x1031, 0x1032, 0x1033, 0x1034, 0x1035, 0x1036, 0x1037, 0x1038, 0x1039, 0x103A, 0x103B, 0x103C, 0x103D, 0x103E, 0x103F,
0x1040, 0x1041, 0x1042, 0x1043, 0x1044, 0x1045, 0x1046, 0x1047, 0x1048, 0x1049, 0x104A, 0x104B, 0x104C, 0x104D, 0x104E, 0x104F,
0x1050, 0x1051, 0x1052, 0x1053, 0x1054, 0x1055, 0x1056, 0x1057, 0x1058, 0x1059, 0x105A, 0x105B, 0x105C, 0x105D, 0x105E, 0x105F,
0x1060, 0x1061, 0x1062, 0x1063, 0x1064, 0x1065, 0x1066, 0x1067, 0x1068, 0x1069, 0x106A, 0x106B, 0x106C, 0x106D, 0x106E, 0x106F,
0x1070, 0x1071, 0x1072, 0x1073, 0x1074, 0x1075, 0x1076, 0x1077, 0x1078, 0x1079, 0x107A, 0x107B, 0x107C, 0x107D, 0x107E, 0x107F,
0x1080, 0x1081, 0x1082, 0x1083, 0x1084, 0x1085, 0x1086, 0x1087, 0x1088, 0x1089, 0x108A, 0x108B, 0x108C, 0x108D, 0x108E, 0x108F,
0x1090, 0x1091, 0x1092, 0x1093, 0x1094, 0x1095, 0x1096, 0x1097, 0x1098, 0x1099, 0x109A, 0x109B, 0x109C, 0x109D, 0x109E, 0x109F,
0x10A0, 0x10A1, 0x10A2, 0x10A3, 0x10A4, 0x10A5, 0x10A6, 0x10A7, 0x10A8, 0x10A9, 0x10AA, 0x10AB, 0x10AC, 0x10AD, 0x10AE, 0x10AF,
0x10B0, 0x10B1, 0x10B2, 0x10B3, 0x10B4, 0x10B5, 0x10B6, 0x10B7, 0x10B8, 0x10B9, 0x10BA, 0x10BB, 0x10BC, 0x10BD, 0x10BE, 0x10BF,

0x0FFF,                                                                                                                          // Default config flag address / CRC
0x1FFF                                                                                                                           // Working config flag address / CRC
}; */
}

void Erase_FLASH_EEPROM_Page_Default(){
  uint16_t tmp;
  _FLASH_Unlock();
  tmp = FLASH_ErasePage(0x0801F000);
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Erase_Default);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
                                                                                
  if(tmp==FLASH_ERROR_PROGRAM){                                                  
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Error);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(tmp==FLASH_ERROR_WRP){                                                  
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_FLASH_WRP);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(tmp==FLASH_COMPLETE){                                                   
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_PAGE_62);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(tmp==FLASH_TIMEOUT){                                                    
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Error_Timeout);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  
  //FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
                                                                                if(Config_Debug_Mode())  UART1_Write_Text(txt_config_new_line);
}

void Erase_FLASH_EEPROM_Page_Working(){
  uint16_t tmp;
  _FLASH_Unlock();
  tmp = FLASH_ErasePage(0x0801F800);
  
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Erase_Working);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  
  if(tmp==FLASH_ERROR_PROGRAM){                                                   
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Error);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(tmp==FLASH_ERROR_WRP){                                                  
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_FLASH_WRP);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(tmp==FLASH_COMPLETE){                                                   
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_PAGE_63);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(tmp==FLASH_TIMEOUT){                                                    
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Error_Timeout);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
                                                                                if(Config_Debug_Mode())  UART1_Write_Text(txt_config_new_line);
}


uint16_t Internal_Working_Configuration_Flag(){
  uint32_t i=0;
  uint16_t err;

                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Internal_Working_Flag);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }

  _FLASH_Unlock();
  _EE_Init();

  err = EE_ReadVariable(EE_INTERNAL_WORKING_TABLE_BASE_ADDRESS + EE_FLAG_ADDRESS_OFFSET, &i);

                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_ReadVariable);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  Debug_IntToStr(err);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
                                                                                  
  if(err == 0xAB){                                                                
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_No_Valid_page);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(err == 0){                                                              
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Variable_Found);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
                                                                                  
  }
  else if (err == 1){                                                             
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Variable_Not_Found);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_i);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  Debug_IntToStr(i);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  if(err != 0) return 0;
  else if (i != 1) return 0;
  else return 1;
}

uint16_t Internal_Default_Configuration_Flag(){
  uint16_t i = 0, j=0;
  uint16_t ii=0;
  uint16_t err;
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Internal_Default_Flag);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  _FLASH_Unlock();
  _EE_Init();
  
  
/*
  *           - FLASH_COMPLETE: on success
  *           - PAGE_FULL: if valid page is full
  *           - NO_VALID_PAGE: if no valid page was found
  *           - Flash error code: on write Flash error
*/

/*  err = EE_WriteVariable(EE_INTERNAL_DEFAULT_TABLE_BASE_ADDRESS + EE_FLAG_ADDRESS_OFFSET, 1);

                                                                                             for(i = 0; i < 12; i++){
                                                                                               for(j=0; j<16; j++){
                                                                                                   err = EE_WriteVariable(EE_INTERNAL_DEFAULT_TABLE_BASE_ADDRESS + i*16 + j, i*16 + j);
                                                                                                    if(err == FLASH_COMPLETE) UART1_Write_Text("EE_Write Default Flag: FLASH_COMPLETE! \r\n");
                                                                                                    else if(err == PAGE_FULL) UART1_Write_Text("EE_Write Default Flag: PAGE_FULL! \r\n");
                                                                                                    else if(err == NO_VALID_PAGE) UART1_Write_Text("EE_Write Default Flag: NO_VALID_PAGE! \r\n");
                                                                                                    else {
                                                                                                      UART1_Write_Text("EE_Write Default Flag: Flash error! \r\n");
                                                                                                      IntToStr(err, TxT);
                                                                                                      UART1_Write_Text(TxT);
                                                                                                      UART1_Write_Text("\r\n");
                                                                                                    }
                                                                                               }
                                                                                             }
  if(err == FLASH_COMPLETE) UART1_Write_Text("EE_Write Default Flag: FLASH_COMPLETE! \r\n");
  else if(err == PAGE_FULL) UART1_Write_Text("EE_Write Default Flag: PAGE_FULL! \r\n");
  else if(err == NO_VALID_PAGE) UART1_Write_Text("EE_Write Default Flag: NO_VALID_PAGE! \r\n");
  else {
    UART1_Write_Text("EE_Write Default Flag: Flash error! \r\n");
    IntToStr(err, TxT);
    UART1_Write_Text(TxT);
    UART1_Write_Text("\r\n");
  }*/

  err = EE_ReadVariable(EE_INTERNAL_DEFAULT_TABLE_BASE_ADDRESS + EE_FLAG_ADDRESS_OFFSET, &ii);
  
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_ReadVariable);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  Debug_IntToStr(err);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
                                                                                  
  if(err == 0xAB){                                                                
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_No_Valid_page);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(err == 0){                                                              
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Variable_Found);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if (err == 1){                                                             
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Variable_Not_Found);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_ii);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  Debug_IntToStr(ii);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }

  if(err != 0) return 0;
  else if (ii != 1) return 0;
  else return 1;
}

uint16_t Write_Flag_To_Default_Config_Table(){
  uint8_t TxT[7];
  uint16_t err;
  
  _FLASH_Unlock();
  _EE_Init();
  
  err = EE_WriteVariable(EE_INTERNAL_DEFAULT_TABLE_BASE_ADDRESS + EE_FLAG_ADDRESS_OFFSET, 1);
  
  if(err == FLASH_COMPLETE){                                                     
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_FLASH_COMPLETE);
                                                                                }  UART1_Write_Text(txt_config_new_line);
                                                                                  
  }
  else if(err == PAGE_FULL){                                                     
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_PAGE_FULL);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(err == NO_VALID_PAGE){                                                 
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_NO_VALID_PAGE);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else {
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_FLASH_ERROR);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  Debug_IntToStr(err);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
}

uint16_t Write_Flag_To_Working_Config_Table(){
  uint16_t err;
  
  _FLASH_Unlock();
  _EE_Init();
  
  err = EE_WriteVariable(EE_INTERNAL_WORKING_TABLE_BASE_ADDRESS + EE_FLAG_ADDRESS_OFFSET, 1);
  
  if(err == FLASH_COMPLETE){                                                     
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_FLASH_COMPLETE);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(err == PAGE_FULL){                                                     
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_PAGE_FULL);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(err == NO_VALID_PAGE){                                                 
  
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_NO_VALID_PAGE);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else {
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_FLASH_ERROR);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  Debug_IntToStr(err);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
}

void Clear_Default_Config_Table_Flag(){
  uint16_t err;

  _FLASH_Unlock();
  _EE_Init();

  err = EE_WriteVariable(EE_INTERNAL_DEFAULT_TABLE_BASE_ADDRESS + EE_FLAG_ADDRESS_OFFSET, 0);

  if(err == FLASH_COMPLETE){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_FLASH_COMPLETE);
                                                                                }  UART1_Write_Text(txt_config_new_line);

  }
  else if(err == PAGE_FULL){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_PAGE_FULL);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(err == NO_VALID_PAGE){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_NO_VALID_PAGE);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else {
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_FLASH_ERROR);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  Debug_IntToStr(err);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);


}


void Clear_Working_Config_Table_Flag(){
  uint16_t err;

  _FLASH_Unlock();
  _EE_Init();

  err = EE_WriteVariable(EE_INTERNAL_WORKING_TABLE_BASE_ADDRESS + EE_FLAG_ADDRESS_OFFSET, 0);

  if(err == FLASH_COMPLETE){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_FLASH_COMPLETE);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(err == PAGE_FULL){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_PAGE_FULL);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else if(err == NO_VALID_PAGE){

                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_NO_VALID_PAGE);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else {
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Write_FLASH_ERROR);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  Debug_IntToStr(err);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);

}




uint16_t SD_Card_Working_Configuration_Flag(){

  int16_t rfhand=0;
  int16_t j=0, i=0;
  uint32_t size=0;
  char rdbuf[1] = {' '};
  uint16_t flag = 0;
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Get_SD_Flag);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  SPI_Set_Active(SPI2_Read, SPI2_Write);
  if(!FAT32_ChangeDir("\\")){
    rfhand = FAT32_Open("Config.TXT", 0x01); // READ
    if(rfhand > -1){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_Opened);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      FAT32_Size("Config.TXT", &size);

      if(size==2689){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_size);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
        
        if(FAT32_Seek(rfhand, 2688)){                                           
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Seek_Error);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
        }
          if(!FAT32_Read(rfhand, &rdbuf, 1)){
            flag = atoi(rdbuf);
          }
          else{
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Read_Error);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
          }
      }
      else if(size>2689){                                                       
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_FileSize_over);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      }
      else{                                                                     
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_FileSize_under);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      }
      if(!FAT32_Close(rfhand)){                                                 
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_closed);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      }
    }
    else{                                                                       
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_Not_Found);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    }
  }
  else{                                                                         
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Change_Dir);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  if(flag == 1){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Flag_1);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else{
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Flag_0);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  return flag;
}

void Write_Clear_SD_Card_Configuration_Flag(uint8_t Flag){

  int16_t rfhand=0;
  uint32_t size=0;

                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Get_SD_Flag);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  SPI_Set_Active(SPI2_Read, SPI2_Write);
  if(!FAT32_ChangeDir("\\")){
    rfhand = FAT32_Open("Config.TXT", FILE_APPEND); // READ
    if(rfhand > -1){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_Opened);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      FAT32_Size("Config.TXT", &size);

      if(size==2689){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_size);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }

        if(FAT32_Seek(rfhand, 2688)){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Seek_Error);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
        }
          if(Flag){
            if(!FAT32_Write(rfhand, "1", 1)){
                                                                                  if(Config_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_config_SD_Flag_Written);
                                                                                    UART1_Write_Text(txt_config_new_line);
                                                                                  }
            }
            else{
                                                                                  if(Config_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_config_Read_Error);
                                                                                    UART1_Write_Text(txt_config_new_line);
                                                                                  }
            }
          }
          else{
            if(!FAT32_Write(rfhand, "0", 1)){
                                                                                  if(Config_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_config_SD_Flag_Written);
                                                                                    UART1_Write_Text(txt_config_new_line);
                                                                                  }
            }
            else{
                                                                                  if(Config_Debug_Mode()){
                                                                                    UART1_Write_Text(txt_config_Read_Error);
                                                                                    UART1_Write_Text(txt_config_new_line);
                                                                                  }
            }
          }
      }
      else if(size>2689){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_FileSize_over);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      }
      else{
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_FileSize_under);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      }
      if(!FAT32_Close(rfhand)){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_closed);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      }
    }
    else{
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_Not_Found);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    }
  }
  else{
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Change_Dir);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
}

void Get_Load_Internal_Working_Configuration(){
  uint16_t i = 0, j=0;
  
  _FLASH_Unlock();
  _EE_Init();
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Get_Load_Working);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  for(i = 0; i < 12; i++){
    for(j=0; j<16; j++){
        EE_ReadVariable(EE_INTERNAL_WORKING_TABLE_BASE_ADDRESS + i*16 + j, &Configuration_Table[i][j]);
        
                                                                                if(Config_Debug_Mode()){
                                                                                  Debug_IntToStr(Configuration_Table[i][j]);
                                                                                  UART1_Write_Text(txt_config_space);
                                                                                }
                                                                                
      if(j==15){
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
      }
    }
  }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
}

void Get_Load_Internal_Default_Configuration(){
  uint16_t i, j;
  
  _FLASH_Unlock();
  _EE_Init();
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Get_Load_Default);
                                                                                  UART1_Write_Text(txt_config_new_line);

                                                                                  UART1_Write_Text(txt_config_Internal_Default_Table);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
                                                                                
  for(i = 0; i < 12; i++){
    for(j=0; j<16; j++){
        EE_ReadVariable(EE_INTERNAL_DEFAULT_TABLE_BASE_ADDRESS + i*16 + j, &Configuration_Table[i][j]);
        
                                                                                if(Config_Debug_Mode()){
                                                                                  Debug_WordToStr(Configuration_Table[i][j]);
                                                                                  UART1_Write_Text(txt_config_space);
                                                                                }
                                                                                  
        if(j==15){                                                              
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
        }
    }
  }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
}

void Get_Load_SD_Card_Working_Configuration(){
  int16_t rfhand=0;
  int16_t j=0, i=0;
  uint32_t size=0;
  char rdbuf[6] = {' ', ' ', ' ', ' ', ' ', ' '};
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Get_Load_SD_Card);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
                                                                                
  SPI_Set_Active(SPI2_Read, SPI2_Write);
  if(!FAT32_ChangeDir("\\")){
    rfhand = FAT32_Open("Config.TXT", 0x01); // READ
    if(rfhand > -1){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_Opened);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      FAT32_Size("Config.TXT", &size);

      if(size==2689){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_size);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
        for(i = 0; i < 12; i++){
          for(j=0; j<16; j++){
            if(FAT32_Seek(rfhand, 6+14*(i*16+j))){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Seek_Error);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
            }
            if(!FAT32_Read(rfhand, &rdbuf, 6)){
              Configuration_Table[i][j] = atoi(rdbuf);
            }
            else{
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Read_Error);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
            }
          }
        }
      }
      else if(size>2689){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_FileSize_over);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      }
      else{
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_FileSize_under);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      }

      if(!FAT32_Close(rfhand)){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_closed);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      }
    }
    else{
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_File_Not_Found);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    }
  }
  else{
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Change_Dir);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
}

unsigned int Get_Load_Working_Configuration(){
   unsigned int return_value = 1;

   if(SD_Card_Working_Configuration_Flag()){                                                                                            // if SD card config flag
    Get_Load_SD_Card_Working_Configuration();                                                                                           // load configuration table from SD card
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_SD_Card_Loaded);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
   Config_Table_Write_To_Working();
   Write_Flag_To_Working_Config_Table();
                                                                                                        // save this configuration table to internal working table
   Write_Clear_SD_Card_Configuration_Flag(0);                                                                                                   // clear SD card configuration flag
  }
  else if(Internal_Default_Configuration_Flag()){                                                                                       // if internal default config flag
    Get_Load_Internal_Default_Configuration();
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_internal_Default_Loaded);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    Config_Table_Write_To_Working();                                                                                                    // save this configuration table to internal working table
    Write_Flag_To_Working_Config_Table();
    Clear_Default_Config_Table_Flag();                                                                                                  // clear default configuration flag
  }
  else if(Internal_Working_Configuration_Flag()){
    Get_Load_Internal_Working_Configuration();
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Internal_Working_Loaded);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  else{
    Configuration_Table_Hand_Write();
    Config_Table_Write_To_Working();
   Write_Flag_To_Working_Config_Table();
  }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
  return return_value;
}

unsigned int Init_Ext_Mem() {
  // Place your code here
unsigned int j, i, return_value = 0;

  rfHandle    = -1;
  rfName      = "RV_CBD_2.RES";
  rfStartSect = 0;

  GPIO_Config(&GPIOA_BASE, _GPIO_PINMASK_14, _GPIO_CFG_DIGITAL_INPUT | _GPIO_CFG_PULL_UP);
  if(!GPIOA_IDR.B14){
    // Place your code here
    SPI2_Init_Advanced(_SPI_FPCLK_DIV64, _SPI_MASTER | _SPI_8_BIT |
                       _SPI_CLK_IDLE_LOW | _SPI_FIRST_CLK_EDGE_TRANSITION |
                       _SPI_MSB_FIRST | _SPI_SS_DISABLE | _SPI_SSM_ENABLE | _SPI_SSI_1,
                       &_GPIO_MODULE_SPI2_PB13_14_15);
    SPI2_Init_Advanced(_SPI_FPCLK_DIV2, _SPI_8_BIT | _SPI_MASTER | _SPI_CLK_IDLE_LOW
                                         | _SPI_FIRST_CLK_EDGE_TRANSITION | _SPI_MSB_FIRST
                                         | _SPI_SSM_DISABLE | _SPI_SS_ENABLE | _SPI_SSI_1,
                                         &_GPIO_MODULE_SPI2_PB13_14_15);

    SPI_Set_Active(SPI2_Read, SPI2_Write);

    for(j=0; j<10 ;j++){
      i = Mmc_Init();
      if(i==0){
        for(j=0; j<10 ;j++){
          i = FAT32_Dev_Init();
          if(i==0){
            for(j=0; j<10 ;j++){
              i = FAT32_Init();
              if(i==0){
                
                return_value = 1;
                
                j=100;
                rfHandle    = FAT32_Open(rfName, 0x01);
                rfStartSect = FAT32_ClustToSect(fat32_fdesc[rfHandle]._1stClust);
                
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Init_Ext_Mem);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  UART1_Write_Text(txt_config_SD_Card_Detect);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }

              }
            }
          }
        }
      }
    }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
  //  SPI2_DeInit();
  }
  else{
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Error_SD_Card);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
  }
  return return_value;
}

void Export_Working_Table(){
  uint16_t i,j;
  uint8_t txt[7], txt2[4], err;
  int16_t rfhand=0;
  uint16_t tmp;
  uint32_t tmp2;

  _FLASH_Unlock();
  _EE_Init();

  SPI_Set_Active(SPI2_Read, SPI2_Write);
  if(!FAT32_ChangeDir("\\")){

    if(FAT32_Exists("Config.TXT")){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Config_Already);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  UART1_Write_Text(txt_config_Creating_backup);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }

      if(FAT32_Exists("Config_OLD.TXT")){
                                                                                
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Config_OLD_Already);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  UART1_Write_Text(txt_config_Deleting);
                                                                                  UART1_Write_Text(txt_config_Done);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
                                                                                
        FAT32_Delete("Config_OLD.TXT");
      }

      UART1_Write_Text("Backup created: Config_OLD.TXT! \r\n");

      FAT32_Rename("Config.TXT", "Config_OLD.TXT");
    }
    
    rfhand = FAT32_Open("Config.TXT", FILE_WRITE);
    if(rfhand > -1){
    
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_New_File_Created);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    
      for(i=0; i<12; i++){
        for(j=0; j<16; j++){
 
          err = FAT32_Write(rfhand, "P", strlen("P"));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
          ByteToHex(i, txt2);
//                       UART1_Write_Text(Ltrim(txt2));
          err = FAT32_Write(rfhand, txt2, strlen(txt2));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
//          err = FAT32_Write(rfhand, "0", strlen("0"));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
          ByteToHex(j, txt2);
//                       UART1_Write_Text(Ltrim(txt2));
          err = FAT32_Write(rfhand, txt2, strlen(txt2));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
          err = FAT32_Write(rfhand, " ", strlen(" "));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
          tmp2 = EE_INTERNAL_WORKING_TABLE_BASE_ADDRESS + (i*16) + j;
          EE_ReadVariable(tmp2, &tmp);
          IntToStr(tmp, txt);
//                        UART1_Write_Text(Ltrim(txt));
//                        UART1_Write_Text("\r\n");
          err = FAT32_Write(rfhand, txt, strlen(txt));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
          err = FAT32_Write(rfhand, "\r\n", strlen("\r\n"));
//                       ByteToStr(err, txt3);
 //                      UART1_Write_Text(Ltrim(txt3));
        }
        
//        UART1_Write_Text("\r\n");
        
      }
      err = FAT32_Write(rfhand, "0", strlen("0"));
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Config_Exported);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    }
    else{                                                                       
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_New_File_Failed);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    }
  
  }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
  FAT32_Close(rfhand);
}

void Export_Default_Table(){
  uint16_t i,j;
  uint8_t txt[7], txt2[4], err;
  int16_t rfhand=0;
  uint16_t tmp;
  uint32_t tmp2;

  _FLASH_Unlock();
  _EE_Init();

  SPI_Set_Active(SPI2_Read, SPI2_Write);
  if(!FAT32_ChangeDir("\\")){

    if(FAT32_Exists("Config_DEFAULT.TXT")){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Config_Default_Already);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  UART1_Write_Text(txt_config_Creating_backup);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      
      if(FAT32_Exists("Config_DEFAULT_OLD.TXT")){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Config_Default_OLD_Already);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  UART1_Write_Text(txt_config_Deleting);
                                                                                  UART1_Write_Text(txt_config_Done);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
        FAT32_Delete("Config_DEFAULT_OLD.TXT");
      }
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Backup_Created);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
      FAT32_Rename("Config_DEFAULT.TXT", "Config_DEFAULT_OLD.TXT");
    }


    
    rfhand = FAT32_Open("Config_DEFAULT.TXT", FILE_WRITE);
    if(rfhand > -1){

                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_New_File_Created_Default);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }

      for(i=0; i<12; i++){
        for(j=0; j<16; j++){

          err = FAT32_Write(rfhand, "P", strlen("P"));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
          ByteToHex(i, txt2);
//                       UART1_Write_Text(Ltrim(txt2));
          err = FAT32_Write(rfhand, txt2, strlen(txt2));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
//          err = FAT32_Write(rfhand, "0", strlen("0"));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
          ByteToHex(j, txt2);
//                       UART1_Write_Text(Ltrim(txt2));
          err = FAT32_Write(rfhand, txt2, strlen(txt2));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
          err = FAT32_Write(rfhand, " ", strlen(" "));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
          tmp2 = EE_INTERNAL_DEFAULT_TABLE_BASE_ADDRESS + (i*16) + j;
          EE_ReadVariable(tmp2, &tmp);
          IntToStr(tmp, txt);
//                        UART1_Write_Text(Ltrim(txt));
//                        UART1_Write_Text("\r\n");
          err = FAT32_Write(rfhand, txt, strlen(txt));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
          err = FAT32_Write(rfhand, "\r\n", strlen("\r\n"));
//                       ByteToStr(err, txt3);
//                       UART1_Write_Text(Ltrim(txt3));
        }

//        UART1_Write_Text("\r\n");

      }
      err = FAT32_Write(rfhand, "0", strlen("0"));      // write flag = 0
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Config_Exported);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    }
    else{                                                                        
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_New_File_Failed);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    }
  }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
  FAT32_Close(rfhand);
}

void Config_Table_Write_Rand(){
  uint16_t i, j;
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Config_Write_Rand);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
                                                                                  
   for(i = 0; i < 12; i++){
     for(j=0; j<16; j++){
       Configuration_Table[i][j] = rand();
     }
   }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
}

void Config_Table_Write_To_Working(){
  uint16_t i, j;

   _FLASH_Unlock();
   _EE_Init();
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Config_Write_To_Working);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
                                                                                
   for(i = 0; i < 12; i++){
     for(j=0; j<16; j++){
       EE_WriteVariable(EE_INTERNAL_WORKING_TABLE_BASE_ADDRESS + i*16 + j, Configuration_Table[i][j]);
     }
   }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
}

void Config_Table_Write_To_Default(){
  uint16_t i, j;

  _FLASH_Unlock();
  _EE_Init();
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_Config_Write_To_Default);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
                                                                                
   for(i = 0; i < 12; i++){
     for(j=0; j<16; j++){
       EE_WriteVariable(EE_INTERNAL_DEFAULT_TABLE_BASE_ADDRESS + i*16 + j, Configuration_Table[i][j]);
     }
   }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
}

void Write_Config_Table_To_UART(){
   uint8_t TxT[7];
     uint16_t i, j;
   for(i = 0; i < 12; i++){
     for(j=0; j<16; j++){
       WordToStr(Configuration_Table[i][j], TxT);
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(TxT);
                                                                                  UART1_Write_Text(txt_config_space);
                                                                                }
       if(j==15){
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
       }
     }
   }
                                                                                if(Config_Debug_Mode()) UART1_Write_Text(txt_config_new_line);
}

void _EE_Init(){
  uint16_t err;
  if(!EE_Init_State){
    _FLASH_Unlock();
    err=EE_Init();
    EE_Init_State = 1;
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EE_Init_Return);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                  Debug_IntToStr(err);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
                                                                                
    if(err == FLASH_COMPLETE){
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EEPROM_Init_OK);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    }
  
    else{
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_EEPROM_Init_ERROR);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    }
  }
}

void _FLASH_Unlock(){
  if(!FLASH_Unlock_State){
    FLASH_Unlock();
                                                                                if(Config_Debug_Mode()){
                                                                                  UART1_Write_Text(txt_config_FLASH_Unlocked);
                                                                                  UART1_Write_Text(txt_config_new_line);
                                                                                }
    FLASH_Unlock_State = 1;
  }
}


uint8_t Config_Debug_Mode(){
  if(Configuration_Table[CONF_TABLE_DEBUG][CONF_TABLE_DEBUG_MASK1] & 0B0000000001000000) return 1;
  else return 0;
}





void Configuration_Table_Hand_Write(){

  Configuration_Table[0][0] = 59149;           // DIN
  Configuration_Table[0][1] = 5120;
  Configuration_Table[0][2] = 8192;
  Configuration_Table[0][3] = 0;
  Configuration_Table[0][4] = 0;
  Configuration_Table[0][5] = 0;
  Configuration_Table[0][6] = 18;              // AIN
  Configuration_Table[0][7] = 0;
  Configuration_Table[0][8] = 0;
  Configuration_Table[0][9] = 0;
  Configuration_Table[0][10] = 0;
  Configuration_Table[0][11] = 0;
  Configuration_Table[0][12] = 0;
  Configuration_Table[0][13] = 0;
  Configuration_Table[0][14] = 200;         // DIN CAN OUT 1 200
  Configuration_Table[0][15] = 201;         // DIN CAN OUT 1 201

  Configuration_Table[1][0] = 0;             // PULL-UP
  Configuration_Table[1][1] = 192;
  Configuration_Table[1][2] = 0;
  Configuration_Table[1][3] = 0;
  Configuration_Table[1][4] = 0;
  Configuration_Table[1][5] = 0;
  Configuration_Table[1][6] = 1804;         // PULL-DOWN
  Configuration_Table[1][7] = 5120;
  Configuration_Table[1][8] = 8192;
  Configuration_Table[1][9] = 0;
  Configuration_Table[1][10] = 0;
  Configuration_Table[1][11] = 0;
  Configuration_Table[1][12] = 0;             // MCO
  Configuration_Table[1][13] = 0;
  Configuration_Table[1][14] = 0;
  Configuration_Table[1][15] = 0;

  Configuration_Table[2][0] = 32992;         // DOUT
  Configuration_Table[2][1] = 2054;
  Configuration_Table[2][2] = 0;
  Configuration_Table[2][3] = 0;
  Configuration_Table[2][4] = 0;
  Configuration_Table[2][5] = 0;
  Configuration_Table[2][6] = 0;             // DOUT STATE
  Configuration_Table[2][7] = 2048;
  Configuration_Table[2][8] = 0;
  Configuration_Table[2][9] = 0;
  Configuration_Table[2][10] = 0;
  Configuration_Table[2][11] = 0;
  Configuration_Table[2][12] = 0;
  Configuration_Table[2][13] = 0;
  Configuration_Table[2][14] = 202;         // DOUT CAN IN 1 202
  Configuration_Table[2][15] = 203;         // DOUT CAN IN 2 203

  Configuration_Table[3][0] = 255;           // ADC
  Configuration_Table[3][1] = 1;
  Configuration_Table[3][2] = 255;
  Configuration_Table[3][3] = 255;
  Configuration_Table[3][4] = 1;
  Configuration_Table[3][5] = 255;
  Configuration_Table[3][6] = 255;
  Configuration_Table[3][7] = 255;
  Configuration_Table[3][8] = 0;              // DAC
  Configuration_Table[3][9] = 0;
  Configuration_Table[3][10] = 0;
  Configuration_Table[3][11] = 0;
  Configuration_Table[3][12] = 0;
  Configuration_Table[3][13] = 0;
  Configuration_Table[3][14] = 33041;         // ADC CAN OUT 111
  Configuration_Table[3][15] = 0;             // DAC CAN IN 0

  Configuration_Table[4][0] = 0;             // COMP
  Configuration_Table[4][1] = 0;
  Configuration_Table[4][2] = 0;
  Configuration_Table[4][3] = 0;
  Configuration_Table[4][4] = 0;
  Configuration_Table[4][5] = 1;             // CAN
  Configuration_Table[4][6] = 8;
  Configuration_Table[4][7] = 3;
  Configuration_Table[4][8] = 4;
  Configuration_Table[4][9] = 4;
  Configuration_Table[4][10] = 21792;
  Configuration_Table[4][11] = 13;
  Configuration_Table[4][12] = 0;
  Configuration_Table[4][13] = 0;
  Configuration_Table[4][14] = 0;             // COMP CAN OUT 0
  Configuration_Table[4][15] = 205;         // CONFIG CAN IN 205

  Configuration_Table[5][0] = 204;            // PWM
  Configuration_Table[5][1] = 0;
  Configuration_Table[5][2] = 0;
  Configuration_Table[5][3] = 0;
  Configuration_Table[5][4] = 0;
  Configuration_Table[5][5] = 200;
  Configuration_Table[5][6] = 2;
  Configuration_Table[5][7] = 200;
  Configuration_Table[5][8] = 2;
  Configuration_Table[5][9] = 0;
  Configuration_Table[5][10] = 0;
  Configuration_Table[5][11] = 50;
  Configuration_Table[5][12] = 50;
  Configuration_Table[5][13] = 12;
  Configuration_Table[5][14] = 0;
  Configuration_Table[5][15] = 33121;         // PWM CAN IN 353

  Configuration_Table[6][0] = 0;
  Configuration_Table[6][1] = 0;
  Configuration_Table[6][2] = 0;
  Configuration_Table[6][3] = 0;
  Configuration_Table[6][4] = 0;            // RTCC
  Configuration_Table[6][5] = 0;
  Configuration_Table[6][6] = 0;            // SPEAKER CAN IN
  Configuration_Table[6][7] = 0;            // DIMMER CAN IN
  Configuration_Table[6][8] = 0;            // PWM STATUS CAN IN
  Configuration_Table[6][9] = 0;            // TEMP SET CAN IN
  Configuration_Table[6][10] = 0;            // ACCU CALCULATED CAN IN
  Configuration_Table[6][11] = 0;            // O2, TEMP, ACCU 1 CAN IN
  Configuration_Table[6][12] = 0;            // O2, TEMP, ACCU 2 CAN IN
  Configuration_Table[6][13] = 0;            // STATUS CAN IN
  Configuration_Table[6][14] = 33040;        // KEYS 1 CAN OUT 272
  Configuration_Table[6][15] = 208;          // KEYS 2 CAN OUT 208

  Configuration_Table[7][0] = 0;
  Configuration_Table[7][1] = 0;
  Configuration_Table[7][2] = 0;
  Configuration_Table[7][3] = 0;
  Configuration_Table[7][4] = 0;
  Configuration_Table[7][5] = 4;            // CAN FAST MODE
  Configuration_Table[7][6] = 25;           // TIM 1 10ms
  Configuration_Table[7][7] = 100;          // TIM 2 100ms
  Configuration_Table[7][8] = 500;          // TIM 3 500ms
  Configuration_Table[7][9] = 1000;         // TIM 4 1000ms
  Configuration_Table[7][10] = 96;           // TIM 1 : KEYS
  Configuration_Table[7][11] = 3;            // TIM 2 : DIN
  Configuration_Table[7][12] = 4;            // TIM 3 : ADC
  Configuration_Table[7][13] = 0;            // TIM 4 : 0
  Configuration_Table[7][14] = 65535;        // DEBUG : ALL
  Configuration_Table[7][15] = 65535;

  Configuration_Table[8][0] = 0;
  Configuration_Table[8][1] = 0;
  Configuration_Table[8][2] = 0;
  Configuration_Table[8][3] = 0;
  Configuration_Table[8][4] = 0;
  Configuration_Table[8][5] = 0;
  Configuration_Table[8][6] = 0;
  Configuration_Table[8][7] = 0;
  Configuration_Table[8][8] = 33269;            // SOUND can in address 501
  Configuration_Table[8][9] = 42340;            // ALARM
  Configuration_Table[8][10] = 20805;
  Configuration_Table[8][11] = 33305;
  Configuration_Table[8][12] = 0;            // SIGNAL LED STATUS : NONE
  Configuration_Table[8][13] = 65535;        // BACKLIGHT LED STATUS : ALL
  Configuration_Table[8][14] = 0;
  Configuration_Table[8][15] = 33120;        // LED CAN IN 352

  Configuration_Table[9][0] = 0;
  Configuration_Table[9][1] = 0;
  Configuration_Table[9][2] = 0;
  Configuration_Table[9][3] = 0;
  Configuration_Table[9][4] = 0;
  Configuration_Table[9][5] = 0;
  Configuration_Table[9][6] = 0;
  Configuration_Table[9][7] = 0;
  Configuration_Table[9][8] = 0;
  Configuration_Table[9][9] = 0;
  Configuration_Table[9][10] = 0;
  Configuration_Table[9][11] = 0;
  Configuration_Table[9][12] = 0;
  Configuration_Table[9][13] = 0;
  Configuration_Table[9][14] = 0;
  Configuration_Table[9][15] = 0;

  Configuration_Table[10][0] = 0;
  Configuration_Table[10][1] = 0;
  Configuration_Table[10][2] = 0;
  Configuration_Table[10][3] = 0;
  Configuration_Table[10][4] = 0;
  Configuration_Table[10][5] = 0;
  Configuration_Table[10][6] = 0;
  Configuration_Table[10][7] = 0;
  Configuration_Table[10][8] = 0;
  Configuration_Table[10][9] = 0;
  Configuration_Table[10][10] = 0;
  Configuration_Table[10][11] = 0;
  Configuration_Table[10][12] = 0;
  Configuration_Table[10][13] = 0;
  Configuration_Table[10][14] = 0;
  Configuration_Table[10][15] = 0;

  Configuration_Table[11][0] = 0;
  Configuration_Table[11][1] = 0;
  Configuration_Table[11][2] = 0;
  Configuration_Table[11][3] = 0;
  Configuration_Table[11][4] = 0;
  Configuration_Table[11][5] = 0;
  Configuration_Table[11][6] = 0;
  Configuration_Table[11][7] = 0;
  Configuration_Table[11][8] = 0;
  Configuration_Table[11][9] = 0;
  Configuration_Table[11][10] = 0;
  Configuration_Table[11][11] = 0;
  Configuration_Table[11][12] = 0;
  Configuration_Table[11][13] = 0;
  Configuration_Table[11][14] = 0;
  Configuration_Table[11][15] = 0;
}
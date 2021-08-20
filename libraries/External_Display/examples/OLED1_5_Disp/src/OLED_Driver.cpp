#include "OLED_Driver.h"
#include "ASCII_Font.h"



#if INTERFACE_4WIRE_SPI
  #if INTERFACE_3WIRE_SPI
    #error "SPI Setting Error !!"
  #endif
#elif INTERFACE_3WIRE_SPI

#else
  #error "SPI Setting Error !!"
#endif



uint8_t color_byte[2],color_fill_byte[2];


OLED_Driver::OLED_Driver(void)  {
}

void OLED_Driver::OLED_CS(uint8_t x)  {

  digitalWrite(oled_cs, x);
}

void OLED_Driver::OLED_RST(uint8_t x) {

  digitalWrite(oled_rst, x);
}

void OLED_Driver::OLED_DC(uint8_t x)  {

  digitalWrite(oled_dc, x);
}

inline void OLED_Driver::OLED_SCK(uint8_t x) {

  digitalWrite(oled_sck, x);
}
inline void OLED_Driver::OLED_DIN(uint8_t x) {

  digitalWrite(oled_din, x);
}


void OLED_Driver::Write_Command(uint8_t cmd)  {

//  OLED_CS(LOW);

#if  INTERFACE_4WIRE_SPI

  OLED_DC(LOW);
  SPI.transfer(cmd);
  OLED_DC(HIGH);

#elif INTERFACE_3WIRE_SPI

  uint8_t i;

  OLED_SCK(LOW);
  OLED_DIN(LOW);
  OLED_SCK(HIGH);

  for(i = 0x80; i > 0; i >>= 1) {

    OLED_SCK(LOW);
    
    if(cmd & i)
      OLED_DIN(HIGH);
    else
      OLED_DIN(LOW);
    
    OLED_SCK(HIGH);
  }

#endif

//  OLED_CS(HIGH);
}

void OLED_Driver::Write_Data(uint8_t dat) {

//  OLED_CS(LOW);

#if  INTERFACE_4WIRE_SPI

  OLED_DC(HIGH);
  SPI.transfer(dat);
  OLED_DC(LOW);

#elif INTERFACE_3WIRE_SPI

  uint8_t i;

  OLED_SCK(LOW);
  OLED_DIN(HIGH);
  OLED_SCK(HIGH);

  for(i = 0x80; i > 0; i >>= 1) {

    OLED_SCK(LOW);
    
    if(dat & i)
      OLED_DIN(HIGH);
    else
      OLED_DIN(LOW);
    OLED_SCK(HIGH);
  }

#endif

//  OLED_CS(HIGH);

}

#if INTERFACE_3WIRE_SPI

void OLED_Driver::Write_Data(uint8_t* dat_p, int length) {

  uint16_t i;
  uint8_t j;



  for(i = 0; i < length; i++) {

    OLED_SCK(LOW);
    OLED_DIN(HIGH);
    OLED_SCK(HIGH);
  
    for(j = 0x80; j > 0; j >>= 1) {

      OLED_SCK(LOW);
      if(dat_p[i] & j)
        OLED_DIN(HIGH);
      else
        OLED_DIN(LOW);
      OLED_SCK(HIGH);
    }
  }
}

#endif

void OLED_Driver::Set_Color(uint16_t color)  {
  
  color_byte[0] = (uint8_t)(color >> 8);
  color_byte[1] = (uint8_t)(color & 0x00ff);
}

void OLED_Driver::Set_FillColor(uint16_t color)  {
  
  color_fill_byte[0] = (uint8_t)(color >> 8);
  color_fill_byte[1] = (uint8_t)(color & 0x00ff);
}

void OLED_Driver::RAM_Address(void)  {
  
  Write_Command(0x15);
  Write_Data(0x00);
  Write_Data(0x7f);

  Write_Command(0x75);
  Write_Data(0x00);
  Write_Data(0x7f);
}

void OLED_Driver::Clear_Screen(void)  {
  
  int i,j;
  
  uint8_t clear_byte[] = {0x00, 0x00};
  RAM_Address();
  Write_Command(0x5C);
  for(i=0;i<128;i++)  {
    for(j=0;j<128;j++)  {
#if INTERFACE_4WIRE_SPI
      Write_Data(clear_byte[0]);
      Write_Data(clear_byte[1]);
#elif INTERFACE_3WIRE_SPI
      Write_Data(clear_byte, 2);
#endif
    }
  }
}


void OLED_Driver::Fill_Color(uint16_t color)  {
  
  uint16_t i,j;
  RAM_Address();
  Write_Command(0x5C);
  Set_FillColor(color);
  for(i = 0; i < 128; i++)  {
    for(j = 0; j < 128; j++)  {
#if INTERFACE_4WIRE_SPI
      Write_Data(color_fill_byte[0]);
      Write_Data(color_fill_byte[1]);
#elif INTERFACE_3WIRE_SPI
      Write_Data(color_fill_byte, 2);
#endif

    }
  }
}

void OLED_Driver::Set_Coordinate(uint16_t x, uint16_t y)  {

  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
    return;
  //Set x and y coordinate
  Write_Command(SSD1351_CMD_SETCOLUMN);
  Write_Data(x);
  Write_Data(SSD1351_WIDTH-1);
  
  Write_Command(SSD1351_CMD_SETROW);
  Write_Data(y);
  Write_Data(SSD1351_HEIGHT-1);
  
  Write_Command(SSD1351_CMD_WRITERAM);
}

void OLED_Driver::Set_Address(uint8_t column, uint8_t row)  {
  
  Write_Command(SSD1351_CMD_SETCOLUMN);  
  Write_Data(column);  //X start 
  Write_Data(column); //X end 
  Write_Command(SSD1351_CMD_SETROW); 
  Write_Data(row);  //Y start 
  Write_Data(row+7);  //Y end 
  Write_Command(SSD1351_CMD_WRITERAM); 
}

void OLED_Driver::Write_text(uint8_t dat) {
    
  uint8_t i;
    
  for(i=0;i<8;i++)  {
    if (dat & 0x01) {
#if INTERFACE_4WIRE_SPI
      Write_Data(color_byte[0]);
      Write_Data(color_byte[1]);
#elif INTERFACE_3WIRE_SPI
      Write_Data(color_byte, 2);
#endif
    }
    else  {
      Write_Data(0x00);
      Write_Data(0x00);
    }
    dat >>= 1;
  }
}

void  OLED_Driver::Invert(bool v) {
  
  if (v)
    Write_Command(SSD1351_CMD_INVERTDISPLAY);
  else
    Write_Command(SSD1351_CMD_NORMALDISPLAY);
}

void OLED_Driver::Draw_Pixel(int16_t x, int16_t y)
{
  // Bounds check.
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT)) return;
  if ((x < 0) || (y < 0)) return;

  Set_Address(x, y);
  
  // transfer data
#if INTERFACE_4WIRE_SPI
  Write_Data(color_byte[0]);
  Write_Data(color_byte[1]);
#elif INTERFACE_3WIRE_SPI
  Write_Data(color_byte, 2);
#endif
  
}
  

  
void OLED_Driver::Device_Init(void) {

#if INTERFACE_3WIRE_SPI
    
    OLED_DC(LOW);
  
#endif

  OLED_CS(LOW);
  OLED_RST(LOW);
  delay(500);
  OLED_RST(HIGH);
  delay(500);
    
  Write_Command(0xfd);  // command lock
  Write_Data(0x12);
  Write_Command(0xfd);  // command lock
  Write_Data(0xB1);

  Write_Command(0xae);  // display off
  Write_Command(0xa4);  // Normal Display mode

  Write_Command(0x15);  //set column address
  Write_Data(0x00); //column address start 00
  Write_Data(0x7f); //column address end 95
  Write_Command(0x75);  //set row address
  Write_Data(0x00); //row address start 00
  Write_Data(0x7f); //row address end 63  

  Write_Command(0xB3);
  Write_Data(0xF1);

  Write_Command(0xCA);  
  Write_Data(0x7F);

  Write_Command(0xa0);  //set re-map & data format
  Write_Data(0x74); //Horizontal address increment
            //74
  Write_Command(0xa1);  //set display start line
  Write_Data(0x00); //start 00 line

  Write_Command(0xa2);  //set display offset
  Write_Data(0x00);

  Write_Command(0xAB);  
  Write_Command(0x01);  

  Write_Command(0xB4);  
  Write_Data(0xA0);   
  Write_Data(0xB5);  
  Write_Data(0x55);    

  Write_Command(0xC1);  
  Write_Data(0xC8); 
  Write_Data(0x80);
  Write_Data(0xC0);

  Write_Command(0xC7);  
  Write_Data(0x0F);

  Write_Command(0xB1);  
  Write_Data(0x32);

  Write_Command(0xB2);  
  Write_Data(0xA4);
  Write_Data(0x00);
  Write_Data(0x00);

  Write_Command(0xBB);  
  Write_Data(0x17);

  Write_Command(0xB6);  
  Write_Data(0x01);

  Write_Command(0xBE);  
  Write_Data(0x05);

  Write_Command(0xA6);

  Clear_Screen();
  Write_Command(0xaf);   //display on
}

  
  
// Draw a horizontal line ignoring any screen rotation.
void OLED_Driver::Draw_FastHLine(int16_t x, int16_t y, int16_t length) {
  // Bounds check
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
    return;

  // X bounds check
  if (x+length > SSD1351_WIDTH) {
    length = SSD1351_WIDTH - x - 1;
  }

  if (length < 0)
    return;

  // set location
  Write_Command(SSD1351_CMD_SETCOLUMN);
  Write_Data(x);
  Write_Data(x+length-1);
  Write_Command(SSD1351_CMD_SETROW);
  Write_Data(y);
  Write_Data(y);
  // fill!
  Write_Command(SSD1351_CMD_WRITERAM);  

  for (uint16_t i=0; i < length; i++)  {
    Write_Data(color_byte[0]);
    Write_Data(color_byte[1]);
  }
}
  
  // Draw a vertical line ignoring any screen rotation.
void OLED_Driver::Draw_FastVLine(int16_t x, int16_t y, int16_t length)  {
  // Bounds check

  uint16_t i;
  
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
    return;
  // X bounds check
  if (y+length > SSD1351_HEIGHT) {
    length = SSD1351_HEIGHT - y - 1;
  }
  if (length < 0)
    return;

  // set location
  Write_Command(SSD1351_CMD_SETCOLUMN);
  Write_Data(x);
  Write_Data(x);
  Write_Command(SSD1351_CMD_SETROW);
  Write_Data(y);
  Write_Data(y+length-1);
  // fill!
  Write_Command(SSD1351_CMD_WRITERAM);  
    
  for (i = 0; i < length; i++)  {
#if INTERFACE_4WIRE_SPI
    Write_Data(color_byte[0]);
    Write_Data(color_byte[1]);
#elif INTERFACE_3WIRE_SPI
    Write_Data(color_byte, 2);
#endif
  }
}


void OLED_Driver::Display_Interface(void) {
  
  uint16_t i,j,color;
  
  Set_Coordinate(0,1);
  for(i = 0 ; i < 8 ; i++)  {
    for(j = 0; j < 128; j++) {
      if((interface_1[(i*128+j)/8]>>((i*128+j)%8))&0x01)  
        color = GREEN+((i*128+j)<<11);      
      else
        color = BLACK;
      
      Set_Color(color);
      Write_Data(color_byte[0]);
      Write_Data(color_byte[1]);
    }
  }

  Set_Coordinate(0,20);
  for(i = 0 ; i < 22 ; i++) {
    for(j = 0; j < 128; j++)  {
      if((interface_2[(i*128+j)/8]>>((i*128+j)%8))&0x01)  
        color = CYAN;
      else
        color = BLACK;
      
      Set_Color(color);
      Write_Data(color_byte[0]);
      Write_Data(color_byte[1]);
    }
  }

  Set_Coordinate(0,60);
  for(i = 0 ; i < 18 ; i++) {
    for(j = 0; j < 128; j++)  {
      if((interface_4[(i*128+j)/8]>>((i*128+j)%8))&0x01)  
        color = BLUE+(i&0xf000);
      else
        color = BLACK;
      
      Set_Color(color);
      Write_Data(color_byte[0]);
      Write_Data(color_byte[1]);      
    }
  }

  Write_Command(SSD1351_CMD_SETCOLUMN);  
  Write_Data(80);  //X start 
  Write_Data(80+8*5-1); //X end 
  Write_Command(SSD1351_CMD_SETROW); 
  Write_Data(90);  //Y start 
  Write_Data(90+16-1);  //Y end 
  Write_Command(SSD1351_CMD_WRITERAM); 
  
  for(i = 0 ; i < 16 ; i++) {
    for(j = 0; j < 8*5; j++)  {
      if((interface_text1[(i*8*5+j)/8]>>((i*8*5+j)%8))&0x01)  
        color = BLUE+0x0f00+i*128+j*32;
      else
        color = BLACK;
      
      Set_Color(color);
      Write_Data(color_byte[0]);
      Write_Data(color_byte[1]);      
    }
  }

  Write_Command(SSD1351_CMD_SETCOLUMN);  
  Write_Data(0);  //X start 
  Write_Data(0+8*9-1); //X end 
  Write_Command(SSD1351_CMD_SETROW); 
  Write_Data(90);  //Y start 
  Write_Data(90+16-1);  //Y end 
  Write_Command(SSD1351_CMD_WRITERAM); 
  
  for(i = 0 ; i < 16 ; i++) {
    for(j = 0; j < 8*9; j++)  {
      if((interface_text2[(i*8*9+j)/8]>>((i*8*9+j)%8))&0x01)  
        color = BLUE+0xf000+i*128;
      else
        color = BLACK;
      
      Set_Color(color);
      Write_Data(color_byte[0]);
      Write_Data(color_byte[1]);      
    }
  }

  Set_Coordinate(0,118);
  for(i = 0 ; i < 9 ; i++) {
    for(j = 0; j < 128; j++)  {
      if((interface_3[(i*128+j)/8]>>((i*128+j)%8))&0x01)  
        color = RED+(i*128+j);
      else
        color = BLACK;
      
      Set_Color(color);
      Write_Data(color_byte[0]);
      Write_Data(color_byte[1]);
    }
  }

  
/*
  Set_Coordinate(0,15);
  for(i = 0 ; i < 22 ; i++)  {
    for(j = 0; j < 128; j++) {
      if((interface_2[(i*128+j)/8]>>((i*128+j)%8))&0x01)  {
        if((i*128+j)<128*12)
          color = GREEN+((i*128+j)<<11);
        else if((i*128+j)<128*40)
          color = CYAN;
        else
          color = RED+(i*128+j)-128*40;
      }
      else  {
        color = BLACK;
      }
      Set_Color(color);
      Write_Data(color_byte[0]);
      Write_Data(color_byte[1]);
    }
  }*/

}





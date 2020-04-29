//This application does not rely on any libraries and it is for ILI9488

//This program is a demo of clearing screen to display black,white,red,green,blue.

//when using the BREAKOUT BOARD only and using these hardware spi lines to the LCD,
//the SDA pin and SCK pin is defined by the system and can't be modified.
//if you don't need to control the LED pin,you can set it to 3.3V and set the pin definition to -1.
//other pins can be defined by youself,for example
//pin usage as follow:
//                  CS  DC/RS  RESET  SDI/MOSI  SCK   LED    VCC     GND    
//Arduino Mega2560  A5   A3     A4       51      52   A0   5V/3.3V   GND

//Remember to set the pins to suit your display module!
/********************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE 
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**********************************************************************************/
#define LED   -1   // A0 Not use Allway +3.3V 
#define CS    5   // A5→GPIO5     
#define RS    2   // A3→GPIO2   
#define RESET -1   // A4→MRESET Not port use
#define MOSI  23   // 51→GPIO23
#define SCK   18   // 52→GPIO18

void Lcd_Writ_Bus(unsigned char d)
{
   uint8_t val = 0x80;
    while(val)
    {
      if(d&val)
      {
        digitalWrite(MOSI,HIGH);
      }
      else
      {
        digitalWrite(MOSI,LOW);
      }
      digitalWrite(SCK,LOW);
      digitalWrite(SCK,HIGH);
      val >>= 1;
    }
}

void Lcd_Write_Com(unsigned char VH)  
{   
  *(portOutputRegister(digitalPinToPort(RS))) &=  ~digitalPinToBitMask(RS);//LCD_RS=0;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Data(unsigned char VH)
{
  *(portOutputRegister(digitalPinToPort(RS)))|=  digitalPinToBitMask(RS);//LCD_RS=1;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Com_Data(unsigned char com,unsigned char dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Data(dat);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
        Lcd_Write_Com(0x2a);
	Lcd_Write_Data(x1>>8);
	Lcd_Write_Data(x1);
	Lcd_Write_Data(x2>>8);
	Lcd_Write_Data(x2);
        Lcd_Write_Com(0x2b);
	Lcd_Write_Data(y1>>8);
	Lcd_Write_Data(y1);
	Lcd_Write_Data(y2>>8);
	Lcd_Write_Data(y2);
	Lcd_Write_Com(0x2c); 							 
}

void Lcd_Init(void)
{
  // digitalWrite(RESET,HIGH);
  // delay(5); 
  // digitalWrite(RESET,LOW);
  // delay(15);
  // digitalWrite(RESET,HIGH);
  // delay(15);

  digitalWrite(CS,LOW);  //CS

    Lcd_Write_Com(0xF7);  
    Lcd_Write_Data(0xA9); 
    Lcd_Write_Data(0x51); 
    Lcd_Write_Data(0x2C); 
    Lcd_Write_Data(0x82);  

    Lcd_Write_Com(0xC0);  
    Lcd_Write_Data(0x11); 
    Lcd_Write_Data(0x09); 

    Lcd_Write_Com(0xC1);  
    Lcd_Write_Data(0x41); 

    Lcd_Write_Com(0xC5);  
    Lcd_Write_Data(0x00); 
    Lcd_Write_Data(0x0A); 
    Lcd_Write_Data(0x80);
 
    Lcd_Write_Com(0xB1);  
    Lcd_Write_Data(0xB0); 
    Lcd_Write_Data(0x11); 

    Lcd_Write_Com(0xB4);  
    Lcd_Write_Data(0x02); 
  
    Lcd_Write_Com(0xB6);    
    Lcd_Write_Data(0x02);
    Lcd_Write_Data(0x22);  
 
    Lcd_Write_Com(0xB7);    
    Lcd_Write_Data(0xC6);  

    Lcd_Write_Com(0xBE);    
    Lcd_Write_Data(0x00);   
    Lcd_Write_Data(0x04); 
 
    Lcd_Write_Com(0xE9);    
    Lcd_Write_Data(0x00);   
 
    Lcd_Write_Com(0x36);  
    Lcd_Write_Data(0x08);   

    Lcd_Write_Com(0x3A);    
    Lcd_Write_Data(0x66); 

    Lcd_Write_Com(0xE0);    
    Lcd_Write_Data(0x00);  
    Lcd_Write_Data(0x07); 
    Lcd_Write_Data(0x10); 
    Lcd_Write_Data(0x09); 
    Lcd_Write_Data(0x17); 
    Lcd_Write_Data(0x0B); 
    Lcd_Write_Data(0x41); 
    Lcd_Write_Data(0x89); 
    Lcd_Write_Data(0x4B); 
    Lcd_Write_Data(0x0A); 
    Lcd_Write_Data(0x0C); 
    Lcd_Write_Data(0x0E); 
    Lcd_Write_Data(0x18); 
    Lcd_Write_Data(0x1B); 
    Lcd_Write_Data(0x0F); 

    Lcd_Write_Com(0xE1);    
    Lcd_Write_Data(0x00);  
    Lcd_Write_Data(0x17); 
    Lcd_Write_Data(0x1A); 
    Lcd_Write_Data(0x04); 
    Lcd_Write_Data(0x0E); 
    Lcd_Write_Data(0x06); 
    Lcd_Write_Data(0x2F); 
    Lcd_Write_Data(0x45); 
    Lcd_Write_Data(0x43); 
    Lcd_Write_Data(0x02); 
    Lcd_Write_Data(0x0A); 
    Lcd_Write_Data(0x09); 
    Lcd_Write_Data(0x32); 
    Lcd_Write_Data(0x36); 
    Lcd_Write_Data(0x0F); 

    Lcd_Write_Com(0x11);    //Exit Sleep 
    delay(120); 			
    Lcd_Write_Com(0x29);    //Display on 

    digitalWrite(CS,HIGH);
}

void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{	
  unsigned int i,j;
  digitalWrite(CS,LOW);
  Lcd_Write_Com(0x02c); //write_memory_start
  //digitalWrite(RS,HIGH);
  l=l+x;
  Address_set(x,y,l,y);
  j=l*2;
  for(i=1;i<=j;i++)
  {
      Lcd_Write_Data((c>>8)&0xF8);
      Lcd_Write_Data((c>>3)&0xFC);
      Lcd_Write_Data(c<<3);
  }
  digitalWrite(CS,HIGH);   
}

void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{	
  unsigned int i,j;
  digitalWrite(CS,LOW);
  Lcd_Write_Com(0x02c); //write_memory_start
  //digitalWrite(RS,HIGH);
  l=l+y;
  Address_set(x,y,x,l);
  j=l*2;
  for(i=1;i<=j;i++)
  { 
      Lcd_Write_Data((c>>8)&0xF8);
      Lcd_Write_Data((c>>3)&0xFC);
      Lcd_Write_Data(c<<3);
  }
  digitalWrite(CS,HIGH);   
}

void Rect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}

void Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  unsigned int i;
  for(i=0;i<h;i++)
  {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}

int RGB(int r,int g,int b)
{
  return r << 16 | g << 8 | b;
}

void LCD_Clear(unsigned int j)                   
{	
  unsigned int i,m;
  digitalWrite(CS,LOW);
  Address_set(0,0,320,480);
  for(i=0;i<320;i++)
    for(m=0;m<480;m++)
    {
      Lcd_Write_Data((j>>8)&0xF8);
      Lcd_Write_Data((j>>3)&0xFC);
      Lcd_Write_Data(j<<3);
    }
  digitalWrite(CS,HIGH);   
}

void setup()
{
  // pinMode(A0,OUTPUT);  //A0:LED ON/OFF Port not use
  pinMode(2,OUTPUT);  //A3:RS GPIO2
  //pinMode(A4,OUTPUT);  //A4:Reset MReset not use Gpio use Push on EN Switch
  pinMode(5,OUTPUT);  //A5:CS GPIO5 TFT-LCD Select 
  pinMode(23,OUTPUT);  //51:MOSI GPIO23
  pinMode(18,OUTPUT);  //52:SCK GPIO18

  // digitalWrite(A0, HIGH);  //A0:LED ON/OFF Port not use
  digitalWrite(2, HIGH);  //A3:RS GPIO2
  //digitalWrite(A4, HIGH);  //A4:Reset MReset not use Gpio use Push on EN Switch
  digitalWrite(5, HIGH);  //A5:CS GPIO5 TFT-LCD Select 
  digitalWrite(23, HIGH);  //51:MOSI GPIO23
  digitalWrite(18, HIGH);  //52:SCK GPIO18
  
  Lcd_Init();
  
}

void loop()
{  
   LCD_Clear(0xf800);   //赤で画面をクリア
   LCD_Clear(0x07E0);   //緑で画面をクリア
   LCD_Clear(0x001F);   //青で画面をクリア
   LCD_Clear(0xFFFF);   //白で画面をクリア  
   LCD_Clear(0x0);      //黒で画面をクリア
   for(int i=0;i<500;i++)
  {
    Rect(random(300),random(300),random(300),random(300),random(65535)); // rectangle at x, y, with, hight, color
  }

}

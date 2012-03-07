#include<msp430g2231.h>

#define RS(X) 	P1OUT = ((P1OUT & ~BIT2) | (X))
#define EN(X)   P1OUT = ((P1IN & ~BIT1) | (X<<1)) 
#define databits P1OUT  //lower nibble
#define LINE1 cmd(0x80)
#define LINE2 cmd(0xc0)

void lcd_init(void);
void port_init(void);
void LCD_STROBE(void);
void data(unsigned char c);
void cmd(unsigned char c); 
void clear(void);
void string(char *p);

void port_init(void)
{
    P1OUT = 0 ;
    P1DIR = 0xff;
}
void LCD_STROBE(void)
{   EN(0);
     __delay_cycles(100);	
    EN(1);
    __delay_cycles(100);
    EN(0);
}
 
void data(unsigned char c)
{
    RS(1);
    __delay_cycles(10000);
    unsigned char msb , lsb ;
    msb = c & 0xf0;
    lsb = (c<<4);
    databits = (databits & 0x0f) | msb;
    LCD_STROBE();
    databits = lsb | (databits & 0x0f) ;
    LCD_STROBE();
}
 
void cmd(unsigned char c)
{
    RS(0);
    __delay_cycles(10000);
    unsigned char msb , lsb ;
    msb = c & 0xf0;
    lsb = (c<<4);
    databits = (databits & 0x0f) | msb;
    LCD_STROBE();
    databits = lsb | (databits & 0x0f) ;
    LCD_STROBE();
}
 
void clear(void)
{
    cmd(0x01);
    __delay_cycles(30000);
}
 
void lcd_init()
{
    __delay_cycles(20000);
    cmd(0x30);
    __delay_cycles(10000);
    cmd(0x30);
    __delay_cycles(1000);
    cmd(0x30);
    __delay_cycles(1000);
    cmd(0x28);            // Function set (4-bit interface, 2 lines, 5*7Pixels)
    cmd(0x28);            // Function set (4-bit interface, 2 lines, 5*7Pixels)
    cmd(0x0c);            // Make cursorinvisible
    clear();            // Clear screen
    cmd(0x6);            // Set entry Mode(auto increment of cursor)
}
 
void string(char *p)
{
    while(*p) data(*p++);
}
 
int main()
{
    port_init();
    lcd_init();
    LINE1;
    string("Hello ");
    LINE2;
    string("world!");
    while(1);
  
}

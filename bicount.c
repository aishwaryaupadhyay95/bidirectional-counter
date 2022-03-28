#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#define lcd PORTB
void lcd_cmd(int x)
{
	lcd=x & 0xf0;
	lcd=lcd+0x04;
	_delay_ms(2);
	lcd=lcd-0x04;

	lcd=(x<<4) & 0xf0;
	lcd=lcd+0x04;
	_delay_ms(2);
	lcd=lcd-0x04;

}

void lcd_data(int y)
{
	lcd=y & 0xf0;
	lcd=lcd+0x05;
	_delay_ms(2);
	lcd=lcd-0x04;

	lcd=(y<<4) & 0xf0;
	lcd=lcd+0x05;
	_delay_ms(2);
	lcd=lcd-0x04;
}
void lcd_string(char *str)
{
int j=0;
while(str[j]!=0)
{ lcd_data(str[j]);
		j++;
}
}

int lcd_number(int n)
{
int d=0;
if(n==0)
{lcd_data(48);}

lcd_cmd(0x04);
	while(n!=0)
	{ d=n%10;
	  lcd_data(d+48);
	  n=n/10;
	 }
	  lcd_cmd(0x06);
}

void lcd_init()
{
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0c);
	lcd_cmd(0x06);

}

int main()
{
DDRA=0xfc;
PORTA=0xff;
DDRB=0xff;
lcd_init();
int up=0,c=0,d=0,down=0;
lcd_cmd(0x85);
			  lcd_string("IN");
lcd_cmd(0x8a);
		  lcd_string("OUT");			  
			  
while(1)
{

if(PINA==0xfe)
{while(PINA==0xfe);
c=c+1;
}

if((PINA==0xfd) && (c==1))
{while(PINA==0xfd)
{}
up=up+1;
lcd_cmd(0xc5);
lcd_number(up);
c=0;
}
else if(PINA==0xfd)
{while(PINA==0xfd);
d=d+1;
}

if((PINA==0xfe) && (d==1))
{while(PINA==0xfe)
{}
down=down+1;
lcd_cmd(0xca);
lcd_number(down);
d=0;
}


}
}



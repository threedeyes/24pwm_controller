/*
Copyright (C) 2013-2015 Gerasim Troeglazov (3dEyes**)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in the
Software without restriction, including without limitation the rights to use, copy, 
modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to 
the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY 
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#define __AVR_LIBC_DEPRECATED_ENABLE__ 

#include <avr/io.h>
#include <avr/interrupt.h>

//initial pwm values (0-99)
unsigned char pwm[256]={
	50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50
};

unsigned int cnt = 0;
unsigned int tmp = 0;
unsigned int enabled = 0;

SIGNAL(SIG_OVERFLOW0)
{
	cli();
	TCNT0 = 222;

	if(enabled == 0)
		return;
	if(cnt == 0)
		PORTA = 255;
	
	tmp = cnt - 25;
	
	if(tmp <= 100) {
		if(tmp == pwm[0])PORTA&=~1; //A
		if(tmp == pwm[1])PORTA&=~2; //B
		if(tmp == pwm[2])PORTA&=~4; //C
		if(tmp == pwm[3])PORTA&=~8; //D
		if(tmp == pwm[4])PORTA&=~16; //E
		if(tmp == pwm[5])PORTA&=~32; //F
		if(tmp == pwm[6])PORTA&=~64; //G
		if(tmp == pwm[7])PORTA&=~128; //H
	}

	if(cnt == 400)
		PORTC = 255;
	tmp = cnt - 425;
	
	if(tmp <= 100) {
		if(tmp == pwm[8])PORTC&=~1; //I
		if(tmp == pwm[9])PORTC&=~2; //J
		if(tmp == pwm[10])PORTC&=~4; //K
		if(tmp == pwm[11])PORTC&=~8; //L
		if(tmp == pwm[12])PORTC&=~16; //M
		if(tmp == pwm[13])PORTC&=~32; //N
		if(tmp == pwm[14])PORTC&=~64; //O
		if(tmp == pwm[15])PORTC&=~128; //P
	}

	if(cnt == 800)
		PORTB = 255;
	tmp = cnt - 825;
	
	if(tmp <= 100) {
		if(tmp == pwm[16])PORTB&=~1; //Q
		if(tmp == pwm[17])PORTB&=~2; //R
		if(tmp == pwm[18])PORTB&=~4; //S
		if(tmp == pwm[19])PORTB&=~8; //T
		if(tmp == pwm[20])PORTB&=~16; //U
		if(tmp == pwm[21])PORTB&=~32; //V
		if(tmp == pwm[22])PORTB&=~64; //W
		if(tmp == pwm[23])PORTB&=~128; //X
	}

	cnt++;

	if(cnt == 1000)
		cnt = 0;
}

void USARTInit(uint16_t ubrr_value)
{
	UBRRL = ubrr_value;
	UBRRH = (ubrr_value>>8);
	UCSRC=(1<<URSEL)|(3<<UCSZ0);
	UCSRB=(1<<RXEN)|(1<<TXEN);
}

void USARTWriteChar(unsigned char data)
{
	while(!(UCSRA & (1<<UDRE))) { }
	UDR = data;
}

char USARTReadChar()
{
	while(!(UCSRA & (1<<RXC))) { }
	return UDR;
}

int main(void) 
{
	DDRB = 0xff;
	PORTB = 0x00;

	DDRA = 0xff;
	PORTA = 0x00;

	DDRC = 0xff;
	PORTC = 0x00;

	TIMSK = 0b00000001; 
	TCNT0 = 240; 
	TCCR0 = ( (1<<WGM13) |(1<<WGM12) | (1<<CS11) ) & ~0b00110000;
	
	sei();

	USARTInit(25); //UBRR = 25 (38400)

	for(;;) {
		unsigned char n = USARTReadChar();
		
		if(n >= 'A' && n <= 'X') {
			unsigned char val = USARTReadChar();
			n -= 'A';
			pwm[n] = val;
			continue;
		}

		if(n == '#') {
			unsigned char val = USARTReadChar();
			if(val == 'E')
				enabled = 1;
			if(val == 'D')
				enabled = 0;
			continue;
		}
	}
}


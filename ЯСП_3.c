#include <mega328p.h>
#include <stdio.h>
#include <delay.h>
#include <ds18b20.h>
#asm  
  .equ __w1_port=0xB; PORTD
  .equ __w1_bit=7; 
#endasm
unsigned char RomCode[2][9];
unsigned char devices;




void main(void)
{

// Предделитель частоты в 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif


PORTB=0x00;
DDRB=0xFF;// Data Direction Register, все пины на выход. На выходах нули.

PORTC=0x00;
DDRC=0x00;// Data Direction Register, все пины на вход, внутренние сопротивления отключены
 
PORTD=0x00;
DDRD=0x00;//Data Direction Register, все пины на вход, внутренние сопротивления отключены




// Инициализация внешних системных прерываний
// INT0 и INT1 отключены
// Прерывания при изменении напряжения на пинах PCINT0-7, PCINT8-14, PCINT16-23 отключены
EICRA=0x00;
EIMSK=0x00;
PCICR=0x00;

// Прерывания по таймеру
TIMSK0=0x00;
TIMSK1=0x00;
TIMSK2=0x00;

// Инициализация UARTа
// TxD + RxD
// 8 Data, 1 Stop, No Parity, Asynch
// Скорость: 9600 Бод
UCSR0A=0x00;
UCSR0B=0x18;
UCSR0C=0x06;
UBRR0H=0x00;
UBRR0L=0x33;

// Инициализация аналогового компаратора
ACSR=0x80;
ADCSRB=0x00;
DIDR1=0x00;


devices=w1_search( DS18B20_SEARCH_ROM_CMD, RomCode );


while (1)
      {

      data=UDR0;
        printf("t1 %.2f \xefC", ds18b20_temperature( &RomCode[0][0] ) );
      if(data=='1')
      {
      PORTB=0xFF;
      putchar('1');    
      printf("Hello, world!");
      }
      if(data=='0')
      {
      PORTB=0x00;
        putchar('0');
      }
      delay_ms(1000);
      }
      }
      else { printf("No devices");}
	}

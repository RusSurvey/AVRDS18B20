/*

Chip type               : ATmega328P
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*/

#include <mega328p.h>
#include <ds18b20.h>
#include <1wire.h>
// Standard Input/Output functions
#include <stdio.h>
#include <delay.h>

int temp;
int pwm;
unsigned char RomCode[2][9];
// Declare your global variables here
void setPWM(int temperature)
{
    OCR0A=17*temp-20*17;   
    pwm=   17*temp-20*17;  
    printf("pwm=%i    ;",pwm);  
 //   delay_ms(1000);
}


 void writetemp()
{
                        temp=ds18b20_temperature(0);  //?????? ???????????  
          if (temp>1000){               //???? ?????? ?????? ?????? 1000
             temp=4096-temp;            //???????? ?? ?????? 4096
             temp=-temp;                //? ?????? ???? "?????"
          }
          printf("t=%i C",temp);    //????????? ????? ??? ?????? ??????????? ? ??? ?????      
          
       //   lcd_clear();                //?????? ??????? ????? ???????
       //   lcd_puts(lcd_buffer);        //??????? ????? ?? LCD
        //  delay_ms(500);              //???? 500??
}



void main(void)
{
int i=0;
// Declare your local variables here
unsigned char devices;

devices = w1_init();
// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x01;
DDRC=0x01;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0b00000000;
DDRD=0b01000000;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x00;
TCCR0B=0x00;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2A output: Disconnected
// OC2B output: Disconnected
ASSR=0x00;
TCCR2A=0x00;
TCCR2B=0x00;
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-14: Off
// Interrupt on any change on pins PCINT16-23: Off
EICRA=0x00;
EIMSK=0x00;
PCICR=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x00;

// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=0x00;

// Timer/Counter 2 Interrupt(s) initialization
TIMSK2=0x00;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART0 Mode: Asynchronous
// USART Baud Rate: 9600
UCSR0A=0x00;
UCSR0B=0x18;
UCSR0C=0x06;
UBRR0H=0x00;
UBRR0L=0x33;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
ADCSRB=0x00;
DIDR1=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

//printf("%u", devices);

TCCR0A=0b10100011; //выбираем неинверсный режим шим для обоих светодиодов
TCCR0B=0b00000001;

  for(i=0;i<256;i++) //увеличиваем яркость первого диода, и уменьшаем яркость второго каждые 10 мс
  {
   OCR0A=i;
   delay_ms(100);
  } 

while (1)
{
    writetemp();
    setPWM(temp);
    PORTB=0x00;
    delay_ms(3000);
    PORTB=0x01;
    delay_ms(3000);
    
}
/*
devices=w1_search( DS18B20_SEARCH_ROM_CMD, RomCode );

 
  if( devices )
  {    
//printf("DS18B20 = ");
    printf(devices);  
    
   
   // lcd_gotoxy( 0,1 ); lcd_puts( LcdBuffDevices ); lcd_gotoxy( 0,0 ); lcd_puts( str1 );
   
    ds18b20_init( &RomCode[0][0], 30, 60, DS18B20_12BIT_RES ); 
   // ds18b20_init( &RomCode[1][0], 30, 60, DS18B20_12BIT_RES );      
   // printf((int)DS18B20_12BIT_RES);

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
      */
}


#include <avr/io.h>                  
#include <util/delay.h>                     
#include "portpins.h"

uint8_t random_seq[20];

uint8_t random4(void);
void tone(uint8_t ocr);

uint8_t button;
uint8_t button_pulse;

uint8_t count = 0;

int main(void) {

  uint8_t input_seq[20];
  uint8_t error = 0;
  int i, j;          

  while (1) {
  
  error = 0;

  DDRB &= ~(1 << PB1);

  while(PINB & (1 << PB1))
  {

  }
  
  simon_start();

  DDRD |= (1 << PD6);

  _delay_ms(800);

  random_seq[0] = random4();

  count = 0;

   _delay_ms(800);


  while(error == 0)
  {

  random_seq[count] = random4();

  //_delay_ms(500);

  for (i=0; i <= count; i++)
  {

    blink_random_led(random_seq[i]);
    _delay_ms(500); 
  }

  DDRB &= ~(1<<PB1);
  DDRB &= ~(1<<PB2);
  DDRB &= ~(1<<PB3);
  DDRB &= ~(1<<PB4);


    for (j = 0; j <= count; j++) 
    {
          while ( (PINB & 0b00011110) == 0b00011110 ) 
    {

    }
      switch (PINB & 0b00011110) {
      case (0b00011100):
        button = 0;
        tone(15);
        break;
      case (0b00011010):
        button = 1;
        tone(20);
        break;
        case 0b00010110:
        button = 2;
        tone(70);
        break;
        case 0b00001110:
        button = 3;
        tone(120);
        break;
      }

      if (random_seq[j] != button)
      {
        error = 1;
        tone(220);
        tone(220);
        tone(220);
        break;
      }

      _delay_ms(500);
      
    }


    _delay_ms(800);

  count++; 

  }

  }

  return 0;                            
}

void simon_start() {

  DDRB |= (1 << PB1);  
  PORTB &= ~(1<<PB1);
  _delay_ms(100); 
  DDRB |= (1 << PB2);  
  PORTB &= ~(1<<PB2);
  _delay_ms(100); 
  DDRB |= (1 << PB3);  
  PORTB &= ~(1<<PB3);
  _delay_ms(100); 
  DDRB |= (1 << PB4);  
  PORTB &= ~(1<<PB4);
  _delay_ms(100); 
  PORTB |= (1 << PB1) | (1 << PB4);
  PORTB |= (1 << PB2) | (1 << PB3);
  _delay_ms(100); 
  PORTB &= ~(1<<PB1);
  PORTB &= ~(1<<PB2); 
  PORTB &= ~(1<<PB3); 
  PORTB &= ~(1<<PB4);
  _delay_ms(100); 
  PORTB |= (1 << PB1) | (1 << PB4);
  PORTB |= (1 << PB2) | (1 << PB3);
   _delay_ms(100); 
  PORTB &= ~(1<<PB1);
  PORTB &= ~(1<<PB2); 
  PORTB &= ~(1<<PB3); 
  PORTB &= ~(1<<PB4);
  _delay_ms(100); 
  PORTB |= (1 << PB4) | (1 << PB1);
  PORTB |= (1 << PB2) | (1 << PB3);

}

void blink_random_led (uint8_t led) {

   switch (led) {
    case 0:
      PORTB |= (1 << PB1) | (1 << PB4);
      PORTB |= (1 << PB2) | (1 << PB3);
      DDRB |= (1 << PB1);  
      PORTB &= ~(1<<PB1);
      tone(15);
      PORTB |= (1 << PB1);
    break;

    case 1:
      PORTB |= (1 << PB1) | (1 << PB4);
      PORTB |= (1 << PB2) | (1 << PB3);
      DDRB |= (1 << PB2);  
      PORTB &= ~(1<<PB2);
      tone(20);
      PORTB |= (1 << PB2);
    break;

    case 2:
      PORTB |= (1 << PB1) | (1 << PB4);
      PORTB |= (1 << PB2) | (1 << PB3);
      DDRB |= (1 << PB3);  
      PORTB &= ~(1<<PB3);
      tone(70);
      PORTB |= (1 << PB3);
    break;

    case 3:
      PORTB |= (1 << PB1) | (1 << PB4);
      PORTB |= (1 << PB2) | (1 << PB3);
      DDRB |= (1 << PB4);  
      PORTB &= ~(1<<PB4);
      tone(120);
      PORTB |= (1 << PB4);
    break;
  }
}

uint8_t random4(void) {
    static uint8_t s=0xaa,a=0;

        s^=s<<3;
        s^=s>>5;
        s^=a++>>2;

        return (4*s)/255;
}

void tone(uint8_t ocr) {
  TCCR0A = 0b01000010;
  TCCR0B = 0b00000100;
  OCR0A = ocr;         // set the OCR
  _delay_ms(200);
  TCCR0A = 0b00000000; 
}

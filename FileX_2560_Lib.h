/*
ES IST WICHTIG, ES ZU VERSTEHEN, NICHT NUR ZU BENUTZEN!
Ich weiß dass es komplizierter Code ist, aber sobald du das verstanden hast, wirst du kein Problem mehr haben
so etwas selbst zu programmieren. Aber es ist nicht nur das: Immer wieder üben, fragen und weiter"bilden".
Übung macht nunmal den Meister.
*/

#ifndef __FILEX_LIB
#define __FILEX_LIB

#include <ctype.h>
#include <stdlib.h>
#include <mega2560.h>

unsigned char i, x, cur_depth, cur_time;
// Declare as extern, define as intern
extern unsigned char M_ARRAY[1000], M_ARRAY_MAP[500];

/* ANDERE IDE ? INT MAIN = NEW MAIN 
Invertion Invertion */

/*static void std_init(unsigned char entrances[11], unsigned char exits[11], char interrupts[8]) {
    for (i = 0; i < sizeof(entrances); i++) (entrances[i]) = 0x00;
    for (i = 0; i < sizeof(exits); i++) (exits[i]) = 0xFF;

    for (i = 0; interrupts && i < sizeof(interrupts); i++) {
        switch (tolower(interrupts[i])) {
            case 't0': TIFR0 |= 1; TIMSK0 |= 1; break;
            case 't1': TIFR1 |= 1; TIMSK1 |= 1; break;
            case 't2': TIFR2 |= 1; TIMSK2 |= 1; break;
            case 't3': TIFR3 |= 1; TIMSK3 |= 1; break;
            case 't4': TIFR4 |= 1; TIMSK4 |= 1; break;
            case 't5': TIFR5 |= 1; TIMSK5 |= 1; break;
            case 'i4': EIFR |= 0x10; EIMSK |= 0x10; break;
            case 'i5': EIFR |= 8; EIMSK |= 8; break;
        }
    }
    if (interrupts) SREG |= 0x01;
}*/


// MATRIX STUFF
static void matrix_change(unsigned char index, unsigned int time) {
    cur_depth = 0, cur_time = 0;

    for (i = 0; i < index; i++) {
        cur_depth += M_ARRAY_MAP[i];
    }
     
    while (cur_time < time) {
        for (i = cur_depth; i < (cur_depth + M_ARRAY_MAP[index]); i += 2) {
            PORTC = M_ARRAY[i];
            PORTA = M_ARRAY[i+1];
            delay_ms(1);  
            cur_time++;
        }
    }
}
    

static void matrix_anim(unsigned char start, unsigned char end, unsigned int time) {
    for (x = start; x <= end; x++) {
        matrix_change(x, time);
    }
}


// READ ADC
static int read_adc(void) {
    ADCSRA |= 0x40;
    while((ADCSRA & 0x40) != 0) 0;
    return ADCW;
}


// THOUSAND-HUNDRED-TEN-ONE 7-SEG OUT (it is important to understand what is happening here)
static int split_7_seg_out(unsigned char number) {
    PORTA = ((number/1000)<<4) | ((number%1000)/100);
    PORTB = (((number%100)/10)<<4) | ((number%10)/1);
    return ((PORTA<<8)|PORTB);
}


// delay_ms replacement fix (only for use in Arduino IDE)
static int delay_ms(int delay) {
    _delay_ms(delay);
    return delay;
}
static int delay_us(int delay) {
    _delay_us(delay);
    return delay;
}


// delay_us anti-constant-rqu
static int delay_us_v(int delay) {
    // To avoid performance and thus accuracy loss caused by to many for loops / calls (9320 : 9+3+2=14 loops)
    for (i = 0; i < delay/1000000; i++) delay_us(1000000);
    for (i = 0; i < (delay%1000000)/100000; i++) delay_us(100000);
    for (i = 0; i < (delay%100000)/10000; i++) delay_us(10000);
    for (i = 0; i < (delay%10000)/1000; i++) delay_us(1000);
    for (i = 0; i < (delay%1000)/100; i++) delay_us(100);
    for (i = 0; i < (delay%100)/10; i++) delay_ms(10);
    for (i = 0; i < delay%10; i++) delay_us(1);
    return delay;
} // looks a bit like a ship


/* ((rand()%(int)(((max) + 1)-(min)))+ (min))  for Random Gen, danke Herr Ld */
// Random Gen
static int random_num(int min, int max) {
    return ((rand()%(int)((max+1)-min))+min);
}


// SINGLE IO
// PORTS OUT
#define PORTA_0 (PORTA & 1)
#define PORTA_1 ((PORTA & 2) >> 1)
#define PORTA_2 ((PORTA & 4) >> 2)
#define PORTA_3 ((PORTA & 8) >> 3)
#define PORTA_4 ((PORTA & 16) >> 4)
#define PORTA_5 ((PORTA & 32) >> 5)
#define PORTA_6 ((PORTA & 64) >> 6)
#define PORTA_7 ((PORTA & 128) >> 6)

#define PORTB_0 (PORTB & 1)
#define PORTB_1 ((PORTB & 2) >> 1)
#define PORTB_2 ((PORTB & 4) >> 2)
#define PORTB_3 ((PORTB & 8) >> 3)
#define PORTB_4 ((PORTB & 16) >> 4)
#define PORTB_5 ((PORTB & 32) >> 5)
#define PORTB_6 ((PORTB & 64) >> 6)
#define PORTB_7 ((PORTB & 128) >> 6)

#define PORTC_0 (PORTC & 1)
#define PORTC_1 ((PORTC & 2) >> 1)
#define PORTC_2 ((PORTC & 4) >> 2)
#define PORTC_3 ((PORTC & 8) >> 3)
#define PORTC_4 ((PORTC & 16) >> 4)
#define PORTC_5 ((PORTC & 32) >> 5)
#define PORTC_6 ((PORTC & 64) >> 6)
#define PORTC_7 ((PORTC & 128) >> 6)

#define PORTD_0 (PORTD & 1)
#define PORTD_1 ((PORTD & 2) >> 1)
#define PORTD_2 ((PORTD & 4) >> 2)
#define PORTD_3 ((PORTD & 8) >> 3)
#define PORTD_4 ((PORTD & 16) >> 4)
#define PORTD_5 ((PORTD & 32) >> 5)
#define PORTD_6 ((PORTD & 64) >> 6)
#define PORTD_7 ((PORTD & 128) >> 6)

#define PORTE_0 (PORTE & 1)
#define PORTE_1 ((PORTE & 2) >> 1)
#define PORTE_2 ((PORTE & 4) >> 2)
#define PORTE_3 ((PORTE & 8) >> 3)
#define PORTE_4 ((PORTE & 16) >> 4)
#define PORTE_5 ((PORTE & 32) >> 5)
#define PORTE_6 ((PORTE & 64) >> 6)
#define PORTE_7 ((PORTE & 128) >> 6)

#define PORTF_0 (PORTF & 1)
#define PORTF_1 ((PORTF & 2) >> 1)
#define PORTF_2 ((PORTF & 4) >> 2)
#define PORTF_3 ((PORTF & 8) >> 3)
#define PORTF_4 ((PORTF & 16) >> 4)
#define PORTF_5 ((PORTF & 32) >> 5)
#define PORTF_6 ((PORTF & 64) >> 6)
#define PORTF_7 ((PORTF & 128) >> 6)

#define PORTG_0 (PORTG & 1)
#define PORTG_1 ((PORTG & 2) >> 1)
#define PORTG_2 ((PORTG & 4) >> 2)
#define PORTG_3 ((PORTG & 8) >> 3)
#define PORTG_4 ((PORTG & 16) >> 4)
#define PORTG_5 ((PORTG & 32) >> 5)
#define PORTG_6 ((PORTG & 64) >> 6)
#define PORTG_7 ((PORTG & 128) >> 6)

#define PORTH_0 (PORTH & 1)
#define PORTH_1 ((PORTH & 2) >> 1)
#define PORTH_2 ((PORTH & 4) >> 2)
#define PORTH_3 ((PORTH & 8) >> 3)
#define PORTH_4 ((PORTH & 16) >> 4)
#define PORTH_5 ((PORTH & 32) >> 5)
#define PORTH_6 ((PORTH & 64) >> 6)
#define PORTH_7 ((PORTH & 128) >> 6)

#define PORTJ_0 (PORTJ & 1)
#define PORTJ_1 ((PORTJ & 2) >> 1)
#define PORTJ_2 ((PORTJ & 4) >> 2)
#define PORTJ_3 ((PORTJ & 8) >> 3)
#define PORTJ_4 ((PORTJ & 16) >> 4)
#define PORTJ_5 ((PORTJ & 32) >> 5)
#define PORTJ_6 ((PORTJ & 64) >> 6)
#define PORTJ_7 ((PORTJ & 128) >> 6)

#define PORTK_0 (PORTK & 1)
#define PORTK_1 ((PORTK & 2) >> 1)
#define PORTK_2 ((PORTK & 4) >> 2)
#define PORTK_3 ((PORTK & 8) >> 3)
#define PORTK_4 ((PORTK & 16) >> 4)
#define PORTK_5 ((PORTK & 32) >> 5)
#define PORTK_6 ((PORTK & 64) >> 6)
#define PORTK_7 ((PORTK & 128) >> 6)

#define PORTL_0 (PORTL & 1)
#define PORTL_1 ((PORTL & 2) >> 1)
#define PORTL_2 ((PORTL & 4) >> 2)
#define PORTL_3 ((PORTL & 8) >> 3)
#define PORTL_4 ((PORTL & 16) >> 4)
#define PORTL_5 ((PORTL & 32) >> 5)
#define PORTL_6 ((PORTL & 64) >> 6)
#define PORTL_7 ((PORTL & 128) >> 6)

// PORTS IN

#define PORTA_0E0 PORTA &= 0xFE
#define PORTA_0E1 PORTA |= 1
#define PORTA_1E0 PORTA &= 0xFD
#define PORTA_1E1 PORTA |= 2
#define PORTA_2E0 PORTA &= 0xFB   
#define PORTA_2E1 PORTA |= 4
#define PORTA_3E0 PORTA &= 0xF7
#define PORTA_3E1 PORTA |= 8
#define PORTA_4E0 PORTA &= 0xEF    
#define PORTA_4E1 PORTA |= 0x10
#define PORTA_5E0 PORTA &= 0xDF 
#define PORTA_5E1 PORTA |= 0x20
#define PORTA_6E0 PORTA &= 0xBF
#define PORTA_6E1 PORTA |= 0x40
#define PORTA_7E0 PORTA &= 0x7F
#define PORTA_7E1 PORTA |= 0x80

#define PORTB_0E0 PORTB &= 0xFE
#define PORTB_0E1 PORTB |= 1
#define PORTB_1E0 PORTB &= 0xFD
#define PORTB_1E1 PORTB |= 2
#define PORTB_2E0 PORTB &= 0xFB   
#define PORTB_2E1 PORTB |= 4
#define PORTB_3E0 PORTB &= 0xF7
#define PORTB_3E1 PORTB |= 8
#define PORTB_4E0 PORTB &= 0xEF    
#define PORTB_4E1 PORTB |= 0x10
#define PORTB_5E0 PORTB &= 0xDF 
#define PORTB_5E1 PORTB |= 0x20
#define PORTB_6E0 PORTB &= 0xBF
#define PORTB_6E1 PORTB |= 0x40
#define PORTB_7E0 PORTB &= 0x7F
#define PORTB_7E1 PORTB |= 0x80

#define PORTC_0E0 PORTC &= 0xFE
#define PORTC_0E1 PORTC |= 1
#define PORTC_1E0 PORTC &= 0xFD
#define PORTC_1E1 PORTC |= 2
#define PORTC_2E0 PORTC &= 0xFB   
#define PORTC_2E1 PORTC |= 4
#define PORTC_3E0 PORTC &= 0xF7
#define PORTC_3E1 PORTC |= 8
#define PORTC_4E0 PORTC &= 0xEF    
#define PORTC_4E1 PORTC |= 0x10
#define PORTC_5E0 PORTC &= 0xDF 
#define PORTC_5E1 PORTC |= 0x20
#define PORTC_6E0 PORTC &= 0xBF
#define PORTC_6E1 PORTC |= 0x40
#define PORTC_7E0 PORTC &= 0x7F
#define PORTC_7E1 PORTC |= 0x80

#define PORTD_0E0 PORTD &= 0xFE
#define PORTD_0E1 PORTD |= 1
#define PORTD_1E0 PORTD &= 0xFD
#define PORTD_1E1 PORTD |= 2
#define PORTD_2E0 PORTD &= 0xFB   
#define PORTD_2E1 PORTD |= 4
#define PORTD_3E0 PORTD &= 0xF7
#define PORTD_3E1 PORTD |= 8
#define PORTD_4E0 PORTD &= 0xEF    
#define PORTD_4E1 PORTD |= 0x10
#define PORTD_5E0 PORTD &= 0xDF 
#define PORTD_5E1 PORTD |= 0x20
#define PORTD_6E0 PORTD &= 0xBF
#define PORTD_6E1 PORTD |= 0x40
#define PORTD_7E0 PORTD &= 0x7F
#define PORTD_7E1 PORTD |= 0x80

#define PORTE_0E0 PORTE &= 0xFE
#define PORTE_0E1 PORTE |= 1
#define PORTE_1E0 PORTE &= 0xFD
#define PORTE_1E1 PORTE |= 2
#define PORTE_2E0 PORTE &= 0xFB   
#define PORTE_2E1 PORTE |= 4
#define PORTE_3E0 PORTE &= 0xF7
#define PORTE_3E1 PORTE |= 8
#define PORTE_4E0 PORTE &= 0xEF    
#define PORTE_4E1 PORTE |= 0x10
#define PORTE_5E0 PORTE &= 0xDF 
#define PORTE_5E1 PORTE |= 0x20
#define PORTE_6E0 PORTE &= 0xBF
#define PORTE_6E1 PORTE |= 0x40
#define PORTE_7E0 PORTE &= 0x7F
#define PORTE_7E1 PORTE |= 0x80

#define PORTF_0E0 PORTF &= 0xFE
#define PORTF_0E1 PORTF |= 1
#define PORTF_1E0 PORTF &= 0xFD
#define PORTF_1E1 PORTF |= 2
#define PORTF_2E0 PORTF &= 0xFB   
#define PORTF_2E1 PORTF |= 4
#define PORTF_3E0 PORTF &= 0xF7
#define PORTF_3E1 PORTF |= 8
#define PORTF_4E0 PORTF &= 0xEF    
#define PORTF_4E1 PORTF |= 0x10
#define PORTF_5E0 PORTF &= 0xDF 
#define PORTF_5E1 PORTF |= 0x20
#define PORTF_6E0 PORTF &= 0xBF
#define PORTF_6E1 PORTF |= 0x40
#define PORTF_7E0 PORTF &= 0x7F
#define PORTF_7E1 PORTF |= 0x80

#define PORTG_0E0 PORTG &= 0xFE
#define PORTG_0E1 PORTG |= 1
#define PORTG_1E0 PORTG &= 0xFD
#define PORTG_1E1 PORTG |= 2
#define PORTG_2E0 PORTG &= 0xFB   
#define PORTG_2E1 PORTG |= 4
#define PORTG_3E0 PORTG &= 0xF7
#define PORTG_3E1 PORTG |= 8
#define PORTG_4E0 PORTG &= 0xEF    
#define PORTG_4E1 PORTG |= 0x10
#define PORTG_5E0 PORTG &= 0xDF 
#define PORTG_5E1 PORTG |= 0x20
#define PORTG_6E0 PORTG &= 0xBF
#define PORTG_6E1 PORTG |= 0x40
#define PORTG_7E0 PORTG &= 0x7F
#define PORTG_7E1 PORTG |= 0x80

#define PORTH_0E0 PORTH &= 0xFE
#define PORTH_0E1 PORTH |= 1
#define PORTH_1E0 PORTH &= 0xFD
#define PORTH_1E1 PORTH |= 2
#define PORTH_2E0 PORTH &= 0xFB   
#define PORTH_2E1 PORTH |= 4
#define PORTH_3E0 PORTH &= 0xF7
#define PORTH_3E1 PORTH |= 8
#define PORTH_4E0 PORTH &= 0xEF    
#define PORTH_4E1 PORTH |= 0x10
#define PORTH_5E0 PORTH &= 0xDF 
#define PORTH_5E1 PORTH |= 0x20
#define PORTH_6E0 PORTH &= 0xBF
#define PORTH_6E1 PORTH |= 0x40
#define PORTH_7E0 PORTH &= 0x7F
#define PORTH_7E1 PORTH |= 0x80

#define PORTJ_0E0 PORTJ &= 0xFE
#define PORTJ_0E1 PORTJ |= 1
#define PORTJ_1E0 PORTJ &= 0xFD
#define PORTJ_1E1 PORTJ |= 2
#define PORTJ_2E0 PORTJ &= 0xFB   
#define PORTJ_2E1 PORTJ |= 4
#define PORTJ_3E0 PORTJ &= 0xF7
#define PORTJ_3E1 PORTJ |= 8
#define PORTJ_4E0 PORTJ &= 0xEF    
#define PORTJ_4E1 PORTJ |= 0x10
#define PORTJ_5E0 PORTJ &= 0xDF 
#define PORTJ_5E1 PORTJ |= 0x20
#define PORTJ_6E0 PORTJ &= 0xBF
#define PORTJ_6E1 PORTJ |= 0x40
#define PORTJ_7E0 PORTJ &= 0x7F
#define PORTJ_7E1 PORTJ |= 0x80

#define PORTK_0E0 PORTK &= 0xFE
#define PORTK_0E1 PORTK |= 1
#define PORTK_1E0 PORTK &= 0xFD
#define PORTK_1E1 PORTK |= 2
#define PORTK_2E0 PORTK &= 0xFB   
#define PORTK_2E1 PORTK |= 4
#define PORTK_3E0 PORTK &= 0xF7
#define PORTK_3E1 PORTK |= 8
#define PORTK_4E0 PORTK &= 0xEF    
#define PORTK_4E1 PORTK |= 0x10
#define PORTK_5E0 PORTK &= 0xDF 
#define PORTK_5E1 PORTK |= 0x20
#define PORTK_6E0 PORTK &= 0xBF
#define PORTK_6E1 PORTK |= 0x40
#define PORTK_7E0 PORTK &= 0x7F
#define PORTK_7E1 PORTK |= 0x80

#define PORTL_0E0 PORTL &= 0xFE
#define PORTL_0E1 PORTL |= 1
#define PORTL_1E0 PORTL &= 0xFD
#define PORTL_1E1 PORTL |= 2
#define PORTL_2E0 PORTL &= 0xFB   
#define PORTL_2E1 PORTL |= 4
#define PORTL_3E0 PORTL &= 0xF7
#define PORTL_3E1 PORTL |= 8
#define PORTL_4E0 PORTL &= 0xEF    
#define PORTL_4E1 PORTL |= 0x10
#define PORTL_5E0 PORTL &= 0xDF 
#define PORTL_5E1 PORTL |= 0x20
#define PORTL_6E0 PORTL &= 0xBF
#define PORTL_6E1 PORTL |= 0x40
#define PORTL_7E0 PORTL &= 0x7F
#define PORTL_7E1 PORTL |= 0x80

// PINS OUT

#define PINA_0 (PINA & 1)
#define PINA_1 ((PINA & 2) >> 1)
#define PINA_2 ((PINA & 4) >> 2)
#define PINA_3 ((PINA & 8) >> 3)
#define PINA_4 ((PINA & 16) >> 4)
#define PINA_5 ((PINA & 32) >> 5)
#define PINA_6 ((PINA & 64) >> 6)
#define PINA_7 ((PINA & 128) >> 6)

#define PINB_0 (PINB & 1)
#define PINB_1 ((PINB & 2) >> 1)
#define PINB_2 ((PINB & 4) >> 2)
#define PINB_3 ((PINB & 8) >> 3)
#define PINB_4 ((PINB & 16) >> 4)
#define PINB_5 ((PINB & 32) >> 5)
#define PINB_6 ((PINB & 64) >> 6)
#define PINB_7 ((PINB & 128) >> 6)

#define PINC_0 (PINC & 1)
#define PINC_1 ((PINC & 2) >> 1)
#define PINC_2 ((PINC & 4) >> 2)
#define PINC_3 ((PINC & 8) >> 3)
#define PINC_4 ((PINC & 16) >> 4)
#define PINC_5 ((PINC & 32) >> 5)
#define PINC_6 ((PINC & 64) >> 6)
#define PINC_7 ((PINC & 128) >> 6)

#define PIND_0 (PIND & 1)
#define PIND_1 ((PIND & 2) >> 1)
#define PIND_2 ((PIND & 4) >> 2)
#define PIND_3 ((PIND & 8) >> 3)
#define PIND_4 ((PIND & 16) >> 4)
#define PIND_5 ((PIND & 32) >> 5)
#define PIND_6 ((PIND & 64) >> 6)
#define PIND_7 ((PIND & 128) >> 6)

#define PINE_0 (PINE & 1)
#define PINE_1 ((PINE & 2) >> 1)
#define PINE_2 ((PINE & 4) >> 2)
#define PINE_3 ((PINE & 8) >> 3)
#define PINE_4 ((PINE & 16) >> 4)
#define PINE_5 ((PINE & 32) >> 5)
#define PINE_6 ((PINE & 64) >> 6)
#define PINE_7 ((PINE & 128) >> 6)

#define PINF_0 (PINF & 1)
#define PINF_1 ((PINF & 2) >> 1)
#define PINF_2 ((PINF & 4) >> 2)
#define PINF_3 ((PINF & 8) >> 3)
#define PINF_4 ((PINF & 16) >> 4)
#define PINF_5 ((PINF & 32) >> 5)
#define PINF_6 ((PINF & 64) >> 6)
#define PINF_7 ((PINF & 128) >> 6)

#define PING_0 (PING & 1)
#define PING_1 ((PING & 2) >> 1)
#define PING_2 ((PING & 4) >> 2)
#define PING_3 ((PING & 8) >> 3)
#define PING_4 ((PING & 16) >> 4)
#define PING_5 ((PING & 32) >> 5)
#define PING_6 ((PING & 64) >> 6)
#define PING_7 ((PING & 128) >> 6)

#define PINH_0 (PINH & 1)
#define PINH_1 ((PINH & 2) >> 1)
#define PINH_2 ((PINH & 4) >> 2)
#define PINH_3 ((PINH & 8) >> 3)
#define PINH_4 ((PINH & 16) >> 4)
#define PINH_5 ((PINH & 32) >> 5)
#define PINH_6 ((PINH & 64) >> 6)
#define PINH_7 ((PINH & 128) >> 6)

#define PINJ_0 (PINJ & 1)
#define PINJ_1 ((PINJ & 2) >> 1)
#define PINJ_2 ((PINJ & 4) >> 2)
#define PINJ_3 ((PINJ & 8) >> 3)
#define PINJ_4 ((PINJ & 16) >> 4)
#define PINJ_5 ((PINJ & 32) >> 5)
#define PINJ_6 ((PINJ & 64) >> 6)
#define PINJ_7 ((PINJ & 128) >> 6)

#define PINK_0 (PINK & 1)
#define PINK_1 ((PINK & 2) >> 1)
#define PINK_2 ((PINK & 4) >> 2)
#define PINK_3 ((PINK & 8) >> 3)
#define PINK_4 ((PINK & 16) >> 4)
#define PINK_5 ((PINK & 32) >> 5)
#define PINK_6 ((PINK & 64) >> 6)
#define PINK_7 ((PINK & 128) >> 6)

#define PINL_0 (PINL & 1)
#define PINL_1 ((PINL & 2) >> 1)
#define PINL_2 ((PINL & 4) >> 2)
#define PINL_3 ((PINL & 8) >> 3)
#define PINL_4 ((PINL & 16) >> 4)
#define PINL_5 ((PINL & 32) >> 5)
#define PINL_6 ((PINL & 64) >> 6)
#define PINL_7 ((PINL & 128) >> 6)

// DDRS OUT

#define DDRA_0 (DDRA & 1)
#define DDRA_1 ((DDRA & 2) >> 1)
#define DDRA_2 ((DDRA & 4) >> 2)
#define DDRA_3 ((DDRA & 8) >> 3)
#define DDRA_4 ((DDRA & 16) >> 4)
#define DDRA_5 ((DDRA & 32) >> 5)
#define DDRA_6 ((DDRA & 64) >> 6)
#define DDRA_7 ((DDRA & 128) >> 6)

#define DDRB_0 (DDRB & 1)
#define DDRB_1 ((DDRB & 2) >> 1)
#define DDRB_2 ((DDRB & 4) >> 2)
#define DDRB_3 ((DDRB & 8) >> 3)
#define DDRB_4 ((DDRB & 16) >> 4)
#define DDRB_5 ((DDRB & 32) >> 5)
#define DDRB_6 ((DDRB & 64) >> 6)
#define DDRB_7 ((DDRB & 128) >> 6)

#define DDRC_0 (DDRC & 1)
#define DDRC_1 ((DDRC & 2) >> 1)
#define DDRC_2 ((DDRC & 4) >> 2)
#define DDRC_3 ((DDRC & 8) >> 3)
#define DDRC_4 ((DDRC & 16) >> 4)
#define DDRC_5 ((DDRC & 32) >> 5)
#define DDRC_6 ((DDRC & 64) >> 6)
#define DDRC_7 ((DDRC & 128) >> 6)

#define DDRD_0 (DDRD & 1)
#define DDRD_1 ((DDRD & 2) >> 1)
#define DDRD_2 ((DDRD & 4) >> 2)
#define DDRD_3 ((DDRD & 8) >> 3)
#define DDRD_4 ((DDRD & 16) >> 4)
#define DDRD_5 ((DDRD & 32) >> 5)
#define DDRD_6 ((DDRD & 64) >> 6)
#define DDRD_7 ((DDRD & 128) >> 6)

#define DDRE_0 (DDRE & 1)
#define DDRE_1 ((DDRE & 2) >> 1)
#define DDRE_2 ((DDRE & 4) >> 2)
#define DDRE_3 ((DDRE & 8) >> 3)
#define DDRE_4 ((DDRE & 16) >> 4)
#define DDRE_5 ((DDRE & 32) >> 5)
#define DDRE_6 ((DDRE & 64) >> 6)
#define DDRE_7 ((DDRE & 128) >> 6)

#define DDRF_0 (DDRF & 1)
#define DDRF_1 ((DDRF & 2) >> 1)
#define DDRF_2 ((DDRF & 4) >> 2)
#define DDRF_3 ((DDRF & 8) >> 3)
#define DDRF_4 ((DDRF & 16) >> 4)
#define DDRF_5 ((DDRF & 32) >> 5)
#define DDRF_6 ((DDRF & 64) >> 6)
#define DDRF_7 ((DDRF & 128) >> 6)

#define DDRG_0 (DDRG & 1)
#define DDRG_1 ((DDRG & 2) >> 1)
#define DDRG_2 ((DDRG & 4) >> 2)
#define DDRG_3 ((DDRG & 8) >> 3)
#define DDRG_4 ((DDRG & 16) >> 4)
#define DDRG_5 ((DDRG & 32) >> 5)
#define DDRG_6 ((DDRG & 64) >> 6)
#define DDRG_7 ((DDRG & 128) >> 6)

#define DDRH_0 (DDRH & 1)
#define DDRH_1 ((DDRH & 2) >> 1)
#define DDRH_2 ((DDRH & 4) >> 2)
#define DDRH_3 ((DDRH & 8) >> 3)
#define DDRH_4 ((DDRH & 16) >> 4)
#define DDRH_5 ((DDRH & 32) >> 5)
#define DDRH_6 ((DDRH & 64) >> 6)
#define DDRH_7 ((DDRH & 128) >> 6)

#define DDRJ_0 (DDRJ & 1)
#define DDRJ_1 ((DDRJ & 2) >> 1)
#define DDRJ_2 ((DDRJ & 4) >> 2)
#define DDRJ_3 ((DDRJ & 8) >> 3)
#define DDRJ_4 ((DDRJ & 16) >> 4)
#define DDRJ_5 ((DDRJ & 32) >> 5)
#define DDRJ_6 ((DDRJ & 64) >> 6)
#define DDRJ_7 ((DDRJ & 128) >> 6)

#define DDRK_0 (DDRK & 1)
#define DDRK_1 ((DDRK & 2) >> 1)
#define DDRK_2 ((DDRK & 4) >> 2)
#define DDRK_3 ((DDRK & 8) >> 3)
#define DDRK_4 ((DDRK & 16) >> 4)
#define DDRK_5 ((DDRK & 32) >> 5)
#define DDRK_6 ((DDRK & 64) >> 6)
#define DDRK_7 ((DDRK & 128) >> 6)

#define DDRL_0 (DDRL & 1)
#define DDRL_1 ((DDRL & 2) >> 1)
#define DDRL_2 ((DDRL & 4) >> 2)
#define DDRL_3 ((DDRL & 8) >> 3)
#define DDRL_4 ((DDRL & 16) >> 4)
#define DDRL_5 ((DDRL & 32) >> 5)
#define DDRL_6 ((DDRL & 64) >> 6)
#define DDRL_7 ((DDRL & 128) >> 6)

// DDRS IN

#define DDRA_0E0 DDRA &= 0xFE
#define DDRA_0E1 DDRA |= 1
#define DDRA_1E0 DDRA &= 0xFD
#define DDRA_1E1 DDRA |= 2
#define DDRA_2E0 DDRA &= 0xFB   
#define DDRA_2E1 DDRA |= 4
#define DDRA_3E0 DDRA &= 0xF7
#define DDRA_3E1 DDRA |= 8
#define DDRA_4E0 DDRA &= 0xEF    
#define DDRA_4E1 DDRA |= 0x10
#define DDRA_5E0 DDRA &= 0xDF 
#define DDRA_5E1 DDRA |= 0x20
#define DDRA_6E0 DDRA &= 0xBF
#define DDRA_6E1 DDRA |= 0x40
#define DDRA_7E0 DDRA &= 0x7F
#define DDRA_7E1 DDRA |= 0x80

#define DDRB_0E0 DDRB &= 0xFE
#define DDRB_0E1 DDRB |= 1
#define DDRB_1E0 DDRB &= 0xFD
#define DDRB_1E1 DDRB |= 2
#define DDRB_2E0 DDRB &= 0xFB   
#define DDRB_2E1 DDRB |= 4
#define DDRB_3E0 DDRB &= 0xF7
#define DDRB_3E1 DDRB |= 8
#define DDRB_4E0 DDRB &= 0xEF    
#define DDRB_4E1 DDRB |= 0x10
#define DDRB_5E0 DDRB &= 0xDF 
#define DDRB_5E1 DDRB |= 0x20
#define DDRB_6E0 DDRB &= 0xBF
#define DDRB_6E1 DDRB |= 0x40
#define DDRB_7E0 DDRB &= 0x7F
#define DDRB_7E1 DDRB |= 0x80

#define DDRC_0E0 DDRC &= 0xFE
#define DDRC_0E1 DDRC |= 1
#define DDRC_1E0 DDRC &= 0xFD
#define DDRC_1E1 DDRC |= 2
#define DDRC_2E0 DDRC &= 0xFB   
#define DDRC_2E1 DDRC |= 4
#define DDRC_3E0 DDRC &= 0xF7
#define DDRC_3E1 DDRC |= 8
#define DDRC_4E0 DDRC &= 0xEF    
#define DDRC_4E1 DDRC |= 0x10
#define DDRC_5E0 DDRC &= 0xDF 
#define DDRC_5E1 DDRC |= 0x20
#define DDRC_6E0 DDRC &= 0xBF
#define DDRC_6E1 DDRC |= 0x40
#define DDRC_7E0 DDRC &= 0x7F
#define DDRC_7E1 DDRC |= 0x80

#define DDRD_0E0 DDRD &= 0xFE
#define DDRD_0E1 DDRD |= 1
#define DDRD_1E0 DDRD &= 0xFD
#define DDRD_1E1 DDRD |= 2
#define DDRD_2E0 DDRD &= 0xFB   
#define DDRD_2E1 DDRD |= 4
#define DDRD_3E0 DDRD &= 0xF7
#define DDRD_3E1 DDRD |= 8
#define DDRD_4E0 DDRD &= 0xEF    
#define DDRD_4E1 DDRD |= 0x10
#define DDRD_5E0 DDRD &= 0xDF 
#define DDRD_5E1 DDRD |= 0x20
#define DDRD_6E0 DDRD &= 0xBF
#define DDRD_6E1 DDRD |= 0x40
#define DDRD_7E0 DDRD &= 0x7F
#define DDRD_7E1 DDRD |= 0x80

#define DDRE_0E0 DDRE &= 0xFE
#define DDRE_0E1 DDRE |= 1
#define DDRE_1E0 DDRE &= 0xFD
#define DDRE_1E1 DDRE |= 2
#define DDRE_2E0 DDRE &= 0xFB   
#define DDRE_2E1 DDRE |= 4
#define DDRE_3E0 DDRE &= 0xF7
#define DDRE_3E1 DDRE |= 8
#define DDRE_4E0 DDRE &= 0xEF    
#define DDRE_4E1 DDRE |= 0x10
#define DDRE_5E0 DDRE &= 0xDF 
#define DDRE_5E1 DDRE |= 0x20
#define DDRE_6E0 DDRE &= 0xBF
#define DDRE_6E1 DDRE |= 0x40
#define DDRE_7E0 DDRE &= 0x7F
#define DDRE_7E1 DDRE |= 0x80

#define DDRF_0E0 DDRF &= 0xFE
#define DDRF_0E1 DDRF |= 1
#define DDRF_1E0 DDRF &= 0xFD
#define DDRF_1E1 DDRF |= 2
#define DDRF_2E0 DDRF &= 0xFB   
#define DDRF_2E1 DDRF |= 4
#define DDRF_3E0 DDRF &= 0xF7
#define DDRF_3E1 DDRF |= 8
#define DDRF_4E0 DDRF &= 0xEF    
#define DDRF_4E1 DDRF |= 0x10
#define DDRF_5E0 DDRF &= 0xDF 
#define DDRF_5E1 DDRF |= 0x20
#define DDRF_6E0 DDRF &= 0xBF
#define DDRF_6E1 DDRF |= 0x40
#define DDRF_7E0 DDRF &= 0x7F
#define DDRF_7E1 DDRF |= 0x80

#define DDRG_0E0 DDRG &= 0xFE
#define DDRG_0E1 DDRG |= 1
#define DDRG_1E0 DDRG &= 0xFD
#define DDRG_1E1 DDRG |= 2
#define DDRG_2E0 DDRG &= 0xFB   
#define DDRG_2E1 DDRG |= 4
#define DDRG_3E0 DDRG &= 0xF7
#define DDRG_3E1 DDRG |= 8
#define DDRG_4E0 DDRG &= 0xEF    
#define DDRG_4E1 DDRG |= 0x10
#define DDRG_5E0 DDRG &= 0xDF 
#define DDRG_5E1 DDRG |= 0x20
#define DDRG_6E0 DDRG &= 0xBF
#define DDRG_6E1 DDRG |= 0x40
#define DDRG_7E0 DDRG &= 0x7F
#define DDRG_7E1 DDRG |= 0x80

#define DDRH_0E0 DDRH &= 0xFE
#define DDRH_0E1 DDRH |= 1
#define DDRH_1E0 DDRH &= 0xFD
#define DDRH_1E1 DDRH |= 2
#define DDRH_2E0 DDRH &= 0xFB   
#define DDRH_2E1 DDRH |= 4
#define DDRH_3E0 DDRH &= 0xF7
#define DDRH_3E1 DDRH |= 8
#define DDRH_4E0 DDRH &= 0xEF    
#define DDRH_4E1 DDRH |= 0x10
#define DDRH_5E0 DDRH &= 0xDF 
#define DDRH_5E1 DDRH |= 0x20
#define DDRH_6E0 DDRH &= 0xBF
#define DDRH_6E1 DDRH |= 0x40
#define DDRH_7E0 DDRH &= 0x7F
#define DDRH_7E1 DDRH |= 0x80

#define DDRJ_0E0 DDRJ &= 0xFE
#define DDRJ_0E1 DDRJ |= 1
#define DDRJ_1E0 DDRJ &= 0xFD
#define DDRJ_1E1 DDRJ |= 2
#define DDRJ_2E0 DDRJ &= 0xFB   
#define DDRJ_2E1 DDRJ |= 4
#define DDRJ_3E0 DDRJ &= 0xF7
#define DDRJ_3E1 DDRJ |= 8
#define DDRJ_4E0 DDRJ &= 0xEF    
#define DDRJ_4E1 DDRJ |= 0x10
#define DDRJ_5E0 DDRJ &= 0xDF 
#define DDRJ_5E1 DDRJ |= 0x20
#define DDRJ_6E0 DDRJ &= 0xBF
#define DDRJ_6E1 DDRJ |= 0x40
#define DDRJ_7E0 DDRJ &= 0x7F
#define DDRJ_7E1 DDRJ |= 0x80

#define DDRK_0E0 DDRK &= 0xFE
#define DDRK_0E1 DDRK |= 1
#define DDRK_1E0 DDRK &= 0xFD
#define DDRK_1E1 DDRK |= 2
#define DDRK_2E0 DDRK &= 0xFB   
#define DDRK_2E1 DDRK |= 4
#define DDRK_3E0 DDRK &= 0xF7
#define DDRK_3E1 DDRK |= 8
#define DDRK_4E0 DDRK &= 0xEF    
#define DDRK_4E1 DDRK |= 0x10
#define DDRK_5E0 DDRK &= 0xDF 
#define DDRK_5E1 DDRK |= 0x20
#define DDRK_6E0 DDRK &= 0xBF
#define DDRK_6E1 DDRK |= 0x40
#define DDRK_7E0 DDRK &= 0x7F
#define DDRK_7E1 DDRK |= 0x80

#define DDRL_0E0 DDRL &= 0xFE
#define DDRL_0E1 DDRL |= 1
#define DDRL_1E0 DDRL &= 0xFD
#define DDRL_1E1 DDRL |= 2
#define DDRL_2E0 DDRL &= 0xFB   
#define DDRL_2E1 DDRL |= 4
#define DDRL_3E0 DDRL &= 0xF7
#define DDRL_3E1 DDRL |= 8
#define DDRL_4E0 DDRL &= 0xEF    
#define DDRL_4E1 DDRL |= 0x10
#define DDRL_5E0 DDRL &= 0xDF 
#define DDRL_5E1 DDRL |= 0x20
#define DDRL_6E0 DDRL &= 0xBF
#define DDRL_6E1 DDRL |= 0x40
#define DDRL_7E0 DDRL &= 0x7F
#define DDRL_7E1 DDRL |= 0x80


/*
Ich hoffe diese Bibliothek kommt zu einem guten Einsatz. Ihr könnt euch glücklich schätzen 
dass ihr nicht CodeVision AVR verwenden müsst sondern diesen Luxus habt.
Auch bleibt Herr Ka hoffentlich Lehrer in EIT. Er ist einer der besten die ich bisher hatte. 

- FileX
*/

#endif 
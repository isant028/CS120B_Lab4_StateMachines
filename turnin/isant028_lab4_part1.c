/*	Author: isant028
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum LED_STATES {LED_Start, LED_On, LED_Button, LED_On2, LED_Button2} LED_STATE;
void LED_Tick() {
	switch(LED_STATE) {
		case LED_Start:
			LED_STATE = LED_On;
			break;
		case LED_On:
			if ((PINA & 0x01) == 0x01) {
				LED_STATE = LED_On;
			}
			else {
				LED_STATE = LED_Button;
			}
			break;
		
		case LED_Button:
			if ((PINA & 0x01) == 0x01) {
                 LED_STATE = LED_On2;
                        }
            else {
                LED_STATE = LED_Button;
                }
                break;
	
		case LED_On2:
			if ((PINA & 0x01) == 0x01) {
				LED_STATE = LED_On2;
			}
			else {
				LED_STATE = LED_Button2;
			}
			break;
		
		case LED_Button2:
			if ((PINA & 0x01) == 0x01) {
				LED_STATE = LED_On;
			}
			else {
				LED_STATE = LED_Button2;
			}
			break;

		default:
			LED_STATE = LED_Start;
			break;
	}
	switch(LED_STATE) {
		
		case LED_Start:
			 
			PORTB = 0x01;//B0 = 1; B1 =0;
			break;
		
		case LED_On:
			
            PORTB = 0x01;//B0 = 1; B1 =0; 
             break;
		
		case LED_Button:
			break;
		
		case LED_On2:
			
            PORTB = 0x02;//B0 = 0 B1 =1; 
            break;
		
		case LED_Button2: 
			break;
		
		default:
			PORTB = 0x01;
			break;
	}
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
	while (1) {
	LED_Tick();
	}
    return 1;
}
	


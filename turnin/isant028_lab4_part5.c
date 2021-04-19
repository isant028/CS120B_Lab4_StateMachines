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
enum Padlock_STATES {Padlock_Start, Padlock_Lock, Padlock_Unlock, Padlock_Code, Padlock_Wait} Padlock_STATE;

unsigned char temp = 0; 
unsigned char arr[4]= {0x04, 0x01, 0x02, 0x01};

void Padlock_Tick() {
	switch(Padlock_STATE) {
		
  		case Padlock_Start:
			Padlock_STATE =Padlock_Code;
			break;
		case Padlock_Code:
			if(PINA & 0x80){ //inside button pressed automatic locked
                Padlock_STATE = Padlock_Lock;
                 }
			else if(PINA == 0x00){ //stay here untill input is not 0
				Padlock_STATE =Padlock_Code;
			}			
			else if(PINA == arr[temp]){ //check sequences and keep track 
				temp++;
				Padlock_STATE = Padlock_Wait;
			}
			else if(temp == 4){ //check if went through all 4 sequences and if so unlock door
				temp = 0;
				Padlock_STATE = Padlock_Unlock;
			}
			else{
				Padlock_STATE =Padlock_Code;
				temp = 0;	
			}
			break;
		case Padlock_Wait:
			if(PINA == 0){ //go to code state when no button is pushed
				Padlock_STATE =Padlock_Code;
			}
			else{ //else stay here
				Padlock_STATE = Padlock_Wait;
			}
			break;
		case Padlock_Lock:
			Padlock_STATE =Padlock_Code;
			break;
		case Padlock_Unlock:
			Padlock_STATE =Padlock_Code;
			break;
		default:
			Padlock_STATE = Padlock_Start;
			break;
	}

	switch(Padlock_STATE){
		case Padlock_Start:
			PORTB=0x00;
			PORTC=0x00;
		break;
		case Padlock_Lock:
			PORTB=0x00;
			PORTC=0x01;
		break;
		case Padlock_Unlock:
			PORTB=0x01;
			PORTC=0x02;
		break;
		case Padlock_Code:
			PORTC=0x03;
		break;
		case Padlock_Wait:
			PORTC=0x04;
			
		break;
		default:
		break;
	}
}
	


int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    
	while (1) {
		Padlock_Tick();
	}
    return 1;
}

/*	Author: isant028
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum Padlock_STATES {Padlock_Start, Padlock_Lock, Padlock_Unlock, Padlock_Release, Padlock_CodeLock, Padlock_CodeRelease} Padlock_STATE;
unsigned char x; 
unsigned char p; 
unsigned char y; 
unsigned char in; 

void Padlock_Tick() {
	switch(Padlock_STATE) {
		
		case Padlock_Start:
			if(p&& !y&& !x &&!in){ //press pound buton goes to next state to ttry and unlock it
				Padlock_STATE=Padlock_Lock;
			}
			else{
				Padlock_STATE=Padlock_Start;
			}
		break;
		
		case Padlock_Lock:
			if(!p && !y&& !x &&!in){ //if pund button release, 2nd step to opening door is complete
                        Padlock_STATE=Padlock_Release;
            }
			else if(p&& !y&& !x &&!in){ //if pound button is still pushed stay here
                Padlock_STATE=Padlock_Lock;
                 }
			else{
				Padlock_STATE=Padlock_Start;
			}
		break;	
		
		case Padlock_Release:
			if(!p && y&& !x &&!in){ //once the y button is rleased, it will unlock the door
				Padlock_STATE=Padlock_Unlock;
			}
			else if (!p && !y&& !x &&!in){ //while y is still presses, stay in state
				Padlock_STATE=Padlock_Release;
			}
			else{
				Padlock_STATE=Padlock_Start;
			}
		break;
		
		case Padlock_Unlock:
			if (in){ //inside button pressed,  go to beginiing 
                    Padlock_STATE=Padlock_Start;
                }
	
			if(!x &&!y && p && !in){ //door is unlock and press pund to lock it
				Padlock_STATE=Padlock_CodeLock;
			}
			else{
				Padlock_STATE=Padlock_Unlock;
			}
		break;
		
		case Padlock_CodeLock:
			if(in){//inside button pressed,  go to beginiing
				Padlock_STATE=Padlock_Start;
			}
			else if(!x &&!y && !p && !in){ //go to next state when pund button is released
				Padlock_STATE=Padlock_CodeRelease;
			}
			else if(!x &&!y && p && !in){ //stay in state if pund button doesnt release
				Padlock_STATE=Padlock_CodeLock;
			}
			
			else{
				Padlock_STATE=Padlock_Unlock;
			}
		break;
		case Padlock_CodeRelease:
			if((!x && y && !p) || in){ //inside button pressed or y then lock door
				Padlock_STATE=Padlock_Start;
			}
			else if(!x && !y &&!p&&!in){ //no button pushed, stay here
				Padlock_STATE=Padlock_CodeRelease;
			}
			else{ //nothing else, unlock door 
				Padlock_STATE=Padlock_Unlock;
			}
		break;
		
		default:
			Padlock_STATE=Padlock_Start;
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
		case Padlock_Release:
			PORTB=0x00;
			PORTC=0x02;
		break;
		case Padlock_Unlock:
			PORTB=0x01;
			PORTC=0x03;
		break;
		case Padlock_CodeLock:
			PORTB=0x01;
			PORTC=0x04;
		break;
		case Padlock_CodeRelease:
			PORTB=0x01;
			PORTC=0x05;
			
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
		x = PINA & 0x01; 
		p = PINA & (0x01 << 2); 
		y = PINA & (0x01 << 1); 
		in = PINA & (0x01 << 7); 
		Padlock_Tick();
	}
    return 1;
}

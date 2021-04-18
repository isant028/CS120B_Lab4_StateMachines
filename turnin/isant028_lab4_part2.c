/*	Author: isant028
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum Count_STATES {Count_Start, Count_Inc, Count_Dec, Count_Res} Count_STATE;
void Count_Tick() {
	switch(Count_STATE) {
	case Count_Start:
        if (PINA == 0x01 && PORTC < 9){ //A0 pushed and add 1 to C up to 9
            PORTC++;
            Count_STATE = Count_Inc;
        }
        else if (PINA == 0x02 && PORTC > 0){ //A1 pushed and subs 1 to c till 0
            PORTC--;
            Count_STATE =  Count_Dec;
        }
        else if (PINA == 0x03){ //if both buttons pushed, c =0 
            PORTC = 0;
            Count_STATE = Count_Res;
        }
        else{
            Count_STATE = Count_Start;
        }
        break;

    case Count_Inc:
        if (PINA == 0x01){ //is Ao is still pushed stay here
            Count_STATE = Count_Inc;
        }
        else if (PINA == 0x00){ //if neother are pushed go to beginning 
            Count_STATE = Count_Start;
        }
        else if (PINA == 0x03){ //if both are pushed, C =0
            PORTC = 0;
            Count_STATE = Count_Res;
        }
        break;

    case  Count_Dec:
        if (PINA == 0x02){ //if A1 is still pushed stay here
            Count_STATE =  Count_Dec;
        }
        else if (PINA == 0x00){ //if neither is pushed go to start
            Count_STATE = Count_Start;
        }
        else if (PINA == 0x03){ //if both are pushed c =0
            PORTC = 0;
            Count_STATE = Count_Res;
        }
        break;

    case Count_Res:
        if (PINA == 0x03){ //when both A0 and A1 are oushed 
            Count_STATE = Count_Res;
        }
        else if (PINA == 0x01){ //if Ao is pushed, add 1
            PORTC++;
            Count_STATE = Count_Inc;
        }
        break;
	default:
			Count_STATE = Count_Start;
			break;
}
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
	PORTC = 0x07;
    
	while (1) {
	Count_Tick();
	}
    return 1;
}	


// ******************************************************************************************* //
//
// File:        main.c
// Due Date:    3/4/2016
// Team:        203
// Description: Main of Lab 2 Part 1 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"
#include "keypad.h"

#define ROW1 PORTDbits.RD7 //READ
#define ROW2 PORTDbits.RD13 //READ
#define ROW3 PORTFbits.RF0 //READ
#define ROW4 PORTGbits.RG1 //READ

#define PRESSED 1
#define RELEASED 0

#define FLAGDOWN 0
   
typedef enum stateTypeEnum
{
    Read_Keypad, 
    Print_LCD 
}stateType;

volatile stateType state = Read_Keypad;

int main(void)
{  
    initLCD();
    initKeypad();
    enableInterrupts();
    
    int counter = 1;
    char output = 'a';
    
    while(1)
    {
        switch(state)
        {
            case Read_Keypad:
               
               if(ROW1 == PRESSED || ROW2 == PRESSED || ROW3 == PRESSED || ROW4 == PRESSED)
               {
                   output = scanKeypad();
               }
               
               if(ROW1 == RELEASED || ROW2 == RELEASED || ROW3 == RELEASED ||  ROW4 == RELEASED)   
               {
                   state = Print_LCD;  
               }
               break;
                
            case Print_LCD:
                 
                if( counter < 8)
                {
                    printCharLCD(output);
                    counter++;          
                }
                else if (counter == 8)
                {
                    printCharLCD(output);
                    counter++; 
                    moveCursorLCD(1, 2);
                }
                else if (counter > 8 && counter < 16)
                {
                    printCharLCD(output);
                    counter++;        
                }
                else if(counter == 16)
                {
                    printCharLCD(output);
                    counter = 0; 
                    moveCursorLCD(1, 1);      
                }
                
                state = Read_Keypad;
            
            break;         
         }
    } 
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL2SRS) _CNInterrupt()
{
    IFS1bits.CNDIF = FLAGDOWN;
    IFS1bits.CNFIF = FLAGDOWN;
    IFS1bits.CNGIF = FLAGDOWN;
    
    int i;
    int j;
    int k;
     
    i = PORTD;
    j = PORTF;
    k = PORTG;
    
    if(state == Read_Keypad) 
        state = Print_LCD;
    else
        state = Read_Keypad;   
 
}
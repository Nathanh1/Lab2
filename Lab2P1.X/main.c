// ******************************************************************************************* //
//
// File:         main.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
// Team: 207
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"
#include "keypad.h"
   
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
    
    int counter = 1;
    char output = 'a';
    
    while(1)
    {
        switch(state)
        {
            case Read_Keypad:
               
               if(PORTDbits.RD7 == 0 || PORTDbits.RD13 == 0 || PORTFbits.RF0 == 0 || PORTGbits.RG1 == 0)
               {
                   
                   output = scanKeypad();
                   
               }
               
               if(PORTDbits.RD7 == 0 || PORTDbits.RD13 == 0 || PORTFbits.RF0 == 0 || PORTGbits.RG1 == 0)
                   
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
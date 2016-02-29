#include <xc.h>
#include <proc/p32mx470f512l.h>
#include "keypad.h"
#include "timer.h"

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void)
{
//ROW
    TRISDbits.TRISD7 = 1; // 1
    TRISDbits.TRISD13 = 1; //2
    TRISFbits.TRISF0 = 1;
    TRISGbits.TRISG1 = 1;      
        ;  
    
    //We are not using inter pull-ups
//    CNPU?bits.CNPU?# = 1;
//    CNPU?bits.CNPU?# = 1;
//    CNPU?bits.CNPU?# = 1;
//    CNPU?bits.CNPU?# = 1;
        
//INTERRUPT  
//    CNCON?bits.ON = 1;
//    
//    CNEN?bits.CNIE?# = 1;
//    CNEN?bits.CNIE?# = 1;
//    CNEN?bits.CNIE?# = 1;
//    CNEN?bits.CNIE?# = 1;
//       ;
//    
//    IFS1bits.CN?IF = 0;
//    IEC1bits.CN?IE = 1;
//    IPC8bits.CNIP = 7;
    
//COLUMN
    TRISDbits.TRISD12 = 0; //1 
    TRISFbits.TRISF1 = 0; //2
    TRISGbits.TRISG0 = 0; //3
        ;
    
    ODCDbits.ODCD12 = 1;
    ODCFbits.ODCF1 = 1;
    ODCGbits.ODCG0 = 1;
        ;
         
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed. The ascii character c programmatically is just 'c'
 */
char scanKeypad(void)
{
    
    
    
    //I NEED TO TURN OFF CHANGE NOTICE  CNEN
    
    char key = 'b';
    
    //COLUMN 1 ?
    LATDbits.LATD12 = 0;
    LATFbits.LATF1 = 0;
    LATGbits.LATG0 = 1;
    ;
    
    if(PORTDbits.RD7 == 0)
        key = '1';
    
    if(PORTDbits.RD13 == 0)
        key = '4';
    
    if(PORTFbits.RF0 == 0)
        key = '7';
    
    if(PORTGbits.RG1 == 0)
        key = '*';
    
    
    
    //COLUMN 2 ?
    LATDbits.LATD12 = 0;
    LATFbits.LATF1 = 1;
    LATGbits.LATG0 = 0;
    
    if(PORTDbits.RD7 == 0)
        key = '2';
    
    if(PORTDbits.RD13 == 0)
        key = '5';
    
    if(PORTFbits.RF0 == 0)
        key = '8';
    
    if(PORTGbits.RG1 == 0)
        key = '0';
      
    //COLUMN 3 ?
    LATDbits.LATD12 = 1;
    LATFbits.LATF1 = 0;
    LATGbits.LATG0 = 0;
    
    if(PORTDbits.RD7 == 0)
        key = '3';
    
    if(PORTDbits.RD13 == 0)
        key = '6';
    
    if(PORTFbits.RF0 == 0)
        key = '9';
    
    if(PORTGbits.RG1 == 0)
        key = '#';
        
    return key;
}

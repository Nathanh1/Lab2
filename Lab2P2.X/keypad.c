// ******************************************************************************************* //
//
// File:        keypad.c
// Due Date:    3/4/2016
// Team:        203
// Description: Keypad for Lab 2 Part 1 
// ******************************************************************************************* //
#include <xc.h>
#include <proc/p32mx470f512l.h>
#include "keypad.h"
#include "timer.h"

#define ROW1 PORTDbits.RD7 //READ
#define ROW2 PORTDbits.RD13 //READ
#define ROW3 PORTFbits.RF0 //READ
#define ROW4 PORTGbits.RG1 //READ

#define COL1 LATDbits.LATD12//WRITE
#define COL2 LATFbits.LATF1//WRITE
#define COL3 LATGbits.LATG0//WRITE

#define ROW1TYPE TRISDbits.TRISD7 //TYPE OF PIN
#define ROW2TYPE TRISDbits.TRISD13 //TYPE OF PIN
#define ROW3TYPE TRISFbits.TRISF0 //TYPE OF PIN
#define ROW4TYPE TRISGbits.TRISG1 //TYPE OF PIN

#define COL1TYPE TRISDbits.TRISD12 //TYPE OF PIN
#define COL2TYPE TRISFbits.TRISF1 //TYPE OF PIN
#define COL3TYPE TRISGbits.TRISG0 //TYPE OF PIN

#define CHGNOTICE_D7 CNENDbits.CNIED7
#define CHGNOTICE_D13 CNENDbits.CNIED13
#define CHGNOTICE_F0 CNENFbits.CNIEF0
#define CHGNOTICE_G1 CNENGbits.CNIEG1

#define PRESSED 1
#define RELEASED 0

#define INPUT 1
#define OUTPUT 0

#define TURNON 1
#define TURNOFF 0

#define ENABLE 1 
#define DISABLE 0

#define FLAGDOWN 0 

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void)
{
    //ROW
    ROW1TYPE = INPUT;
    ROW2TYPE = INPUT;
    ROW3TYPE = INPUT;
    ROW4TYPE = INPUT;
        
    //INTERRUPTs
    CNCONDbits.ON = ENABLE;
    CNCONFbits.ON = ENABLE;
    CNCONGbits.ON = ENABLE;
   
    CHGNOTICE_D7 = ENABLE;
    CHGNOTICE_D13 = ENABLE;
    CHGNOTICE_F0 = ENABLE;
    CHGNOTICE_G1 = ENABLE;

    //FLAGS
    IFS1bits.CNDIF = FLAGDOWN;
    IEC1bits.CNDIE = ENABLE;
    IFS1bits.CNFIF = FLAGDOWN;
    IEC1bits.CNFIE = ENABLE;
    IFS1bits.CNGIF = FLAGDOWN;
    IEC1bits.CNGIE = ENABLE;
    IPC8bits.CNIP = 7;        //priority
    
    //COLUMN
    COL1TYPE = OUTPUT;  
    COL2TYPE = OUTPUT; 
    COL3TYPE = OUTPUT; 
        
    //Open Drain Collector
    ODCDbits.ODCD12 = ENABLE;
    ODCFbits.ODCF1 = ENABLE;
    ODCGbits.ODCG0 = ENABLE;
        
         
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed. The ascii character c programmatically is just 'c'
 */
char scanKeypad(void)
{
     
    //Change notifications off 
    
    CHGNOTICE_D7 = DISABLE;
    CHGNOTICE_D13 = DISABLE;
    CHGNOTICE_F0 = DISABLE;
    CHGNOTICE_G1 = DISABLE;
    
    char key = 'b';
    
    //COLUMN 1 
   
    COL1=TURNON;
    COL2=TURNOFF;
    COL3=TURNOFF;
    
    if(ROW1==PRESSED)
        key = '1';
    
    else if(ROW2==PRESSED)
        key = '4';
    
    else if(ROW3==PRESSED)
        key = '7';
    
    else if(ROW4==PRESSED)
        key = '*';
    
    //COLUMN 2 
    COL1=TURNOFF;
    COL2=TURNON;
    COL3=TURNOFF;
    
    if(ROW1==PRESSED)
        key = '2';
    
    else if(ROW2==PRESSED)
        key = '5';
    
    else if(ROW3==PRESSED)
        key = '8';
    
    else if(ROW4==PRESSED)
        key = '0';
      
    //COLUMN 3 
    COL1=TURNOFF;
    COL2=TURNOFF;
    COL3=TURNON;
    
    if(ROW1==PRESSED)
        key = '3';
    
    else if(ROW2==PRESSED)
        key = '6';
    
    else if(ROW3==PRESSED)
        key = '9';
    
    else if(ROW4==PRESSED)
        key = '#';
        
    return key;
}

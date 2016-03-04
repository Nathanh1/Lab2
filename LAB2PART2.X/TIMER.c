#include <xc.h>
#include "timer.h"

#define TIMER2FLAG IFS0bits.T2IF
#define CN T2CONbits.ON

#define UP 1
#define DOWN 0

#define ENABLE 1
#define DISABLE 0

#define TIMER2 TMR2

#define CLEAR 0x0000

#define PRVAL (delay % (256*2))*8 - 1

#define InitPRVAL 4095

#define DELAY delay/(256*2)

#define PERIODREGISTER PR2

void delayUs(unsigned int delay)
{
    int j=0;
    
    TIMER2FLAG = DOWN; //PUT THE FLAG DOWN
    
    TIMER2 = CLEAR; //CLEAR THE TIMER
    
    CN = ENABLE; //ENABLE CHANGE NOTIFICATION
    
    PERIODREGISTER = InitPRVAL;
    /*
    for(j=0; j < DELAY; j++)
    {
        
        while(TIMER2FLAG = DOWN);//WHILE FLAG IS DOWN
        
        TIMER2FLAG = DOWN;//FORCE FLAG DOWN
        
    }*/
    
    while(TIMER2FLAG == DOWN);//WHILE FLAG IS DOWN
        
    TIMER2FLAG = DOWN;//FORCE FLAG DOWN
    
    
    PERIODREGISTER = PRVAL; //SET TIMER2 PERIOD REGISTER TO DELAY CALCULATION
    /*
    while(TIMER2FLAG==DOWN); //BREAK IF TIMER 2 FLAG GOES UP
    
    TIMER2FLAG = DOWN; //PUT THE FLAG DOWN
    */
    CN = DISABLE; //DISABLE CHANGE NOTIFICATION
}
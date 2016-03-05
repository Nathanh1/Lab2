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

#define GOOD 1
#define BAD 0

#define TURNON 1
#define TURNOFF 0

#define FULL 1
#define EMPTY 0

#define VALID 1 //for set mode
#define NOTVALID 0 //for set mode
   
typedef enum stateTypeEnum
{
    Read_Keypad,
    Print_LCD,
    Set_Mode,
    Enter_Mode
    
}stateType;

volatile stateType state = Read_Keypad;

int main(void)
{  
    initLCD();
    initKeypad();
    enableInterrupts();
    
    int counter = 1;
    char output = 'a';
    int count = 0;
    
    char p1[4]={'1','3','3','7'};//PRESET PASSWORD 1
    char p2[4];//PASSWORD 2
    char p3[4];//PASSWORD 3
    char p4[4];//PASSWORD 4
    
    char UserInput[4]; //USER INPUT ARRAY
    int i=0; //USER INPUT ARRAY ELEMENT
    
    int InSet = TURNOFF;
    int InEnter = TURNON;
    int GUESS1;
    int GUESS2;
    int GUESS3;
    int GUESS4;
    
    int StarCount=0;
    
    int PASSWORD2 = EMPTY;
    int PASSWORD3 = EMPTY;
    int PASSWORD4 = EMPTY;
    
    int USERINPUT= VALID; //for checking * or 
    
    while(1)
    {
        switch(state)
        {
            case  Enter_Mode:
                
                InSet = TURNOFF;
                InEnter = TURNON;             
                clearLCD();
                printStringLCD("Enter Code:");
                moveCursorLCD(0,2); //COL ROW
                count=0;
                StarCount=0;
            
                if(count == 4)
                {
                   count = 0;
                
                   for(i=0;i<4;i++)
                   {
                        if(p1[i]!=UserInput[i])
                        {
                            GUESS1=BAD;
                            break;
                        }
                        else
                        {
                            GUESS1=GOOD;
                        }
                    }
                    for(i=0;i<4;i++)
                    {
                        if(p2[i]!=UserInput[i])
                        {
                           GUESS2=BAD;
                           break;
                        }
                        else
                        {
                           GUESS2=GOOD;
                        }
                    }
                    for(i=0;i<4;i++)
                    {
                        if(p3[i]!=UserInput[i])
                        {
                            GUESS3=BAD;
                            break;
                        }
                        else
                        {
                            GUESS3=GOOD;
                        }
                    }
                    for(i=0;i<4;i++)
                    {
                        if(p4[i]!=UserInput[i])
                        {
                            GUESS4=BAD;
                            break;
                        }
                        else
                        {
                            GUESS4=GOOD;
                        }
                    }  
                    if(GUESS1==GOOD || GUESS2==GOOD || GUESS3==GOOD || GUESS4==GOOD)
                    {
                        clearLCD();
                        printStringLCD("GOOD");
                        for(i=0;i<500;i++)
                        {
                            delayUs(1000);
                        }
                    }
                    else if(GUESS1==BAD && GUESS2==BAD && GUESS3==BAD && GUESS4==BAD)
                    {
                        clearLCD();
                        printStringLCD("BAD");
                        for(i=0;i<500;i++)
                        {
                            delayUs(1000);
                        }
                    }        
                }
                if(StarCount==1)
                {
                    USERINPUT=VALID; //ASSUME
                    InSet = TURNOFF;
                    InEnter = TURNON;
                    StarCount=0;
                    count=0;
                
                    for(i=0;i<4;i++)//RESET USER INPUT
                    {
                        UserInput[i]='0';
                    }  
                    state = Set_Mode;
                }
            
                break;
            
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
                
                count++;
                          
                break;
            
            case Set_Mode:
                
                InSet = TURNON;
                InEnter = TURNOFF;
                
                clearLCD();
                printStringLCD("Set Mode:");
                moveCursorLCD(0,2); //COL ROW
                
                
                USERINPUT=VALID;
            
                for(i=0;i<4;i++)//Check UserInput values UI[0]->UI[4]      
                {
                    if(UserInput[i]=='*' || UserInput[i]=='#')//Check for * or # 
                    {
                        USERINPUT=NOTVALID; //SET USERINPUT to NOTVALID
                        
                    }
                }
            
                if(USERINPUT==VALID)// No * or # in USERINPUT VALUES
                {
                    if(PASSWORD2==EMPTY)
                    {
                                for(i=0;i<4;i++)
                                    {
                                        p2[i]=UserInput[i]; 

                                    }
                                PASSWORD2 = FULL;
                            
                                clearLCD();
                                printStringLCD("PW2 STORED");
                                for(i=0;i<500;i++)
                                    {
                                        delayUs(1000);
                                    }
           
                    }
                    else if(PASSWORD2==FULL && PASSWORD3==EMPTY)
                    {
                        for(i=0;i<4;i++)
                        {
                            p3[i]=UserInput[i]; 

                        }
                        PASSWORD3 = FULL;
                            
                        clearLCD();
                        printStringLCD("PW3 STORED");
                        for(i=0;i<500;i++)
                        {
                            delayUs(1000);
                        }
                    }
                    
                     else if(PASSWORD2==FULL && PASSWORD3==FULL && PASSWORD4==EMPTY)
                    {
                        for(i=0;i<4;i++)
                        {
                            p4[i]=UserInput[i]; 
                        }
                        PASSWORD4 = FULL;
                            
                        clearLCD();
                        printStringLCD("PW4 STORED");
                            
                        for(i=0;i<500;i++)
                        {
                            delayUs(1000);
                        }

                        clearLCD();
                        printStringLCD("VALID"); //PW4 IS THE LAST PASSWORD ENTERED

                        for(i=0;i<500;i++)
                        {
                            delayUs(1000);
                        }
                    }
                    if (PASSWORD2==FULL && PASSWORD3==FULL && PASSWORD4==FULL) //ALL PASSWORDS ARE FULL
                    {
                        clearLCD();
                        printStringLCD("STORAGE FULL");
                        for(i=0;i<500;i++)
                        {
                            delayUs(1000);
                        }
                    }
                    else if (PASSWORD2==EMPTY || PASSWORD3==EMPTY || PASSWORD4==EMPTY) //At LEAST ONE PASSWORD IS EMPTY
                    {
                        clearLCD();
                        printStringLCD("VALID");
                        for(i=0;i<500;i++)
                        {
                            delayUs(1000);
                        }
                    }
                
                }
            
            else if(USERINPUT==NOTVALID)// * or # is in USERINPUT VALUES
            {
                    clearLCD();
                    printStringLCD("NOT VALID");
                    
                    for(i=0;i<500;i++)
                        {
                            delayUs(1000);
                        }
            }
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
    
    int l;
    int j;
    int k;
    int count = 0;
     
    l = PORTD;
    j = PORTF;
    k = PORTG;
    
    if(state == Read_Keypad) 
    {
        state = Print_LCD;
        count++;
    }
    else if (state == Print_LCD && count < 4)
        state = Read_Keypad; 
    else if (count == 4)
        state = Enter_Mode;
}
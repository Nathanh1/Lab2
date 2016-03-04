#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "LCD.h"
#include "TIMER.h"


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

#define GOOD 1
#define BAD 0

#define PRESSED 1
#define RELEASED 0

#define INPUT 1
#define OUTPUT 0

#define TURNON 1
#define TURNOFF 0

#define FULL 1
#define EMPTY 0

#define VALID 1 //for set mode
#define NOTVALID 0 //for set mode

int main(void)
{    
    
    initLCD();
    ROW1TYPE=INPUT;
    ROW2TYPE=INPUT;
    ROW3TYPE=INPUT;
    ROW4TYPE=INPUT;
    
    COL1TYPE=OUTPUT;
    COL2TYPE=OUTPUT;
    COL3TYPE=OUTPUT;
    
    int count =0;
    
    int ROW=1;
    
    char output='0';
    char p1[4]={'1','3','3','7'};//PRESET PASSWORD 1
    char p2[4];//PASSWORD 2
    char p3[4];//PASSWORD 3
    char p4[4];//PASSWORD 4
    
    char UserInput[4]; //USER INPUT ARRAY
    int i=0; //USER INPUT ARRAY ELEMENT
    
    int SetMode=TURNOFF;
    int EnterMode=TURNON;
    int GUESS1;
    int GUESS2;
    int GUESS3;
    int GUESS4;
    
    int StarCount=0;
    
    int PASSWORD2 = EMPTY;
    int PASSWORD3 = EMPTY;
    int PASSWORD4 = EMPTY;
    
    int USERINPUT= VALID; //for checking * or #
    
    
    printStringLCD("Enter Code:");
    moveCursorLCD(0,2); //COL ROW
    
    while(1)
    {
        
        /*if(count==4)
        {
            SETMODE=0;
            for(i=0;i<4;i++)
            {
                if(x[i]=='*' || x[i]=='#')
                {
                    if(x[i]=='*')
                    {
                        SETMODE=SETMODE+1;
                    }
                    if(x[i]=='#')
                    {
                        SETMODE=0;
                        
                    }
                    BAD=1;
                    if(SETMODE==2)
                    {
                        PASS=1;
                    }
                   
                }
            }
            if(SETMODE<2)
            {
                if(BAD==1)
                {

                    clearLCD();
                    printStringLCD("BAD");
                    delayUs(20000000);
                }
                else if(BAD==0)
                {
                    clearLCD();
                    printStringLCD("GOOD");
                    delayUs(20000000);
                }
                clearLCD();
                printStringLCD("Enter");
                moveCursorLCD(0,2); //COL ROW
                count=0;
                BAD=0;
                SETMODE=0;
            }
            if(SETMODE>=2)
            {
                clearLCD();
                printStringLCD("SET MODE");
                moveCursorLCD(0,2); //COL ROW
                count=0;
                
                if(BAD==1 && PASS==0)
                {
                    SETMODE=0;
                    clearLCD();
                    printStringLCD("NOT VALID");
                    delayUs(20000000);
                    
                    PASS=1;
                }
                else if (BAD==0 && PASS==0)
                {
                    SETMODE=0;
                    clearLCD();
                    printStringLCD("VALID");
                    delayUs(20000000);
                    
                    PASS=1;
                }
                PASS=0;
                BAD=0;
            }
        }*/
        
        
//----------------------------------------------------------------------------------------------------------------------------------///
//ENTER MODE
        if(count==4 && EnterMode==TURNON) 
        {
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
                else if(GUESS1==BAD && GUESS2==BAD & GUESS3==BAD && GUESS4==BAD)
                {
                    clearLCD();
                    printStringLCD("BAD");
                        for(i=0;i<500;i++)
                        {
                        delayUs(1000);
                        }
                }
            
            clearLCD();
            printStringLCD("Enter Code:");
            moveCursorLCD(0,2); //COL ROW
            count=0;
            StarCount=0;
            
        }
//----------------------------------------------------------------------------------------------------------------------------------///
//SETMODE 
        else if(count==4 && SetMode==TURNON)  //SetMode turned on from enter mode
        {
            USERINPUT=VALID;
            
            for(i=0;i<4;i++)//Check UserInput values UI[0]->UI[4]      
            {
                if(UserInput[i]=='*' || UserInput[i]=='#')//Check for * or # 
                {
                    USERINPUT=NOTVALID; //SET USERINPUT to NOTVALID
                    break;//break the check loop
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
           
            SetMode=TURNOFF;
            EnterMode=TURNON;
            
            clearLCD();
            printStringLCD("Enter Code:");
            moveCursorLCD(0,2); //COL ROW
            
            count=0;
            USERINPUT=VALID;
            StarCount=0;
            
        }
        
        
        
//----------------------------------------------------------------------------------------------------------------------------------///
//SCAN KEYBOARD
        
            COL1=TURNON;
            COL2=TURNOFF;
            COL3=TURNOFF;
            
                if(ROW1==PRESSED)
                        {

                            output='1';
                            printCharLCD(output);
                            count=count+1;
                            while(ROW1==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
                else if(ROW2==PRESSED)
                        {

                            output='4';
                            printCharLCD(output);
                            count=count+1;
                            while(ROW2==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
                else if(ROW3==PRESSED)
                        {

                            output='7';
                            printCharLCD(output);
                            count=count+1;
                            while(ROW3==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
                else if(ROW4==PRESSED)
                        {

                            output='*';
                            printCharLCD(output);
                            count=count+1;
                            
                            if(SetMode==TURNOFF)
                            {
                                if(UserInput[count-2]=='*' && UserInput[0]=='*')//CHECK VALUE BEFORE
                                {
                                    StarCount=StarCount+1;
                                }
                               
                            }
                            
                            while(ROW4==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
            
            
            COL1=TURNOFF;
            COL2=TURNON;
            COL3=TURNOFF;
       
                if(ROW1==PRESSED)
                        {
                            output='2';
                            printCharLCD(output);
                            count=count+1;
                            while(ROW1==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
                else if(ROW2==PRESSED)
                        {
                            output='5';
                            printCharLCD(output);
                            count=count+1;
                            while(ROW2==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
                else if(ROW3==PRESSED)
                        {
                            output='8';
                            printCharLCD(output);
                            count=count+1;
                            while(ROW3==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
                else if(ROW4==PRESSED)
                        {
                            output='0';
                            printCharLCD(output);
                            count=count+1;
                            while(ROW4==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
            
            
            COL1=TURNOFF;
            COL2=TURNOFF;
            COL3=TURNON;
        
                if(ROW1==PRESSED)
                        {
                            output='3';
                            printCharLCD(output);
                            count=count+1;
                            while(ROW1==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
                else if(ROW2==PRESSED)
                        {
                            output='6';
                            printCharLCD(output);
                            count=count+1;
                            while(ROW2==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
                else if(ROW3==PRESSED)
                        {
                            output='9';
                            printCharLCD(output);
                            count=count+1;
                            while(ROW3==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
                else if(ROW4==PRESSED)
                        {
                            output='#';
                            printCharLCD(output);
                            count=count+1;
                            while(ROW4==PRESSED)
                            {
                                //DO NOTHING
                            }
                        }
            
            UserInput[count-1] = output; //SET UserInput ARRAY element equal to value typed
            
//CHECK IF SET MDOE IS ENTERED     
            if(StarCount==1)
            {
                USERINPUT=VALID; //ASSUME
                SetMode=TURNON;
                EnterMode=TURNOFF;
                StarCount=0;
                count=0;
                
                    for(i=0;i<4;i++)//RESET USER INPUT
                    {
                        UserInput[i]='0';
                    }
                
                clearLCD();
                printStringLCD("Set Mode:");
                moveCursorLCD(0,2); //COL ROW
            }
        
    }   
    
    
    
    return 0;
    
    
}

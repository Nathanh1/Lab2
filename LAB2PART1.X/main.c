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



#define PRESSED 1
#define RELEASED 0

#define INPUT 1
#define OUTPUT 0

#define TURNON 1
#define TURNOFF 0

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
    
    while(1)
    {
        if(count>=16)
        {
            count=0;
            if(ROW==1)
            {
                ROW=2;
                moveCursorLCD(0,2); //COL ROW
            }
            else if(ROW==2)
            {
                ROW=1;
                moveCursorLCD(0,1); //COL ROW
                
            }
        }
            
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
                        while(ROW4==PRESSED)
                        {
                            //DO NOTHING
                        }
                    }
            else
                    {
                        
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
            else
                    {
                        
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
            else
                    {
                        
                    }
        
    }    
    return 0;
}

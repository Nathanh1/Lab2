//// ******************************************************************************************* //
////
//// File:         debugLab2.c
//// Date:         3/3/2016
//// Authors: Riley Magsino      
////
//// Description: Quality Assurance for lab 2
//// ******************************************************************************************* //
//


//   HAD TO COMMENT THE CODE OUT TO GET IT TO COMPILE      



//#include <xc.h>
//#include <sys/attribs.h>
//
//#define CONFIGTEST 1
//#define TIMERTEST 0
//#define INVALIDTEST 0
//#define ENTERTEST 0
//#define TRUE 1
//#define FALSE 0
//
//#define ROW_TEST PORTDbits.RD7
//#define COLUMN_TEST LATDbits.LATD12
//
//int main(void)
//{
//	int result;
//    
//    if (CONFIGTEST = 1) 
//    {
//        while(1)
//        {
//
//        result = ConfigTest();
//        if (ConfigTest == TRUE)
//        {
//            printStringLCD("Pass");
//        }
//	else
//    {
//		printStringLCD("Fail");
//	}
//		}
//    }   
//
//    if(TIMERTEST = 1)
//    {
//        while(1) 
//        {
//	
//        //result = TimerTest();
//        if(result == TRUE)
//        {
//            printStringLCD("Pass");
//        }
//        else
//        {
//            printStringLCD("Fail");
//        }
//
//        }   
//    }
//
//    if(INVALIDTEST == 1) 
//    {
//        while(1) 
//        {
//	
//            result = InvalidValidTest();
//        
//            if(result == TRUE) 
//            {
//                printStringLCD("Pass");
//            }
//            else 
//            {
//                printStringLCD("Fail");
//            }
//        }
//    }
//    return;
//    if(ENTERTEST = 1)  
//    {
//        while(1)
//        {
//            result = EnterTest();
//            if(result == TRUE) 
//            {
//                printStringLCD("Pass");
//            }
//            else
//            {
//                printStringLCD("Fail");
//            }
//        }
//    }	
//}
//
//
//
//int ConfigTest()
//{
//	char pin;
//	//pin = Config(ROW_TEST, COLUMN_TEST); // test function that returns character that is sent when the programmed column and row are high with specifications from data sheet
//	if (pin == '1') { // expected value to be returned back
//		return TRUE;
//	}
//	else {
//		return FALSE;
//	}
//}
//
//// tests timer to ensure it is accurate
////int TimerTest(){ 
////	
////	int delay = 2000000; // delay for 2 seconds
////	int value = delayUs(delay); // value of PR returned and changed delay to also return an int
////	PR = 78124; // expected value
////    
////	if( value = PR ) {
////		return TRUE;
////	}
////	
////	else	{
////		return FALSE;
////	}
////}
//
//int InvalidValidTest(){ // tests SET mode
//		char test = '*';
//		int result;
//		result = InvalidValid(test);
//		if (result == TRUE) {
//			return TRUE;
//		}
//		else {
//			return FALSE;
//		}
//}
//
//int EnterTest()
//{
//		char test = '*';
//		int result;
//		result = InvalidValid(test); // calls InvalidValid function because the two functions behave very similarly
//		if(result == TRUE) 
//        {
//			return TRUE;
//		}
//		else 
//        {
//			return FALSE;
//		}
//}
//
//int InvalidValid(char testString) 
//{
//	int i;
//	int j = strlen(testString);
//
//	for(i = 0; i < j; i++) 
//    {
//		if (testString[i] == '*' || testString[i] == '#')
//        {
//			return FALSE;
//		}
//	}
//	return TRUE;
//}
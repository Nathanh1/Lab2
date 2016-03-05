// ******************************************************************************************* //
//
// File:        lcd.h
// Due Date:    3/4/2016
// Team:        203
// Description: LCD header file for Lab 2 Part 1 
// ******************************************************************************************* //


void writeLCD(unsigned char word, unsigned int commandType, unsigned int delay);
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower);
void initLCD(void);
void clearLCD(void);
void moveCursorLCD(unsigned char x, unsigned char y);
void printCharLCD(char c);
void printStringLCD(const char* s);
void testLCD();
#include "wramp.h"

int counter;

// Prototype headers for this program's subroutines.
int getChar();
void printChar(int c);
void writesp2_ints(int c);
void writesp2_mins(int c);
void writesp2_secs(int c);

/**
 * Serial main reads a global counter and displays the 
 * value in Serial Port 2.
 * 
 * Note: This function contains an infinite loop which
 *       breaks if 'q' is written to Serial Port 2.
 * 
 * This program continuously prints the value of the
 * global counter variable and prints its value in the
 * specified format to Serial Port 2.
 **/
int serial_main(){

    int format = 1; 
    while(1){

        // Loop checks the format and writes accordingly
        if(WrampSp2->Stat & WRAMP_SP_RDR){         
            format = WrampSp2->Rx;

            // Exit program if 'q' is written.
            if(format == 'q'){
                return 0;
            }
        }
        /* TESTING INCREMENT */
        global_counter++;
    
        // Write as timer minutes if '2' is written.   
        if(format == '2'){
            writesp2_mins(global_counter);
        }
        // Write as seconds if '3' is written.   
        else if(format == '3'){
            writesp2_secs(global_counter);
        }
        // Else write the value as a count.   
        else{
            writesp2_ints(global_counter);
        }      
    }
    return 1;
}

/**
 * Receives a character from Serial Port 2.
 * Note:    This function blocks by polling to wait
 *          for Receive Data Ready is 1.
 *
 * Returns:
 *      The character received from Serial Port 2.
 **/
int getChar(){

    while(!(WrampSp2->Stat & WRAMP_SP_RDR)); 
    return WrampSp2->Rx;
}

/**
 * Transmits a character to Serial Port 2.
 * Note:    This function blocks by polling to wait
 *          for Transmit Data Sent is 0.
 *
 * Parameters:
 *  c    The next character to transmit.
 **/
void printChar(int c){

    while(!(WrampSp2->Stat & WRAMP_SP_TDS)); 
    WrampSp2->Tx = c;
    return;
}

/**
 * Displays number of timer interrupts.
 * Formats number to '\rtttttt' then calls printChar.
 * Note:    This method calls a function that blocks.
 * Parameters:
 *  c   The number to format and send to Serial Port 2.
 */
void writesp2_ints(int c){

    int s1 = (c / 100000) % 10; // t00000
    int s2 = (c / 10000) % 10;  // 0t0000
    int s3 = (c / 1000) % 10;   // 00t000
    int s4 = (c / 100) % 10;    // 000t00
    int s5 = (c / 10) % 10;     // 0000t0
    int s6 = c % 10;            // 00000t

    printChar('\r');
    printChar(s1 + '0');
    printChar(s2 + '0');
    printChar(s3 + '0');
    printChar(s4 + '0');
    printChar(s5 + '0');
    printChar(s6 + '0');
    return;
}

/**
 * Displays timer as minutes and seconds.
 * Formats number to '\rmm:ss' then calls printChar.
 * Note:    This method calls a function that blocks.
 * 
 * Parameters:
 *  c   The number to format and send to Serial Port 2.
 */
void writesp2_mins(int c){

    int s1 = (c / 600) % 6;     // m0:00
    int s2 = (c / 60) % 10;     // 0m:00
    int s3 = (c % 60) / 10;     // 00:s0
    int s4 = c % 10;            // 00:0s

    printChar('\r');
    printChar(s1 + '0');
    printChar(s2 + '0');
    printChar(':');
    printChar(s3 + '0');
    printChar(s4 + '0');
    return;
}

/**
 * Displays number of seconds and hundredths of a second.
 * Formats number to '\rssss.ss' then calls printChar.
 * Note: This method calls a function that blocks.
 * 
 * Parameters:
 *  c   The number to format and send to Serial Port 2.
 */
void writesp2_secs(int c){

    int h = (c % 100);          // hundredths
    int s = (c / 100);          // seconds

    int s1 = (s / 1000);        // s000.00
    int s2 = (s % 1000) / 100;  // 0s00.00
    int s3 = (s % 100) / 10;    // 00s0.00
    int s4 = (s % 10);          // 000s.00
    int s5 = (h / 10);          // 0000.h0
    int s6 = (h % 10);          // 0000.0h

    printChar('\r');
    printChar(s1 + '0');
    printChar(s2 + '0');
    printChar(s3 + '0');
    printChar(s4 + '0');
    printChar('.');
    printChar(s5 + '0');
    printChar(s6 + '0');
    return;
}

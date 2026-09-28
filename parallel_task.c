#include "wramp.h"

// Prototype headers for this program's subroutines.
void writessd_dec(int n); 
void writessd_hex(int n);

/**
 * Main reads the switches and writes to the SSDs.
 * 
 * Note:    This function contains an infinite loop 
 *          and breaks if parallel button 2 is pushed.
 * 
 * This program continously reads the values of the
 * switches and the buttons from the Parallel Port, 
 * and changes the format of the number to display as 
 * a hex number if button 1 is pushed, else displays
 * as a decimal number.  
 **/
int main(){

    // Variables at the top the block to read from I/O.
    int switches = 0;
    int buttons = 0;
    while(1){

        // Read current values of switches and buttons.
        switches = WrampParallel->Switches;
        buttons = WrampParallel->Buttons;

        // If the pressed button was not 0 or 1, exit.
        if(buttons > 0x2){
            return 0;
        }
        // Else if button 0, write in decimal.
        else if(buttons & 0x1){
            WrampParallel->Ctrl = 0; // Unset HEX decode.
            writessd_dec(switches);
        }
        // Else if button 1, write in hex.
        else if(buttons & 0x2){
            WrampParallel->Ctrl = 1; // Set HEX decode.
            writessd_hex(switches);
        }
    }
    return 1;
}
  
/**
 * Writes each decimal digit to the SSD's
 * Parameters:
 *  n   The int number to calculate each digit from.
 **/            
void writessd_dec(int n){
  
    WrampParallel->UpperLeftSSD = (n / 1000) % 10; 
    WrampParallel->UpperRightSSD = (n / 100) % 10;
    WrampParallel->LowerLeftSSD = (n / 10) % 10;   
    WrampParallel->LowerRightSSD = n % 10;
    
    return;
}

/**
 * Writes each hex digit to the SSD's
 * Parameters:
 *  n   The int number to calculate each hex digit from.
 **/
void writessd_hex(int n){
    
    WrampParallel->UpperLeftSSD = (n >> 12) & 0xF; 
    WrampParallel->UpperRightSSD = (n >> 8) & 0xF; 
    WrampParallel->LowerLeftSSD = (n >> 4) & 0xF; 
    WrampParallel->LowerRightSSD = n & 0xF;
    return;
}







#include "stdio.h"
#include "stdlib.h"
#include "p30fxxxx.h"
#include "p30F4013.h"
#include "Tasteri.h"
#include "serijska.h"

_FOSC(CSW_FSCM_OFF & amp; XT_PLL4); // Instruction clock is the same as the crystal clock
_FWDT(WDT_OFF);

unsigned int forward = 0, backward = 0, left = 0, right = 0, turbo = 0;
unsigned int i = 0, stopwatch = 0;
unsigned char rxTemp;

void attribute((interrupt)) _U1RXInterrupt(void) {
  IFS0bits.U1RXIF = 0;
  rxTemp = U1RXREG;
}


int main(int argc, char ** argv) {
    
    Pinovi_tasteri();
    Init_UART1();
    
    while (1) {
      Pritisnuto_lijevo(); // check if left is pressed, if yes set left = 1
      Pritisnuto_desno(); // check if right is pressed, if yes set right = 1
      Pritisnuto_naprijed(); // software debouncing is not needed because hardware debouncing exists
      Pritisnuto_nazad();
      Pritisnuto_turbo();
      
      if (forward == 1) {
        // if forward is pressed, send "00000fffff"  (forward)
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
       
        for (i = 0; i < 1000; i++);

        Write_UART1('f');
        Write_UART1('f');
        Write_UART1('f');
        Write_UART1('f');
        Write_UART1('f');
       
        for (i = 0; i < 1000; i++);


      }
      if (backward == 1) {
        // if backward is pressed, send "00000bbbbb" (reverse)
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
       
        for (i = 0; i < 1000; i++);
	
	Write_UART1('b');
        Write_UART1('b');
        Write_UART1('b');
        Write_UART1('b');
        Write_UART1('b');
       
        for (i = 0; i < 1000; i++);


      }
      
      if (left == 1) {
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
       
        for (i = 0; i < 1000; i++);
	
	Write_UART1('l');
        Write_UART1('l');
        Write_UART1('l');
        Write_UART1('l');
        Write_UART1('l');
       
        for (i = 0; i < 1000; i++);

      }

       if (turbo == 1) {
       Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
       
        for (i = 0; i < 1000; i++);
	Write_UART1('t');
        Write_UART1('t');
        Write_UART1('t');
        Write_UART1('t');
        Write_UART1('t');
       
        for (i = 0; i < 1000; i++);

      }
      if (right == 1) {
         Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
       
        for (i = 0; i < 1000; i++);
	Write_UART1('r');
        Write_UART1('r');
        Write_UART1('r');
        Write_UART1('r');
        Write_UART1('r');
       
        for (i = 0; i < 1000; i++);

      }
      if (forward == 0 && backward == 0 && right == 0 && left == 0 && turbo == 0) {
        // if nothing is pressed, send "00000nnnnn"
        // so the receiver knows when braking should be activated
	Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
        Write_UART1('0');
       
        for (i = 0; i < 1000; i++);
	Write_UART1('n');
        Write_UART1('n');
        Write_UART1('n');
        Write_UART1('n');
        Write_UART1('n');
       
        for (i = 0; i < 1000; i++);
       
      }
    }
    return (EXIT_SUCCESS);

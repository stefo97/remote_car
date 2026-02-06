#include "stdio.h"
#include "stdlib.h"
#include "p30fxxxx.h"
#include "serijska.h"
#include "motori.h"
#include "tajmer.h"
#include "outcompare.h"



_FOSC(CSW_FSCM_OFF & amp; XT_PLL4); // Instruction clock is the same as the crystal clock
_FWDT(WDT_OFF);


unsigned char rxTemp;
unsigned char inputBuffer[];
unsigned int bufferIndex = 0;
unsigned int forward = 0, backward = 0, left = 0, right = 0, turbo = 0, i, none = 0;
unsigned int rx_forward = 0, rx_left = 0, rx_right = 0, rx_backward = 0, rx_turbo = 0, rx_none;

void attribute((interrupt)) _T2Interrupt(void) {
  TMR2 = 0;
  IFS0bits.T2IF = 0;
}


void attribute((interrupt)) _T3Interrupt(void) {
  TMR3 = 0;
  IFS0bits.T3IF = 0;
}

// state check
void Check_Pressed(void)
{
  // if 3 out of 5 useful characters are received, set the corresponding flag
  if (rx_forward >= 3) {
    forward = 1;
    rx_forward = 0;
  } else forward = 0;
  if (rx_left >= 3) {
    left = 1;
    rx_left = 0;
  } else left = 0;
  if (rx_right >= 3) {
    right = 1;
    rx_right = 0;
  } else right = 0;
  if (rx_backward >= 3) {
    backward = 1;
    rx_backward = 0;
  } else backward = 0;
  if (rx_turbo >= 3) {
    turbo = 1;
    rx_turbo = 0;
  } else turbo = 0;
  if (rx_none >= 3) {
    none = 1;
    rx_none = 0;
  } else none = 0;
}



void attribute((interrupt)) _U1RXInterrupt(void) 
{
  rxTemp = U1RXREG;
  inputBuffer[bufferIndex] = rxTemp;
  bufferIndex++; // store 10 received characters in inputBuffer

  if (bufferIndex >= 10) {
    
    // in sequences of 10 characters, check how many are valid
    for (i = 0; i < bufferIndex; i++) {
      switch (inputBuffer[i]) {

      case 'f': // forward
        rx_forward++;
        inputBuffer[i] = 0;
        break;
      case 'b': // reverse
        rx_backward++;
        inputBuffer[i] = 0;
        break;
      case 'l': // left
        rx_left++;
        inputBuffer[i] = 0;
        break;
      case 'r': // right
        rx_right++;
        inputBuffer[i] = 0;
        break;
      case 't': // turbo
        rx_turbo++;
        inputBuffer[i] = 0;
        break;
      case 39: // nothing
        rx_none++;
        inputBuffer[i] = 0;
        break;
      default: // useless noise
        inputBuffer[i] = 0;
        break;
      }
    }
    Check_Pressed();
    bufferIndex = 0;
  }
  IFS0bits.U1RXIF = 0;
}


int main(int argc, char ** argv) {
  Init_UART1();
  Pinovi_motora();
  Dodatni_pinovi();

  Init_PWM(); // initialize PWM pins and set frequency to 25 kHz
  while (1) {
    if (forward == 1) {
      Pravo(); // both wheels get the same voltage and rotate in the same direction
    }
    if (none == 1) {
      Nista(); // braking, forced &quot;1&quot; on both motors
    }
    if (right == 1) {
      Desno(); // one motor driven much stronger than the other + right indicator
    }
    if (left == 1) {
      Lijevo(); // left indicator
    }
    if (turbo == 1) {
      Turbo(); // maximum PWM duty cycle and all lights on
    }
    if (backward == 1) {
      Rikverc(); // reverse lights and same PWM on both wheels, reversed direction
    }
  }
  return (EXIT_SUCCESS);
}

#include <msp430.h>
/**
 * main.c
 */
int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;     // desbloqueo pines
  // Activo pin de led rojo como salida
  P1DIR |= BIT0; // del puerto 1 activo el bit 0
  P1REN |= BIT1; // enable el switch como pull on
  P1OUT |= BIT1; // pongo el pull-up en el switch
  while (1) {

    if (P1IN & BIT1) {
      // si no pulso el led
      // 1 es default porque es pull up
      P1OUT |= BIT0;
    } else {
      P1OUT &= ~BIT0;
    }
  }
  
}
#include <msp430.h>
/**
 * main.c
 */
int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;     // desbloqueo pines
  // Pongo mi led rojo a salida
  P1DIR |= BIT0;
  // Pongo el boton como entrada
  P1DIR &= ~BIT1;
  // hago enable en el switch como pull on
  P1REN |= BIT1;
  // Lo pongo como pullup
  P1OUT |= BIT1;
  P1IE |= BIT1; // enable IRQ ( pongo que el boton es una inte
  // Falling edge -> cuando no esta pulsado creo* que es interr
  P1IES |= BIT1;
  // Le pongo el flag que habilita las interrupciones. Avisa a
  // de que ha habido un cambio en su valor -> hace caso a la i
  // y el gie estan activos
  P1IFG &= ~BIT1;
  // el ordenador entra en modo sleep hasta que encuentre una i
  __enable_interrupt();
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void) {
  if (P1IFG & BIT1) { // si hay aviso de que ha habido un cambio
    P1OUT ^= BIT0;    // Toggle P1 .0
    P1IFG &= ~BIT1;   // P1 .1 clear pending interrupts
  }
}
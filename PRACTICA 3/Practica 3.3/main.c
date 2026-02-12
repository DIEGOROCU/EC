#include <msp430.h>
/**
 * main.c
 */
int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;     // habilito pines
  P1DIR |= BIT0;            // Activo led rojo como salida
  P1OUT |= BIT0;            // enciendo el led rojo
  // TIMER:
  TA0CTL = TASSEL_1 | TACLR | MC_1; // Primer timer = ACLK, Cl
  TA0CCR0 = 40000;                  // inicializo, cuanto mas grande el numero m
  // Hasta donde cuenta el timer
  TA0CCTL0 = CCIE; // Habilita interrupcion (bit CCTIMER0_A0I
  // cuando cuente hasta el numero hace la interrupcion
  __enable_interrupt();
}
// Rutina de interrupcion de TIMER0_A0
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void) {
  P1OUT ^= BIT0; // conmuta LED en P1 .0
  TA0CCTL0 &= ~CCIFG; //Quitar la flag de interrupciones
}
#include <msp430.h>
#include <stdio.h>
#include "intrinsics.h"

/**
 * PROGRAMA: Parpadeo Síncrono de LED Rojo
 * OBJETIVO: Alternar el estado de P1.0.
 */

int main(void) {

    // Detener el Watchdog Timer
    // Imprescindible para evitar que el microcontrolador se reinicie solo.
    WDTCTL = WDTPW | WDTHOLD; 

    // SWITCH
    P1REN |=  BIT2;
    P1OUT |=  BIT2;

    // CONFIGURACIÓN DEL LED ROJO (P1.0)
    P1DIR |= BIT0;              // Establece P1.0 como salida (Escribir 1)
    P1OUT &= ~BIT0;             // Apaga el LED rojo inicialmente (Escribir 0)

    // CONFIGURACIÓN DEL LED VERDE (P9.7)
    P9DIR |= BIT7;              // Establece P9.7 como salida
    P9OUT &= ~BIT7;             // Apaga el LED verde inicialmente

    // DESBLOQUEO DE PERIFÉRICOS (Power Management)
    PM5CTL0 &= ~LOCKLPM5; 

    // 5. BUCLE DE EJECUCIÓN INFINITO
    while(1) {
        // Operación XOR (^=): Invierte el valor actual del bit.
        // Si el bit es 0, pasa a 1. Si es 1, pasa a 0.
        P1OUT ^= BIT0;          // Conmuta LED Rojo

        if (!P1IN) {
            P9OUT |= BIT7;
        }
        else {
            P9OUT &= ~BIT7;
        }

        // Retardo basado en ciclos de reloj.
        __delay_cycles(10000); 
    }
}

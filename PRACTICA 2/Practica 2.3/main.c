#include <msp430.h>
#include <stdio.h>
#include "intrinsics.h"
#include "msp430fr6989.h"

int main(void) {

    WDTCTL = WDTPW | WDTHOLD;   // Detener Watchdog

    // CONFIGURACIÓN DEL LED VERDE (P9.7)
    // El bit 7 corresponde al valor hexadecimal 0x80 (1000 0000 en binario)
    // Podemos poner 0x80 o su nombre directamente (BIT7)
    P9DIR |= BIT7;              // P9.7 como salida
    P9OUT &= ~BIT7;             // Empezar con el LED apagado

    PM5CTL0 &= ~LOCKLPM5;       // Desbloquear GPIO

    while(1) {
        P9OUT ^= BIT7;          // Alternar (Toggle) el bit 7 del Puerto 9
        __delay_cycles(500000); // Retardo de 0.5 segundos (a 1MHz)
    }

}


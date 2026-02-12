#include <msp430.h>
#include <stdio.h>      // Requerido para printf y fflush

int main(void) {
    // Detener el perro guardián
    WDTCTL = WDTPW | WDTHOLD;

    // Configurar el sistema (desbloquear GPIO aunque no usemos LEDs)
    PM5CTL0 &= ~LOCKLPM5;

    // --- HOLA MUNDO ---
    
    // Opción A: Usando salto de línea para vaciar el búfer automáticamente
    printf("Hola Mundo desde MSP430FR6989!\n");

    // Opción B: Forzando el vaciado del búfer manualmente
    printf("Comprobando entorno...");
    fflush(stdout); 

    while(1) {
        // Bucle infinito para evitar que el programa termine
    }
}
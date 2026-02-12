#include "intrinsics.h" // Librería para funciones especiales del compilador
#include <msp430.h>    // Diccionario de hardware: mapea nombres como P1DIR a direcciones de memoria

int main(void) {
    // Detener el Watchdog Timer (Requisito estándar en MSP430)
    // Se usa la "contraseña" WDTPW para poder modificar el registro WDTCTL
    WDTCTL = WDTPW | WDTHOLD;

    // Configurar el pin del LED
    // En la placa FR6989, el LED rojo (LED1) está en el Puerto 1, Pin 0 (P1.0)
    P1DIR |= 0x01;    // Configura P1.0 como salida (Pone un 1 usando una máscara OR)
    P1OUT &= ~0x01;   // Asegura que el LED empiece apagado (Pone un 0 usando AND NOT)

    // Desbloquear los pines GPIO 
    // Por defecto, los pines están bloqueados para ahorrar energía al arrancar
    PM5CTL0 &= ~LOCKLPM5;

    // El bucle infinito (Main Loop)
    while(1) {
        // Alterna el estado del pin P1.0 (Operación XOR)
        // Si es 0 se convierte en 1, si es 1 se convierte en 0
        P1OUT ^= 0x01;  

        // Retardo, lo podemos hacer con un bucle o con __delay_cycles()
        // volatile unsigned int i;
        // for(i = 30000; i > 0; i--);
        __delay_cycles(30000);
    }

    return 0;
}

/* ¿Qué es 'intrinsic'?
   Una función "intrinsic" (intrínseca) no es código C normal escrito en una librería, 
   sino una instrucción que el compilador entiende directamente. Actúa como un "atajo" 
   para insertar comandos de lenguaje ensamblador que el procesador MSP430 conoce, 
   permitiendo hacer cosas que el lenguaje C estándar no puede (como contar ciclos 
   exactos de reloj o manipular registros internos del sistema).
*/
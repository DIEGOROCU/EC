#include <msp430.h> // Incluye la definición de registros específicos para la familia MSP430

// VARIABLES GLOBALES
volatile int tx_ready = 1; // Bandera para saber si la UART está libre (1=si, 0=ocupada). 'volatile' evita optimizaciones del compilador.
char current_letter = 'A'; // Carácter que vamos a enviar (empezamos por la A)

// FUNCIÓN: Configuración del Sistema de Reloj (Clock System)
void Init_Clock(void) {
    CSCTL0_H = CSKEY >> 8;                    // Desbloquea los registros de reloj usando la contraseña CSKEY
    CSCTL1 = DCOFSEL_3 | DCORSEL;             // Configura el DCO (oscilador interno) a 8 MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK; // Asigna fuentes: ACLK=VLO, SMCLK=DCO, MCLK=DCO
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Establece todos los divisores de frecuencia en 1 (sin división)
    CSCTL0_H = 0;                             // Bloquea de nuevo los registros CS para proteger la configuración
}

// FUNCIÓN: Configuración del periférico UART (A1)
void Init_UART(void) {
    // Selección de función de los pines: Configura P3.4 (TX) y P3.5 (RX) para modo UART
    P3SEL0 |= BIT4 | BIT5;                    // Pone a 1 los bits 4 y 5 en P3SEL0
    P3SEL1 &= ~(BIT4 | BIT5);                 // Pone a 0 los bits 4 y 5 en P3SEL1 (Función primaria: UART)

    UCA1CTLW0 = UCSWRST;                      // Pone el módulo eUSCI en estado de reset para poder configurarlo
    UCA1CTLW0 |= UCSSEL__SMCLK;               // Selecciona SMCLK (8MHz) como fuente de reloj para la UART
    
    // Cálculo de Baud Rate para 9600 baudios (usando fórmulas del manual técnico)
    UCA1BR0 = 52;                             // Valor de división N=8000000/(16*9600) = 52.083
    UCA1BR1 = 0x00;                           // Parte alta del divisor (0 en este caso)
    UCA1MCTLW |= UCOS16 | UCBRF_1 | 0x4900;   // Activa sobremuestreo (UCOS16), configura filtro y ajuste fraccional
    
    UCA1CTLW0 &= ~UCSWRST;                    // Finaliza la configuración liberando el reset (inicia el módulo)
}

// FUNCIÓN PRINCIPAL
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Detiene el Watchdog Timer (evita que el micro se reinicie solo)
    PM5CTL0 &= ~LOCKLPM5;       // Desbloquea los pines de E/S tras salir del modo de bajo consumo inicial

    Init_Clock();               // Configura el reloj a 8MHz
    Init_UART();                // Configura la comunicación serie a 9600 baudios

    // CONFIGURACIÓN DE INTERRUPCIONES
    UCA1IE |= UCTXIE;           // Habilita la interrupción local: se dispara cuando el buffer de envío está vacío

    // CONFIGURACIÓN DEL TIMER A0 (Para controlar el ritmo de envío)
    TA0CCTL0 = CCIE;                          // Habilita la interrupción del comparador del Timer (CCR0)
    TA0CCR0 = 50000;                          // Establece el valor de comparación (define el tiempo de espera)
    TA0CTL = TASSEL__SMCLK | MC__UP | ID__8;  // Fuente=SMCLK, Modo=UP (cuenta hasta CCR0), Divisor=8 (frecuencia más lenta)

    __bis_SR_register(GIE);     // Habilita las interrupciones globales (activa el bit GIE en el registro de estado)

    while(1) {
        // El micro se queda aquí sin hacer nada; todo el trabajo se hace en las RTI (Rutinas de Interrupción)
    }
}

// RUTINA DE INTERRUPCIÓN (RTI) DEL TIMER A0
#pragma vector = TIMER0_A0_VECTOR             // Indica al compilador que esta función es para el vector del Timer A0
__interrupt void Timer_A (void) {             // Se ejecuta automáticamente cada vez que el Timer llega a 50000 (TA0CCR0)
    if (tx_ready == 1) {                      // Si la UART no está enviando nada actualmente...
        UCA1TXBUF = current_letter;           // Escribe la letra en el buffer de transmisión (esto inicia el envío físico)
        tx_ready = 0;                         // Marcamos como ocupado; no enviaremos otra hasta que la UART termine
        
        current_letter++;                     // Pasamos a la siguiente letra (A -> B -> C...)
        if (current_letter > 'Z') {           // Si llegamos después de la Z...
            current_letter = 'A';             // Reiniciamos el alfabeto
        }
    }
}

// RUTINA DE INTERRUPCIÓN (RTI) DE LA UART (USCI_A1)
#pragma vector = USCI_A1_VECTOR               // Indica que esta función gestiona eventos de la UART A1
__interrupt void USCI_A1_ISR (void) {
    // Leemos el registro de vector de interrupción para saber qué evento ocurrió
    switch(__even_in_range(UCA1IV, USCI_UART_UCTXCPTIFG)) {
        case USCI_NONE: break;                // No hay interrupción pendiente
        case USCI_UART_UCRXIFG: break;        // Se ha recibido un dato (no lo usamos en este ejercicio)
        case USCI_UART_UCTXIFG:               // El buffer de transmisión se ha vaciado (se terminó de enviar el bit de stop)
            tx_ready = 1;                     // Ponemos la bandera en 1 para que el Timer sepa que puede mandar otra letra
            break;
    }
}
#include <msp430.h> // Biblioteca estándar de registros para MSP430

// --- Diccionario para transformar letras ASCII a segmentos físicos del LCD ---
// Cada letra se define por dos bytes que activan los segmentos correspondientes (a, b, c, etc.)
const char alphabetBig [26][2] = {
    {0xEF, 0x00}, /* A */ {0xF1, 0x50}, /* B */ {0x9C, 0x00}, /* C */ {0xF0, 0x50}, /* D */
    {0x9F, 0x00}, /* E */ {0x8F, 0x00}, /* F */ {0xBD, 0x00}, /* G */ {0x6F, 0x00}, /* H */
    {0x90, 0x50}, /* I */ {0x78, 0x00}, /* J */ {0x0E, 0x22}, /* K */ {0x1C, 0x00}, /* L */
    {0x6C, 0xA0}, /* M */ {0x6C, 0x82}, /* N */ {0xFC, 0x00}, /* O */ {0xCF, 0x00}, /* P */
    {0xFC, 0x02}, /* Q */ {0xCF, 0x02}, /* R */ {0xB7, 0x00}, /* S */ {0x80, 0x50}, /* T */
    {0x7C, 0x00}, /* U */ {0x0C, 0x28}, /* V */ {0x6C, 0x0A}, /* W */ {0x00, 0xAA}, /* X */
    {0x00, 0xB0}, /* Y */ {0x90, 0x28}  /* Z */
};

// Almacena las 6 letras que se muestran. Se inicializa con 'A' para verificar el LCD al encender.
int buffer[6] = {'A', 'A', 'A', 'A', 'A', 'A'}; 

// VARIABLE DE CONTROL: Lleva la cuenta de cuántas letras hemos escrito (0 a 6)
int indice_lcd = 0; 

// FUNCIÓN: Mapea el buffer a los registros de memoria del LCD (LCDMEM)
void ShowBuffer (int buffer[]) {
    // Hemos invertido el orden aquí para que buffer[0] sea físicamente la izquierda del LCD
    LCDMEM[9]  = alphabetBig[(buffer[0])-65][0]; LCDMEM[10] = alphabetBig[(buffer[0])-65][1]; // Dígito 1 (Izq)
    LCDMEM[5]  = alphabetBig[(buffer[1])-65][0]; LCDMEM[6]  = alphabetBig[(buffer[1])-65][1]; // Dígito 2
    LCDMEM[3]  = alphabetBig[(buffer[2])-65][0]; LCDMEM[4]  = alphabetBig[(buffer[2])-65][1]; // Dígito 3
    LCDMEM[18] = alphabetBig[(buffer[3])-65][0]; LCDMEM[19] = alphabetBig[(buffer[3])-65][1]; // Dígito 4
    LCDMEM[14] = alphabetBig[(buffer[4])-65][0]; LCDMEM[15] = alphabetBig[(buffer[4])-65][1]; // Dígito 5
    LCDMEM[7]  = alphabetBig[(buffer[5])-65][0]; LCDMEM[8]  = alphabetBig[(buffer[5])-65][1]; // Dígito 6 (Der)
}

// --- Funciones de Inicialización ---

void Initialize_LCD() {
    PJSEL0 = BIT4 | BIT5;       // Configura los pines para el cristal de cuarzo LFXT (reloj del LCD)
    LCDCPCTL0 = 0xFFFF;         // Habilita los pines de segmentos 0-21
    LCDCPCTL1 = 0xFC3F;         // Habilita los pines de segmentos 26-43
    LCDCPCTL2 = 0x0FFF;
    CSCTL0_H = CSKEY >> 8;      // Desbloquea registros de reloj
    CSCTL4 &= ~LFXTOFF;         // Enciende el oscilador de cristal de baja frecuencia
    do {
        CSCTL5 &= ~LFXTOFFG;    // Limpia bandera de fallo del cristal
        SFRIFG1 &= ~OFIFG;
    } while (SFRIFG1 & OFIFG);  // Espera a que el cristal sea estable
    CSCTL0_H = 0;               // Bloquea registros de reloj
    
    // Configura el LCD: fuente ACLK, divisor 16, modo 4-mux (4 líneas comunes)
    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;
    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN; // Contraste interno y bomba de carga
    LCDCCPCTL = LCDCPCLKSYNC;   // Sincronización de reloj
    LCDCMEMCTL = LCDCLRM;       // Borra toda la memoria del LCD (pantalla limpia)
    LCDCCTL0 |= LCDON;          // Activa el controlador del LCD
}

void Init_Clock(void) {
    CSCTL0_H = CSKEY >> 8;      // Desbloquea registros de reloj
    CSCTL1 = DCOFSEL_3 | DCORSEL; // Configura el oscilador interno (DCO) a 8 MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK; // Fuentes de reloj para periféricos
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1; // Divisores a 1 para mantener los 8 MHz
    CSCTL0_H = 0;               // Bloquea registros de reloj
}

void Init_UART(void) {
    P3SEL0 |= BIT4 | BIT5;      // Configura pines P3.4 (TX) y P3.5 (RX) para función UART
    P3SEL1 &= ~(BIT4 | BIT5);

    UCA1CTLW0 = UCSWRST;        // Pone la UART en estado de reset para configurar parámetros
    UCA1CTLW0 |= UCSSEL__SMCLK; // Usa SMCLK (8 MHz) como fuente de tiempo
    
    // Configuración para 9600 baudios con reloj de 8 MHz
    UCA1BR0 = 52;               
    UCA1BR1 = 0x00;
    UCA1MCTLW |= UCOS16 | UCBRF_1 | 0x4900; // Activa sobremuestreo y modulación
    
    UCA1CTLW0 &= ~UCSWRST;      // Libera el reset para activar la UART
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Detiene el perro guardián (Watchdog)
    PM5CTL0 &= ~LOCKLPM5;       // Desbloquea la configuración de pines E/S (GPIO)

    Init_Clock();               // Inicializa relojes
    Init_UART();                // Inicializa comunicación UART
    Initialize_LCD();           // Inicializa pantalla LCD

    ShowBuffer(buffer);         // Muestra el estado inicial ('AAAAAA')

    UCA1IE |= UCRXIE;           // Habilita la interrupción de recepción (avisar cuando llegue una tecla)

    __enable_interrupt();       // Activa las interrupciones globales (bit GIE)

    while(1);                   // Bucle infinito: el programa espera interrupciones
}

// --- RTI (Rutina de Interrupción) de la UART ---
#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR (void) {
    // El registro UCA1IV indica qué evento causó la interrupción
    switch(__even_in_range(UCA1IV, USCI_UART_UCTXCPTIFG)) {
        case USCI_NONE: break;  // No hay interrupción pendiente
        case USCI_UART_UCRXIFG: { // EVENTO: Se recibió un carácter desde el PC
            char received_char = UCA1RXBUF; // Lee el dato del buffer de entrada
            
            // FILTRO: Solo procesar letras mayúsculas de la A a la Z
            if (received_char >= 'A' && received_char <= 'Z') {
                
                // LÓGICA DE ESCRITURA DE IZQUIERDA A DERECHA
                if (indice_lcd < 6) {
                    // Si aún no hemos llenado los 6 huecos, escribimos en la siguiente posición libre
                    buffer[indice_lcd] = received_char;
                    indice_lcd++; // Avanzamos a la siguiente posición del LCD
                } else {
                    // Si la pantalla ya está llena (6 letras), hacemos scroll a la izquierda
                    int i;
                    for(i = 0; i < 5; i++) {
                        buffer[i] = buffer[i+1]; // Mueve el contenido de cada hueco al de su izquierda
                    }
                    // Colocamos la nueva letra recibida en el hueco que quedó libre a la derecha
                    buffer[5] = received_char;
                }
                
                ShowBuffer(buffer); // Actualiza la pantalla con el buffer modificado
            }
            break;
        }
        case USCI_UART_UCTXIFG: break; // Evento de transmisión (no se usa aquí)
    }
}
#include <msp430.h> // Incluye las definiciones de registros para el MSP430FR6989

// --- Diccionario para transformar letras ASCII a segmentos físicos del LCD ---
// Cada letra tiene 2 bytes que indican qué segmentos (a, b, c...) se deben encender.
const char alphabetBig [26][2] = {
    {0xEF, 0x00}, /* A */ {0xF1, 0x50}, /* B */ {0x9C, 0x00}, /* C */ {0xF0, 0x50}, /* D */
    {0x9F, 0x00}, /* E */ {0x8F, 0x00}, /* F */ {0xBD, 0x00}, /* G */ {0x6F, 0x00}, /* H */
    {0x90, 0x50}, /* I */ {0x78, 0x00}, /* J */ {0x0E, 0x22}, /* K */ {0x1C, 0x00}, /* L */
    {0x6C, 0xA0}, /* M */ {0x6C, 0x82}, /* N */ {0xFC, 0x00}, /* O */ {0xCF, 0x00}, /* P */
    {0xFC, 0x02}, /* Q */ {0xCF, 0x02}, /* R */ {0xB7, 0x00}, /* S */ {0x80, 0x50}, /* T */
    {0x7C, 0x00}, /* U */ {0x0C, 0x28}, /* V */ {0x6C, 0x0A}, /* W */ {0x00, 0xAA}, /* X */
    {0x00, 0xB0}, /* Y */ {0x90, 0x28}  /* Z */
};

// Buffer que guarda las 6 letras que se ven en pantalla (inicializado con 'A')
int buffer[6] = {'A', 'A', 'A', 'A', 'A', 'A'}; 

// FUNCIÓN: Escribe el contenido del buffer en la memoria del LCD
void ShowBuffer (int buffer[]) {
    // Se resta 65 al valor ASCII (donde 'A'=65) para obtener el índice 0-25 del diccionario
    LCDMEM[9]  = alphabetBig[(buffer[5])-65][0]; LCDMEM[10] = alphabetBig[(buffer[5])-65][1]; // Posición 6
    LCDMEM[5]  = alphabetBig[(buffer[4])-65][0]; LCDMEM[6]  = alphabetBig[(buffer[4])-65][1]; // Posición 5
    LCDMEM[3]  = alphabetBig[(buffer[3])-65][0]; LCDMEM[4]  = alphabetBig[(buffer[3])-65][1]; // Posición 4
    LCDMEM[18] = alphabetBig[(buffer[2])-65][0]; LCDMEM[19] = alphabetBig[(buffer[2])-65][1]; // Posición 3
    LCDMEM[14] = alphabetBig[(buffer[1])-65][0]; LCDMEM[15] = alphabetBig[(buffer[1])-65][1]; // Posición 2
    LCDMEM[7]  = alphabetBig[(buffer[0])-65][0]; LCDMEM[8]  = alphabetBig[(buffer[0])-65][1]; // Posición 1
}

// FUNCIÓN: Inicializa el hardware del LCD (obtenida de la práctica anterior)
void Initialize_LCD() {
    PJSEL0 = BIT4 | BIT5;       // Configura los pines para el cristal de cuarzo externo (LFXT)
    LCDCPCTL0 = 0xFFFF;         // Habilita los segmentos del LCD (0-21)
    LCDCPCTL1 = 0xFC3F;         // Habilita los segmentos del LCD (26-43)
    LCDCPCTL2 = 0x0FFF;
    CSCTL0_H = CSKEY >> 8;      // Desbloquea registros de reloj
    CSCTL4 &= ~LFXTOFF;         // Enciende el cristal de baja frecuencia
    do {
        CSCTL5 &= ~LFXTOFFG;    // Limpia bandera de fallo de cristal
        SFRIFG1 &= ~OFIFG;
    } while (SFRIFG1 & OFIFG);  // Espera a que el cristal sea estable
    CSCTL0_H = 0;               // Bloquea registros de reloj
    // Configura el modo de refresco, divisor y multiplexado (4-mux) del LCD
    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;
    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN; // Configura la bomba de carga interna para el contraste
    LCDCCPCTL = LCDCPCLKSYNC;   // Sincroniza el reloj del LCD
    LCDCMEMCTL = LCDCLRM;       // Borra la memoria del LCD (pantalla limpia)
    LCDCCTL0 |= LCDON;          // Enciende físicamente el LCD
}

// FUNCIÓN: Configura el reloj del sistema a 8 MHz
void Init_Clock(void) {
    CSCTL0_H = CSKEY >> 8;      // Desbloquea registros de control de reloj
    CSCTL1 = DCOFSEL_3 | DCORSEL; // Configura el DCO interno a 8 MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK; // Fuentes de reloj para periféricos
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1; // Divisores a 1 (frecuencia real 8MHz)
    CSCTL0_H = 0;               // Bloquea registros
}

// FUNCIÓN: Configura el módulo UART A1 a 9600 baudios
void Init_UART(void) {
    P3SEL0 |= BIT4 | BIT5;      // Selecciona función UART para pines P3.4 y P3.5
    P3SEL1 &= ~(BIT4 | BIT5);

    UCA1CTLW0 = UCSWRST;        // Detiene el módulo UART para configurarlo
    UCA1CTLW0 |= UCSSEL__SMCLK; // Usa SMCLK (8MHz) como base de tiempo
    
    // Configuración para 9600 baudios (según tabla 21-4 del manual)
    UCA1BR0 = 52;               
    UCA1BR1 = 0x00;
    UCA1MCTLW |= UCOS16 | UCBRF_1 | 0x4900; // Sobremuestreo y modulación
    
    UCA1CTLW0 &= ~UCSWRST;      // Reinicia el módulo UART (ya operativo)
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Detiene el temporizador de vigilancia (Watchdog)
    PM5CTL0 &= ~LOCKLPM5;       // Desactiva el modo de alta impedancia de los pines I/O

    Init_Clock();               // Inicializa relojes
    Init_UART();                // Inicializa comunicación serie
    Initialize_LCD();           // Inicializa pantalla

    ShowBuffer(buffer);         // Muestra las letras iniciales ('AAAAAA')

    UCA1IE |= UCRXIE;           // Habilita la interrupción por recepción de dato (cuando llega algo del PC)

    __enable_interrupt();       // Activa las interrupciones globales (GIE)

    while(1);                   // Bucle infinito: el micro espera "durmiendo" a la UART
}

// RTI: Se ejecuta cuando llega un carácter por la UART
#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR (void) {
    // Identifica la causa de la interrupción (Lectura del registro UCA1IV)
    switch(__even_in_range(UCA1IV, USCI_UART_UCTXCPTIFG)) {
        case USCI_NONE: break;  // No hay interrupción
        case USCI_UART_UCRXIFG: { // Caso: Se ha recibido un carácter
            char received_char = UCA1RXBUF; // Lee el carácter del buffer de entrada
            
            // Filtro: Solo procesamos letras mayúsculas (A-Z)
            if (received_char >= 'A' && received_char <= 'Z') {
                int i;
                // Lógica de desplazamiento (Shift): Mueve las letras a la izquierda
                for(i = 0; i < 5; i++) {
                    buffer[i] = buffer[i+1];
                }
                buffer[5] = received_char; // Coloca la nueva letra en la última posición
                ShowBuffer(buffer);        // Actualiza el LCD con el nuevo buffer
            }
            break;
        }
        case USCI_UART_UCTXIFG: break; // Caso: Transmisión (no se usa aquí)
    }
}
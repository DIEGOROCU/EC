#include <msp430.h> // Librería para el acceso a los registros del MSP430FR6989

// --- VARIABLES GLOBALES ---
volatile int tx_ready = 1;      // Flag que indica si la UART está libre para enviar (1) u ocupada (0)
char current_letter = 'A';      // Letra actual que el Timer enviará automáticamente al PC
int buffer[2] = {'A', 'A'}; // Almacena las 6 letras que se muestran en el LCD
int cantidadLetras = 0;
int numerosRecividos = 0;
int letrasMostradas = 0;

// --- DICCIONARIO DE SEGMENTOS LCD ---
// Mapa de bits para encender los segmentos correctos de cada letra (A-Z)
const char alphabetBig [26][2] = {
    {0xEF, 0x00}, {0xF1, 0x50}, {0x9C, 0x00}, {0xF0, 0x50}, {0x9F, 0x00}, {0x8F, 0x00}, 
    {0xBD, 0x00}, {0x6F, 0x00}, {0x90, 0x50}, {0x78, 0x00}, {0x0E, 0x22}, {0x1C, 0x00}, 
    {0x6C, 0xA0}, {0x6C, 0x82}, {0xFC, 0x00}, {0xCF, 0x00}, {0xFC, 0x02}, {0xCF, 0x02}, 
    {0xB7, 0x00}, {0x80, 0x50}, {0x7C, 0x00}, {0x0C, 0x28}, {0x6C, 0x0A}, {0x00, 0xAA}, 
    {0x00, 0xB0}, {0x90, 0x28}
};

const unsigned char LCD_Num[10] = {0xFC, 0x60, 0xDB, 0xF3, 0x67, 0xB7, 0xBF, 0xE0, 0xFF, 0xE7};

// FUNCIÓN: Actualiza físicamente los 6 dígitos del LCD con el contenido del buffer
void ShowBuffer (int buffer[]) {
    // CAMBIO APLICADO: Ahora buffer[5] (la letra más nueva) se dibuja en la DERECHA del LCD
    // y buffer[0] (la letra más antigua) se dibuja en la IZQUIERDA del LCD.
    LCDM8  = LCD_Num[buffer[0] - 48];// = alphabetBig[(buffer[0])-65][1]; // Posición 1 (Izquierda)
    LCDM15  = LCD_Num[buffer[1] - 48]; //LCDMEM[6]  = alphabetBig[(buffer[1])-65][1]; // Posición 2
    //LCDMEM[3]  = alphabetBig[(buffer[2])-65][0]; LCDMEM[4]  = alphabetBig[(buffer[2])-65][1]; // Posición 3
    //LCDMEM[18] = alphabetBig[(buffer[3])-65][0]; LCDMEM[19] = alphabetBig[(buffer[3])-65][1]; // Posición 4
    //LCDMEM[14] = alphabetBig[(buffer[4])-65][0]; LCDMEM[15] = alphabetBig[(buffer[4])-65][1]; // Posición 5
    //LCDMEM[7]  = alphabetBig[(buffer[5])-65][0]; LCDMEM[8]  = alphabetBig[(buffer[5])-65][1]; // Posición 6 (Derecha)
}

// FUNCIÓN: Configuración inicial del hardware del controlador LCD
void Initialize_LCD() {
    PJSEL0 = BIT4 | BIT5;       // Configura pines para el cristal de cuarzo de 32kHz
    LCDCPCTL0 = 0xFFFF;         // Activa los pines de los segmentos
    LCDCPCTL1 = 0xFC3F;
    LCDCPCTL2 = 0x0FFF;
    CSCTL0_H = CSKEY >> 8;      // Desbloquea registros de reloj
    CSCTL4 &= ~LFXTOFF;         // Activa el oscilador de baja frecuencia (LFXT)
    do {
        CSCTL5 &= ~LFXTOFFG;    // Limpia banderas de error del cristal
        SFRIFG1 &= ~OFIFG;
    } while (SFRIFG1 & OFIFG);  // Bucle hasta que el oscilador sea estable
    CSCTL0_H = 0;               // Bloquea registros de reloj
    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP; // Configura reloj y multiplexado del LCD
    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;             // Configura contraste y bomba de carga
    LCDCCPCTL = LCDCPCLKSYNC;   // Sincronización de reloj
    LCDCMEMCTL = LCDCLRM;       // Limpia la memoria del LCD
    LCDCCTL0 |= LCDON;          // Enciende el panel LCD
}

// FUNCIÓN: Configura el reloj principal (DCO) a 8 MHz
void Init_Clock(void) {
    CSCTL0_H = CSKEY >> 8;      // Desbloqueo de registros
    CSCTL1 = DCOFSEL_3 | DCORSEL; // DCO a 8 MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK; // Configura fuentes de reloj periféricas
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1; // Divisores a 1
    CSCTL0_H = 0;               // Bloqueo de registros
}

// FUNCIÓN: Configura la UART A1 para comunicación serie a 9600 baudios
void Init_UART(void) {
    P3SEL0 |= BIT4 | BIT5;      // Configura pines P3.4 y P3.5 para función UART
    P3SEL1 &= ~(BIT4 | BIT5);

    UCA1CTLW0 = UCSWRST;        // Módulo en pausa para configuración
    UCA1CTLW0 |= UCSSEL__SMCLK; // Usa el reloj SMCLK (8MHz)
    
    // Configuración de baudios (8MHz / 9600 baud)
    UCA1BR0 = 52;               
    UCA1BR1 = 0x00;
    UCA1MCTLW |= UCOS16 | UCBRF_1 | 0x4900; // Modulación y sobremuestreo
    
    UCA1CTLW0 &= ~UCSWRST;      // Módulo operativo
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Detiene el temporizador Watchdog
    PM5CTL0 &= ~LOCKLPM5;       // Habilita los pines de entrada/salida

    Init_Clock();               // Inicializa reloj de 8MHz
    Init_UART();                // Inicializa la UART
    Initialize_LCD();           // Inicializa el LCD

    ShowBuffer(buffer);         // Muestra el estado inicial del buffer en el LCD

    // Habilitar interrupciones de Transmisión (TX) y Recepción (RX) de la UART
    //UCA1IE |= (UCRXIE | UCTXIE);
    UCA1IE |= UCRXIE;
    UCA1IE &= ~UCTXIE;
    // Configuración del Temporizador TA0 para generar envíos cada cierto tiempo
    TA0CCTL0 = CCIE;                          // Habilita interrupción del Timer
    TA0CCR0 = 50000;                          // Límite de cuenta (define la velocidad del abecedario)
    TA0CTL = TASSEL__SMCLK | MC__UP | ID__8;  // SMCLK, modo ascendente, divisor por 8

    __enable_interrupt();       // Activa las interrupciones globales

    while(1);                   // El programa principal no hace nada, todo ocurre en las RTI
}

// --- RTI DEL TIMER: Envía automáticamente el abecedario al PC ---
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void) {
    if (tx_ready == 1) {              // Si la UART terminó el envío anterior...
        if (letrasMostradas < cantidadLetras) {
            UCA1TXBUF = current_letter;   // Carga la nueva letra en el buffer de salida (inicia transmisión)
            tx_ready = 0;                 // Marca la UART como ocupada
            
            current_letter++;             // Prepara la siguiente letra
            if (current_letter > 'Z') {
                current_letter = 'A';     // Vuelve a la A si llegamos al final
            }
            letrasMostradas++;
        }
        else {
            tx_ready = 0;                 // Marca la UART como ocupada
            letrasMostradas = 0;
            cantidadLetras = 0;
            current_letter = 'A';
            UCA1IE |= UCRXIE;
            UCA1IE &= ~UCTXIE;
        }  
    }
    TA0CCTL0 &= ~CCIFG;               // Limpia la bandera de interrupción del temporizador
}

// --- RTI DE LA UART: Gestiona la recepción de teclas y la disponibilidad de envío ---
#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR (void) {
    // El registro UCA1IV nos dice qué evento de la UART disparó la interrupción
    switch(__even_in_range(UCA1IV, USCI_UART_UCTXCPTIFG)) {
        case USCI_NONE: break;
        
        case USCI_UART_UCRXIFG: {     // EVENTO: Ha llegado un carácter desde el PC
            char received_num = UCA1RXBUF; // Recupera el carácter recibido

            // Si el carácter es una letra mayúscula (A-Z)
            if (received_num >= '0' && received_num <= '9') {
                if (numerosRecividos == 0) {
                    cantidadLetras = 10*(received_num - 48);
                    buffer[1] = received_num;
                    numerosRecividos++;
                }
                else if (numerosRecividos == 1) {
                    cantidadLetras = cantidadLetras + (received_num - 48);
                    buffer[0] = received_num;
                    tx_ready = 1;
                    numerosRecividos = 0;
                    UCA1IE &= ~UCRXIE;
                    UCA1IE |= UCTXIE;
                }
                ShowBuffer(buffer);
            }
            break;
        }
        
        case USCI_UART_UCTXIFG:       // EVENTO: La UART ha terminado de enviar el carácter anterior
            tx_ready = 1;             // Indica al Timer que puede enviar la siguiente letra del abecedario
            break;
    }
}
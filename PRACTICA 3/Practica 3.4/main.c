#include <msp430.h>

unsigned int n = 0;
unsigned int contar = 1;

//**********************************
// Configures ACLK to 32 KHz crystal
void config_ACLK_to_32KHz_crystal() {
  // By default, ACLK runs on LFMODCLK at 5MHz/128 = 39 KHz
  // Reroute pins to LFXIN/LFXOUT functionality
  PJSEL1 &= ~BIT4;
  PJSEL0 |= BIT4;
  // Wait until the oscillator fault flags remain cleared
  CSCTL0 = CSKEY; // Unlock CS registers
  do {
    CSCTL5 &= ~LFXTOFFG; // Local fault flag
    SFRIFG1 &= ~OFIFG;   // Global fault flag
  } while ((CSCTL5 & LFXTOFFG) != 0);
  CSCTL0_H = 0; // Lock CS registers
  return;
}
const unsigned char LCD_Num[10] = {0xFC, 0x60, 0xDB, 0xF3, 0x67,
                                   0xB7, 0xBF, 0xE0, 0xFF, 0xE7};
//***************function that displays any 16-bit unsigned integer************
inline void display_num_lcd(unsigned int n) {
  int i = 0;
  do {
    unsigned int digit = n % 10;
    switch (i) {
    case 0:
      LCDM8 = LCD_Num[digit];
      break; // first digit
    case 1:
      LCDM15 = LCD_Num[digit];
      break; // second digit
    case 2:
      LCDM19 = LCD_Num[digit];
      break; // third digit
    case 3:
      LCDM4 = LCD_Num[digit];
      break; // fourth digit
    case 4:
      LCDM6 = LCD_Num[digit];
      break; // fifth digit
    }
    n /= 10;
    i++;
  } while (i < 5);
}
//**********************************************************
// Initializes the LCD_C module
// *** Source: Function obtained from MSP430FR6989 Sample Code ***
void Initialize_LCD() {
  PJSEL0 = BIT4 | BIT5; // For LFXT
  // Initialize LCD segments 0 - 21; 26 - 43
  LCDCPCTL0 = 0xFFFF;
  LCDCPCTL1 = 0xFC3F;
  LCDCPCTL2 = 0x0FFF;
  // Configure LFXT 32kHz crystal
  CSCTL0_H = CSKEY >> 8; // Unlock CS registers
  CSCTL4 &= ~LFXTOFF;    // Enable LFXT
  do {
    CSCTL5 &= ~LFXTOFFG; // Clear LFXT fault flag
    SFRIFG1 &= ~OFIFG;
  } while (SFRIFG1 & OFIFG); // Test oscillator fault flag
  CSCTL0_H = 0;              // Lock CS registers
  // Initialize LCD_C
  // ACLK, Divider = 1, Pre-divider = 16; 4-pin MUX
  LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;
  // VLCD generated internally,
  // V2-V4 generated internally, v5 to ground
  // Set VLCD voltage to 2.60v
  // Enable charge pump and select internal reference for it
  LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;
  LCDCCPCTL = LCDCPCLKSYNC; // Clock synchronization enabled
  LCDCMEMCTL = LCDCLRM;     // Clear LCD memory
  // Turn LCD on
  LCDCCTL0 |= LCDON;
  return;
}

int main(void) {

  // ============ CONFIGURACIÓN INICIAL DEL MICROCONTROLADOR ============
  // disable watchdog (desactiva el temporizador watchdog para evitar reinicios)
  WDTCTL = WDTPW | WDTHOLD;
  // disable high impeadance on I/O (habilita los pines de entrada/salida)
  PM5CTL0 &= ~LOCKLPM5;

  // ============ CONFIGURACIÓN DEL BOTÓN 1 (P1.1) - PAUSAR/REANUDAR
  // ============
  // Configuramos como entrada pull-up P1.1
  P1SEL0 &= ~BIT1; // Configura P1.1 como función de I/O general (no función alternativa)
  P1SEL1 &= ~BIT1;
  P1DIR &= ~BIT1; // Configura P1.1 como entrada
  P1REN |= BIT1;  // Habilita resistencia pull-up/pull-down en P1.1
  P1OUT |= BIT1; // Configura la resistencia como pull-up (botón conectado a GND)

  // Hacemos que P1.1 pueda interrumpir (cuando se presiona el botón se
  // pausa/reanuda)
  P1IE |= BIT1; // Habilita la interrupción en P1.1
  P1IES |= BIT1; // Interrupción en flanco de bajada (cuando se presiona el botón)
  P1IFG &= ~BIT1; // Limpia cualquier interrupción pendiente en P1.1

  // ============ CONFIGURACIÓN DEL BOTÓN 2 (P1.2) - REINICIAR CONTADOR
  // ============
  // Configuramos como entrada pull-up P1.2
  P1SEL0 &= ~BIT2; // Configura P1.2 como función de I/O general (no función alternativa)
  P1SEL1 &= ~BIT2;
  P1DIR &= ~BIT2; // Configura P1.2 como entrada
  P1REN |= BIT2;  // Habilita resistencia pull-up/pull-down en P1.2
  P1OUT |= BIT2; // Configura la resistencia como pull-up (botón conectado a GND)

  // Hacemos que P1.2 pueda interrumpir (cuando se presiona el botón se reinicia
  // el contador)
  P1IE |= BIT2; // Habilita la interrupción en P1.2
  P1IES |= BIT2; // Interrupción en flanco de bajada (cuando se presiona el botón)
  P1IFG &= ~BIT2; // Limpia cualquier interrupción pendiente en P1.2

  // ============ CONFIGURACIÓN DEL TIMER A0 ============
  // Configuración TIMER_A:
  // TimerA0, ACLK/1, modo up (cuenta ascendente), reinicia el contador
  TA0CTL = TASSEL__ACLK | ID__1 | MC__UP | TACLR;
  // ACLK tiene una frecuencia de 32768 Hz
  // Configuramos para que interrumpa aproximadamente cada 0.1 segundos
  // Sin embargo, TA0CCR0 = 40000 da aprox. 1.22 segundos (40000/32768)
  // Para 0.1seg debería ser: (0.1*32768)-1 = 3276
  TA0CCR0 = 40000;
  TA0CCTL0 = CCIE; // Habilita la interrupción del Timer A0 (CCR0)

  // ============ INICIALIZACIÓN FINAL ============
  __enable_interrupt(); // Habilita las interrupciones globalmente
  Initialize_LCD();     // Inicializa la pantalla LCD para mostrar el contador
}

// Rutina de interrupcion de TIMER0_A0
// DEL TIMER: Se ejecuta cada vez que el contador llega a TA0CCR0
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void) {
  display_num_lcd(n);
  if (contar) {
    n++;
  }
  TA0CCTL0 &= ~CCIFG; // Quitar la flag de interrupciones
}

// INTERRUPCIONES DEL VECTOR DE PUERTO 1
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void) {
  if (P1IFG & BIT1) {
    // paro contador: alterno el int contar
    contar = 1 - contar;
    P1IFG &= ~BIT1; // Limpia el flag de interrupción
  } else if (P1IFG & BIT2) {
    n = 0;          // Reset del tiempo
    P1IFG &= ~BIT2; // Limpia el flag de interrupción
  }
}
# Estructuras de Computadores

[![MSP430](https://img.shields.io/badge/MSP430-FR6989-red.svg)](https://www.ti.com/product/MSP430FR6989)
[![Code Composer Studio](https://img.shields.io/badge/IDE-Code%20Composer%20Studio-blue.svg)](https://www.ti.com/tool/CCSTUDIO)

Repositorio de prácticas de la asignatura **Estructuras de Computadores** del 2º cuatrimestre de 3º curso del Doble Grado en Ingeniería Informática y Matemáticas UCM.

## 📑 Tabla de Contenidos

- [📋 Descripción](#-descripción)
- [🛠️ Tecnologías Utilizadas](#️-tecnologías-utilizadas)
- [🔌 Hardware - MSP430FR6989 LaunchPad](#-hardware---msp430fr6989-launchpad)
- [📂 Estructura del Repositorio](#-estructura-del-repositorio)
- [🚀 Contenido de las Prácticas](#-contenido-de-las-prácticas)
  - [Práctica 2: Introducción a MSP430 y GPIO](#práctica-2-introducción-a-msp430-y-gpio)
  - [Práctica 3: Interrupciones y Temporizadores](#práctica-3-interrupciones-y-temporizadores)
  - [Práctica 4: Comunicación UART y Periféricos Avanzados](#práctica-4-comunicación-uart-y-periféricos-avanzados)
- [🔧 Conceptos Clave Trabajados](#-conceptos-clave-trabajados)
- [💻 Requisitos Previos](#-requisitos-previos)
- [📥 Instalación y Configuración](#-instalación-y-configuración)
- [🔧 Compilación y Estructura de Proyectos](#-compilación-y-estructura-de-proyectos)
- [📖 Guía Rápida de Registros](#-guía-rápida-de-registros-msp430fr6989)
- [📝 Notas Importantes](#-notas-importantes)
- [⚠️ Troubleshooting](#️-troubleshooting-solución-de-problemas)
- [💡 Ejemplos de Código Útiles](#-ejemplos-de-código-útiles)
- [🎯 Objetivos de Aprendizaje](#-objetivos-de-aprendizaje)
- [📚 Recursos Adicionales](#-recursos-adicionales)
- [🏫 Contexto Académico](#-contexto-académico)
- [👨‍💻 Autor](#-autor)
- [📄 Licencia](#-licencia)

---

## 📋 Descripción

Este repositorio contiene las prácticas de laboratorio realizadas con el microcontrolador **MSP430FR6989** de Texas Instruments. Los ejercicios cubren conceptos fundamentales de arquitectura de computadores, programación embebida y control de periféricos.

## 🛠️ Tecnologías Utilizadas

- **Microcontrolador:** MSP430FR6989
- **IDE:** Code Composer Studio (CCS)
- **Lenguaje:** C
- **Toolchain:** MSP430 Compiler Tools

## 🔌 Hardware - MSP430FR6989 LaunchPad

### Especificaciones Técnicas
- **CPU:** 16-bit RISC MSP430 a 16 MHz
- **Memoria:** 128 KB FRAM, 2 KB SRAM
- **Voltaje:** 1.8V - 3.6V
- **Consumo ultra-bajo:** Varios modos de bajo consumo (LPM)
- **Periféricos:** Timer_A, eUSCI (UART, SPI, I²C), ADC, LCD Controller

### Pinout Importante
| Pin | Función | Descripción |
|-----|---------|-------------|
| P1.0 | LED Rojo | LED1 integrado en la placa |
| P9.7 | LED Verde | LED2 integrado en la placa |
| P1.1 | Botón S1 | Pulsador con pull-up interno |
| P1.2 | Botón S2 | Pulsador con pull-up interno |
| P3.4 | UCA1TXD | UART TX (Transmisión) |
| P3.5 | UCA1RXD | UART RX (Recepción) |
| PJ.4-5 | LFXIN/LFXOUT | Cristal de 32.768 kHz para LCD/RTC |

### Pantalla LCD Integrada
- **Tipo:** 6 dígitos alfanuméricos de 7 segmentos
- **Multiplexado:** 4-mux
- **Segmentos totales:** 192 (6 dígitos × 32 posiciones)
- **Controlador:** Integrado en el MSP430FR6989

## 📂 Estructura del Repositorio

```
├── PRACTICA 2/
│   ├── LABORATORIO/          # Ejercicios de laboratorio guiado
│   ├── Practica 2.1/         # Control básico de LED (Blink)
│   ├── Practica 2.2/         # Control con pulsadores
│   ├── Practica 2.3/         # Control de LED verde
│   ├── Practica 2.4/         # Parpadeo sícrono de LEDs rojo y verde
│   └── Practica 2.5/         # Parpadeo rápido de LED rojo
├── PRACTICA 3/
│   ├── Practica 3.1/         # Interrupciones con pulsadores
│   ├── Practica 3.2/         # Temporizadores y control de LEDs
│   ├── Practica 3.3/         # Interrupciones por flanco
│   ├── Practica 3.4/         # Pantalla LCD - Contador
│   └── Practica3_LAB/        # Ejercicios de laboratorio
├── PRACTICA 4/
│   ├── Practica 4.1/         # Comunicación UART básica
│   ├── Practica 4.2/         # UART con LCD - Recepción de letras
│   ├── Practica 4.2.1/       # Buffer circular en LCD
│   ├── Practica 4.3/         # Transmisión automática con Timer
│   ├── Practica 4.3.1/       # Transmisión automática mejorada
│   └── LaboratorioMain.c     # Ejercicio final de laboratorio
```

## 🚀 Contenido de las Prácticas

### Práctica 2: Introducción a MSP430 y GPIO

#### **Práctica 2.1 - "Hola Mundo" con LED**
Implementación del clásico programa de parpadeo de LED (Blink). Control básico del LED rojo (P1.0).

**Conceptos:**
- Configuración del Watchdog Timer (`WDTCTL`)
- Configuración de GPIO como salida (`P1DIR`)
- Control de estados de salida (`P1OUT`)
- Retardos con `__delay_cycles()`
- Desbloqueo de periféricos (`PM5CTL0 &= ~LOCKLPM5`)

#### **Práctica 2.2 - Lectura de Pulsadores**
Control de LED mediante pulsador. El LED rojo se enciende al pulsar el botón S1 (P1.1).

**Conceptos:**
- Configuración de GPIO como entrada (`P1DIR`)
- Resistencias pull-up (`P1REN`, `P1OUT`)
- Lectura del estado de pines (`P1IN`)
- Lógica de control basada en entradas

#### **Práctica 2.3 - Control del LED Verde**
Parpadeo del LED verde (P9.7) usando el Puerto 9.

**Conceptos:**
- Manejo de múltiples puertos GPIO (P9)
- Operación XOR para toggle de bits (`P9OUT ^= BIT7`)
- Direccionamiento de bits con máscaras

#### **Práctica 2.4 - Parpadeo Síncrono**
Parpadeo sincronizado de ambos LEDs (rojo P1.0 y verde P9.7) simultáneamente.

**Conceptos:**
- Control simultáneo de múltiples puertos
- Sincronización de salidas
- Documentación de código con comentarios detallados

#### **Práctica 2.5 - Parpadeo Rápido**
Parpadeo rápido del LED rojo con retardo reducido (`__delay_cycles(10000)`).

**Conceptos:**
- Ajuste de frecuencias de parpadeo
- Optimización de retardos

---

### Práctica 3: Interrupciones y Temporizadores

#### **Práctica 3.1 - Interrupciones por GPIO**
Control del LED mediante interrupciones. El LED cambia de estado al pulsar el botón usando IRQ (Interrupt Request).

**Conceptos:**
- Habilitación de interrupciones por puerto (`P1IE`)
- Selección de flanco (rising/falling edge) (`P1IES`)
- Limpieza de banderas de interrupción (`P1IFG`)
- Vectores de interrupción (`#pragma vector = PORT1_VECTOR`)
- Rutinas de servicio de interrupción (ISR) (`__interrupt`)
- Instrucción `__enable_interrupt()`

#### **Práctica 3.2 - Timer A0 Básico**
Uso del temporizador Timer_A0 para generar parpadeo periódico sin usar `__delay_cycles()`.

**Conceptos:**
- Configuración de Timer_A (`TA0CTL`)
- Selección de fuente de reloj (ACLK) (`TASSEL_1`)
- Modos de conteo (`MC_1` - Up mode)
- Registro de comparación (`TA0CCR0`)
- Interrupción por Timer (`TIMER0_A0_VECTOR`)
- Limpieza de bandera (`CCIFG`)

#### **Práctica 3.3 - Interrupciones Avanzadas**
Implementación de interrupciones por flanco de bajada para detección de pulsaciones.

**Conceptos:**
- Detección de eventos por flanco
- Configuración de modos pull-up/pull-down
- Gestión de rebotes (debouncing)

#### **Práctica 3.4 - Pantalla LCD**
Control de la pantalla LCD integrada del MSP430FR6989 para mostrar números.

**Conceptos:**
- Inicialización del controlador LCD (`LCDCCTL0`)
- Configuración del cristal LFXT de 32 kHz
- Registros de memoria LCD (`LCDMEM`, `LCDM`)
- Mapeo de segmentos LCD
- Display de números (0-9) con codificación de 7 segmentos
- Bomba de carga interna para contraste (`LCDCVCTL`)
- Configuración del multiplexado 4-mux

---

### Práctica 4: Comunicación UART y Periféricos Avanzados

#### **Práctica 4.1 - UART Básica (Transmisión)**
Transmisión de caracteres por puerto serie usando el módulo eUSCI_A1.

**Conceptos:**
- Configuración del sistema de reloj (DCO a 8 MHz)
- Inicialización del módulo UART (`UCA1CTLW0`)
- Configuración de pines para UART (`P3SEL0`, P3.4=TX, P3.5=RX)
- Cálculo de Baud Rate (9600 baudios)
- Registro de transmisión (`UCA1TXBUF`)
- Interrupciones de transmisión (`UCTXIE`)
- Timer_A0 para transmisión periódica
- Envío automático del alfabeto (A-Z)

#### **Práctica 4.2 - UART con LCD (Recepción)**
Recepción de caracteres por UART y visualización en la pantalla LCD.

**Conceptos:**
- Módulo UART en modo recepción (`UCRXIE`)
- Lectura del buffer de recepción (`UCA1RXBUF`)
- Diccionario de segmentos para letras (A-Z)
- Mapeo de caracteres ASCII a segmentos LCD
- Función `ShowBuffer()` para actualizar LCD
- Sincronización UART-LCD

#### **Práctica 4.3 - Transmisión Bidireccional**
Sistema completo de transmisión automática y recepción con visualización en LCD.

**Conceptos:**
- Comunicación full-duplex
- Variable `tx_ready` para control de flujo
- Interrupción dual (TX y RX)
- Gestión de buffer circular

#### **Práctica 4.2.1 / 4.3.1 - Buffer Circular en LCD**
Implementación de un buffer circular de 6 posiciones para mostrar las últimas letras recibidas.

**Conceptos:**
- Estructuras de datos tipo FIFO
- Gestión de índices circulares
- Desplazamiento de datos en el buffer
- Actualización dinámica del LCD
- Variables de control (`indice_lcd`)

#### **Laboratorio Final (LaboratorioMain.c)**
Ejercicio integrador que combina recepción UART, display LCD con números y procesamiento de datos.

**Conceptos:**
- Integración completa de periféricos
- Display de números en LCD
- Procesamiento de datos recibidos
- Variables de estado (`cantidadLetras`, `numerosRecividos`, `letrasMostradas`)

---

## 🔧 Conceptos Clave Trabajados

### Hardware
- **Watchdog Timer (WDT):** Sistema de seguridad que resetea el microcontrolador
- **GPIO (General Purpose I/O):** Control de pines digitales de entrada/salida
- **Timer_A:** Temporizador programable de 16 bits
- **eUSCI (Enhanced Universal Serial Communication Interface):** Módulo UART
- **LCD Controller:** Controlador de pantalla de cristal líquido integrado

### Software
- **Registros de configuración:** DIR, OUT, IN, REN, IES, IE, IFG
- **Operaciones de bits:** OR (`|`), AND (`&`), XOR (`^`), NOT (`~`)
- **Interrupciones:** ISR, vectores, banderas (flags)
- **Retardos:** `__delay_cycles()`, temporizadores hardware
- **Comunicación serie:** UART, Baud Rate, frames de datos

## 💻 Requisitos Previos

1. **Code Composer Studio** (versión 12 o superior)
   - Descargar desde: [ti.com/tool/CCSTUDIO](https://www.ti.com/tool/CCSTUDIO)

2. **MSP430FR6989 LaunchPad**
   - Hardware de desarrollo de Texas Instruments

3. **Drivers USB**
   - Instalados automáticamente con CCS

## 📥 Instalación y Configuración

1. **Clonar el repositorio:**
   ```bash
   git clone https://github.com/DIEGOROCU/EC.git
   cd EC
   ```

2. **Abrir Code Composer Studio**

3. **Importar un proyecto:**
   - File → Import → CCS Projects
   - Seleccionar la carpeta de la práctica deseada
   - Marcar "Copy projects into workspace" (opcional)

4. **Conectar la placa MSP430FR6989** vía USB

5. **Compilar y ejecutar:**
   - Click en el botón "Build" (🔨)
   - Click en "Debug" (🐛) o "Run" (▶️)

## 🔧 Compilación y Estructura de Proyectos

### Estructura de Carpetas
Cada carpeta de práctica contiene:
```
Practica X.X/
├── main.c                      # Código fuente principal
├── lnk_msp430fr6989.cmd        # Linker script (mapa de memoria)
├── Debug/                      # Archivos generados por compilación
│   ├── *.obj                   # Archivos objeto
│   ├── *.out                   # Ejecutable final
│   ├── *.map                   # Mapa de memoria
│   ├── makefile                # Makefile generado
│   └── *.d                     # Archivos de dependencias
├── driverlib/                  # Librerías del dispositivo (opcional)
│   └── MSP430FR5xx_6xx/        # Drivers específicos
└── targetConfigs/              # Configuración del target
    ├── MSP430FR6989.ccxml      # Configuración de depuración
    └── readme.txt
```

### Compilación desde CCS (GUI)
1. **Importar proyecto:**
   - `File` → `Import` → `CCS Projects`
   - Seleccionar carpeta de la práctica
   - (Opcional) Marcar "Copy projects into workspace"

2. **Compilar:**
   - Click derecho en el proyecto → `Build Project`
   - O usar el icono de martillo (🔨) en la barra de herramientas
   - Resultado: archivo `.out` en la carpeta `Debug/`

3. **Depurar/Ejecutar:**
   - **Debug Mode:** Click en el icono de bug (🐛)
     - Permite breakpoints, step-by-step, watch variables
   - **Run Mode:** Click en el icono de play (▶️)
     - Ejecución directa sin debugging

### Compilación desde Línea de Comandos
Para compilar desde PowerShell/CMD (requiere CCS instalado):

```powershell
# Navegar a la carpeta del proyecto
cd "PRACTICA 2/Practica 2.1"

# Compilar con make
make -C Debug clean
make -C Debug all

# O usando el compilador directamente
msp430-elf-gcc main.c -mmcu=msp430fr6989 -o main.out
```

### Variables de Entorno (Opcional)
Para compilar desde terminal, configurar:
```powershell
# Agregar CCS al PATH (ejemplo para Windows)
$env:PATH += ";C:\ti\ccs1210\ccs\tools\compiler\ti-cgt-msp430_21.6.1.LTS\bin"
```

### Opciones de Compilación Comunes
```bash
-mmcu=msp430fr6989    # Especifica el microcontrolador
-O0                   # Sin optimización (mejor para debug)
-O2                   # Optimización de velocidad
-Os                   # Optimización de tamaño
-g                    # Incluir información de debug
-Wall                 # Mostrar todos los warnings
```

### Carga del Programa (Flashing)
El programa se carga automáticamente al hacer Debug/Run desde CCS.
Alternativamente, usar `mspdebug` desde terminal:
```bash
mspdebug tilib "prog main.out"
```

## 📖 Guía Rápida de Registros MSP430FR6989

### Registros de GPIO
| Registro | Función | Ejemplo |
|----------|---------|---------|
| `PxDIR` | Dirección (0=entrada, 1=salida) | `P1DIR \|= BIT0;` |
| `PxOUT` | Valor de salida | `P1OUT \|= BIT0;` |
| `PxIN` | Valor de entrada (solo lectura) | `if (P1IN & BIT1)` |
| `PxREN` | Habilita resistencia pull-up/down | `P1REN \|= BIT1;` |
| `PxIE` | Habilita interrupción | `P1IE \|= BIT1;` |
| `PxIES` | Selección de flanco (0=subida, 1=bajada) | `P1IES \|= BIT1;` |
| `PxIFG` | Bandera de interrupción | `P1IFG &= ~BIT1;` |

### Registros de Timer_A0
| Registro | Función | Valores Típicos |
|----------|---------|-----------------|
| `TA0CTL` | Control del timer | `TASSEL_1 \| MC_1 \| TACLR` |
| `TA0CCR0` | Valor de comparación | `32768` (1 seg con ACLK) |
| `TA0CCTL0` | Control de captura/comparación | `CCIE` (habilita IRQ) |

**Fuentes de reloj:**
- `TASSEL_0` = TACLK (externo)
- `TASSEL_1` = ACLK (~32 kHz)
- `TASSEL_2` = SMCLK (~1 MHz)
- `TASSEL_3` = INCLK (invertido)

**Modos de conteo:**
- `MC_0` = Stop
- `MC_1` = Up (hasta CCR0)
- `MC_2` = Continuous (hasta 0xFFFF)
- `MC_3` = Up/Down

### Registros de UART (eUSCI_A1)
| Registro | Función | Ejemplo |
|----------|---------|---------|
| `UCA1CTLW0` | Control principal | `UCSWRST \| UCSSEL__SMCLK` |
| `UCA1BR0/1` | Baud Rate (divisor) | `52` para 9600@8MHz |
| `UCA1MCTLW` | Modulación (ajuste fino) | `UCOS16 \| UCBRF_1` |
| `UCA1TXBUF` | Buffer de transmisión | `UCA1TXBUF = 'A';` |
| `UCA1RXBUF` | Buffer de recepción | `char c = UCA1RXBUF;` |
| `UCA1IE` | Habilita interrupciones | `UCTXIE \| UCRXIE` |
| `UCA1IFG` | Banderas de interrupción | `UCTXIFG`, `UCRXIFG` |

### Registros del Sistema de Reloj
| Registro | Función |
|----------|---------|
| `CSCTL0` | Contraseña de acceso (`CSKEY`) |
| `CSCTL1` | Configuración del DCO |
| `CSCTL2` | Selección de fuentes de reloj |
| `CSCTL3` | Divisores de reloj |
| `CSCTL4` | Control de osciladores externos |
| `CSCTL5` | Banderas de fallo de cristal |

### Registros del LCD
| Registro | Función |
|----------|---------|
| `LCDCCTL0` | Control principal del LCD |
| `LCDCVCTL` | Control de voltaje (contraste) |
| `LCDCMEMCTL` | Control de memoria |
| `LCDMx` | Memoria de segmentos (x=0-43) |

## 🔍 Vectores de Interrupción Principales

```c
#pragma vector = PORT1_VECTOR          // Interrupción del Puerto 1
#pragma vector = PORT2_VECTOR          // Interrupción del Puerto 2
#pragma vector = TIMER0_A0_VECTOR      // Timer A0 CCR0
#pragma vector = TIMER0_A1_VECTOR      // Timer A0 CCR1-4, overflow
#pragma vector = USCI_A1_VECTOR        // UART/SPI/I2C A1
#pragma vector = ADC12_VECTOR          // Conversor ADC
```

## 🎲 Definiciones y Constantes Útiles

### Máscaras de Bits (BITx)
```c
#define BIT0    (0x0001)  // 0000 0000 0000 0001
#define BIT1    (0x0002)  // 0000 0000 0000 0010
#define BIT2    (0x0004)  // 0000 0000 0000 0100
#define BIT3    (0x0008)  // 0000 0000 0000 1000
#define BIT4    (0x0010)  // 0000 0000 0001 0000
#define BIT5    (0x0020)  // 0000 0000 0010 0000
#define BIT6    (0x0040)  // 0000 0000 0100 0000
#define BIT7    (0x0080)  // 0000 0000 1000 0000
// ... hasta BIT15 (0x8000)
```

### Contraseñas de Protección
```c
#define WDTPW   (0x5A00)  // Watchdog Timer password
#define CSKEY   (0xA500)  // Clock System password
```

### Frecuencias Típicas de Reloj
| Reloj | Frecuencia | Uso Típico |
|-------|------------|------------|
| MCLK | 1-16 MHz | CPU principal |
| SMCLK | 1-16 MHz | Periféricos rápidos (UART, SPI) |
| ACLK | 32.768 kHz | Temporizadores de baja potencia, LCD |
| VLOCLK | 10 kHz | Modo ultra bajo consumo |

### Tabla de Conversión de Retardos
Con MCLK a 1 MHz:
```c
__delay_cycles(1000);      // ~1 ms
__delay_cycles(10000);     // ~10 ms
__delay_cycles(100000);    // ~100 ms
__delay_cycles(1000000);   // ~1 segundo
```

Con MCLK a 8 MHz (como en Práctica 4):
```c
__delay_cycles(8000);      // ~1 ms
__delay_cycles(80000);     // ~10 ms
__delay_cycles(800000);    // ~100 ms
__delay_cycles(8000000);   // ~1 segundo
```

## 📝 Notas Importantes

### Configuración Básica Obligatoria
```c
// 1. Detener el Watchdog Timer (SIEMPRE primero)
WDTCTL = WDTPW | WDTHOLD;

// 2. Configurar GPIO
P1DIR |= BIT0;  // P1.0 como salida

// 3. Desbloquear periféricos (SIEMPRE antes de usar GPIO)
PM5CTL0 &= ~LOCKLPM5;
```

### Operaciones de Bits Comunes
```c
// Establecer bit (set)
P1OUT |= BIT0;    // Enciende LED

// Limpiar bit (clear)
P1OUT &= ~BIT0;   // Apaga LED

// Toggle bit (alternar)
P1OUT ^= BIT0;    // Cambia estado del LED

// Leer bit
if (P1IN & BIT1) { /* botón no pulsado */ }
```

### Configuración de Interrupciones
```c
P1IE  |= BIT1;     // Habilita interrupción en P1.1
P1IES |= BIT1;     // Flanco de bajada (falling edge)
P1IFG &= ~BIT1;    // Limpia bandera de interrupción
__enable_interrupt(); // Habilita interrupciones globales

// Rutina de servicio de interrupción
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void) {
    if (P1IFG & BIT1) {
        P1OUT ^= BIT0;
        P1IFG &= ~BIT1;  // Limpiar bandera
    }
}
```

### Puntos Críticos
- **Watchdog Timer:** Siempre debe detenerse con `WDTCTL = WDTPW | WDTHOLD;` al inicio del `main()`
- **Power Management:** Desbloquear periféricos con `PM5CTL0 &= ~LOCKLPM5;` antes de usar GPIO
- **GPIO:** Configurar dirección (DIR), resistencias (REN) y salidas (OUT) en el orden correcto
- **Interrupciones:** Siempre limpiar las banderas de interrupción (`IFG`) al final de la ISR
- **UART:** Calcular correctamente el Baud Rate según la frecuencia del reloj

## ⚠️ Troubleshooting (Solución de Problemas)

### Los LEDs no funcionan
- ✅ Verificar que se ha llamado `PM5CTL0 &= ~LOCKLPM5;`
- ✅ Comprobar que el pin está configurado como salida (`P1DIR |= BIT0;`)
- ✅ Verificar que el Watchdog Timer está detenido

### Las interrupciones no se disparan
- ✅ Verificar que `__enable_interrupt()` ha sido llamado
- ✅ Comprobar que la bandera de interrupción está limpia (`P1IFG &= ~BIT`)
- ✅ Verificar que la interrupción está habilitada (`P1IE |= BIT`)
- ✅ Asegurar que el vector de interrupción es correcto

### La UART no transmite/recibe
- ✅ Verificar la configuración de los pines (`P3SEL0`)
- ✅ Comprobar el cálculo del Baud Rate
- ✅ Verificar que el módulo no está en reset (`UCA1CTLW0 &= ~UCSWRST`)
- ✅ Usar un terminal serie (PuTTY, Tera Term) a 9600 baudios

### El LCD no muestra nada
- ✅ Verificar la inicialización del cristal LFXT (32 kHz)
- ✅ Esperar hasta que las banderas de fallo se limpien (`LFXTOFFG`)
- ✅ Comprobar que el LCD está encendido (`LCDCCTL0 |= LCDON`)
- ✅ Verificar el mapeo correcto de segmentos en `LCDMEM`

### El código no compila
- ✅ Verificar que `#include <msp430.h>` está al inicio
- ✅ Comprobar que el proyecto está configurado para MSP430FR6989
- ✅ Verificar la sintaxis de pragmas (`#pragma vector`)

## 💡 Ejemplos de Código Útiles

### Retardo Preciso (sin Timer)
```c
void delay_ms(unsigned int ms) {
    while (ms--) {
        __delay_cycles(1000);  // Asumiendo 1 MHz
    }
}
```

### Detección de Pulsación (con anti-rebote)
```c
unsigned char button_pressed(unsigned char pin) {
    if (!(P1IN & pin)) {  // Botón pulsado
        __delay_cycles(10000);  // Retardo anti-rebote
        if (!(P1IN & pin)) {    // Confirmar
            while (!(P1IN & pin));  // Esperar liberación
            return 1;
        }
    }
    return 0;
}
```

## 🎯 Objetivos de Aprendizaje

### Arquitectura de Computadores
- ✅ Comprender la arquitectura RISC de 16 bits del MSP430
- ✅ Conocer la organización de memoria (FRAM vs SRAM)
- ✅ Entender el funcionamiento de los registros especiales
- ✅ Aprender sobre modos de bajo consumo (Low Power Modes)

### Programación de Sistemas Embebidos
- ✅ Programación de bajo nivel en C para microcontroladores
- ✅ Gestión directa de registros y periféricos hardware
- ✅ Control de entradas/salidas digitales (GPIO)
- ✅ Implementación de sistemas basados en interrupciones
- ✅ Uso de temporizadores hardware (Timer_A)
- ✅ Comunicación serie (UART)

### Hardware y Periféricos
- ✅ Configuración y uso de GPIO (entradas/salidas digitales)
- ✅ Control de dispositivos mediante pulsadores y LEDs
- ✅ Manejo de pantallas LCD de segmentos
- ✅ Implementación de protocolos de comunicación (UART)
- ✅ Gestión de interrupciones por hardware

### Debugging y Desarrollo
- ✅ Uso de Code Composer Studio (CCS)
- ✅ Debugging con breakpoints y watch variables
- ✅ Análisis de señales y timing
- ✅ Optimización de código embebido
- ✅ Documentación de código con comentarios técnicos

### Conceptos Avanzados
- ✅ Sincronización de eventos mediante interrupciones
- ✅ Gestión de buffers circulares
- ✅ Máquinas de estados finitos
- ✅ Control de flujo en comunicaciones
- ✅ Configuración de sistemas de reloj (Clock System)

## 📚 Recursos Adicionales

### Documentación Oficial
- 📘 [MSP430FR6989 Datasheet](https://www.ti.com/product/MSP430FR6989) - Especificaciones completas del hardware
- 📗 [MSP430FR6989 User's Guide](https://www.ti.com/lit/ug/slau367p/slau367p.pdf) - Guía detallada de periféricos
- 📕 [MSP430 DriverLib Documentation](https://dev.ti.com/tirex/explore/node?node=A__AFvafJWmWWzL2Z-.kZq5kA__msp430_devtools__FyagoK9__LATEST) - Librerías de alto nivel
- 🔧 [Code Composer Studio User's Guide](https://software-dl.ti.com/ccs/esd/documents/users_guide/index.html) - Manual del IDE

### Tutoriales y Ejemplos
- 💻 [MSP430 Workshop](https://training.ti.com/msp430-workshop) - Curso completo de Texas Instruments
- 📺 [TI Training Videos](https://training.ti.com/) - Videos educativos oficiales
- 📚 [MSP430 Code Examples](https://www.ti.com/tool/MSP430WARE) - Colección de ejemplos oficiales
- 🎓 [MSP430FR69xx Workshop Guide](https://www.ti.com/lit/ml/slau682/slau682.pdf) - Material de laboratorio

### Herramientas de Desarrollo
- 🛠️ [Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO) - IDE oficial (gratis)
- 🔌 [MSP Debug Stack](https://www.ti.com/tool/MSPDS) - Drivers y utilidades de depuración
- 📊 [Energy Trace Technology](https://www.ti.com/tool/ENERGYTRACE) - Análisis de consumo energético
- 🖥️ [UniFlash](https://www.ti.com/tool/UNIFLASH) - Programación de memoria flash

### Comunicación Serie (UART)
- 💬 [PuTTY](https://www.putty.org/) - Cliente terminal serie (Windows/Linux)
- 💬 [Tera Term](https://ttssh2.osdn.jp/) - Cliente terminal serie alternativo
- 💬 [CoolTerm](https://freeware.the-meiers.org/) - Cliente serie multiplataforma

### Comunidad y Soporte
- 🌐 [TI E2E Forums - MSP430](https://e2e.ti.com/support/microcontrollers/msp-low-power-microcontrollers-group/msp430/) - Foro oficial
- 💬 [Reddit r/embedded](https://www.reddit.com/r/embedded/) - Comunidad de sistemas embebidos
- 📖 [Stack Overflow - MSP430 Tag](https://stackoverflow.com/questions/tagged/msp430)

### Libros Recomendados
- 📖 *"MSP430 Microcontroller Basics"* - John H. Davies
- 📖 *"Embedded Systems: Introduction to MSP430"* - Jonathan Valvano

## 🏫 Contexto Académico

**Asignatura:** Estructuras de Computadores  
**Curso:** 3º - Segundo Cuatrimestre  
**Titulación:** Doble Grado en Ingeniería Informática y Matemáticas  
**Universidad:** Universidad Complutense de Madrid (UCM)

### Prerrequisitos
- Fundamentos de Programación (C)
- Arquitectura de Computadores I
- Sistemas Digitales

### Competencias Desarrolladas
1. **CE03:** Capacidad para diseñar y analizar sistemas digitales
2. **CE04:** Conocimiento de arquitecturas de computadores
3. **CE06:** Capacidad para programar sistemas embebidos
4. **CE12:** Conocimiento de sistemas de tiempo real

## 📋 Progreso de Prácticas

- [x] Práctica 2.1 - Blink LED básico
- [x] Práctica 2.2 - Control con pulsadores
- [x] Práctica 2.3 - LED verde
- [x] Práctica 2.4 - Parpadeo síncrono
- [x] Práctica 2.5 - Parpadeo rápido
- [x] Práctica 3.1 - Interrupciones GPIO
- [x] Práctica 3.2 - Timer A0
- [x] Práctica 3.3 - Interrupciones avanzadas
- [x] Práctica 3.4 - Control LCD
- [x] Práctica 4.1 - UART transmisión
- [x] Práctica 4.2 - UART + LCD recepción
- [x] Práctica 4.2.1 - Buffer circular
- [x] Práctica 4.3 - Transmisión automática
- [x] Práctica 4.3.1 - TX automática mejorada
- [x] Laboratorio Final - Integración completa

## 🤝 Contribuciones

Este repositorio contiene material académico personal. Si encuentras errores o mejoras:
1. Abre un **Issue** describiendo el problema
2. O envía un **Pull Request** con la corrección

## ⚖️ Aviso Académico

Este repositorio contiene soluciones a prácticas académicas y está destinado a:
- ✅ Servir como referencia para estudiar conceptos
- ✅ Ayudar a entender la arquitectura MSP430
- ✅ Proporcionar ejemplos de código comentado

**Por favor:**
- ⚠️ Usa este material de forma responsable
- ⚠️ No copies directamente las soluciones sin entenderlas
- ⚠️ Respeta las políticas académicas de tu institución

## 👨‍💻 Autor

**Diego Rodríguez**
- GitHub: [@DIEGOROCU](https://github.com/DIEGOROCU)
- Universidad: UCM - Doble Grado Ingeniería Informática y Matemáticas
- Curso: 2025-2026

## 📄 Licencia

Este proyecto está bajo licencia académica para uso educativo en el contexto de la asignatura **Estructuras de Computadores**.

### Condiciones de Uso
- ✅ **Permitido:** Estudiar, aprender, referenciar el código
- ✅ **Permitido:** Usar como guía para comprender conceptos
- ✅ **Permitido:** Compartir con fines educativos citando la fuente
- ⚠️ **No permitido:** Copiar directamente para entregar como trabajo propio
- ⚠️ **No permitido:** Uso comercial sin autorización

### Disclaimer
El código se proporciona "tal cual" (AS IS) sin garantías. El autor no se hace responsable del uso indebido o de problemas derivados de su uso.

---

<div align="center">

**⭐ Si este repositorio te ha sido útil, considera darle una estrella ⭐**

*Universidad Complutense de Madrid - Facultad de Informática*  
*3º Curso - Doble Grado Ingeniería Informática y Matemáticas*  
*Estructuras de Computadores - 2º Cuatrimestre - 2025/2026*

**Made with ❤️ and lots of ☕**

</div>

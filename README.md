# Estructuras de Computadores

[![MSP430](https://img.shields.io/badge/MSP430-FR6989-red.svg)](https://www.ti.com/product/MSP430FR6989)
[![Code Composer Studio](https://img.shields.io/badge/IDE-Code%20Composer%20Studio-blue.svg)](https://www.ti.com/tool/CCSTUDIO)

Repositorio de prácticas de la asignatura **Estructuras de Computadores** del 2º cuatrimestre de 3º curso del Doble Grado en Ingeniería Informática y Matemáticas.

## 📋 Descripción

Este repositorio contiene las prácticas de laboratorio realizadas con el microcontrolador **MSP430FR6989** de Texas Instruments. Los ejercicios cubren conceptos fundamentales de arquitectura de computadores, programación embebida y control de periféricos.

## 🛠️ Tecnologías Utilizadas

- **Microcontrolador:** MSP430FR6989
- **IDE:** Code Composer Studio (CCS)
- **Lenguaje:** C
- **Toolchain:** MSP430 Compiler Tools

## 📂 Estructura del Repositorio

```
├── PRACTICA 2/
│   ├── LABORATORIO/          # Ejercicios de laboratorio guiado
│   ├── Practica 2.1/         # Ejercicio 1: Control básico de LED
│   ├── Practica 2.2/         # Ejercicio 2: Control con pulsadores
│   ├── Practica 2.3/         # Ejercicio 3: Múltiples LEDs
│   ├── Practica 2.4/         # Ejercicio 4: Ejercicios avanzados
│   └── Practica 2.5/         # Ejercicio 5
├── PRACTICA 3/
│   ├── Practica 3.1/         # Ejercicio 1
│   ├── Practica 3.2/         # Ejercicio 2
│   ├── Practica 3.3/         # Ejercicio 3
│   └── Practica 3.4/         # Ejercicio 4
```

## 🚀 Contenido de las Prácticas

### Práctica 2: Introducción a MSP430

- **Ejercicio 1:** "Hola Mundo" con printf y configuración básica
- **Ejercicio 2:** Control de LEDs (rojo y verde)
- **Ejercicio 3:** Lectura de pulsadores y GPIO
- **Ejercicio 4:** Integración de entradas y salidas
- **Ejercicio 5:** Ejercicios complementarios

**Conceptos trabajados:**
- Configuración del Watchdog Timer
- Gestión de puertos GPIO (P1, P9)
- Control de LEDs
- Lectura de pulsadores con pull-up
- Desbloqueo de periféricos (PM5CTL0)
- Retardos con `__delay_cycles()`

### Práctica 3: Programación Avanzada

Ejercicios avanzados de control de periféricos y programación del MSP430.

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

## 🔧 Compilación

Cada carpeta de práctica contiene:
- `main.c` - Código fuente principal
- `lnk_msp430fr6989.cmd` - Linker script
- `Debug/` - Archivos de compilación
- `driverlib/` - Librerías del dispositivo
- `targetConfigs/` - Configuración del target

Para compilar desde línea de comandos:
```bash
cd "PRACTICA 2/Practica 2.1"
make -C Debug
```

## 📝 Notas Importantes

- **Watchdog Timer:** Siempre debe detenerse con `WDTCTL = WDTPW | WDTHOLD;`
- **Power Management:** Desbloquear periféricos con `PM5CTL0 &= ~LOCKLPM5;`
- **GPIO:** Configurar dirección (DIR), resistencias (REN) y salidas (OUT) antes de usar

## 🎯 Objetivos de Aprendizaje

- Comprender la arquitectura del MSP430
- Programación de bajo nivel en C
- Gestión de registros y periféricos
- Control de entradas/salidas digitales
- Debugging de sistemas embebidos
- Optimización de código embebido

## 📚 Recursos Adicionales

- [MSP430FR6989 Datasheet](https://www.ti.com/product/MSP430FR6989)
- [MSP430 DriverLib Documentation](https://dev.ti.com/tirex/explore/node?node=A__AFvafJWmWWzL2Z-.kZq5kA__msp430_devtools__FyagoK9__LATEST)
- [Code Composer Studio User's Guide](https://software-dl.ti.com/ccs/esd/documents/users_guide/index.html)

## 👨‍💻 Autor

**Diego Rodríguez**
- GitHub: [@DIEGOROCU](https://github.com/DIEGOROCU)

## 📄 Licencia

Este proyecto está bajo licencia académica para uso educativo en el contexto de la asignatura Estructuras de Computadores.

---

*Universidad: 3º Curso - Doble Grado Ingeniería Informática y Matemáticas*  
*Asignatura: Estructuras de Computadores - 2º Cuatrimestre*

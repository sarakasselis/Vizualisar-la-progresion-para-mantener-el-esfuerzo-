# Visualizar la progresión para mantener el esfuerzo

**Dispositivo Wearable Low-Tech de Monitoreo Biométrico e Interfaz Lumínica Periférica**  
*Cátedra: Dispositivos Low-Tech e Interfaces Interactivas*  
*Facultad de Arquitectura y Urbanismo (FAU), Universidad de Chile*  
**Autores:** Sara Kasselis & Prune Ferru  

---

## 1. Resumen Ejecutivo
Este proyecto propone el diseño y prototipado de un dispositivo biométrico de indumentaria (*wearable*) orientado a deportistas en movimiento. El sistema captura la frecuencia cardíaca instantánea mediante fotopletismografía analógica y procesa la señal en tiempo real para traducirla en un código cromático periférico (Verde, Amarillo, Rojo). 

El enfoque **Low-Tech** prioriza la inteligibilidad inmediata y la reducción del esfuerzo cognitivo del usuario, eliminando la necesidad de interacción con pantallas digitales o interfaces densas durante la actividad física.

---

## 2. Definición del Problema y Concepto
Durante la carrera continua, el monitoreo del rendimiento fisiológico suele depender de pantallas complejas (*smartwatches*, teléfonos inteligentes) que requieren atención visual directa, rompiendo la concentración y la fluidez biomecánica del atleta. 

La solución desarrollada propone una **interfaz lumínica periférica integrada al textil** que transmite el estado de carga fisiológica mediante estimulación cromática directa, comprensible de un vistazo a través de la visión periférica.

---

## 3. Especificaciones Técnicas y Arquitectura Hardware

### 3.1 Prototipo V1 — Validación Mecánica y Electrónica (Benchtop)
* **Unidad de Procesamiento:** Microcontrolador Arduino UNO.
* **Captación Biométrica:** Sensor óptico de pulso (Pulse Sensor) conectado a la entrada analógica `A0`.
* **Interfaz de Salida:** Módulo de tres indicadores LED (5 mm) con resistencias limitadoras de corriente conectados a los pines digitales `2`, `3` y `4`.
* **Validación:** Comprobación experimental de la captación continua de señal y respuesta del algoritmo ante variaciones de latidos por minuto (BPM).

### 3.2 Prototipo V2 — Evolución e Integración E-Textil
* **Unidad de Procesamiento:** Placa ultraplana LilyPad compatible con el ecosistema Arduino.
* **Interfaz de Salida:** Cinta LED flexible integrada de forma envolvente en el contorno del magnesero deportivo.
* **Alimentación:** Batería alcalina de 9V con conector adaptado.
* **Criterio Ergonométrico:** Reducción de masa, eliminación de protoboard rígida e interconexión mediante cableado flexible para integración en indumentaria deportiva.

---

## 4. Criterio de Medición y Rangos Fisiológicos

El algoritmo clasifica el estado cardíaco del usuario en tres zonas funcionales operativas:

| Zona de Esfuerzo | Rango Fisiológico (BPM) | Estado del Atleta | Indicador Lumínico | Pin Digital Activo |
| :--- | :--- | :--- | :--- | :--- |
| **Zona 1: Reposo** | $< 85 \text{ BPM}$ | Estado base / Ritmo estable | LED Verde | Pin 2 |
| **Zona 2: Moderado** | $85 - 115 \text{ BPM}$ | Exigencia física media | LED Amarillo | Pin 3 |
| **Zona 3: Intenso** | $> 115 \text{ BPM}$ | Exigencia física alta / Umbral | LED Rojo | Pin 4 |

---

## 5. Algoritmo y Control de Señal (`.ino`)
La lógica de control desarrollada en C++ ejecuta las siguientes tareas:
1. **Detección de Pico Cardíaco:** Filtrado de umbral de voltaje analógico (`threshold = 550`).
2. **Cálculo Temporal Continuo:** Determinación del intervalo inter-beat ($\Delta T$) mediante la función `millis()` sin bloqueo de ejecución.
3. **Filtro Fisiológico:** Validación estricta de lecturas comprendidas dentro del rango biológico de 40 a 200 BPM para descartar artefactos por movimiento.
4. **Conmutación Exclusiva:** Discriminación condicional para la activación dinámica y no simultánea de las salidas digitales.

---

## 6. Estructura del Repositorio
* `magnesero_lowtech.ino`: Código fuente documentado en C++ compatible con Arduino UNO y LilyPad Arduino.
* `README.md`: Memoria técnica y especificaciones del proyecto.

---

## Entregas / Bitácora Digital
* [Sesión 01 - Marco del Problema](bitacora/S01.md)
* [Sesión 02 - Prototipado y Validación Biométrica](bitacora/S02.md)

/*
  =============================================================================
  PROYECTO: Magnesero Biométrico Low-Tech (Frecuencia Cardíaca & Interfaz LED)
  AUTORAS: Sara Kasselis & Prune Ferru
  INSTITUCIÓN: FAU, Universidad de Chile
  =============================================================================
  Descripción:
  Sistema de monitoreo de frecuencia cardíaca en tiempo real para deportistas.
  Lee la señal analógica de un Pulse Sensor en A0, calcula los BPM mediante 
  la diferencia de tiempo entre picos con millis(), y activa de forma condicional 
  un semáforo cromático (Verde, Amarillo, Rojo) en los pines 2, 3 y 4.
  
  Compatibilidad Hardware:
  - V1: Arduino UNO + Breadboard + LEDs 5mm
  - V2: LilyPad Arduino + E-Textiles + Cinta LED Flexible + Batería 9V
  =============================================================================
*/

// Asignación de Pines de Salida Digital (Semáforo Cromático)
const int ledVerde   = 2; // Reposo (< 85 BPM)
const int ledAmarillo = 3; // Esfuerzo Moderado (85 - 115 BPM)
const int ledRojo    = 4; // Esfuerzo Intenso (> 115 BPM)

// Entrada Analógica (Pulse Sensor)
const int pulsePin   = A0;

// Variables de Calibración y Algoritmo
int sensorValue      = 0;
int threshold        = 550;         // Umbral para aislar el pico de la onda PQRST
unsigned long lastBeatTime = 0;     // Registro del último latido detectado (ms)
int bpm              = 0;
bool beatDetected    = false;

void setup() {
  // Configuración de pines de salida
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  // Inicialización del Puerto Serie para Monitoreo
  Serial.begin(9600);
}

void loop() {
  // Lectura de la señal analógica
  sensorValue = analogRead(pulsePin);

  // Detección de pulso al superar el umbral
  if (sensorValue > threshold && !beatDetected) {
    beatDetected = true;
    unsigned long currentTime = millis();
    unsigned long duration = currentTime - lastBeatTime;

    // Cálculo de BPM: (60,000 ms / intervalo en ms)
    if (duration > 0) {
      bpm = 60000 / duration;
    }

    // Filtro Fisiológico (Validación entre 40 y 200 BPM)
    if (bpm >= 40 && bpm <= 200) {
      Serial.print("BPM Filtré: ");
      Serial.println(bpm);

      // Control Dinámico de Salidas Digitales (Activación Exclusiva)
      if (bpm < 85) {
        // Zona 1: Reposo
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledAmarillo, LOW);
        digitalWrite(ledRojo, LOW);
      } 
      else if (bpm >= 85 && bpm <= 115) {
        // Zona 2: Esfuerzo Moderado
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledAmarillo, HIGH);
        digitalWrite(ledRojo, LOW);
      } 
      else {
        // Zona 3: Esfuerzo Intenso (> 115 BPM)
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledAmarillo, LOW);
        digitalWrite(ledRojo, HIGH);
      }
    }
    lastBeatTime = currentTime;
  }

  // Restablecimiento de bandera al caer la señal por debajo del umbral
  if (sensorValue < threshold) {
    beatDetected = false;
  }
}

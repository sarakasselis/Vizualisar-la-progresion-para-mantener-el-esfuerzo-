// =========================================================================
// Proyecto: Acumulación del Esfuerzo Físico — Interfaces Low-Tech e Interactivas
// Preentrega N°3 / Prototipo V1 & V2
// =========================================================================

const int ledVerde     = 2; // Reposo (< 85 BPM)
const int ledAmarillo  = 3; // Esfuerzo Moderado (85 - 115 BPM)
const int ledRojo      = 4; // Esfuerzo Intenso (> 115 BPM)

const int pulsePin     = A0;

int sensorValue        = 0;
int threshold          = 550;        
unsigned long lastBeatTime = 0;    
int bpm                = 0;
bool beatDetected      = false;

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(pulsePin);

  if (sensorValue > threshold && !beatDetected) {
    beatDetected = true;
    unsigned long currentTime = millis();
    unsigned long duration = currentTime - lastBeatTime;

    if (duration > 0) {
      bpm = 60000 / duration;
    }

    if (bpm >= 40 && bpm <= 200) {
      Serial.print("BPM Filtrado: ");
      Serial.println(bpm);

      if (bpm < 85) {
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledAmarillo, LOW);
        digitalWrite(ledRojo, LOW);
      }
      else if (bpm >= 85 && bpm <= 115) {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledAmarillo, HIGH);
        digitalWrite(ledRojo, LOW);
      }
      else {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledAmarillo, LOW);
        digitalWrite(ledRojo, HIGH);
      }
    }
    lastBeatTime = currentTime;
  }

  if (sensorValue < threshold) {
    beatDetected = false;
  }
}

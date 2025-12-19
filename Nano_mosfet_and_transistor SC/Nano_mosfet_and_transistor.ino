#define transistorPin 8
#define mosfetPin 9
#define buttonTransistor 7
#define buttonMosfet 10

unsigned long prevBlinkMillis = 0;
bool blinkState = false;
unsigned long transistorTimer = 0;
unsigned long mosfetTimer = 0;
const unsigned long blinkInterval = 1000;
const unsigned long activeDuration = 3000;

void setup() {
  pinMode(transistorPin, OUTPUT);
  pinMode(mosfetPin, OUTPUT);
  pinMode(buttonTransistor, INPUT_PULLUP);
  pinMode(buttonMosfet, INPUT_PULLUP);
}

void loop() {
  unsigned long now = millis();
  
  // Cek tombol transistor
  if (digitalRead(buttonTransistor) == LOW) {
    transistorTimer = now;
  }
  
  // Cek tombol mosfet
  if (digitalRead(buttonMosfet) == LOW) {
    mosfetTimer = now;
  }
  
  // Update state blink
  if (now - prevBlinkMillis >= blinkInterval) {
    prevBlinkMillis = now;
    blinkState = !blinkState;
  }
  
  // Kontrol transistor pin
  bool transistorOverride = (now - transistorTimer < activeDuration);
  digitalWrite(transistorPin, transistorOverride ? HIGH : blinkState);
  
  // Kontrol mosfet pin
  bool mosfetOverride = (now - mosfetTimer < activeDuration);
  digitalWrite(mosfetPin, mosfetOverride ? HIGH : blinkState);
}
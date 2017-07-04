long timer=0;
int state=0;

void setup() {
  pinMode(0,INPUT);
  pinMode(16,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // A/D-Wandler auslesen
  int value=analogRead(A0);
  
  // LED im Herz-Rhythmus blinken lassen
  if (value>500)
    digitalWrite(16,HIGH);
  else
    digitalWrite(16,LOW);
    
  // falls Schwellwert überschritten
  if (value>500) {
    
    // falls aktiver Zustand 0
    if (state==0) {
      // zu Zustand 1 übergehen
      state=1;
      // Zeit merken
      timer=millis();
    }
    
    // falls aktiver Zustand 2
    if (state==2) {
      
      // zu Startzustand zurückkehren
      state=0;
      // Zeitdifferenz berechnen
      long ms=millis()-timer;
      // Puls berechnen und ausgeben
      if (ms>400) {
        Serial.print("Abstand (ms): ");
        Serial.println(ms);
        Serial.print("Puls (1/min): ");
        Serial.println(60000/ms);
      }
    }
  }
  
  // falls Schwellwert UNTERschritten
  if (value<500 && state==1) {
    // zu Zustand 2 übergehen
    state=2;
  }

}

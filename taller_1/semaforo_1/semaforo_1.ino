const int leds[] = {13, 12, 9, 5, 2}; 
int numero = 0;                         

void setup() {
 
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  
  for (int i = 0; i < 5; i++) {
    int bit = (numero >> i) & 1;  
    digitalWrite(leds[i], bit);    
  }

  numero++;  
  if (numero > 20) {
    numero = 0;  
  }

  delay(2000);  
}
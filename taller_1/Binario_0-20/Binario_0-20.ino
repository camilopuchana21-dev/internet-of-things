const int led1 = 13;  
const int led2 = 12;   
const int led3 = 9;    
const int boton = 5;

int mode = 0;
bool ultimoEstado = HIGH;
unsigned long tiempoUltimaLectura = 0;  
unsigned long intervaloRebote = 200;    

int estadoSemaforo = 0;
bool estadoIntermitente = false;

unsigned long tiempoCambio = 0;   
unsigned long intervalo = 500;    

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(boton, INPUT_PULLUP);
}

void loop() {
   
  bool estadoBoton = digitalRead(boton);

  if (estadoBoton == LOW && ultimoEstado == HIGH && (millis() - tiempoUltimaLectura) > intervaloRebote) {
    mode++;
    if (mode > 4) mode = 0;
    estadoSemaforo = 0; 
    tiempoUltimaLectura = millis();
  }

  ultimoEstado = estadoBoton;

  
  unsigned long tiempoActual = millis();

  switch (mode) {
    case 0: 
      if (tiempoActual - tiempoCambio >= 1000) {  
        tiempoCambio = tiempoActual;
        estadoSemaforo++;
        if (estadoSemaforo > 3) estadoSemaforo = 0;
      }

      digitalWrite(led1, estadoSemaforo == 0);
      digitalWrite(led2, estadoSemaforo == 1 || estadoSemaforo == 3);
      digitalWrite(led3, estadoSemaforo == 2);
      break;

    case 1: 
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      break;

    case 2: 
      if (tiempoActual - tiempoCambio >= 500) {
        tiempoCambio = tiempoActual;
        estadoIntermitente = !estadoIntermitente;
      }
      digitalWrite(led1, estadoIntermitente);
      digitalWrite(led2, estadoIntermitente);
      digitalWrite(led3, estadoIntermitente);
      break;

    case 3: 
      if (tiempoActual - tiempoCambio >= 500) {
        tiempoCambio = tiempoActual;
        estadoIntermitente = !estadoIntermitente;
      }
      digitalWrite(led1, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led2, estadoIntermitente);
      break;

    case 4: 
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      break;
  }
}
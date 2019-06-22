const byte LED1 = 10;
const byte LED2 = 11;
const byte LED3 = 12;
const byte LED4 = 13;

const byte BUTTON1 = 2;
const byte BUTTON2 = 3;
const byte BUTTON3 = 4;
 
unsigned long buttonPushedMillis; // when button was released
unsigned long ledTurnedOnAt; // when led was turned on
unsigned long turnOnDelay = 100; // wait to turn on LED
unsigned long turnOffDelay = 5000; // turn off LED after this time
bool es_derecha = true; // flag for when button is let go

byte lectura = '0';      // a variable to read incoming serial data into
byte ultima_lectura = '0';      // a variable to read incoming serial data into

bool title = false;
bool title_ejercicio = false;
bool menu = false;

void setup() {
   pinMode(BUTTON1, INPUT_PULLUP);
   pinMode(BUTTON2, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  Serial.begin(9600); 
  // put your setup code here, to run once:

}

void reiniciar() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void prenderDerecha() {
    unsigned long currentMillis = millis(); 
    if ((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnDelay) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
    }
    if ((unsigned long)(currentMillis - buttonPushedMillis) >= (turnOnDelay + 500)) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
    } 
    if ((unsigned long)(currentMillis - buttonPushedMillis) >= (turnOnDelay + 1000)) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
    }
    if ((unsigned long)(currentMillis - buttonPushedMillis) >= (turnOnDelay + 1500)) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      buttonPushedMillis = currentMillis;
    }    
}

void prenderIzquierda() {
    unsigned long currentMillis = millis(); 
    if ((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnDelay) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
    }
    if ((unsigned long)(currentMillis - buttonPushedMillis) >= (turnOnDelay + 500)) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
    } 
    if ((unsigned long)(currentMillis - buttonPushedMillis) >= (turnOnDelay + 1000)) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
    }
    if ((unsigned long)(currentMillis - buttonPushedMillis) >= (turnOnDelay + 1500)) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      buttonPushedMillis = currentMillis;
    }    
}

void ejercicioA() {
    // get the time at the start of this loop()
    
      
      // check the button
    if (digitalRead(BUTTON1) == LOW) {
      // update the time when button was pushed
      es_derecha = true;
      
    }

    if (digitalRead(BUTTON2) == LOW) {
      // update the time when button was pushed
      es_derecha = false;
    }
    if ( es_derecha ) {
      prenderDerecha();
    } else {
     prenderIzquierda();
    }
    

}

void ejercicioB() {

}

void loop() {
  if ( title == false ) {
    Serial.println("=== Sistema Escada ===");
    title = true;
  }

  if ( menu == false ) {
    Serial.println("A - Ejercicio 1.");
    Serial.println("B - Ejercicio 2.");
    Serial.println("Elija una opcion: ");
     menu = true;
  }
    lectura = Serial.read();
   // read the oldest byte in the serial buffer:
    if ( lectura == 255 || lectura == 10 ) {

     if (ultima_lectura == 'A') {
       ejercicioA();
     } else if (ultima_lectura == 'B') {
      ejercicioB();
   }
      
      return;   
    }
   
   if (lectura == 'A') {
    if ( lectura != ultima_lectura ) {
     Serial.println("---------------------------");
     Serial.println("Ejecutando el ejercicio 1.");      
     ultima_lectura = lectura;
     reiniciar();
    }
     ejercicioA();
   } else if (lectura == 'B' ) {
    if ( lectura != ultima_lectura ) {
     Serial.println("---------------------------");
     Serial.println("Ejecutando el ejercicio 2.");      
     ultima_lectura = lectura;
     reiniciar();
    }
    ejercicioB();
   }
}

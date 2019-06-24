const byte LED1 = 10;
const byte LED2 = 11;
const byte LED3 = 12;
const byte LED4 = 13;
const int BUZZER = 9;

const byte BUTTON1 = 2;
const byte BUTTON2 = 3;
const byte BUTTON3 = 4;

unsigned long buttonPushedMillis; // when button was released
unsigned long bButtonMillisUp = 0; // when button was released
unsigned long bButtonMillisDown = 0;
unsigned long buzzerMillis = 0;
unsigned long ledTurnedOnAt; // when led was turned on
unsigned long turnOnDelay = 400; // wait to turn on LED
unsigned long turnOffDelay = 5000; // turn off LED after this time
bool es_derecha = false;
bool es_izquierda = false;

byte lectura = '0'; // a variable to read incoming serial data into
byte ultima_lectura = '0'; // a variable to read incoming serial data into

bool title = false;
bool title_ejercicio = false;
bool menu = false;
char buffer_string[250];
int contador = 0;
int ultimo_contador = 0;
bool esta_sonando = false;

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
 pinMode(BUZZER, OUTPUT);

 Serial.begin(9600);
 // put your setup code here, to run once:

}

void reiniciar() {
 contador = 0;
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
 if (digitalRead(BUTTON1) == LOW) {
  es_derecha = false;
  es_izquierda = true;
 }

 if (digitalRead(BUTTON2) == LOW) {
  es_derecha = true;
  es_izquierda = false;
 }

 if (es_derecha) {
  prenderDerecha();
 }
 if (es_izquierda) {
  prenderIzquierda();
 }
}

void ejercicioB() {
 unsigned long currentMillis = millis();

  if (digitalRead(BUTTON1) == LOW) {
    if ( bButtonMillisUp == 0 ) {
      bButtonMillisUp = currentMillis;
    }
  
     if (bButtonMillisUp != 0 && (unsigned long)(currentMillis - bButtonMillisUp) >= 250) {
      if (contador <= 9) {
       contador++;
      }
       bButtonMillisUp = 0;
     }
  }
  if (digitalRead(BUTTON2) == LOW) {
    if ( bButtonMillisDown == 0 ) {
      bButtonMillisDown = currentMillis;
    }
  
     if (bButtonMillisDown != 0 && (unsigned long)(currentMillis - bButtonMillisDown) >= 250) {
  if (contador > 0) {
       contador--;
      }
       bButtonMillisDown = 0;
     }
  }
  
 if (ultimo_contador != contador) {
  if (contador == 10) {
   Serial.println("Intensidad al: 100%");
   analogWrite(LED1, 254);
  } else {
   sprintf(buffer_string, "Intensidad al %d%%", contador);
   Serial.println(buffer_string);
   analogWrite(LED1, contador * 25);
  }
   ultimo_contador = contador;
 }
}

void ejercicioC() {
 unsigned long currentMillis = millis();

  if (buzzerMillis != 0 && (unsigned long)(currentMillis - buzzerMillis) >= 500) {
    noTone(BUZZER); 
    buzzerMillis = 0;
  }
  
  if (digitalRead(BUTTON1) == LOW) {
    if ( bButtonMillisUp == 0 ) {
      bButtonMillisUp = currentMillis;
    }
  
     if (bButtonMillisUp != 0 && (unsigned long)(currentMillis - bButtonMillisUp) >= 250) {
      if (contador <= 5) {
       contador++;
      }
       bButtonMillisUp = 0;
     }
  }
  if (digitalRead(BUTTON2) == LOW) {
    if ( bButtonMillisDown == 0 ) {
      bButtonMillisDown = currentMillis;
    }
  
     if (bButtonMillisDown != 0 && (unsigned long)(currentMillis - bButtonMillisDown) >= 250) {
  if (contador > 1) {
       contador--;
      }
       bButtonMillisDown = 0;
     }
  }
  
 if (ultimo_contador != contador) {
   if ( contador == 1 ) {
        Serial.println("Tono C...");
         tone(BUZZER,261);
   } else if (contador == 2  ) {
             Serial.println("Tono D...");
         tone(BUZZER,293);   
   } else if (contador == 3  ) {
             Serial.println("Tono E...");
         tone(BUZZER,329);   
   } else if (contador == 4  ) {
             Serial.println("Tono F...");
         tone(BUZZER,349 );   
   } else if (contador == 5  ) {
             Serial.println("Tono G...");
         tone(BUZZER,392 );   
   }
   buzzerMillis = currentMillis;
   //esta_sonando = true;
   ultimo_contador = contador;
 }
  
}

void loop() {
 if (title == false) {
  Serial.println("=== Sistema Escada ===");
  title = true;
 }

 if (menu == false) {
  Serial.println("A - Ejercicio 1 - Secuencia de leds: ");
  Serial.println("B - Ejercicio 2 - Led 10 pulsos:");
  Serial.println("C - Ejercicio 3 - Buzzer:");
  Serial.println("Elija una opcion: ");
  menu = true;
 }
 lectura = Serial.read();
 // read the oldest byte in the serial buffer:
 if (lectura == 255 || lectura == 10) {

  if (ultima_lectura == 'A') {
   ejercicioA();
  } else if (ultima_lectura == 'B') {
   ejercicioB();
  } else if (ultima_lectura == 'C') {
   ejercicioC();
  }

  return;
 }

 if (lectura == 'A') {
  if (lectura != ultima_lectura) {
   Serial.println("---------------------------");
   Serial.println("Ejecutando el ejercicio 1.");
   ultima_lectura = lectura;
   reiniciar();
  }
  ejercicioA();
 } else if (lectura == 'B') {
  if (lectura != ultima_lectura) {
   Serial.println("---------------------------");
   Serial.println("Ejecutando el ejercicio 2.");
   ultima_lectura = lectura;
   reiniciar();
  }
  ejercicioB();
 } else if (lectura == 'C') {
  if (lectura != ultima_lectura) {
   Serial.println("---------------------------");
   Serial.println("Ejecutando el ejercicio 3.");
   ultima_lectura = lectura;
   reiniciar();
  }
  ejercicioC();
 }
}

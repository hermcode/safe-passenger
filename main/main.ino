#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>



// Set these to run example.
#define FIREBASE_HOST "safepassenger-727db-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "KymPvloSVcQbQKmxmsHCYiLfzXtnC8esNdMEcJY8"
#define WIFI_SSID "Totalplay-9BA2"
#define WIFI_PASSWORD "9BA22550Z452nd66"

//Asiento 1
#define PIN_TRIG D6
#define PIN_ECHO D5

//Asiento 2
#define PIN_TRIG_01 D8
#define PIN_ECHO_01 D7

//Pasillo
#define PIN_TRIG_02 D1
#define PIN_ECHO_02 D0

void setup() {
  Serial.begin(9600);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG_01, OUTPUT);
  pinMode(PIN_ECHO_01, INPUT);
  pinMode(PIN_TRIG_02, OUTPUT);
  pinMode(PIN_ECHO_02, INPUT);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;
float tiempo;
float distancia;

void loop() {

  AsientoUno();
  AsientoDos();
  Pasillo();
  delay(1000);
}

void AsientoUno(){
  digitalWrite(PIN_TRIG, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
   
  digitalWrite(PIN_TRIG, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
   
  tiempo = pulseIn(PIN_ECHO, HIGH);
  distancia = tiempo/58.3;

  if (distancia < 10){
   Firebase.setBool("Camiones/001/asiento1", true);
  } else {
   Firebase.setBool("Camiones/001/asiento1", false);
  }
}

void AsientoDos(){
  digitalWrite(PIN_TRIG_01, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
   
  digitalWrite(PIN_TRIG_01, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG_01, LOW);
   
  tiempo = pulseIn(PIN_ECHO_01, HIGH);
  distancia = tiempo/58.3;

  if (distancia < 10){
   Firebase.setBool("Camiones/001/asiento2", true);
  } else {
   Firebase.setBool("Camiones/001/asiento2", false);
  }
}

void Pasillo(){
  digitalWrite(PIN_TRIG_02, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
   
  digitalWrite(PIN_TRIG_02, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG_02, LOW);
   
  tiempo = pulseIn(PIN_ECHO_02, HIGH);
  distancia = tiempo/58.3;

  if (distancia < 10){
   Firebase.setBool("Camiones/001/pasillo", true);
  } else {
   Firebase.setBool("Camiones/001/pasillo", false);
  }
}

/*Sensor de asiento 2*/
const int PIN_8 = 8; //Echo
const int PIN9 = 9; //Trig

/*Sensor de asiento 1*/
const int PIN10 = 10; //Echo
const int PIN11 = 11; //Trig

// Sensor para el control de personas
const int PIN12 = 12; //Echo
const int PIN13 = 13; //Trig

//Motores
int ENA = 2;      // ENA de L298N a pin digital 2
int IN1 = 3;      // IN1 de L298N a pin digital 3
int IN2 = 4;      // IN2 de L298N a pin digital 4

int IN3 = 5;      // IN3 de L298N a pin digital 5
int IN4 = 6;      // IN4 de L298N a pin digital 6
int ENB = 7;      // ENB de L298N a pin digital 7

int VELOCIDAD = 255;
int PIN5V = 2 ;
int DURACION;
int DISTANCIA; 
int ASIENTOS;
bool Personas_de_pie;
int Arrancar;

void setup() {
  /*Motores*/
  pinMode(IN1, OUTPUT);   // pin 2 como salida
  pinMode(IN2, OUTPUT);   // pin 3 como salida  
  pinMode(ENA, OUTPUT);   // pin 5 como salida

  pinMode(IN3, OUTPUT);   // pin 2 como salida
  pinMode(IN4, OUTPUT);   // pin 3 como salida  
  pinMode(ENB, OUTPUT);   // pin 5 como salida
  
  /* Sensor de Asiento 2 */
  pinMode(PIN9, OUTPUT);
  pinMode(PIN_8, INPUT);

  /* Sensor de Asiento 1 */
  pinMode(PIN11, OUTPUT);
  pinMode(PIN10, INPUT);
  
  /*Sensor para el control de personas*/
  pinMode(PIN13, OUTPUT);
  pinMode(PIN12, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  ASIENTOS = 2;

  Serial.println("=========================");
  lecturaPersonas(PIN13, PIN12);
  Serial.println(DISTANCIA);
  Serial.print("Personas de pie: ");
  Serial.println(Personas_de_pie);
  
  lecturaAsientos(PIN11,PIN10);
  Serial.println(DISTANCIA);
  
  lecturaAsientos(PIN9,PIN_8);
  Serial.println(DISTANCIA);

  Serial.print("Asientos disponibles: ");
  Serial.println(ASIENTOS);

  if(Personas_de_pie == 1 && ASIENTOS > 0){
    Arrancar = 0;
  } else {
    Arrancar = 1;
  }
  Serial.print("Arrancar: ");
  Serial.println(Arrancar);

  if(Arrancar == 1){
    funcionamientoMotores();
  }else {
    analogWrite(ENA, LOW);
    analogWrite(ENB, LOW);
  }
  //delay(500);
}

int lecturaPersonas(int TRIG, int ECHO){
  digitalWrite(TRIG, HIGH);
  delay(2);
  digitalWrite(TRIG, LOW);
  DURACION = pulseIn(ECHO, HIGH);
  DISTANCIA = DURACION / 58.2;

  if(DISTANCIA < 20 && DISTANCIA >= 0){
    Personas_de_pie = true;
  } else {
    Personas_de_pie = false;
  }

  return DISTANCIA, Personas_de_pie;
}

int lecturaAsientos(int TRIG, int ECHO){
  digitalWrite(TRIG, HIGH);
  delay(2);
  digitalWrite(TRIG, LOW);
  DURACION = pulseIn(ECHO, HIGH);
  DISTANCIA = DURACION / 58.2;

  if(DISTANCIA < 11 && DISTANCIA >= 0){
    ASIENTOS = ASIENTOS - 1;
  }
  
  return DISTANCIA, ASIENTOS;
}

void funcionamientoMotores(){
    analogWrite(ENA, VELOCIDAD);   // el valor de velocidad y aplica a ENA
    digitalWrite(IN1, HIGH);       // IN1 en 1
    digitalWrite(IN2, LOW);        // IN2 en 0

    analogWrite(ENB, VELOCIDAD);   // el valor de velocidad y aplica a ENB
    digitalWrite(IN3, LOW);       // IN1 en 0
    digitalWrite(IN4, HIGH);      // IN2 en 1
}

#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 pressure;
#define ALTITUDE 95.0
int valor_limite=500 ;
int rainsense= A2;

// Orden de los sensores
// s1-Temperatura
// s2-Presion
// s3-Sensor de Humedad 1
// s4-Sensor de Humedad 2
// s5-Sensor de Lluvia

void setup() {
  Serial.begin(9600);
  pinMode(rainsense, INPUT); // Sensor de lluvia
  pinMode(13,OUTPUT);      // Configura el Pin 13 como salida para el led 
  pinMode(8,OUTPUT);      //Configura el Pin 8 como salida para el Zumbador 
  pinMode(22,OUTPUT);
  pinMode(11,OUTPUT);
  if (pressure.begin()){}
  else
  {
    while(1); // Pause forever.
  }
}

void loop() {
  char status;
  double T,P,p0,a;
  status = pressure.startTemperature();
  status = pressure.getTemperature(T);
  if (status != 0)
  {
    delay(status);
    Serial.print(T,2);
    Serial.print(" ");
    delay(100);
    status = pressure.getPressure(P,T);
    delay(status);
    Serial.print(P*0.0295333727,2);
    Serial.print(" ");
    delay(100);
  }

  Serial.print(analogRead(A0));    //Envia al Serial el valor leido del Sensor]
  Serial.print(" ");
  Serial.print(analogRead(A1));    //Envia al Serial el valor leido del Sensor] 
  Serial.print(" ");
  Serial.println(analogRead(rainsense));    //Envia al Serial el valor leido del Sensor] 
   
  if(analogRead(A0) < valor_limite or analogRead(A1) < valor_limite or  analogRead(A7) < 50) {  //Si la medida de humedad es mayor de valor limite
    digitalWrite(13, HIGH) ;           //Enciende el led conectado al Pin 13 
    digitalWrite(8, HIGH) ;           //Enciende el zumbador conectado al Pin 8 
  }
  else{                           //Si es mayor del valor limite apaga el zumbador y el led
  digitalWrite(13,LOW);
  digitalWrite(8,LOW);
  
  }
  if(analogRead(rainsense)<500){
    digitalWrite(11, HIGH) ; 
    }
  else {
    digitalWrite(11, LOW) ; 
    }
  delay(250);
}

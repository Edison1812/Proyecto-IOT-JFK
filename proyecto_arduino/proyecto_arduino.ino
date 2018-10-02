#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 pressure;
#define ALTITUDE 95.0
int valor_limite=500 ;
int rainsense= A2;
int ph_pin = A0; 
int m_7 = 745; //PH-agua
int m_13 = 580;//PH-legia

// Orden de los sensores
// s1-Temperatura
// s2-Presion
// s3-Sensor de Humedad 1 0-100%
// s4-Sensor de Humedad 2 0-100%
// s5-Sensor de Lluvia 0-100%
// s6-Sensor de PH 0-14
// s7-Flujometro 0-20

const int sensorPin = 2;
const int measureInterval = 2500;
volatile int pulseConter;
 
// YF-S201
const float factorK = 7.5;
// FS300A
//const float factorK = 5.5;
// FS400A
//const float factorK = 3.5;
 
 
void ISRCountPulse()
{
   pulseConter++;
}
 
float GetFrequency()
{
   pulseConter = 0;
 
   interrupts();
   delay(measureInterval);
   noInterrupts();
 
   return (float)pulseConter * 1000 / measureInterval;
}

void setup() {
  Serial.begin(9600);
  pinMode(rainsense, INPUT); // Sensor de lluvia
  pinMode(13,OUTPUT);      // Configura el Pin 13 como salida para el led 
  pinMode(8,OUTPUT);      //Configura el Pin 8 como salida para el Zumbador 
  pinMode(22,OUTPUT);
  pinMode(11,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), ISRCountPulse, RISING);
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
  Serial.print(analogRead(rainsense));    //Envia al Serial el valor leido del Sensor] 
  Serial.print(" ");
  
  int measure = 0;
  int prom = 0;

  for(int i=0;i<20;i++)
  {  measure = analogRead(ph_pin);
     prom = prom + measure;
     delay(50);
  }
  prom = prom/20;
  float Po = 7 - ((measure - m_7 ) * 6 / ( m_7 - m_13 ));
  Serial.print(Po, 2);
  Serial.print(" ");
   
  float frequency = GetFrequency(); // obtener frecuencia en Hz
  float flow_Lmin = frequency * factorK;// calcular caudal L/min
  
  Serial.println(flow_Lmin, 2);

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

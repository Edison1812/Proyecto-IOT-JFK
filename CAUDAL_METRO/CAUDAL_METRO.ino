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
 
void setup()
{
   Serial.begin(9600);
   attachInterrupt(digitalPinToInterrupt(sensorPin), ISRCountPulse, RISING);
}
 
void loop()
{
   // obtener frecuencia en Hz
   float frequency = GetFrequency();
 
   // calcular caudal L/min
   float flow_Lmin = frequency * factorK;
 
   Serial.print("Frecuencia: ");
   Serial.print(frequency, 0);
   Serial.print(" (Hz)\tCaudal: ");
   Serial.print(flow_Lmin, 3);
   Serial.println(" (L/min)");
}

int ph_pin = A0; // A2 -> Po

int m_7 = 745; //agua
int m_13=580;//legia
void setup() {
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  
int measure = 0;
int prom = 0;

    for(int i=0;i<20;i++)
  {  measure = analogRead(ph_pin);
     prom = prom + measure;
     delay(50);
  }

  prom = prom/20;
  
  Serial.print("Medida: ");
  Serial.print(prom);

  //calibracion
  float Po = 7 - ((measure - m_7 ) * 6 / ( m_7 - m_13 ));
  Serial.print("\tPH: ");
  Serial.print(Po, 2);
  Serial.println("");
  delay(100);
}

//Sensor Ultrasonico 1
int v1 = 13;//DECLARACION DE LOS LEDS
int a1 = 12;//DECLARACION DE LOS LEDS
int r1 = 14;//DECLARACION DE LOS LEDS

int echoPin1 = 26;//DECLARACION DE PUERTO ECHO
int triggerPin1 = 25;//DECLARACION DE PUERTO TRIGGER
long ultrason1 = 0;

//Distancia sensor ultrasonico1 1
long readUltrasonicDistance1(int triggerPin1, int echoPin1)
{
  pinMode(triggerPin1, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin1, LOW);//LECTURA DEL PUERTO TRIGGER 
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW);//LECTURA DEL PUERTO TRIGGER 
  pinMode(echoPin1, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds *0.01723
  return (pulseIn(echoPin1, HIGH)*0.01723);
  
}

//Sensor Ultrasonico 2
int v2 = 21;//DECLARACION DE LOS LEDS
int a2 = 19;//DECLARACION DE LOS LEDS
int r2 = 18;//DECLARACION DE LOS LEDS

int echoPin2 = 23;//DECLARACION DE PUERTO ECHO
int triggerPin2 = 22;//DECLARACION DE PUERTO TRIGGER
long ultrason2 = 0;

long readUltrasonicDistance2(int triggerPin2, int echoPin2)
{
  pinMode(triggerPin2, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin2, LOW);//LECTURA DEL PUERTO TRIGGER 
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin2, LOW);//LECTURA DEL PUERTO TRIGGER 
  pinMode(echoPin2, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds *0.01723
  return (pulseIn(echoPin2, HIGH)*0.01723);
  
}



void setup()
{
  Serial.begin(115200);
  
  pinMode(v1, OUTPUT);//SALIDA DEL LED 13 
  pinMode(a1, OUTPUT);//SALIDA DEL LED 12 
  pinMode(r1, OUTPUT);//SALIDA DEL LED 11 

  pinMode(v2, OUTPUT);//SALIDA DEL LED 21 
  pinMode(a2, OUTPUT);//SALIDA DEL LED 19 
  pinMode(r2, OUTPUT);//SALIDA DEL LED 18 
}

void loop()
{
  //Revision lugar de estacionamiento 1
  ultrason1 =readUltrasonicDistance1(25, 26);
  Serial.print(ultrason1);
  Serial.println("cm");
  
  if (ultrason1 > 12) {
    digitalWrite(v1, HIGH);// LECRURA DIGITAL DEL LED 13
    digitalWrite(a1, LOW);// LECRURA DIGITAL DEL LED 12
    digitalWrite(r1, LOW);// LECRURA DIGITAL DEL LED 11
  }
  if (ultrason1 <= 8 && ultrason1 > 4) {
    digitalWrite(v1, LOW);// LECRURA DIGITAL DEL LED 13
    digitalWrite(a1, HIGH);// LECRURA DIGITAL DEL LED 12
    digitalWrite(r1, LOW);// LECRURA DIGITAL DEL LED 11
  }
  if (ultrason1 <= 4) {
    digitalWrite(v1, LOW);// LECRURA DIGITAL DEL LED 13
    digitalWrite(a1, LOW);// LECRURA DIGITAL DEL LED 12
    digitalWrite(r1, HIGH);// LECRURA DIGITAL DEL LED 11
  }
  
  //Revision lugar de estacionamiento 2
  ultrason2 =readUltrasonicDistance2(22, 23);
  Serial.print(ultrason2);
  Serial.println("cm");
  
  if (ultrason2 > 12) {
    digitalWrite(v2, HIGH);// LECRURA DIGITAL DEL LED 13
    digitalWrite(a2, LOW);// LECRURA DIGITAL DEL LED 12
    digitalWrite(r2, LOW);// LECRURA DIGITAL DEL LED 11
  }
  if (ultrason2 <= 8 && ultrason2 > 4) {
    digitalWrite(v2, LOW);// LECRURA DIGITAL DEL LED 13
    digitalWrite(a2, HIGH);// LECRURA DIGITAL DEL LED 12
    digitalWrite(r2, LOW);// LECRURA DIGITAL DEL LED 11
  }
  if (ultrason2 <= 4) {
    digitalWrite(v2, LOW);// LECRURA DIGITAL DEL LED 13
    digitalWrite(a2, LOW);// LECRURA DIGITAL DEL LED 12
    digitalWrite(r2, HIGH);// LECRURA DIGITAL DEL LED 11
  }

  delay(100); // Wait for 100 millisecond(s)
  
}

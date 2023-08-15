#include <ESP32_Servo.h>

Servo servo1; 
int servoPin = 14;
int pos = 0; 
int entrada = 13;
int salida = 12;
int minUs = 500;
int maxUs = 2400;

void setup() {
 Serial.begin(115200);   //iniciar puerto serie
 servo1.attach(servoPin);
 pinMode(entrada, OUTPUT);
 pinMode(salida, OUTPUT);
}

void loop(){
  int valueEntrada = 0;
  int valueSalida = 0;

  valueEntrada = digitalRead(entrada);
  valueSalida = digitalRead(salida);

 if (valueEntrada == HIGH) {
   servo1.write(180);
    delay(1000); 
    digitalWrite(entrada,HIGH);
 }
 else{
 if(valueEntrada == LOW) {
   servo1.write(0);
   digitalWrite(entrada,LOW);//Apagar LED cuando no detecte nada
    }
  }

  if (valueSalida == HIGH) {
   servo1.write(180);
    delay(1000); 
    digitalWrite(salida,HIGH);
 }
 else{
 if(valueSalida == LOW) {
   servo1.write(0);
   digitalWrite(salida,LOW);//Apagar LED cuando no detecte nada
    }
  }
}
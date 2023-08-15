#include <esp_now.h>
#include <WiFi.h>
#include <ESP32_Servo.h>

Servo servo1; 
int servoPin = 14;
int pos = 0; 
int entrada = 13;
int salida = 12;
int minUs = 500;
int maxUs = 2400;

// Structure example to receive data
typedef struct struct_message {
    int slotR1;
    int slotR2;
    int slotR3;
    int slotR4;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  //--------SLOT 1 ----------------------
  Serial.print("Estado Slot 1: ");
  int recepSlot1 = myData.slotR1;
  Serial.println(myData.slotR1);
  if(recepSlot1 == 1){
    Serial.print("Ocupado");
  }else{
    Serial.print("Disponible");
  }
  //---------SLOT 2----------------------
  Serial.print("Estado Slot 2: ");
  int recepSlot2 = myData.slotR2;
  Serial.println(myData.slotR2);
  if(recepSlot2 == 1){
    Serial.print("Ocupado");
  }else{
    Serial.print("Disponible");
  }

  //---------SLOT 3----------------------
  Serial.print("Estado Slot 3: ");
  int recepSlot3 = myData.slotR3;
  Serial.println(myData.slotR3);
  if(recepSlot3 == 1){
    Serial.print("Ocupado");
  }else{
    Serial.print("Disponible");
  }  

  //---------SLOT 4----------------------
  Serial.print("Estado Slot 4: ");
  int recepSlot4 = myData.slotR4;
  Serial.println(myData.slotR4);
  if(recepSlot4 == 1){
    Serial.print("Ocupado");
  }else{
    Serial.print("Disponible");
  }

}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for recv CB to get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
  //Servomotor
  servo1.attach(servoPin);
  pinMode(entrada, OUTPUT);
  pinMode(salida, OUTPUT);
}
 
void loop() {
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
#include <esp_now.h>
#include <WiFi.h>
//------------------------------SLOT 1--------------------------------------------------------------------------------------------
//Sensor Ultrasonico 1
int v1 = 14;//DECLARACION DE LOS LEDS
int a1 = 12;//DECLARACION DE LOS LEDS
int r1 = 13;//DECLARACION DE LOS LEDS
int echoPin1 = 35;//DECLARACION DE PUERTO ECHO
int triggerPin1 = 27;//DECLARACION DE PUERTO TRIGGER
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
//----------------------------SLOT 2------------------------------------------------------------------------
//Sensor Ultrasonico 2
int v2 = 26;//DECLARACION DE LOS LEDS
int a2 = 25;//DECLARACION DE LOS LEDS
int r2 = 33;//DECLARACION DE LOS LEDS
int echoPin2 = 34;//DECLARACION DE PUERTO ECHO
int triggerPin2 = 32;//DECLARACION DE PUERTO TRIGGER
long ultrason2 = 0;

//Distancia sensor ultrasonico 2
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
//-----------------------SLOT 3----------------------------------------------------------------------------
//Sensor Ultrasonico 3
int v3 = 23;//DECLARACION DE LOS LEDS
int a3 = 22;//DECLARACION DE LOS LEDS
int r3 = 21;//DECLARACION DE LOS LEDS
int echoPin3 = 17;//DECLARACION DE PUERTO ECHO
int triggerPin3 = 16;//DECLARACION DE PUERTO TRIGGER
long ultrason3 = 0;

//Distancia sensor ultrasonico 3
long readUltrasonicDistance3(int triggerPin3, int echoPin3)
{
  pinMode(triggerPin3, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin3, LOW);//LECTURA DEL PUERTO TRIGGER 
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin3, LOW);//LECTURA DEL PUERTO TRIGGER 
  pinMode(echoPin3, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds *0.01723
  return (pulseIn(echoPin3, HIGH)*0.01723);
  
}
//-------------------------SLOT 4-----------------------------------------------------------------------------
//Sensor Ultrasonico 4
int v4 = 19;//DECLARACION DE LOS LEDS
int a4 = 18;//DECLARACION DE LOS LEDS
int r4 = 5;//DECLARACION DE LOS LEDS
int echoPin4 = 4;//DECLARACION DE PUERTO ECHO
int triggerPin4 = 15;//DECLARACION DE PUERTO TRIGGER
long ultrason4 = 0;

//Distancia sensor ultrasonico 4
long readUltrasonicDistance4(int triggerPin4, int echoPin4)
{
  pinMode(triggerPin4, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin4, LOW);//LECTURA DEL PUERTO TRIGGER 
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin4, LOW);//LECTURA DEL PUERTO TRIGGER 
  pinMode(echoPin4, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds *0.01723
  return (pulseIn(echoPin4, HIGH)*0.01723);
  
}
//-----------------------------------------------------------------------------------
// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = { 0xC8, 0xF0, 0x9E, 0xF7, 0xAB, 0x78 };

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int slotR1;
  int slotR2;
  int slotR3;
  int slotR4;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
//Salidas leds Slot 1
  pinMode(v1, OUTPUT);//SALIDA DEL LED 
  pinMode(a1, OUTPUT);//SALIDA DEL LED 
  pinMode(r1, OUTPUT);//SALIDA DEL LED 
//Salidas leds Slot 2
  pinMode(v2, OUTPUT);//SALIDA DEL LED 
  pinMode(a2, OUTPUT);//SALIDA DEL LED 
  pinMode(r2, OUTPUT);//SALIDA DEL LED 

//Salidas leds Slot 3
  pinMode(v3, OUTPUT);//SALIDA DEL LED 
  pinMode(a3, OUTPUT);//SALIDA DEL LED 
  pinMode(r3, OUTPUT);//SALIDA DEL LED   

//Salidas leds Slot 4
  pinMode(v4, OUTPUT);//SALIDA DEL LED 
  pinMode(a4, OUTPUT);//SALIDA DEL LED 
  pinMode(r4, OUTPUT);//SALIDA DEL LED   

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
//-----------------------------SLOT 1 ------------------------------------------------------------
  //Revision lugar de estacionamiento 1
  ultrason1 =readUltrasonicDistance1(27, 35);
  
  if (ultrason1 > 12) {
    digitalWrite(v1, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(a1, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r1, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason1 <= 8 && ultrason1 > 4) {
    digitalWrite(v1, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a1, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(r1, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason1 <= 4) {
    digitalWrite(v1, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a1, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r1, HIGH);// LECRURA DIGITAL DEL LED 
  }

//-----------------------------SLOT 2 ------------------------------------------------------------
  ultrason2 =readUltrasonicDistance2(32, 34);
  
  if (ultrason2 > 12) {
    digitalWrite(v2, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(a2, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r2, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason2 <= 8 && ultrason2 > 4) {
    digitalWrite(v2, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a2, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(r2, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason2 <= 4) {
    digitalWrite(v2, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a2, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r2, HIGH);// LECRURA DIGITAL DEL LED 
  }

//-----------------------------SLOT 3 ------------------------------------------------------------
  ultrason3 =readUltrasonicDistance3(16, 17);
  
  if (ultrason3 > 12) {
    digitalWrite(v3, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(a3, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r3, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason3 <= 8 && ultrason3 > 4) {
    digitalWrite(v3, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a3, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(r3, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason3 <= 4) {
    digitalWrite(v3, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a3, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r3, HIGH);// LECRURA DIGITAL DEL LED 
  }
  
//-----------------------------SLOT 4 ------------------------------------------------------------
  ultrason4 =readUltrasonicDistance4(15, 4);
  Serial.print(ultrason4);
  
  if (ultrason4 > 12) {
    digitalWrite(v4, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(a4, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r4, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason4 <= 8 && ultrason4 > 4) {
    digitalWrite(v4, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a4, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(r4, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason4 <= 4) {
    digitalWrite(v4, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a4, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r4, HIGH);// LECRURA DIGITAL DEL LED 
  }

//Actualizacion de estado de las entradas despues del proceso
//Envio solo de los leds rojos ya que con esos se trabajaran los estados
//estacionamiento
  int slotR1 = digitalRead(13);
  int slotR2 = digitalRead(33);
  int slotR3 = digitalRead(21);
  int slotR4 = digitalRead(5);
//Envio de valores de los leds
  myData.slotR1 = slotR1;
  myData.slotR2 = slotR2;
  myData.slotR3 = slotR3;
  myData.slotR4 = slotR4;

  
  delay(100); // Wait for 100 millisecond(s)

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
  delay(100);  
}

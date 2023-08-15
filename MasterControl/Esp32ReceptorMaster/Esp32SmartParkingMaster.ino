#include <WiFi.h>
#include <WebServer.h>
#include <esp_now.h>
#include <WiFi.h>
#include <ESP32_Servo.h>

//Sensor Ultrasonico 5
int v5 = 23;//DECLARACION DE LOS LEDS
int a5 = 22;//DECLARACION DE LOS LEDS
int r5 = 21;//DECLARACION DE LOS LEDS
int echoPin5 = 18;//DECLARACION DE PUERTO ECHO
int triggerPin5 = 19;//DECLARACION DE PUERTO TRIGGER
long ultrason5 = 0;

//Distancia sensor ultrasonico 5
long readUltrasonicDistance5(int triggerPin5, int echoPin5)
{
  pinMode(triggerPin5, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin5, LOW);//LECTURA DEL PUERTO TRIGGER 
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin5, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin5, LOW);//LECTURA DEL PUERTO TRIGGER 
  pinMode(echoPin5, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds *0.01723
  return (pulseIn(echoPin5, HIGH)*0.01723);
  
}

//Sensor Ultrasonico 6
int v6 = 25;//DECLARACION DE LOS LEDS
int a6 = 26;//DECLARACION DE LOS LEDS
int r6 = 27;//DECLARACION DE LOS LEDS
int echoPin6 = 15;//DECLARACION DE PUERTO ECHO
int triggerPin6 = 2;//DECLARACION DE PUERTO TRIGGER
long ultrason6 = 0;

//Distancia sensor ultrasonico 6
long readUltrasonicDistance6(int triggerPin6, int echoPin6)
{
  pinMode(triggerPin6, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin6, LOW);//LECTURA DEL PUERTO TRIGGER 
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin6, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin6, LOW);//LECTURA DEL PUERTO TRIGGER 
  pinMode(echoPin6, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds *0.01723
  return (pulseIn(echoPin6, HIGH)*0.01723);
  
}

String estadoSlot1;
String estadoSlot2;
String estadoSlot3;
String estadoSlot4;
String estadoSlot5;
String estadoSlot6;


Servo servo1; 
int servoPin = 14;
int pos = 0; 
int c = 13;
int salida = 12;
int entrada = 13;
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
const char* ssid = "SmartParking";      // Nombre de la red Wi-Fi creada por el ESP32
const char* password = "123456789";  // Contraseña para la red Wi-Fi creada por el ESP32

WebServer server(80);

void setup() {
  Serial.begin(115200);
  //Salidas leds Slot 5
  pinMode(v5, OUTPUT);//SALIDA DEL LED 
  pinMode(a5, OUTPUT);//SALIDA DEL LED 
  pinMode(r5, OUTPUT);//SALIDA DEL LED 

  //Salidas leds Slot 6
  pinMode(v6, OUTPUT);//SALIDA DEL LED 
  pinMode(a6, OUTPUT);//SALIDA DEL LED 
  pinMode(r6, OUTPUT);//SALIDA DEL LED 

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


  // Configurar el ESP32 como punto de acceso------
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Dirección IP del Punto de Acceso: ");
  Serial.println(myIP);

  // Configuración de las rutas en el servidor web
  server.on("/", handleRoot);
  server.on("/led", handleLed);

  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
    //Revision lugar de estacionamiento 5
  ultrason5 =readUltrasonicDistance5(19, 18);

 if (ultrason5 > 12) {
    digitalWrite(v5, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(a5, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r5, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason5 <= 8 && ultrason5 > 4) {
    digitalWrite(v5, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a5, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(r5, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason5 <= 4) {
    digitalWrite(v5, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a5, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r5, HIGH);// LECRURA DIGITAL DEL LED 
  }

  //Revision lugar de estacionamiento 6
  ultrason6 =readUltrasonicDistance6(2, 15);
  
 if (ultrason6 > 12) {
    digitalWrite(v6, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(a6, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r6, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason6 <= 8 && ultrason6 > 4) {
    digitalWrite(v6, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a6, HIGH);// LECRURA DIGITAL DEL LED 
    digitalWrite(r6, LOW);// LECRURA DIGITAL DEL LED 
  }
  if (ultrason6 <= 4) {
    digitalWrite(v6, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(a6, LOW);// LECRURA DIGITAL DEL LED 
    digitalWrite(r6, HIGH);// LECRURA DIGITAL DEL LED 
  }
  
  server.handleClient(); // Manejo de solicitudes del servidor web
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

void handleRoot() {
  //--------SLOT 1 ----------------------
  int recepSlot1 = myData.slotR1;
  if(recepSlot1 == 1){
    estadoSlot1 = "Ocupado";
  }else{
    estadoSlot1 ="Disponible";
  }
  //---------SLOT 2----------------------
  int recepSlot2 = myData.slotR2;
  if(recepSlot2 == 1){
    estadoSlot2 = "Ocupado";
  }else{
    estadoSlot2 ="Disponible";
  }
    //---------SLOT 3----------------------
  int recepSlot3 = myData.slotR3;
  if(recepSlot3 == 1){
    estadoSlot3 = "Ocupado";
  }else{
    estadoSlot3 ="Disponible";
  }

  //---------SLOT 4----------------------
  int recepSlot4 = myData.slotR4;
  if(recepSlot4 == 1){
    estadoSlot4 = "Ocupado";
  }else{
    estadoSlot4 ="Disponible";
  }
  //---------SLOT 5----------------------
  if(r5 == 1){
    estadoSlot5 = "Ocupado";
  }else{
    estadoSlot5 ="Disponible";
  }
  //---------SLOT 6----------------------
  if(r6 == 1){
    estadoSlot6 = "Ocupado";
  }else{
    estadoSlot6 ="Disponible";
  }
  // Página de inicio con la tabla para mostrar el estado del LED
  String html = "<html><body>";
  html += "<h1>Smart Parking</h1>";
  html += "<table border='1'>";
  html += "<tr><th>Espacio</th><th>Estado</th></tr>";
  html += "<tr><td>Slot 1</td><td id='slot1'>" + String(estadoSlot1) + "</td></tr>";
  html += "<tr><td>Slot 2</td><td id='slot2'>" + String(estadoSlot2) + "</td></tr>";
  html += "<tr><td>Slot 3</td><td id='slot3'>" + String(estadoSlot3) + "</td></tr>";
  html += "<tr><td>Slot 4</td><td id='slot4'>" + String(estadoSlot4) + "</td></tr>";
  html += "<tr><td>Slot 5</td><td id='slot5'>" + String(estadoSlot5) + "</td></tr>";
  html += "<tr><td>Slot 6</td><td id='slot6'>" + String(estadoSlot6) + "</td></tr>";
  html += "</table>";
  html += "<script>function updateTable() {var xhttp = new XMLHttpRequest();xhttp.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {var values = this.responseText.split(',');document.getElementById('slot1').innerHTML = values[0];document.getElementById('slot2').innerHTML = values[1];document.getElementById('slot3').innerHTML = values[2];document.getElementById('slot4').innerHTML = values[3];document.getElementById('slot5').innerHTML = values[4];document.getElementById('slot6').innerHTML = values[5];}};xhttp.open('GET', '/led', true);xhttp.send();}setInterval(updateTable, 1000);</script>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleLed() {
  // Respuesta con el nuevo estado de los slots
  String response = String(estadoSlot1) + "," + String(estadoSlot2) + "," + String(estadoSlot3) + "," + String(estadoSlot4) + "," + String(estadoSlot5) + "," + String(estadoSlot6);
  server.send(200, "text/plain", response);
}


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
float gyx;
float gyy;
float gyz;
bool state, state2, state3;
Adafruit_MPU6050 mpu;
WiFiManager wifiManager;
WiFiClient client;
HTTPClient http;
char auth[] = "urtepnRcq94VQjS5YXEC3AowJb6VLMBx"; //Enter your Blynk application auth token
char ssid[] = "Redmi Note 11_2022"; //Enter your WIFI name
char pass[] = "himank004"; //Enter your WIFI passowrd

void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");
  HTTPClient http;
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
  wifiManager.autoConnect("esp", "1234567890");

}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  gyy=a.acceleration.y;
  gyx=a.acceleration.x;
  gyz=g.gyro.z;

  if (gyy>3) {
    state=0;
    http.begin(client,"http://blr1.blynk.cloud/external/api/update?token=urtepnRcq94VQjS5YXEC3AowJb6VLMBx&V0=1");
    // Serial.println("Forward");
    http.GET();
    // Blynk.virtualWrite(V0, HIGH);
    Serial.println("Forward");
  }
  else if (gyy<3 &&  gyy>-5 ) {
    if (state==0){
    http.begin(client,"http://blr1.blynk.cloud/external/api/update?token=urtepnRcq94VQjS5YXEC3AowJb6VLMBx&V0=0");
    http.GET();
    http.begin(client,"http://blr1.blynk.cloud/external/api/update?token=urtepnRcq94VQjS5YXEC3AowJb6VLMBx&V3=0");
    http.GET();
    state=1;
    // Blynk.virtualWrite(V0, LOW);
    // Blynk.virtualWrite(V3, LOW);
    Serial.println("Center");
    }
  }
  else if (gyy<-5){
    state=0;
    http.begin(client,"http://blr1.blynk.cloud/external/api/update?token=urtepnRcq94VQjS5YXEC3AowJb6VLMBx&V3=1");
    http.GET();
    // Blynk.virtualWrite(V3, HIGH);
    Serial.println("Back");
  }
  if (gyx>5) {
    state2=0;
    http.begin(client,"http://blr1.blynk.cloud/external/api/update?token=urtepnRcq94VQjS5YXEC3AowJb6VLMBx&V1=1");
    http.GET();
    // Blynk.virtualWrite(V2, HIGH);
    Serial.println("Right");
  }
  else if (gyx<5 &&  gyx>-3 ) {
    if (state2==0){
    http.begin(client,"http://blr1.blynk.cloud/external/api/update?token=urtepnRcq94VQjS5YXEC3AowJb6VLMBx&V2=0");
    http.GET();
    http.begin(client,"http://blr1.blynk.cloud/external/api/update?token=urtepnRcq94VQjS5YXEC3AowJb6VLMBx&V1=0");
    http.GET();
    // Blynk.virtualWrite(V2, LOW);
    // Blynk.virtualWrite(V1, LOW);
    state2=1;
    Serial.println("Center");
    }
  }
  else if (gyx<-3){
    state2=0;
    http.begin(client,"http://blr1.blynk.cloud/external/api/update?token=urtepnRcq94VQjS5YXEC3AowJb6VLMBx&V2=1");
    http.GET();
    // Blynk.virtualWrite(V1, HIGH);
    Serial.println("Left");
  }

  if(gyz>1.8){
    http.begin(client,"http://blr1.blynk.cloud/external/api/update?token=urtepnRcq94VQjS5YXEC3AowJb6VLMBx&V6=1");
    http.GET();
    state3=0;
    // Blynk.virtualWrite(V5, HIGH);
  }
  else if (gyz<-1.8){
    if(state3==0){
    http.begin(client,"http://blr1.blynk.cloud/external/api/update?token=urtepnRcq94VQjS5YXEC3AowJb6VLMBx&V6=0");
    http.GET();
    state3=1;
    }
    // Blynk.virtualWrite(V5,LOW);
  }
}
/*
  Rui Santos
    http.GET();
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  
  Code compatible with ESP8266 Boards Version 3.0.0 or above 
  (see in Tools > Boards > Boards Manager > ESP8266)
*/

// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <WiFiClient.h>

// const char* ssid = "Redmi Note 11_2022";
// const char* password = "himank004";

// //Your Domain name with URL path or IP address with path
// String serverName = "http://blr1.blynk.cloud/external/api/update?token=urtepnRcq94VQjS5YXEC3AowJb6VLMBx&V0=1";

// // the following variables are unsigned longs because the time, measured in
// // milliseconds, will quickly become a bigger number than can be stored in an int.
// unsigned long lastTime = 0;
// // Timer set to 10 minutes (600000)
// //unsigned long timerDelay = 600000;
// // Set timer to 5 seconds (5000)
// unsigned long timerDelay = 5000;

// void setup() {
//   Serial.begin(115200); 

//   WiFi.begin(ssid, password);
//   Serial.println("Connecting");
//   while(WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.print("Connected to WiFi network with IP Address: ");
//   Serial.println(WiFi.localIP());
 
//   Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
// }

// void loop() {
//   // Send an HTTP POST request depending on timerDelay
//   if ((millis() - lastTime) > timerDelay) {
//     //Check WiFi connection status
//     if(WiFi.status()== WL_CONNECTED){
//       WiFiClient client;
//       HTTPClient http;

//       String serverPath = serverName;
      
//       // Your Domain name with URL path or IP address with path
//       http.begin(client, serverName);
  
//       // If you need Node-RED/server authentication, insert user and password below
//       //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
        
//       // Send HTTP GET request
//       int httpResponseCode = http.GET();
      
//       if (httpResponseCode>0) {
//         Serial.print("HTTP Response code: ");
//         Serial.println(httpResponseCode);
//         String payload = http.getString();
//         Serial.println(payload);
//       }
//       else {
//         Serial.print("Error code: ");
//         Serial.println(httpResponseCode);
//       }
//       // Free resources
//       http.end();
//     }
//     else {
//       Serial.println("WiFi Disconnected");
//     }
//     lastTime = millis();
//   }
// }
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiManager.h>
#include <Wire.h>

WiFiManager wifiManager;
 
//Motor PINs
#define rc D7
#define ra D8
#define la D3
#define lc D4
#define light D6

bool forward=false;
bool back=false;
bool left=false;
bool right=false;


//char auth[] = "urtepnRcq94VQjS5YXEC3AowJb6VLMBx"; //Enter your Blynk application auth token
char auth[] = "urtepnRcq94VQjS5YXEC3AowJb6VLMBx";
char ssid[] = "Redmik20"; //Enter your WIFI name
char pass[] = "123456789001"; //Enter your WIFI passowrd

BLYNK_WRITE(V0){  
  bool value1 = param.asInt();
  if (value1==1){
    // Blynk.virtualWrite(V5, HIGH);
  digitalWrite(rc, HIGH);
  digitalWrite(la, HIGH);
  }
  else{
    forward=false;
  digitalWrite(rc, LOW);
  digitalWrite(la, LOW); 
  }
}

BLYNK_WRITE(V1){  
  bool value1 = param.asInt();
  if (value1==1){
    left=true;
   digitalWrite(rc, HIGH);
  }
  else{
    left=false;
  digitalWrite(rc, LOW);
  }
}
BLYNK_WRITE(V2){  
  bool value1 = param.asInt();
  if (value1==1){
    right=true;
     digitalWrite(la, HIGH);
  }
  else{
    right=false;
  digitalWrite(la, LOW);

  }
}
BLYNK_WRITE(V3){  
  bool value1 = param.asInt();
  if (value1==1){
    back=true;
    digitalWrite(ra, HIGH);
  digitalWrite(lc, HIGH);
  }
  else{
    back=false;
  digitalWrite(ra, LOW);
  digitalWrite(lc, LOW);
}
}
BLYNK_WRITE(V5){  
  bool value1 = param.asInt();
  if (value1==1){
  digitalWrite(rc, HIGH);
  digitalWrite(lc, HIGH);

  }
  
  else{
  digitalWrite(rc, LOW);
  digitalWrite(lc, LOW);
  }
}

BLYNK_WRITE(V6){
  bool value1 = param.asInt();
  if(value1==1){
    Serial.println("ON");
    digitalWrite(light, HIGH);
  }
  else{
    Serial.println("Of");
    digitalWrite(light, LOW);
  }
}

void setup() {


  Serial.begin(115200);
  delay(1000);
  pinMode(la, OUTPUT);
  pinMode(ra, OUTPUT);
  pinMode(rc, OUTPUT);
  pinMode(lc, OUTPUT);
  pinMode(light, OUTPUT);
  wifiManager.autoConnect("esp", "1234567890");
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
    // pinMode(10, OUTPUT);
    // Blynk.begin(auth, ssid, pass);

}

void loop(){
  Blynk.run();
}
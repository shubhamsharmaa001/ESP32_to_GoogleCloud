
#if defined(ARDUINO_SAMD_MKR1000) or defined(ESP8266)
#define __SKIP_ESP32__
#endif

#if defined(ESP32)
#define __ESP32_MQTT_H__
#endif

#ifdef __SKIP_ESP32__

#include <Arduino.h>


void setup(){
  Serial.begin(115200);
}

void loop(){
  Serial.println("Hello World");
}

#endif

#ifdef __ESP32_MQTT_H__

#include "esp32-mqtt.h"
#include "esp_system.h"


const int wdtTimeout = 10000;  
hw_timer_t *timer = NULL;
char buf[3] = {0 ,0 ,0};
String Data= "";
int statu = 0;
bool pingStatus =0;

#define RXD2 16
#define TXD2 17

void IRAM_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(LED_BUILTIN, OUTPUT);

   timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);  //attach callback
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //set time in us
  timerAlarmEnable(timer);                          //enable interrupt
// WiFi.disconnect();
  setupCloudIoT();
 
  
   while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
}

unsigned long lastMillis = 0;
unsigned long lastMillis1 = 0;
void loop() {
  
 timerWrite(timer, 0);

 // receive 3 byte data
  while (Serial2.available()) {
    //Serial.print(char(Serial2.read()));
    buf[0] = char(Serial2.read());
    buf[1] = char(Serial2.read());
    buf[2] = char(Serial2.read());

   
  }
   // compare checksum
  if( buf[2] == buf[0] + buf[1] && Data.length()<2 )
   {
     Data += buf[0];
     Data += buf[1];
     Serial.print(buf[0]);
     Serial.print(buf[1]);
     buf[0] = 0;
     buf[1] = 0;
     buf[2] = 9;
     Serial.print(Data.length());
      
   
   }
  mqtt->loop();
  delay(10);  

  if (!mqttClient->connected()) {
    connect();
    Serial.print("Error");
  }


  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
           //publish data to google cloud
    statu =  publishTelemetry(getDataJSON());
    Data.clear();
    
    if(statu == 1 && pingStatus == 1)
    {
     Serial2.write(0x01);
     Serial.println('1');
     statu = 0;
    }else
    {
      Serial.println('0');
     Serial2.write(0x00);
    }
   
  }

   if (millis() - lastMillis1 > 10000) {
    lastMillis1 = millis();
    
    bool success = Ping.ping("www.google.com", 3);
 
    if(!success){
    Serial.println("Ping failed");
    pingStatus = 0;
    return;
    }else{
     pingStatus = 1;
    Serial.println("Ping succesful.");
    }
    }
}
#endif

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "SSD1306.h"

void ChangeWifi()
{
  Serial.begin(115200);
  display.init();         
  display.flipScreenVertically();
  
  display.setColor(WHITE);
  display.clear();
   HTTPClient http;    //Declare object of class HTTPClient
    DynamicJsonBuffer jsonBuffer;
   
    //http.begin("http://dataservice.accuweather.com/currentconditions/v1/202439?apikey=GYpocjiLIX4Vb9RLeArUSc9jsDXY5Bku&details=true");
    //http.begin("http://dataservice.accuweather.com/locations/v1/cities/search?apikey=GYpocjiLIX4Vb9RLeArUSc9jsDXY5Bku&q=Mumbai");
    http.begin("http://api.thingspeak.com/channels/319597/feeds.json?api_key=NP1EDHJZH4TNSDEU&results=1");
     delay(200);
     int httpCode = http.GET(); //Send the request
     String payload = http.getString();   
     //Serial.println(httpCode);   //Print HTTP return code 200 correct data 401 invalid data  404 Error
     //Serial.println(payload);    //Print request response payload
     JsonObject& root = jsonBuffer.parseObject(payload);
   
       if(!root.success()){
             Serial.println("Nope");
              }
  
            else{
              
              JsonArray& feeds = root["feeds"];
              JsonObject& feeds1 = feeds[0];
                          
              const char* ssid = feeds1["field1"];
              const char* password = feeds1["field2"];
              Serial.println(ssid);
              Serial.println(password);
              WiFi.begin(ssid,password);
               while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
                  delay(500);
                    Serial.print(".");

                   }
                  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
                    Serial.println("WiFi Connected....");
                    Serial.println(ssid);
                          }
                if (mdns.begin("esp8266", WiFi.localIP())) {
                Serial.println("MDNS responder started");
    

  }
 
    server.begin();
              
              
              }
}

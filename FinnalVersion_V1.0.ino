#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>
#include <ArduinoJson.h>

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial);
SoftwareSerial mySerial(13,15); // This is the RX TX pin connection on NodeMcu PINS. See NodeMcu For pin connection diagram from google. 
MDNSResponder mdns;


const char* ssid = "Vistaura";
const char* password = "taneja1993";

ESP8266WebServer server(80);
uint8_t id;
 // Below are bunch of variable, some gets used but most now dont as we are not using Fingerprint. 
uint8_t getFingerprintEnroll();
int F=0,R=0;
char c;
String ok="";
String ok1="";
String BIBI="";
String bibi="";
String webPage = "";
String webPage2 = "";
String block1 = "Welcome";
String block2="";
String block3="";
String Refresh ="";
String data ="";
int k=0,l,j=0;
int ReadingOne[5];


void setup(void){
  attachInterrupt(digitalPinToInterrupt(2),RFID, RISING);
  delay(1000);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
 server.on("/", [](){
  
           server.send(200, "text/plain", block1);
           delay(100);
         
  });
  server.on("/socket1", [](){  // Here when you hit on NodeMcu IP followed by the name 'socket1' what is in this block gets executed. eg. 192.168.225.28/socket1
    if(l>=1){
       server.send(200, "text/html", webPage2);
    }
    else{
       server.send(200, "text/html", webPage); 
    }
 
 });
    server.on("/reading", [](){
       server.send(200, "text/html", bibi); 
       ok="";
       bibi="";
     });

  server.on("/socket2L5R", [](){
    server.send(200, "text/html", data);
    });

  server.begin();
  Serial.println("HTTP server started");

}

void loop(){
 server.handleClient();  // This can't be omitted. 
}

void RFID(){
    mySerial.begin(9600);
     c = mySerial.read();  // This function reads RFID Card details into 'c'
   if(isAlphaNumeric(c)){ // Here it gets filtered and only letters and number gets thorugh
    Serial.print(c);
     ok+=c;  
     }
     
   String first1="{\"card\":\"";
   String first2="\"}";
   String fin=first1+ok+first2;  // Forms one combine string in the Json Format.  {"card":"012345678ABCD"}
   //Serial.print(fin);
   HTTPClient http;    //Declare object of class HTTPClient
   
   DynamicJsonBuffer jBuffer;
 //  root["card"] = "newcard1234567890";
 //  String req = "{\"card\":\"newcard1234567890\"}";   
   http.begin("http://192.168.1.111:3000/api/register/VISTAURA-HR0003/card");      //Specify request destination
   http.addHeader("Content-Type", "application/json");  //Specify content-type header
   
   int httpCode = http.POST(fin);   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection*/
   // Serial.print(c);
  // Serial.println(fin);
   
}



void Checker(int p){
  if(p==200){
    // Success
  }
  else if(p==401){
    //invalid 
  }
  else{
    //Error
  }
}


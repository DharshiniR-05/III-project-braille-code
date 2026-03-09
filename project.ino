#include <stdio.h> 
#include <conio.h> 
#include <ESP3266WiFi.h> 
WiFiClient client; WiFiServer server(80); const char* ssid = "iot"; const char* password = "1234567890"; 
String  command =""; // Command received from Android device 
// Set Motor Control Pins 
int rightMotor2 = 13;    // D7 - right Relay- int rightMotor1 = 15;    // D8 - right Relay + int leftRelay2 = 0;    // D3 - left Relay -  int leftRelay1 = 2;    // D4 - left Relay + int eneLeftRelay = 12;  // D6 - enable Relay Left int eneRightRelay = 14; // D5 - enable Relay Right int relaySpeed = 255; // Set the default speed (0-255) void setup() 
{ 
  Serial.begin(115200);   pinMode(eneLeftRelay, OUTPUT);    pinMode(eneRightRelay, OUTPUT);    pinMode(leftRelay1, OUTPUT);    pinMode(leftRelay2, OUTPUT);     pinMode(rightRelay1, OUTPUT);     pinMode(rightRelay2, OUTPUT);     digitalWrite(eneLeftRelay,LOW);   digitalWrite(eneRightRelay,LOW);   digitalWrite(leftRelay1,LOW);   digitalWrite(leftRelay2,LOW);   digitalWrite(rightRelay1,LOW);   digitalWrite(rightRelay2,LOW);         connectWiFi();   server.begin(); 
} void loop() 
{ 
    client = server.available();     if (!client) return;      command = checkClient ();     Serial.println(command); 
         if (command == "on" || command == "frente" || command == "a frente")  onRelay(); 
    else if (command == "reverse" || command == "reverso"|| command == 
"voltar") reverseRelay(); 
    else if (command == "left"    || command == "esquerda") leftRelay();         else if (command == "right"   || command == "direita") rightRelay();          else if (command == "stop"    || command == "pare" || command == "parar" || command == "parando")     stopRelay();      
         sendBackEcho(command); // send command echo back to android device     command = "";    
}  
/* command relay on */ void onRelay(void)    
{ 
  analogWrite(eneLeftRelay, 150);   analogWrite(eneRightRelay, 150); 
     
  digitalWrite(leftRelay1,HIGH);   digitalWrite(leftRelay2,LOW);   digitalWrite(rightRelay1,HIGH);   digitalWrite(rightRelay2,LOW); 
} 
/* command relay backward */ void reverseRelay(void)    
{ 
  analogWrite(eneLeftRelay, 150);   analogWrite(eneRightRelay, 150);    digitalWrite(leftRelay1,LOW); digitalWrite(leftRelay2,HIGH); digitalWrite(rightRelay1,LOW); digitalWrite(rightRelay2,HIGH); 
} 
/* command relay turn left */ void leftRelay(void)    
{ 
  analogWrite(eneLeftRelay, 150);   analogWrite(eneRightRelay, 150);      digitalWrite(leftRelay1,LOW);   digitalWrite(leftRelay2,HIGH);   digitalWrite(rightRelay1,HIGH);   digitalWrite(rightRelay2,LOW); 
} 
/* command relay turn right */ void rightRelay(void)    
{ 
  analogWrite(eneLeftRelay, 150);   analogWrite(eneRightRelay, 150);     digitalWrite(leftRelay1,HIGH);   digitalWrite(leftRelay2,LOW);   digitalWrite(rightRelay1,LOW);   digitalWrite(rightRelay2,HIGH); 
} 
/* command relay stop */ void stopRelay(void)    
{  
analogWrite(eneLeftRelay, 0); analogWrite(eneRightRelay, 0); digitalWrite(leftRelay1,LOW);   digitalWrite(leftRelay2,LOW);   digitalWrite(rightRelay1,LOW);   digitalWrite(rightRelay2,LOW); 
} 
/* connecting WiFi */ void connectWiFi() 
{ 
  Serial.println("Connecting to WIFI");   WiFi.begin(ssid, password);   while ((!(WiFi.status() == WL_CONNECTED))) 
  {     delay(300); 
    Serial.print(".."); 
  } 
  Serial.println(""); 
  Serial.println("WiFi connected"); 
  Serial.println("NodeMCU Local IP is : "); 
  Serial.print((WiFi.localIP())); 
} 
/* check command received from Android Device */ 
String checkClient (void) 
{ 
  while(!client.available()) delay(1);  
  String request = client.readStringUntil('\r'); request.remove(0, 5); request.remove(request.length()-9,9); return request; 
} 
/* send command echo back to android device */ void sendBackEcho(String echo) 
{ 
  client.println("HTTP/1.1 200 OK");   client.println("Content-Type: text/html");   client.println(""); 
  client.println("<!DOCTYPE HTML>");   client.println("<html>");   client.println(echo);   client.println("</html>");   client.stop();   delay(1); 
} 
 
 
 

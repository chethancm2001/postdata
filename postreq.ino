#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 


const char* ssid = "Hacker"; 
const char* password = "chethan@123"; 
const char* host = "http://connected-things.herokuapp.com";  
String url = "/post"; 
int leddata = 90;



void setup() 
{ 
pinMode(D0,INPUT);
pinMode(D1,INPUT);
pinMode(A0,INPUT);
Serial.begin(115200); 
delay(10); 
Serial.println(); 
Serial.println();
Serial.print("Connecting to "); 
Serial.println(ssid); 
WiFi.mode(WIFI_STA); 
WiFi.begin(ssid, password); 
while (WiFi.status() != WL_CONNECTED) 
{ 
delay(500); 
Serial.print("."); 
} 
Serial.println(""); 
Serial.println("WiFi connected"); 
Serial.println("IP address: "); 
Serial.println(WiFi.localIP()); 
} 



void loop() 
{ 
int firedata = digitalRead(D0);
int gasdata = !(digitalRead(D1));
int waterdata = analogRead(A0);
if(waterdata>100){
  waterdata = 1;
  }
  else{
    waterdata = 0;
  }


Serial.print("firedata=");
Serial.println(firedata);
Serial.print("gasdata=");
Serial.println(gasdata);
Serial.print("waterdata=");
Serial.println(waterdata);
Serial.print("waterdata=");
Serial.println(waterdata);

delay(500); 
Serial.print("connecting to "); 
Serial.println(host);  
WiFiClient client; 
const int httpPort = 80; 

if (!client.connect(host, httpPort)) 
{ 
Serial.println("connection failed"); 
return; 
} 
String var1= "fire=";
String var2=String(firedata);
String var3= "water=";
String var4=String(waterdata);
String var5= "gas=";
String var6= String(gasdata);
String var7="led=";
String var8=String(leddata);

Serial.print("Requesting URL: "); 
Serial.println(url); //Post Data 

String postData = var1 + var2+"&"+ var3 + var4+"&"+ var5 + var6+"&"+ var7+var8;
String address = host + url; 

HTTPClient http;
http.begin(client,address); 
http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
auto httpCode = http.POST(postData); 
delay(2000);
Serial.println(httpCode);
String payload = http.getString(); 
Serial.println(payload); 
http.end();
Serial.println("closing connection"); 

Serial.println("delay of 5 sec"); 
delay(3000);
}

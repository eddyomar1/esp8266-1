#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  while ((WiFiMulti.run() != WL_CONNECTED)) {
    delay(500);
  }


}

void loop() {

String datos_a_enviar = "ide=1";

HTTPClient https;
WiFiClientSecure newSecure;
newSecure.setInsecure();
https.begin(newSecure, "https://pruevaesp.000webhostapp.com");
//int checkBegin = https.begin(newSecure, "raw.githubusercontent.com", 443, "/coder137/TM4C123G/master/.gitattributes", false);


int code = https.POST(datos_a_enviar);
String payload = https.getString();
Serial.println(code);
Serial.println(payload);

// !
https.end();
newSecure.stop();



delay(2000);
}

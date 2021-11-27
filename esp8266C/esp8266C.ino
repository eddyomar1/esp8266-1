#include <ESP8266WiFi.h>
#include <WiFiManager.h>

const char* host = "192.168.43.110";

int ledPin = 2;

String ide = "1";

String payload;


void setup() {
  Serial.begin(115200); //Iniciamos comunicación serial
  delay(1000);
  
  pinMode(ledPin, OUTPUT);  //Pin del Led como salida
  digitalWrite(ledPin, LOW);  //Ponemos la salida de led en bajo
   
 
    Serial.begin(115200);
    
    WiFiManager wm;

    bool res;
    res = wm.autoConnect("Prueba Wifi con ESP8266"); 

    if(!res) {
        Serial.println("Failed to connect");
    } 
    else {
        Serial.println("connected...yeey :)");
       
    }
WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP

 
  //Mientras se conecta se imprimiran puntos
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi Conectado");
    
}
 
void loop() {
  
  WiFiClient client;
   
  Serial.printf("\n[Conectando a %s ... ", host);  //Establecemos la conexión con el servidor
  if (client.connect(host, 80))
  {
    Serial.println("conectado]");
    Serial.println("[Enviando peticion]");         //Enviamos la petición de datos




client.print(String("GET http://192.168.43.110?") + 
                          ("&ide=") + ide +
                          " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");




delay(10);

  Serial.println("[Respuesta:]");  //Leemos la respuesta del servidor
  while (client.connected())
  {
    if (client.available())
    {
     String payload = client.readStringUntil('\n');
           Serial.println(payload);
/**/if(payload.indexOf("high") != -1){
  digitalWrite(ledPin, HIGH);
  Serial.print("el led esta encendido");
  }

if(payload.indexOf("low") != -1){
  digitalWrite(ledPin, LOW);
  Serial.print("el led esta Apagado");
  }
/**/ 
 
    }
    
  }

  client.stop();                   //Finalizamos la conexión con el servidor
  Serial.println("\n[Desconectado]");
  delay(1);

  }
  
  else
  {
    Serial.println("conexion con el servidor no lograda!]");
    client.stop();
  }
  delay(5000);
   
}

 

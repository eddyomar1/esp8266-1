
/*
pinMode(3, OUTPUT);
pinMode(1, OUTPUT);
pinMode(0, OUTPUT);
pinMode(2, OUTPUT);
*/
int v = 0;

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "*_*";
const char* password =  "";
int ledPin = 2;
String code = "1" ; 

void setup() {
  pinMode(0, INPUT);
    pinMode(2, OUTPUT);
  delay(10);
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.print(".");
  }

  Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());

}

void loop() {

  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
WiFiClientSecure client;

    HTTPClient https;
client.setInsecure();

      v = digitalRead(0);
String datos_a_enviar = "ide=1";
String dsp = "ide="+code+v;     //String dsp = "ide="+code+"listo";


         Serial.println(v);
    https.begin(client, "https://pruevaesp.000webhostapp.com");  //ten en cuenta el SSL-- hemm... ya no se usa, ahora es TLS-- prueva las direcciones especificas -- https://ioticos.org/esp-post.php    //Indicamos el destino
    https.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Preparamos el header text/plain si solo vamos a enviar texto plano sin un paradigma llave:valor.

    int codigo_respuesta = https.POST(datos_a_enviar);   //Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)

    if(codigo_respuesta>0){
      Serial.println("▼▼▼");
      Serial.println("Código HTTP ► " + String(codigo_respuesta));   //Print return code

      if(codigo_respuesta == 200){
        String cuerpo_respuesta = https.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);


if(cuerpo_respuesta.indexOf("high") != -1){
  digitalWrite(ledPin, HIGH);
  Serial.println("el led esta encendido");
  
  delay(10);


    https.end();

delay(100);
    
https.begin(client, "https://pruevaesp.000webhostapp.com");
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
      int sp = https.POST(dsp);
  Serial.println("segundo Código HTTP ► " + String(sp));
  Serial.println(https.getString());

  }

else if(cuerpo_respuesta.indexOf("low") != -1){
  digitalWrite(ledPin, LOW);
  Serial.println("el led esta Apagado");

  delay(10);


    https.end();

delay(100);
    
https.begin(client, "https://pruevaesp.000webhostapp.com");
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
      int sp = https.POST(dsp);
  Serial.println("segundo Código HTTP ► " + String(sp));
  Serial.println(https.getString());

  

  }else if(cuerpo_respuesta.indexOf("listo") != -1){
  Serial.println("listo");
    
  }else{ Serial.print("algo salio mal");}

      }

    }else{
     Serial.print("Error enviando POST, código: ");
     Serial.println(codigo_respuesta);
    }

    https.end();  

  }else{ Serial.println("Error en la conexión WIFI"); }

   delay(2000);
}

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
//
const char* ssid = "*_*";
const char* password =  "";
int ledPin = 2;
String code = "1" ; 

void setup() {
  delay(10);
  Serial.begin(115200);

//
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

  //^^^Que es esto?^^^
    
    HTTPClient https;
//WiFiClientSecure newSecure;
client.setInsecure();
  //  String datos_a_enviar = "user=" + user + "&pass=" + pass;
      String datos_a_enviar = "ide=1";
String dsp = "ide="+code+"listo";
//String dspp = "&segundap=listo";
      
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
  
  delay(1000);
  //digitalWrite(ledPin, LOW);

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
  Serial.print("el led esta Apagado");

  delay(1000);
  //digitalWrite(ledPin, LOW);

    https.end();

delay(100);
    
https.begin(client, "https://pruevaesp.000webhostapp.com");
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
      int sp = https.POST(dsp);
  Serial.println("segundo Código HTTP ► " + String(sp));
  Serial.println(https.getString());

  

  }else if(cuerpo_respuesta.indexOf("listo") != -1){
  Serial.print("listo");
    
  }else{ Serial.print("algo salio mal");}




      }

    }else{

     Serial.print("Error enviando POST, código: ");
     Serial.println(codigo_respuesta);

    }

    https.end();  //libero recursos

  }else{

     Serial.println("Error en la conexión WIFI");

  }

   delay(2000);
}

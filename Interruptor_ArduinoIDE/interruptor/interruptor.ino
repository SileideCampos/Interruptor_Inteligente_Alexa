#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Espalexa.h>

#define button 16
#define rele 2
bool Status = 0;

const char* ssid = "colocar-o-nome-do-wifi";
const char* senha = "colocar-a-sua-senha-do-wifi";
unsigned int localPort = 3333;
char pacote[3];

IPAddress ip(192,168,2,10);         //Necessário alterar também
IPAddress gateway(192,168,2,1);     //Necessário alterar também
IPAddress subnet(255,255,255,0);    //Necessário alterar também

WiFiUDP conexao;
Espalexa alexa;

void setup() {
  Serial.begin(9600);
  pinMode(button, OUTPUT);
  pinMode(rele, OUTPUT);
  
  if (!WiFi.config(ip, gateway, subnet)) {
    Serial.println("Falha ao configurar STA");
  }
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,senha);
  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    Serial.println("Problema ao conectar!");
    delay(2000);
    WiFi.begin(ssid,senha);
  }
  Serial.println(WiFi.localIP());
  conexao.begin(localPort);

  alexa.addDevice("IOT", iotInterruptor);
  alexa.addDevice("Delphi", delphiInterruptor);
  alexa.begin();

  Serial.println("Setup Iniciado!");
}

void loop() {
  digitalWrite(rele, Status);

  if (pulseIn(button, HIGH)>0){
    delay(100);
    Status = !Status;
  }  
     
  int tamanhoPacote = conexao.parsePacket();
  if(tamanhoPacote == 3){
    String recebe;
    recebe = conexao.readString();    
    if (recebe == "OON"){
      Status = 0;
      conexao.beginPacket(conexao.remoteIP(), conexao.remotePort());
      conexao.print(Status);
      conexao.endPacket();      
    }else if (recebe == "OFF"){
      Status = 1;
      conexao.beginPacket(conexao.remoteIP(), conexao.remotePort());
      conexao.print(Status);
      conexao.endPacket();      
    }else if (recebe == "STS"){            
      conexao.beginPacket(conexao.remoteIP(), conexao.remotePort());
      conexao.print(Status);
      conexao.endPacket();
    }     
  }

  alexa.loop();

  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Sem acesso a rede. Reconectando...");
    WiFi.reconnect();
    delay(4000);
  }

}

void delphiInterruptor(uint8_t brilho) {  
  if (brilho) {    
    Serial.println("OON: "+brilho);
    Status = 0;
  } else {
    Serial.println("OFF");
    Status = 1;
  }
}

void iotInterruptor(uint8_t brilho) {  
  if (brilho) {    
    Serial.println("OON: "+brilho);
    Status = 0;
  } else {
    Serial.println("OFF");
    Status = 1;
  }
}

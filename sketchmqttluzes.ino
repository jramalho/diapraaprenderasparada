#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "teste";
const char* password = "12345670";

const char* mqttserver = "broker.hivemq.com";
int mqttserverport = 1883;
const char* mqttUser = "toto";
const char* mqttPassword = "toto";

int led1 = D0;
int led2 = D1;

String msg;

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  
  client.setServer(mqttserver, mqttserverport);
  client.setCallback(callback);
  
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESPtotoramalho", mqttUser, mqttPassword )) {
      Serial.println("connected"); 
    } else { 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
    client.publish("/diadeaprender/teste","Opa joaonathan?");
    client.subscribe("/diadeaprender/teste");
  
}

void callback(char* topic, byte* payload, unsigned int length) { 
  for (int i = 0; i < length; i++) { 
    msg += (char)payload[i];
  }
  if (msg == "00"){
    digitalWrite(led1,LOW);
  }
  if (msg == "01"){
    digitalWrite(led1,HIGH);
  }
  if (msg == "10"){
    digitalWrite(led2,LOW);
  }
  if (msg == "11"){
    digitalWrite(led2,HIGH);
  }
  
  msg = "";
}

void reconnect(){
  while(!client.connected()){
    client.connect("ESPtotoramalho", mqttUser, mqttPassword );
    client.subscribe("/diadeaprender/teste");
    client.setServer(mqttserver, mqttserverport);
  client.setCallback(callback);
  }
}


void loop() {
client.loop();
delay(100);
 if(!client.connected()){
    Serial.print("CAI");
  reconnect();
  }
}

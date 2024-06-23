#include <ESP8266WebServer.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTTYPE DHT11
#define DHTPIN 15
DHT dht(DHTPIN, DHTTYPE);


const char* ssid = "LETICIA OI FIBRA";
const char* password = "Leticia1107";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
float temperatura;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  if(strcmp(topic, "Semana") == 0){
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  switch ((char)payload[0]) {
    
    case '1':
      desligarTudo();
      ligarLuz();
      ligarExaustao();
      for (int i = 0; i < 70; i++) {
        i = i++;
        int umid = dht.readHumidity();
        float temp = dht.readTemperature();
        client.publish("Temperatura", String(temp).c_str());
        client.publish("Umidade", String(umid).c_str());
        if (temp > 35) {
          desligarCalor();
          ligarFrio();
        } else if (temp < 32) {
          desligarFrio();
          ligarCalor();
        }
        if (umid > 70) {
          ligarFrio();
        } else desligarFrio();
        delay(3000);
      }
      break;

    case '2':
      desligarTudo();
      ligarLuz();
      ligarExaustao();
      for (int i = 0; i < 70; i++) {
        i = i++;
        int umid = dht.readHumidity();
        float temp = dht.readTemperature();
        client.publish("Temperatura", String(temp).c_str());
        client.publish("Umidade", String(umid).c_str());
        if (temp > 32) {
          desligarCalor();
          ligarFrio();
        } else if (temp < 29) {
          desligarFrio();
          ligarCalor();
        }
        if (umid > 70) {
          ligarFrio();
        } else desligarFrio();
        delay(3000);
      }
      break;

    case '3':
      desligarTudo();
      ligarLuz();
      ligarExaustao();
      for (int i = 0; i < 70; i++) {
        i = i++;
        int umid = dht.readHumidity();
        float temp = dht.readTemperature();
        client.publish("Temperatura", String(temp).c_str());
        client.publish("Umidade", String(umid).c_str());
        if (temp > 29) {
          desligarCalor();
          ligarFrio();
        } else if (temp < 26) {
          desligarFrio();
          ligarCalor();
        }
        if (umid > 70) {
          ligarFrio();
        } else desligarFrio();
        delay(3000);
      }
      break;

    case '4':
      desligarTudo();
      ligarLuz();
      ligarExaustao();
      for (int i = 0; i < 70; i++) {
        i = i++;
        int umid = dht.readHumidity();
        float temp = dht.readTemperature();
        client.publish("Temperatura", String(temp).c_str());
        client.publish("Umidade", String(umid).c_str());
        if (temp > 26) {
          desligarCalor();
          ligarFrio();
        } else if (temp < 23) {
          desligarFrio();
          ligarCalor();
        }
        if (umid > 70) {
          ligarFrio();
        } else desligarFrio();
        delay(3000);
      }
      break;

    case '5':
      desligarTudo();
      ligarLuz();
      ligarExaustao();
      for (int i = 0; i < 70; i++) {
        i = i++;
        int umid = dht.readHumidity();
        float temp = dht.readTemperature();
        client.publish("Temperatura", String(temp).c_str());
        client.publish("Umidade", String(umid).c_str());
        if (temp > 23) {
          desligarCalor();
          ligarFrio();
        } else if (temp < 20) {
          desligarFrio();
          ligarCalor();
        }
        if (umid > 70) {
          ligarFrio();
        } else desligarFrio();
        delay(3000);
      }
      break;

    case '6':
      desligarTudo();
      ligarLuz();
      ligarExaustao();
      for (int i = 0; i < 70; i++) {
        i = i++;
        int umid = dht.readHumidity();
        float temp = dht.readTemperature();
        client.publish("Temperatura", String(temp).c_str());
        client.publish("Umidade", String(umid).c_str());
        if (temp > 20) {
          desligarCalor();
          ligarFrio();
        } else if (temp < 20) {
          desligarFrio();
          ligarCalor();
        }
        if (umid > 70) {
          ligarFrio();
        } else desligarFrio();
        delay(3000);
      }
      break;
      }
  }
  if(strcmp(topic, "Iluminacao") == 0){
    if((char) payload[0] == '1'){
      ligarLuz();
    }else if((char) payload[0] == '0'){
      desligarLuz();
    }
  }
  if(strcmp(topic, "Exaustao") == 0){
    if((char) payload[0] == '1'){
      ligarExaustao();
    }else if((char) payload[0] == '0'){
      desligarExaustao();
    }
  }
    if(strcmp(topic, "Refrigeracao") == 0){
    if((char) payload[0] == '1'){
      ligarFrio();
    }else if((char) payload[0] == '0'){
      desligarFrio();
    }
  }
    if(strcmp(topic, "Aquecimento") == 0){
    if((char) payload[0] == '1'){
      ligarCalor();
    }else if((char) payload[0] == '0'){
      desligarCalor();
    }
  }
}

void desligarTudo() {
  desligarExaustao();
  desligarFrio();
  desligarCalor();
  desligarLuz();
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("Semana");
      client.subscribe("Iluminacao");
      client.subscribe("Exaustao");
      client.subscribe("Refrigeracao");
      client.subscribe("Aquecimento");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}





//Exaustão
void ligarExaustao() {
  digitalWrite(13, HIGH);  //liga exaustores
}
void desligarExaustao() {
  digitalWrite(13, LOW);  //desliga exaustores
}

//Iluminação
void ligarLuz() {
  digitalWrite(14, HIGH);  //liga luzes
}
void desligarLuz() {
  digitalWrite(14, LOW);  //desliga luzes
}

//Aquecimento
void ligarCalor() {
  digitalWrite(33, HIGH);  //liga motor quente e resistência
}
void desligarCalor() {
  digitalWrite(33, LOW);  //desliga motor quente e resistência
}

//Refrigeração
void ligarFrio() {
  digitalWrite(27, HIGH);  //liga motores frio
  digitalWrite(25, HIGH);  //liga placa 1
  digitalWrite(12, HIGH);  //liga placa 2
}
void desligarFrio() {
  digitalWrite(25, LOW);  //desliga placa 1
  digitalWrite(12, LOW);  //desliga placa 2
  delay(4000);
  digitalWrite(27, LOW);  //desliga motores frio
}

void setup() {
  pinMode(14, OUTPUT);  //luz
  pinMode(13, OUTPUT);  //exaustão
  pinMode(33, OUTPUT);  //motor quente e resistência
  pinMode(27, OUTPUT);  //motores frio
  pinMode(12, OUTPUT);  //placa peltier 1
  pinMode(25, OUTPUT);  //placa peltier 2
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();





  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
}

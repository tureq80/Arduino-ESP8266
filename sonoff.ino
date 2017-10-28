#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "xxxxxxxx";
const char* password =  "xxxxxxx";
const char* mqttServer = "mqtt.server.com";
const int mqttPort = 1883;
const char* mqttUser = "login";
const char* mqttPassword = "passwd";



#define pirPin 14 // Input for HC-SR501

#define ledPin 13

int pirValue; // variable to store read PIR Value

int motionState = 0;

WiFiClient espClient;

PubSubClient client(espClient);

void setup() {

pinMode(pirPin, INPUT);

pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");

  }

Serial.println("Connected to the WiFi network");

 

client.setServer(mqttServer, mqttPort);

//client.setCallback(callback);

 

while (!client.connected()) {

   Serial.println("Connecting to MQTT...");
   if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected"); 
      digitalWrite(ledPin, HIGH); 
    } else {
      Serial.print("failed with state");
      Serial.print(client.state());
      digitalWrite(ledPin, LOW);
      delay(2000);
    }
  }
 // client.publish("esp/test", "jestem online");
}
void loop() {
  getPirValue(); 
  client.loop();
}

/***************************************************

 * Get PIR data

 **************************************************/
void getPirValue(void)
{
  pirValue = digitalRead(pirPin);
  if (pirValue != motionState) 
  { 
    motionState = pirValue;
    Serial.print(pirValue);
    String message = motionState ? "1" : "0";
    client.publish("sonoff/pir", String(message).c_str(), true);
  } 
}

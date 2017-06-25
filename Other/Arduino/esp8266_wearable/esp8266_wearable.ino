#include <ESP8266WiFi.h>
#include <b64.h>
#include <PubSubClient.h>

int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED = 16;   //  The on-board Arduion LED
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore. 
String msgString;

// Update these with values suitable for your network.
const char* ssid = "WiFi";
const char* password = "PASSWORD";
const char* mqtt_server = "ipconfig"; // http://www.hivemq.com/demos/websocket-client/ 212.72.72.12


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

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
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

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
      client.publish("p6/mqtt", "hello world");
      // ... and resubscribe
      client.subscribe("p6/mqtt");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED, OUTPUT);     // Initialize the 16 (BuiltIN-LED) pin as an output
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

  long now = millis();
  if (now - lastMsg > 16) {
    lastMsg = now;
    ++value;
    msgString = String(Signal);
    snprintf (msg, 75, "#%ld", Signal);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("p6/mqtt", msg);
  }

  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value. 
                                              // Assign this value to the "Signal" variable.
   Serial.println(Signal);                    // Send the Signal value to Serial Plotter.
   
   if(Signal > Threshold){                    // If the signal is above "550", then "turn-on" Arduino's on-Board LED.  
     digitalWrite(LED,HIGH);          
   } else {
     digitalWrite(LED,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }
delay(10);


  
}
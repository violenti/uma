#include <PubSubClient.h> //mqtt
#include "DHT.h"
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

const char* mqtt_server = "192.168.0.5";
int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 
const int button = 16;  // pin D0


WiFiClient espClient;
PubSubClient client(espClient);
long lastHumedad = 0;
char moisture[50];
char Temperature[50];
int value = 0;


#define DHTPIN 2     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors
DHT dht(DHTPIN, DHTTYPE);


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    // Attempt to connect
    if (client.connect("Uma")) {
      // Once connected, publish an announcement...
      // ... and resubscribe 
      Serial.print("OK connect \n");

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
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\n Starting");
  
  pinMode(button, INPUT);
  dht.begin();

  client.setServer("192.168.0.10", 1883);
  client.setCallback(callback); 
 
}

int readmoisture()
{

    val = analogRead(soilPin); //Read the SIG value form sensor 
    return val; //send current moisture value
    
}

float readtemp(){


  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  return(t);
  
}

void loop() {
    int Moisture = readmoisture();
    int temp = readtemp();

   //is configuration portal requested?
  if ( digitalRead(button) == LOW ) {
//    //WiFiManager
//    //Local intialization. Once its business is done, there is no need to keep it around
     WiFiManager wifiManager;
//
    if (!wifiManager.startConfigPortal("Uma")) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
     // reset and try again, or maybe put it to deep sleep
      ESP.reset();
      delay(5000);
    }

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }
    {
      if (!client.connected()) {
        reconnect();
    }
    
      client.loop();
      delay (20000);
         
          snprintf (moisture, 50, ":" "%ld",Moisture);
           Serial.print("Publish message: \n");
             client.publish("moisture", moisture);

              snprintf (Temperature, 50, ":" "%ld", temp);
                client.publish("Temperature", Temperature);


               


 

    
} 


}

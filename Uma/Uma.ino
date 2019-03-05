#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "DHT.h"
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager


int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 
const int button = 16;  // pin D0

#define DHTPIN 2     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors
DHT dht(DHTPIN, DHTTYPE);
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\n Starting");
  
  pinMode(button, INPUT);
  dht.begin();

 
}

int readSoil()
{

    val = analogRead(soilPin); //Read the SIG value form sensor 
    return val; //send current moisture value
    
}

float temp(){


  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  return(t);


  
}

  

void loop() {

   //is configuration portal requested?
  if ( digitalRead(button) == LOW ) {
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
     WiFiManager wifiManager;

    if (!wifiManager.startConfigPortal("Uma")) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.reset();
      delay(5000);
    }

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
      
      

  }


  // put your main code here, to run repeated

  //Serial.print("Soil Moisture = ");    
//get soil moisture value from the function below and print it
  //Serial.println(readSoil());
  Serial.println(temp());

  delay (20000);
  
 
  
} 

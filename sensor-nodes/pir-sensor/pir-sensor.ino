
/*
 * pir-sensor.ino
 * 
 * This sketch takes readings from a PIR sensor and sends them in a JSON payload
 * to the relayr Cloud via MQTT. These readings will afterwards trigger actions
 * on the Sonos speakers via the local API.
 * 
 * Website : https://github.com/chronoclast/sensational-sonos-sensor-synchronization
 * Authors : Emelie Hofland (emelie_hofland@hotmail.com)
 *           Jaime González-Arintero (a.lie.called.life@gmail.com)
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

//Have a look at the onboarding tutorial at the relayr Github:
//https://github.com/relayr/ESP8266_Arduino


//Libraries used: To be added manually on the Arduino IDE!
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


//WiFi credentials: 2.4GHz networks only!
//Avoid long SSIDs and passwords, and use preferably only letters and numbers
#define SSID "INTRODUCE_YOUR_WIFI_SSID_HERE"
#define PASSWORD "INTRODUCE_YOUR_WIFI_PASSWORD_HERE"


//Credentials from the developer dashboard
#define DEVICE_ID "INTRODUCE_YOUR_DEVICE_ID_HERE"
#define MQTT_USER "INTRODUCE_YOUR_MQTT_USER_HERE"
#define MQTT_PASSWORD "INTRODUCE_YOUR_MQTT_PASSWORD_HERE"
#define MQTT_CLIENTID "INTRODUCE_YOUR_MQTT_CLIENT_HERE" //It can be anything else
#define MQTT_TOPIC "INTRODUCE_YOUR_MQTT_TOPIC_HERE"
#define MQTT_SERVER "mqtt.relayr.io"


//This specifies the pin used for the presence sensor
#define PRESENCE_SENSOR_PIN D0


//This creates the WiFi client and the pub-sub client instance
WiFiClient espClient;
PubSubClient client(espClient);


//Some definitions, including the publishing period
//If the LED doesn't work, try changing "BUILTIN_LED" for "D0" or "D4"
const int led = BUILTIN_LED;
boolean ledState = LOW;
unsigned long lastPublishTime = 0;
unsigned long lastBlinkTime = 0;
int publishingPeriod = 1000;


//Function prototypes
void setup_wifi();
void mqtt_connect();
void publish();


//Setup function
void setup()
{
  //Initializing pins
  pinMode(PRESENCE_SENSOR_PIN, INPUT);
  pinMode(led, OUTPUT);

  //Initializing the serial port
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Hello there, I'm setting this up...");


  //Initializing the WiFi and the MQTT
  setup_wifi();
  client.setServer(MQTT_SERVER, 1883);
  

  //200ms is the minimum publishing period
  publishingPeriod = publishingPeriod > 200 ? publishingPeriod : 200;
  mqtt_connect();
}




//------------------------------------------------------------------------------------//
// This function connects to the WiFi network, and prints the current IP address      //
//------------------------------------------------------------------------------------//

void setup_wifi() {
  delay(10);
  
  //Trying to connect to the WiFi network
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}




//------------------------------------------------------------------------------------//
// This function establishes the connection with the MQTT server                      //
//------------------------------------------------------------------------------------//

void mqtt_connect()
{
  Serial.println("");
  Serial.println("Connecting to MQTT server...");
  
  if (client.connect(MQTT_CLIENTID, MQTT_USER, MQTT_PASSWORD))
  {
    Serial.println("Connection successful!");
  }

  else
  {
      Serial.println("Connection failed! Check your credentials or the WiFi network.");
      //This reports the error code
      Serial.println("rc = ");
      Serial.print(client.state());
      //And it tries again in 5 seconds
      Serial.println("Retrying in 5 seconds...");
      delay(5000);
  }
}




//------------------------------------------------------------------------------------//
// This is for the LED to blink                                                       //
//------------------------------------------------------------------------------------//

void blink(int interval)
{
  if (millis() - lastBlinkTime > interval)
  {
    //Save the last time you blinked the LED
    lastBlinkTime = millis();
    
    if (ledState == LOW)
      ledState = HIGH;
      
    else
      ledState = LOW;
      
    //Set the LED with the ledState of the variable:
    digitalWrite(led, ledState);
  }
}




//------------------------------------------------------------------------------------//
// This is the MAIN LOOP, it's repeated until the end of time! :)                     //
//------------------------------------------------------------------------------------//

void loop()
{
  //If we're connected, we can send data...
  if (client.connected())
  {
    client.loop();
    //Publish within the defined publishing period
        if (millis() - lastPublishTime > publishingPeriod)
        {
            lastPublishTime = millis();
            
            //Publishing...
            publish();
        }
        //Blink LED  
        blink(publishingPeriod / 2);
  }

  //If the connection is lost, then reconnect...
  else
  {
    Serial.println("Retrying...");
    mqtt_connect();
  }      

  //This function prevents the device from crashing
  //since it allows the ESP8266 background functions to be executed
  //(WiFi, TCP/IP stack, etc.)
  yield();
}




//------------------------------------------------------------------------------------//
// Publish function: What we want to send to the relayr Cloud                         //
//------------------------------------------------------------------------------------//

void publish()
{    
  //MQTT_MAX_PACKET_SIZE is defined in "PubSubClient.h", it's 128 bytes by default
  //A modified version with 512 bytes it's available here:
  //https://github.com/chronoclast/pubsubclient
  StaticJsonBuffer<MQTT_MAX_PACKET_SIZE> pubJsonBuffer;
  //Create our JsonArray
  JsonArray& root = pubJsonBuffer.createArray();

//-------------------------------------------------  
  //First object: presence
  JsonObject& leaf1 = root.createNestedObject();
  leaf1["meaning"] = "presence";
    if(digitalRead(PRESENCE_SENSOR_PIN) == HIGH)
      leaf1["value"] = true;
    else
      leaf1["value"] = false;
//-------------------------------------------------
  
  char message_buff[MQTT_MAX_PACKET_SIZE];
  root.printTo(message_buff, sizeof(message_buff));
  client.publish("/v1/"DEVICE_ID"/data", message_buff);
  Serial.println("Publishing " + String(message_buff));
}


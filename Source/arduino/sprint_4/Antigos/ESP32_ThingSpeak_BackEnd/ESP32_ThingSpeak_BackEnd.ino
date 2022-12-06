#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "config_wifi.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include "display.h"
#include "led.h"
Adafruit_AHTX0 aht;

char ssid[] = SECRET_SSID;   // your network SSID (name) 
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
int number1 = 10;
int number2 = random(0,100);
String myStatus = "";

void setup() {
  Wire.begin(45, 47); // Wire communication begin
  Serial.begin(115200);  //Initialize serial
  Serial.println("Adafruit AHT10/AHT20 demo!");
  iniciaDisplay();

  if (! aht.begin(&Wire, 0x38)) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
// Send an HTTP GET request
  //if ((millis() - lastTime) > timerDelay) {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);//populate temp and humidity objects with fresh data
    number1 = (int) (temp.temperature * 100);
    number2 = (int) (humidity.relative_humidity * 100);
    // Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
    Serial.print("Temperature: "); Serial.print(number1); Serial.println(" degrees C");
    // Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
    Serial.print("Humidity: "); Serial.print(number2); Serial.println("% rH");
    printaDisplay(temp.temperature, humidity.relative_humidity);

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  // set the fields with the values
  // number1 = 57;
  ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);

  // figure out the status message
  //if(number1 > number2){
  //  myStatus = String("field1 is greater than field2"); 
  //}
  //else if(number1 < number2){
  //  myStatus = String("field1 is less than field2");
  //}
  //else{
  //  myStatus = String("field1 equals field2");
  //}
  
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  apontaErro(temp.temperature, humidity.relative_humidity);
  // change the values
  //number1++;
  //if(number1 > 99){
  //  number1 = 0;
  //}
  //number2 = random(0,100);
  //number3 = random(0,100);
  //number4 = random(0,100);
  
  delay(5000); // Wait 20 seconds to update the channel again
}

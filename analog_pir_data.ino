#include <SPI.h> //Library for SPI communication (Pre-Loaded into Arduino)

#define TdsSensorPin A7



#define pirPin A0
const int chipSelect = 10; //SD card CS pin connected to pin 4 of Arduino
float pirvalue;

/////////////////////////////////////////////////////////////////
//#define FREQUENCY_HZ        50
//#define INTERVAL_MS         (100000 / (FREQUENCY_HZ + 1))
/////////////////////////////////////////////////////////////////


static unsigned long last_interval_ms = 0;


void setup() {
  // put your setup code here, to run once:
  // Setup Serial connection
  Serial.begin(9600);
  pinMode(pirPin, INPUT);

}

void reading_pir() {
  // Reading pir values takes 
  
  pirvalue = analogRead(pirPin);
 
  
  // Check if any reads failed and exit early (to try again).
  if  (isnan(pirvalue) ) {
    Serial.println("Failed to read from sensor!");
    return;
  }
  
  //debugging purposes
  Serial.print("pir value: "); 
  Serial.println(pirvalue);
  Serial.println(" ");
}

void loop() {
    //static unsigned long last_interval_ms = 0;

    //if (millis() > last_interval_ms + INTERVAL_MS) {
       // last_interval_ms = millis();
       

  // put your main code here, to run repeatedly:
reading_pir();
//}
}

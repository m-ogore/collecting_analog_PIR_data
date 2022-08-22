#include <SPI.h> //Library for SPI communication (Pre-Loaded into Arduino)

#define IN_PIN A0
#define WINDOW_SIZE 5

/////////////////////////////////////////////////////////////////
//#define FREQUENCY_HZ        50
//#define INTERVAL_MS         (100000 / (FREQUENCY_HZ + 1))
/////////////////////////////////////////////////////////////////


static unsigned long last_interval_ms = 0;

int INDEX = 0;
int VALUE = 0;
int SUM = 0;
int READINGS[WINDOW_SIZE];
int AVERAGED = 0;

void setup() {
  pinMode(IN_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
    // Check if any reads failed and exit early (to try again).
  if  (isnan(pirvalue) ) {
    Serial.println("Failed to read from sensor!");
    return;
  }
  // Reading pir values takes
  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  VALUE = analogRead(IN_PIN);        // Read the next sensor value
  READINGS[INDEX] = VALUE;           // Add the newest reading to the window
  SUM = SUM + VALUE;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  AVERAGED = SUM / WINDOW_SIZE;      // Divide the sum of the window by the window size for the result

  Serial.print(VALUE);
  Serial.print(",");
  Serial.println(AVERAGED);
  
  delay(25); 
 
  



    //static unsigned long last_interval_ms = 0;

    //if (millis() > last_interval_ms + INTERVAL_MS) {
       // last_interval_ms = millis();
       

  // put your main code here, to run repeatedly:

//}
}

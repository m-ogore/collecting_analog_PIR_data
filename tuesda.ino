#include <SPI.h> //Library for SPI communication (Pre-Loaded into Arduino)
#include <SD.h> // for the SD card
#include <RTClib.h> // for the RTC


// change this to match your SD shield or module;
// Arduino Ethernet shield and modules: pin 4
// Data loggin SD shields and modules: pin 10
// Sparkfun SD shield: pin 8

const int chipSelect = 4; //pin of cs



#define pirPin A0
//const int chipSelect = 10; //SD card CS pin connected to pin 4 of Arduino
float pirvalue;

/////////////////////////////////////////////////////////////////
#define FREQUENCY_HZ        166
#define INTERVAL_MS         (100000 / (FREQUENCY_HZ + 1))
/////////////////////////////////////////////////////////////////

// Create a file to store the data
File myFile;

// RTC
RTC_DS1307 rtc;

static unsigned long last_interval_ms = 0;


void setup() {
  // put your setup code here, to run once:
  // Setup Serial connection
  Serial.begin(9600);
  pinMode(pirPin, INPUT);

    // setup for the RTC
  while(!Serial); // /Micro/Zero
    if(! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }
    else {
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    if(! rtc.isrunning()) {
      Serial.println("RTC is NOT running!");
    }

    // setup for the SD card
  Serial.print("Initializing SD card...");

  if(!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
    
  //open file
  myFile=SD.open("DATA.txt", FILE_WRITE);

  // if the file opened ok, write to it:
  if (myFile) {
    Serial.println("File opened ok");
    // print the headings for our data
    myFile.println("Date,Time,pir values");
  }
  myFile.close();

}


void loggingTime() {
  DateTime now = rtc.now();
  myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print(',');
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
    myFile.print(",");
  }
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.println(now.day(), DEC);
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  myFile.close(); 
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


    myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) {
    Serial.println("open with success");
    myFile.print(pirvalue);
    myFile.println(",");
  }
  myFile.close();
}


void loop() {
    static unsigned long last_interval_ms = 0;

    if (millis() > last_interval_ms + INTERVAL_MS) {
        last_interval_ms = millis();
       

  // put your main code here, to run repeatedly:
  loggingTime();
reading_pir();
}
}

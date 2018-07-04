#include <SPI.h>
#include <SD.h>
/*
  5V pin to the 5V pin on the Arduino
  GND pin to the GND pin on the Arduino
  CLK to pin 52
  DO to pin 50
  DI to pin 51
  CS to pin 53
*/
File myFile;
const int CSPin = 53;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  Serial.print("Serial monitor connected. Initializing SD card...");

  if (SD.begin(CSPin)) {
    Serial.println("initialization done.");
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    myFile = SD.open("bajaData.txt", FILE_WRITE);
    // if the file opened okay, write to it:
    if (myFile) {
      Serial.print("Writing to bajaData.txt...");
      myFile.println("testing 1, 2, 3.");
      // close the file. if you don't close the file, no data will be saved.
      myFile.close();
      Serial.println("done.");
      Serial.println("Opening bajaData.txt...");
      // re-open the file for reading:
      myFile = SD.open("bajaData.txt");
      if (myFile) {
        Serial.println("\tbajaData.txt:");
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening bajaData.txt");
      }
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening/creating bajaData.txt");
    }
  } else {
    Serial.println("initialization failed.");
  }
}

void loop() {
  // nothing happens after setup
}

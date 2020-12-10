/*  
 Components
 * ----------
 *  - Arduino Uno
 *  - TPA81 thermal array sensor
 *  
 *  Libraries
 *  ---------
 *  - Wire
 *  - TPA81(https://github.com/ilhamadun/TPA81) 
 *
 * Connections
 * -----------
 *  Break out    |    Arduino Uno
 *  -----------------------------
 *      VCC      |      3.3V
 *      GND      |      GND
 *      SDA      |      A4
 *      SCL      |      A5
 *      
 *      
 *      Based on example from https://electropeak.com/learn/motion-gesture-detection-arduino-pir-sensor/ 
  */

#include <TPA81.h>
#include <Wire.h>

// Create new TPA81 instance
TPA81 tpa;

void setup() {
  Serial.begin(9600);

  // You need to begin the Wire library to use TPA81 library
  Wire.begin();
}

void loop() {
  // Print temperature light
  Serial.print(tpa.getAmbient());
  Serial.print(" ");

  // Print all temperature point
  for (int i = 1; i <= 8; i++) { if (tpa.getPoint(i)>30)
    Serial.print("#  ");
    else
    Serial.print(".  ");
  }
Serial.println(" ");
  delay(100);
}

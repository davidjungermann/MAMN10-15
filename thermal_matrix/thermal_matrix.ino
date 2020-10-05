
/***************************************************************************
  This is a library for the AMG88xx GridEYE 8x8 IR camera

  This sketch tries to read the pixels from the sensor

  Designed specifically to work with the Adafruit AMG88 breakout
  ----> http://www.adafruit.com/products/3538

  These sensors use I2C to communicate. The device's I2C address is 0x69

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

/*  
 Components
 * ----------
 *  - Arduino Uno
 *  - Adafruit_AMG88xx thermal sensor
 *  
 *  Libraries
 *  ---------
 *  - Wire
 *  - Adafruit_AMG88xx https://github.com/adafruit/Adafruit_AMG88xx 
 *
 * Connections
 * -----------
 *  Break out    |    Arduino Uno
 *  -----------------------------
 *      VIN      |      5V
 *      GND      |      GND
 *      SDA      |      A4
 *      SCL      |      A5
  */

#include <Wire.h>
#include <Adafruit_AMG88xx.h>

#define columnSize 8

Adafruit_AMG88xx amg;
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int ambientTemperature;
int totalTemperature;
/* Ugly solution for this - will be rewritten later. */
int column0[columnSize] = {0, 8, 16, 24, 32, 40, 48, 56};
int column1[columnSize] = {1, 9, 17, 25, 33, 41, 49, 57};
int column2[columnSize] = {2, 10, 18, 26, 34, 42, 50, 58};
int column3[columnSize] = {3, 11, 19, 27, 35, 43, 51, 59};
int column4[columnSize] = {4, 12, 20, 28, 36, 44, 52, 60};
int column5[columnSize] = {5, 13, 21, 29, 37, 45, 53, 61};
int column6[columnSize] = {6, 14, 22, 30, 38, 46, 54, 62};
int column7[columnSize] = {7, 15, 23, 31, 39, 47, 55, 63};

bool elementInArray(int column[], int element)
{
  for (int i = 0; i < columnSize; i++)
  {
    if (column[i] == element)
    {
      return true;
    }
  }
  return false;
}

void setup()
{
  Serial.begin(9600);
  Serial.println(F("AMG88xx pixels"));

  bool status;

  // default settings
  status = amg.begin();
  if (!status)
  {
    Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
    while (1)
      ;
  }

  Serial.println("-- Pixels Test --");

  delay(100); // let sensor boot up

  amg.readPixels(pixels);
  for (int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++)
  {
    totalTemperature += pixels[i];
  }
  ambientTemperature = (totalTemperature / AMG88xx_PIXEL_ARRAY_SIZE);
  Serial.println(ambientTemperature);
  Serial.println();
  delay(1000);
}

void loop()
{
  for (int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++)
  {
    /* Check if the current temperature is  */
    if (abs(ambientTemperature - pixels[i]) > 3)
    {

      if(elementInArray(column0, i)) {
        Serial.println("Robot head hard left at: " + String(7.5 * 4) + " degrees");
      }
      
      if(elementInArray(column1, i)) {
        Serial.println("Robot head left at: " + String(7.5 * 3) + " degrees");
      }
      
      if(elementInArray(column2, i)) {
        Serial.println("Robot head slight left at: " + String(7.5 * 2) + " degrees");
      }

      if(elementInArray(column3, i)) {
        Serial.println("Robot head left center at: " + String(7.5) + " degrees");
      }
      
      if(elementInArray(column4, i)) {
        Serial.println("Robot head right center at: " + String(7.5) + " degrees");
      }

      if(elementInArray(column5, i)) {
        Serial.println("Robot head slight right at: " + String(7.5 * 2) + " degrees");
      }

      if(elementInArray(column6, i)) {
        Serial.println("Robot head right at: " + String(7.5 * 3) + " degrees");
      }

     if(elementInArray(column7, i)) {
        Serial.println("Robot head hard right at: " + String(7.5 * 4) + " degrees");
      }
      delay(1000);
      break;
    }
  }
  //read all the pixels
  amg.readPixels(pixels);
}
    


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
 *      
 * This is a simple demo program that illustrates how the AMG8833 sensor can be used with Arduino in a prototype in part 1 of MAMN10. 
  */

#include <Wire.h>
#include <Adafruit_AMG88xx.h>

#define columnSize 8

Adafruit_AMG88xx amg;
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int averageTemperature;
int totalTemperature;

void setup()
{
  Serial.begin(9600);

  bool status;

  status = amg.begin();
  if (!status)
  {
    Serial.println("Could not find a valid AMG8833 sensor, check wiring!");
    while (1);
  }

  delay(1000); // let sensor boot up

  amg.readPixels(pixels);
  for (int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++)
  {
    totalTemperature += pixels[i];
  }
  averageTemperature = (totalTemperature / AMG88xx_PIXEL_ARRAY_SIZE);
  Serial.println("Average temperature: " + String(averageTemperature));
  Serial.println();
  delay(1000);
}

void loop()
{
  //read all the pixels
  amg.readPixels(pixels);
  
  for (int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++)
  {
    /* Check if the current temperature is higher than average. */
    if (pixels[i] - averageTemperature > 3)
    {
      /* Modulo calculations in order to divide the 64 pixels into columns to detect the various angles at. */
      if (i % 8 == 0)
      {
        Serial.println("Robot head hard left at: " + String(7.5 * 4) + " degrees");
      }
      else if (i % 8 == 1)
      {
        Serial.println("Robot head left at: " + String(7.5 * 3) + " degrees");
      }
      else if (i % 8 == 2)
      {
        Serial.println("Robot head slight left at: " + String(7.5 * 2) + " degrees");
      }
      else if (i % 8 == 3)
      {
        Serial.println("Robot head left center at: " + String(7.5) + " degrees");
      }
      else if (i % 8 == 4)
      {
        Serial.println("Robot head right center at: " + String(7.5) + " degrees");
      }
      else if (i % 8 == 5)
      {
        Serial.println("Robot head slight right at: " + String(7.5 * 2) + " degrees");
      }
      else if (i % 8 == 6)
      {
        Serial.println("Robot head right at: " + String(7.5 * 3) + " degrees");
      }
      else if (i % 8 == 7)
      {
        Serial.println("Robot head hard right at: " + String(7.5 * 4) + " degrees");
      }
      /*Added delay to make demos more comprehensible. */
      delay(1000);
      break;
    }
  }
}

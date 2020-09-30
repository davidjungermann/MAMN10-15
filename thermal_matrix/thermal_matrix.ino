
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

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int ambientTemperature;
int totalTemperature;

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
    while (1);
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
  //read all the pixels
  amg.readPixels(pixels);

  Serial.print("[");
  for (int i = 1; i <= AMG88xx_PIXEL_ARRAY_SIZE; i++)
  {
    /* Check if the current temperature is  */
    if (abs(ambientTemperature - pixels[i - 1]) > 2)
    {
      Serial.print(pixels[i - 1]);
    }
    else
    {
      Serial.print(pixels[i - 1]);
    }
    Serial.print(", ");
    if (i % 8 == 0)
      Serial.println();
  }
  Serial.println("]");
  Serial.println();

  //delay a second
  delay(1000);
}

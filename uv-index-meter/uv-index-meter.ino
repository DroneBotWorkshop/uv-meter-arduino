/*
  UV Index Meter
  uv-index-meter.ino
  Measures UV Index with LCD display
  Uses SI1145 UV IR Visible Sensor
  Uses 1602 LCD with I2C adapter
  Use NewLiquidCrystal Library
  Uses Adafruit SI1145 Library

  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/

// Include Wire Library for I2C
#include <Wire.h>

// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

// Include Adafruit SI1145 Library
#include <Adafruit_SI1145.h>


// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x3F;

// Define object lcd
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

// Define object uv
Adafruit_SI1145 uv = Adafruit_SI1145();

void setup()
{

  // Set display type as 16 char, 2 rows
  lcd.begin(16, 2);

  // Initialize UV sensor
  uv.begin();

}

void loop() {

  // Read UV level
  float UVindex = uv.readUV();
  // Divide by 100 for UV index
  UVindex /= 100.0;

  // Display UV Index on LCD

  // Clear the display
  lcd.clear();

  // Print on top line
  lcd.setCursor(0, 0);
  lcd.print("UV Index: ");
  lcd.print(UVindex);

  // Print bottom line
  lcd.setCursor(0, 1);

  if (UVindex < 3.0)
  {
    lcd.print("Low UV Level");
  }
  else if (UVindex >= 3 && UVindex < 6)
  {
    lcd.print("Medium UV Level");
  }
  else if (UVindex >= 6 && UVindex < 8)
  {
    lcd.print("High UV Level");
  }
  else
  {
    lcd.print("Extreme UV Level");
  }

  delay(1000);
}

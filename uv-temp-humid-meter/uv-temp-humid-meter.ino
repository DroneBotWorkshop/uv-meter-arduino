/*
  UV Index Meter with Temperature and Humidity
  uv-temp-humid-meter.ino
  Displays results on LCD display
  Uses SI1145 UV IR Visible Sensor
  Uses AM2320 Temperature and Humidity sensor
  Uses 1602 LCD with I2C adapter
  Use NewLiquidCrystal Library
  Uses Adafruit SI1145 Library
  Uses Adafruit AM2320 Library
  Uses Adafruit Unified Sensor Library

  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/

// Include Wire Library for I2C
#include <Wire.h>

// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

// Include Adafruit SI1145 Library
#include <Adafruit_SI1145.h>

// Include Adafruit Unified Sensor Library
#include <Adafruit_Sensor.h>


// Include Adafruit AM2320 Library
#include <Adafruit_AM2320.h>


// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x3F;

// Define object lcd
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

// Define object uv
Adafruit_SI1145 uv = Adafruit_SI1145();

// Define object am2320
Adafruit_AM2320 am2320 = Adafruit_AM2320();

void setup()
{

  // Set display type as 16 char, 2 rows
  lcd.begin(16, 2);

  // Initialize UV sensor
  uv.begin();

  // Initialize Temp & Humid Sensor
  am2320.begin();

  // Print Greeting on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UV Temp & Humid");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait");

  // Let the sensors initialize
  delay(2000);

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

  lcd.print("UV: ");
  lcd.print(UVindex);

  if (UVindex < 3.0)
  {
    lcd.print(" Low");
  }
  else if (UVindex >= 3 && UVindex < 6)
  {
    lcd.print(" Medium");
  }
  else if (UVindex >= 6 && UVindex < 8)
  {
    lcd.print(" High");
  }
  else
  {
    lcd.print(" Danger");
  }

  // Print bottom line
  lcd.setCursor(0, 1);

  lcd.print("T:");
  lcd.print(am2320.readTemperature(), 1);
  lcd.print("C ");

  lcd.print("H:");
  lcd.print(am2320.readHumidity(), 1);
  lcd.print("%");


  delay(3000);
}

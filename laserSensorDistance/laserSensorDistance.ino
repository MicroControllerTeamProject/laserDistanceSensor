/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm.

Original source: https://github.com/pololu/vl53l0x-arduino

High speed
https://forum.pololu.com/t/high-speed-with-vl53l0x/16585

Modified by Ahmad Shamshiri for RoboJax.com
Date mortified: Sep 26, 2017
*/
/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.
The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.
VL53L0X sensor;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
	pinMode(9, OUTPUT);
    /*sensor.setTimeout(500);*/
    if (!sensor.init())
    {
        Serial.println("Failed to detect and initialize sensor!");
        while (1) {}
    }
    // Start continuous back-to-back mode (take readings as
    // fast as possible).  To use continuous timed mode
    // instead, provide a desired inter-measurement period in
    // ms (e.g. sensor.startContinuous(100)).
    /*sensor.startContinuous();*/
    sensor.setMeasurementTimingBudget(20000);
    sensor.startContinuous();
	lcd.begin(16, 1);   // iInit the LCD for 16 chars 2 lines
}

void loop()
{
	int distance = sensor.readRangeContinuousMillimeters();
	//distance = distance - 55;// -55 is to compensate for error. Change or set it to zero to make it work for your sensor
	/*Serial.print("Distance: ");
	Serial.print(distance);
	Serial.print("mm");*/
	String a = "distance : ";
	a.concat(distance);
	a.concat(" mm");
	lcdPrintMessage(a);
	if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
	Serial.println();
	if (distance < 100 && distance > 10)
	{
		digitalWrite(9, HIGH);
		delay(500);
	}
	else
	{
		digitalWrite(9, LOW);
	}
}
void lcdPrintMessage(String message)
{
	lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
	lcd.setCursor(0, 1); //First line
	lcd.println(message);
}

void lcdSlideMessage(String message) {
	lcd.begin(16, 1);   // iInit the LCD for 16 chars 2 lines
	lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
	lcd.setCursor(16, 1); //First line
	lcd.scrollDisplayLeft();
	lcd.autoscroll();
	for (int thisChar = 0; thisChar < message.length(); thisChar++) {
		lcd.print(message.charAt(thisChar));
		delay(350);
	}
	delay(2000);
	lcd.clear();
}
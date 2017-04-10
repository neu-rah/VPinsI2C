/*
  Virtual pins I2C, LiquidCrystal Library - Hello World
 */

#include <Wire.h>
#include <VPinsI2C.h>

// include the lcd library
#include <LiquidCrystal.h>

//define virtual port D (VPD), 8 bits
//TODO: consider + bits case
I2CBranch i2c(Wire,0x27,VPD);//mount I2C network protocol and port
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(i2c.pin(0), i2c.pin(1), i2c.pin(2), i2c.pin(4), i2c.pin(5), i2c.pin(6), i2c.pin(7));

#define BKLight i2c.pin(3)

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("I2C Virtual pins test!");
  Wire.begin();
  pinMode(BKLight,OUTPUT);
  digitalWrite(BKLight,1);
  // lcd.begin(16, 2);
  lcd.begin(20, 4);
  lcd.print("hello, world!");
}

void loop() {
  lcd.setCursor(0,1);
  lcd.print(millis()/100);
}

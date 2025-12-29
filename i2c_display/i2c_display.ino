#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD address (usually 0x27 or 0x3F)
// If unsure, run I2C Scanner
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin();         // Start I2C communication
  lcd.init();           // Initialize LCD
  lcd.backlight();      // Turn on backlight

  lcd.setCursor(0, 0);
  lcd.print("LCD Connected!");

  lcd.setCursor(0, 1);
  lcd.print("Leonardo I2C");
}

void loop() {
  // Nothing needed here
}

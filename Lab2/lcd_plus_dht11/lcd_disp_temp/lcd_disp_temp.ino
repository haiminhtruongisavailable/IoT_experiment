#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ==================== CHANGE THIS ====================
LiquidCrystal_I2C lcd(0x27, 16, 2);   // ← Change 0x27 to your LCD address (usually 0x27 or 0x3F)
// =====================================================

const int DHTPIN = 14;
const int DHTTYPE = DHT11;

DHT dht(DHTPIN, DHTTYPE);

// Custom degree symbol
byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

void setup() {
  Wire.begin(4, 5);           // SDA = GPIO4 (D2), SCL = GPIO5 (D1)
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Nhiet do: ");
  lcd.setCursor(0, 1);
  lcd.print("Do am:   ");

  lcd.createChar(1, degree);
  dht.begin();

  delay(2000);                // Wait for sensor to stabilize
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    lcd.setCursor(0, 1);
    lcd.print("Check wiring    ");
    delay(2000);
    return;
  }

  // Display Temperature
  lcd.setCursor(10, 0);
  lcd.print("    ");           // Clear old value
  lcd.setCursor(10, 0);
  lcd.print(round(t));
  lcd.write(1);                // Degree symbol
  lcd.print("C");

  // Display Humidity
  lcd.setCursor(10, 1);
  lcd.print("    ");           // Clear old value
  lcd.setCursor(10, 1);
  lcd.print(round(h));
  lcd.print(" %");

  delay(2000);                 // DHT11 needs time between readings
}
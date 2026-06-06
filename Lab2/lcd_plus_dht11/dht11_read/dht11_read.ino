#include "DHT.h" // declaration library DHT11
const int DHTPIN = 14; //read data from DHT11 at GPIO14 pin connected to sensor (D5)
const int DHTTYPE = DHT11; //declaration the sensor type, there are 2 types: DHT11 and DHT22
DHT dht(DHTPIN, DHTTYPE);
void setup() {
Serial.begin(115200);
dht.begin(); // sensor start
}
void loop() {

// wait a few seconds between measurements
delay(10000);
float h = dht.readHumidity(); //Read humidity
float t = dht.readTemperature(); //Read temperature in degrees Celsius
float f = dht.readTemperature(true); //Read temperature in degrees Fahrenheit
Serial.print("Do am: ");
Serial.print(h); // display humidity
Serial.print("%\t");
Serial.print("Nhiet do: ");
Serial.print(t); // display temperature C
Serial.print(" *C ");
Serial.print(f); // display temperature F
Serial.println(" *F ");
Serial.println();
}
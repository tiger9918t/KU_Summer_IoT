#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 65 // OLED display height, in pixels

DHT dht(DHTPIN, DHTTYPE);
// Declaration for an SSD1306 display connected to I2C (SDA, SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // put your setup code here, to run once:

  dht.begin();
  pinMode(27, INPUT);

  Wire.setSDA(13);
  Wire.setSCL(12);
  Wire.begin();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  float F = dht.readTemperature(true);
  int rain_sensor = analogRead(27);

    //Check if any reads failed and exit early (to try again)
  if(isnan(hum) || isnan(temp) || isnan(F)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SDD1306 allocation failed"));
    for(;;);
  }
  delay(2000);

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("C");
  Serial.print("Rain Sensor Value: ");
  Serial.print(rain_sensor);
  Serial.println(" ");
  
  if(hum < 50 && temp > 20)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("GOOD!");
    display.display();
    delay(3000);
  }
  else if(50 <= hum < 70 && 0 < temp <= 20)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("NOT BAD");
    display.display();
    delay(3000);
  }
  else
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("BAD!");
    display.display();
    delay(3000);
  }

  if(rain_sensor < 900) 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("RAINING!");
    display.display();
    delay(3000);
  }
}

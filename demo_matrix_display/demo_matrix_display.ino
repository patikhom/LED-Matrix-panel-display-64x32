#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <DHT.h>
#include <SPI.h>
#include <SD.h>
#include <DS3231.h>
#include <Wire.h>
#include "image.h" 

#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

#define DHTPIN 41 
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#define RL1 35
#define RL2 36
#define RL3 37

#define SW1 43
#define SW2 44
#define SW3 45
#define SW4 46
#define SW5 47
#define SW6 49

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  32

boolean DHTFLAG = 0;
boolean SDFLAG = 0;
boolean ESPFLAG = 0;
boolean RTCFLAG = 0;
boolean DFFFLAG = 0;
boolean RLFLAG = 0;
boolean DRAWFLAG = 0;
int flag = 0;

const int chipSelect = 53;

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);
DHT dht(DHTPIN, DHTTYPE);
DS3231  rtc(SDA, SCL);

void setup() {
  //delay(2000);
  matrix.begin();
  //delay(1000);
  dht.begin();
  Wire.begin();
  rtc.begin();
  //SD.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  drawImage3(0,9);
  delay(4000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setCursor(0, 12);    // start at top left, with 8 pixel of spacing

  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.println("SELF TEST !");
  delay(2000);

  pinMode(RL1, OUTPUT);
  pinMode(RL2, OUTPUT);
  pinMode(RL3, OUTPUT);

  digitalWrite(RL1, HIGH);
  digitalWrite(RL2, HIGH);
  digitalWrite(RL3, HIGH);

  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);
  pinMode(SW5, INPUT_PULLUP);
  pinMode(SW6, INPUT_PULLUP);
  
  matrix.fillScreen(matrix.Color333(3, 3, 3));
  delay(3000);
  matrix.fillScreen(matrix.Color333(0, 0, 4));
  delay(2000);
  matrix.fillScreen(matrix.Color333(0, 4, 0));
  delay(2000);
  matrix.fillScreen(matrix.Color333(4, 0, 0));
  delay(2000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setCursor(0, 0);    // start at top left, with 8 pixel of spacing

  matrix.fillScreen(matrix.Color333(0, 0, 0));
}

void loop() {
  
  matrix.setCursor(0, 0);    // start at top left, with 8 pixel of spacing
 //Serial.println(flag);
  if(flag == 0){
    drawImage(0,0);
    //drawImage1(22,0);
    //drawImage2(44,0);
    //drawImage4(0,0);
    flag = 1;
    delay(4000);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    //delay(2000);
    //DRAWFLAG = 1;
    }

  if(flag == 1) {
    DHTxx();
    }

  if(flag == 2) {
    SDxx();
    }
    
  if(flag == 3) {
    RTCxx();
    }
    
  if(flag == 4) {
    ESPxx();
    }
    
  if(flag == 5) {
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    RELAYxx();
    }
  if(flag == 6) {
    GETSWxx();
    }
}

void DHTxx() {
  // delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    matrix.println("DHT FAIL !");
    flag = 2;
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  matrix.println("DHT OK");
  delay(500);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  flag = 2;
  }

void SDxx() {
    if (!SD.begin(chipSelect)) {
    Serial.println("SDCard failed, or not present");
    matrix.println("SD  FAIL !");
    delay(500);
    flag = 3;
    // don't do anything more:
    return;
  }
  else {
    Serial.println("SDCard device found OK");
    matrix.println("SD  OK");
    delay(500);
    flag = 3;
    }
 }

void RTCxx() {

  byte error, address;
  int nDevices;

   Serial.println("RTC Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      
      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices < 1){
    Serial.println("NOT devices found\n"); 
    matrix.println("RTC FAIL !");
    
      // Send Day-of-Week
          
          Serial.print(rtc.getDOWStr());
          Serial.print(" ");
  
           // Send date
          Serial.print(rtc.getDateStr());
          Serial.print(" -- ");

          // Send time
          Serial.println(rtc.getTimeStr());
    delay(500);
    flag = 4;
  }
  else {
    Serial.println("done\n");
    matrix.println("RTC OK");
    delay(500);
    flag = 4;
   }
 }

void ESPxx() {
  String i = " ";
  if(Serial2.available()) {
    Serial.print(Serial2.read());
    Serial.println("ESP is ready");
    matrix.println("ESP OK");
    delay(500);
    flag = 5;
    }
    else {
      Serial.println("Not found ESP !");
    matrix.println("ESP FAIL !");
    delay(500);
    flag = 5;
      }
  }

void RELAYxx() {

  matrix.setCursor(0, 0); 
  matrix.print("RELAY");
  matrix.setCursor(54, 0); 
  matrix.print("1");
  digitalWrite(RL1, LOW);
  delay(500);
  digitalWrite(RL1, HIGH);
  delay(500);
  matrix.fillRect(54, 0, 5, 7, matrix.Color333(0, 0, 0));
  matrix.setCursor(54, 0); 
  matrix.print("2");
  digitalWrite(RL2, LOW);
  delay(500);
  digitalWrite(RL2, HIGH);
  delay(500);
  matrix.fillRect(54, 0, 5, 7, matrix.Color333(0, 0, 0));
  matrix.setCursor(54, 0); 
  matrix.println("3");
  digitalWrite(RL3, LOW);
  delay(500);
  digitalWrite(RL3, HIGH);
  flag = 6;
  }

void GETSWxx() {
  matrix.setCursor(0, 8); 
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print("BUTTON >");
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.setCursor(0, 16); 
  matrix.print("SUMTECH");
  matrix.setTextColor(matrix.Color333(0,7,0));
  matrix.setCursor(0, 24); 
  matrix.print(".CO.TH");
  if(digitalRead(SW1) == LOW){
    matrix.fillRect(54, 8, 5, 7, matrix.Color333(0, 0, 0));
    matrix.setTextColor(matrix.Color333(7,7,7));
    matrix.setCursor(54, 8);matrix.print("A");
    delay(500);
    }
  else if(digitalRead(SW2) == LOW){
    matrix.fillRect(54, 8, 5, 7, matrix.Color333(0, 0, 0));
    matrix.setTextColor(matrix.Color333(7,7,7));
    matrix.setCursor(54, 8); matrix.print("B");
    delay(300);
    }
  else if(digitalRead(SW3) == LOW){
    matrix.fillRect(54, 8, 5, 7, matrix.Color333(0, 0, 0));
    matrix.setTextColor(matrix.Color333(7,7,7));
    matrix.setCursor(54, 8); matrix.print("C");
    delay(300);
    }
  else if(digitalRead(SW4) == LOW){
    matrix.fillRect(54, 8, 5, 7, matrix.Color333(0, 0, 0));
    matrix.setTextColor(matrix.Color333(7,7,7));
    matrix.setCursor(54, 8); matrix.print("D");
    delay(300);
    }
  else if(digitalRead(SW5) == LOW){
    matrix.fillRect(54, 8, 5, 7, matrix.Color333(0, 0, 0));
    matrix.setTextColor(matrix.Color333(7,7,7));
    matrix.setCursor(54, 8); matrix.print("E");
    delay(300);
    }
  else if(digitalRead(SW6) == LOW){
    matrix.fillRect(54, 8, 5, 7, matrix.Color333(0, 0, 0));
    matrix.setTextColor(matrix.Color333(7,7,7));
    matrix.setCursor(54, 8); matrix.print("F");
    delay(300);
    }
  }
  
void drawImage(int x, int y)
{
  int imageHeight = 20;
  int imageWidth = 20;
  int counter = 0;
  for (int yy = 0; yy < imageHeight; yy++)
  {
    for (int xx = 0; xx < imageWidth; xx++)
    {
      matrix.drawPixel(xx + x , yy + y, xxx[counter]);
      counter++;
    }
  }
}

void drawImage1(int x, int y)
{
  int imageHeight = 20;
  int imageWidth = 20;
  int counter = 0;
  for (int yy = 0; yy < imageHeight; yy++)
  {
    for (int xx = 0; xx < imageWidth; xx++)
    {
      matrix.drawPixel(xx + x , yy + y, sun[counter]);
      counter++;
    }
  }
}

void drawImage2(int x, int y)
{
  int imageHeight = 20;
  int imageWidth = 20;
  int counter = 0;
  for (int yy = 0; yy < imageHeight; yy++)
  {
    for (int xx = 0; xx < imageWidth; xx++)
    {
      matrix.drawPixel(xx + x , yy + y, cloud[counter]);
      counter++;
    }
  }
}

void drawImage3(int x, int y)
{
  int imageHeight = 12;
  int imageWidth = 64;
  int counter = 0;
  for (int yy = 0; yy < imageHeight; yy++)
  {
    for (int xx = 0; xx < imageWidth; xx++)
    {
      matrix.drawPixel(xx + x , yy + y, logo[counter]);
      counter++;
    }
  }
}
void drawImage4(int x, int y)
{
  int imageHeight = 32;
  int imageWidth = 64;
  int counter = 0;
  for (int yy = 0; yy < imageHeight; yy++)
  {
    for (int xx = 0; xx < imageWidth; xx++)
    {
      matrix.drawPixel(xx + x , yy + y, mario[counter]);
      counter++;
    }
  }
}


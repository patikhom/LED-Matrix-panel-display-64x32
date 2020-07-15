
#include <EEPROM.h>

#include "RGBmatrixPanel.h"
#include "Fonts/FreeSansBold12pt7b.h"
#include "Fonts/kongtext4pt7b.h"
#include "Fonts/Org_01.h"

#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

#define Sensor 43
#define SET  44
#define UP   45
#define DOWN 46
#define SHOW 47

byte TIMEFIG = 30;
byte TIMESET = 30;
byte TIMEIN = 30;
long count = 0;
long timeref = 14900; //FIG = 15000
int count2 = 0;
int timeref2 = 0;
int dataflag = 0;
boolean SETFLAG = 0;
boolean cou = 1;

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

void setup() {

  matrix.begin();
  //Serial.begin(9600);

  pinMode(Sensor, INPUT);
  pinMode(SET, INPUT);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);

  if (EEPROM.read(0) < 30) {
    EEPROM.write(0, 30);
  }
  TIMEFIG = EEPROM.read(0);

  matrix.setTextWrap(false);
  matrix.setFont(&Org_01);

  matrix.setTextSize(2);
  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.setCursor(3, 12);
  matrix.print("COUNT");
  matrix.setCursor(9, 25);
  matrix.print("DOWN");
  delay(2000);

  // draw a box in yellow
  matrix.setTextSize(6);     // size 1 == 8 pixels high
  matrix.setCursor(0, 25);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.print(TIMEFIG);
}

void loop() {

  if (digitalRead(SET) == LOW) {
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    TIMEFIG = TIMESET;
    delay(300);
    if (SETFLAG == 1) {
      SHOWTARGET();
      SETFLAG = 0;
    }
    else if (SETFLAG == 0) {
      cou = 0;
      SETFLAG = 1;
    }
  }

  //Serial.println(SETFLAG);

  if (digitalRead(Sensor) == LOW && SETFLAG == 0) {
    //dataflag = 0;
    count++;
    if (count == timeref && TIMEFIG > 0) {
      if (TIMEFIG > 19) {
        matrix.setTextSize(6);
        matrix.setCursor(0, 25);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
        //matrix.fillRect(36, 0, 28, 32, matrix.Color333(0, 0, 0));
        matrix.setTextColor(matrix.Color333(7, 0, 0));
        matrix.print(TIMEFIG);
        TIMEFIG--;
        count = 0;
      }
      //TIMEFIG--;
      else if (TIMEFIG < 20 && TIMEFIG > 10) {
        matrix.setTextSize(6);
        matrix.setCursor(11, 25);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
        matrix.setTextColor(matrix.Color333(7, 0, 0));
        matrix.print(TIMEFIG);
        TIMEFIG--;
        count = 0;
      }
      else if (TIMEFIG < 11 && TIMEFIG > 1) {
        matrix.setTextSize(6);
        matrix.setCursor(18, 25);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
        matrix.setTextColor(matrix.Color333(7, 0, 0));
        matrix.print(TIMEFIG);
        TIMEFIG--;
        count = 0;
      }
      else if (TIMEFIG == 1) {
        matrix.setTextSize(6);
        matrix.setCursor(29, 25);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
        matrix.setTextColor(matrix.Color333(7, 0, 0));
        matrix.print(TIMEFIG);
        TIMEFIG--;
        count = 0;
      }
    }
  }

  /*else if(digitalRead(Sensor) == HIGH && SETFLAG == 0){
      TIMEFIG + 1;
      if(TIMEFIG > 19){
      matrix.setTextSize(6);
      matrix.setCursor(0, 25);
      //matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.setTextColor(matrix.Color333(7,0,0));
      matrix.print(TIMEFIG);
      //count = 0;
      }
      else if(TIMEFIG < 20 && TIMEFIG > 10){
        matrix.setTextSize(6);
        matrix.setCursor(11, 25);
        //matrix.fillScreen(matrix.Color333(0, 0, 0));
        matrix.setTextColor(matrix.Color333(7,0,0));
        matrix.print(TIMEFIG);
        //count = 0;
        }
      else if(TIMEFIG < 11){
        matrix.setTextSize(6);
        matrix.setCursor(18, 25);
        //matrix.fillScreen(matrix.Color333(0, 0, 0));
        matrix.setTextColor(matrix.Color333(7,0,0));
        matrix.print(TIMEFIG);
        //count = 0;
      }
    }*/

  if (TIMEFIG == 0) {
    delay(1000);
    matrix.fillScreen(matrix.Color333(0, 7, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 7, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 7, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 7, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 7, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 7, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 7, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 7, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 7, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 7, 0));
    delay(500);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    delay(500);
    /*matrix.fillScreen(matrix.Color333(0, 7, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 7, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 7, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 7, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 7, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 7, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 7, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 7, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 7, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 7, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 7, 0));
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0));*/

    TIMEFIG = TIMESET;

    /*matrix.setCursor(0, 25);
      matrix.setTextColor(matrix.Color333(7,0,0));
      matrix.print(TIMEFIG);*/
    if (TIMEFIG > 19) {
      matrix.setTextSize(6);
      matrix.setCursor(0, 25);
      //matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.setTextColor(matrix.Color333(7, 0, 0));
      matrix.print(TIMEFIG);
      cou == 1;
    }
    else if (TIMEFIG < 20 && TIMEFIG > 10) {
      matrix.setTextSize(6);
      matrix.setCursor(11, 25);
      //matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.setTextColor(matrix.Color333(7, 0, 0));
      matrix.print(TIMEFIG);
      cou == 1;
    }
    else if (TIMEFIG < 11) {
      matrix.setTextSize(6);
      matrix.setCursor(18, 25);
      //matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.setTextColor(matrix.Color333(7, 0, 0));
      matrix.print(TIMEFIG);
      cou == 1;
    }
    //count2++;
  }

  if (SETFLAG == 1) {
    matrix.setCursor(2, 6);
    matrix.setTextSize(1);
    matrix.setTextColor(matrix.Color333(7, 0, 0));
    matrix.print("SET TARGET");
    matrix.setTextSize(2);
    matrix.setCursor(22, 20);
    matrix.print(TIMESET);
    delay(50);
    if (digitalRead(UP) == LOW) {
      //matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.fillRect(21, 11, 30, 15, matrix.Color333(0, 0, 0));
      TIMESET++;
      EEPROM.write(0, TIMESET);
      //TIMEFIG = TIMESET;
      delay(50);
      if (TIMESET > 98) {
        TIMESET = 0;
      }
    }
  }
}

void SHOWTARGET() {
  if (cou == 0) {
    if (TIMEFIG > 19) {
      matrix.setTextSize(6);
      matrix.setCursor(0, 25);
      //matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.setTextColor(matrix.Color333(7, 0, 0));
      matrix.print(TIMEFIG);
      cou == 1;
    }
    else if (TIMEFIG < 20 && TIMEFIG > 10) {
      matrix.setTextSize(6);
      matrix.setCursor(11, 25);
      //matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.setTextColor(matrix.Color333(7, 0, 0));
      matrix.print(TIMEFIG);
      cou == 1;
    }
    else if (TIMEFIG < 11) {
      matrix.setTextSize(6);
      matrix.setCursor(18, 25);
      //matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.setTextColor(matrix.Color333(7, 0, 0));
      matrix.print(TIMEFIG);
      cou == 1;
    }
  }
}

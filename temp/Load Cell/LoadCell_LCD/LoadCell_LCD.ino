/*
 * Written by Krystal Bernal and Jovanny Santana
 * for CSULA Baja SAE 2017-2018
 * Last Updated: 10/14/17
 * 
 * This program reads force in lbs from Load Cells and prints the readings to an LCD
*/

#include <WheatstoneBridge.h>
#include <LiquidCrystal.h>

WheatstoneBridge cell_1(A0, 365, 675, 0, 1000);
WheatstoneBridge cell_2(A1, 365, 675, 0, 1000);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int force1;
int force2;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  printForces();
}

void printForces(){
  
  force1 = cell_1.measureForce() * 0.49;
  force2 = cell_2.measureForce() * 0.49;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Load1:");
  lcd.setCursor(10, 0);
  lcd.print("Load2:");
  lcd.setCursor(0, 1);

  Serial.print("Load1: ");
  if (force1 > 0) {
    lcd.print(abs(force1), DEC);
    lcd.setCursor(4, 1);
    lcd.print("T");
    Serial.print(abs(force1));
    Serial.print(" T\t");
  } else {
    lcd.print(abs(force1), DEC);
    lcd.setCursor(4, 1);
    lcd.print("C");
    Serial.print(abs(force1));
    Serial.print(" C\t");
  }

  lcd.setCursor(10, 1);           // tab indent
  Serial.print("Load2: ");
  
  if (force2 > 0) {
    lcd.print("NoConn");           // delete when reading load 2
    Serial.print("NoConn");
    //lcd.print(abs(force2),DEC);
    //lcd.setCursor(15,1);
    //lcd.print("T");
    //Serial.print(abs(force2));
    //Serial.print(" T\t");
  } else {
    lcd.print("NoConn");           // delete when reading load 2
    Serial.print("NoConn");
    //lcd.print(abs(force2),DEC);
    //lcd.setCursor(15,1);
    //lcd.print("C");
    //Serial.print(abs(force2));
    //Serial.print(" C\t");
  }
  Serial.println();
  delay(50);
}

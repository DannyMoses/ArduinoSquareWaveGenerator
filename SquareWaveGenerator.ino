/* 
* A simple square wave generator using a tlc5940 IC, an LCD and some buttons
* Author: Daniel Moses
*/

/* 
* PINOUTS:
* LCD on pins 8, 7, 6, 5, 4 and 2
* TLC5940 on the default pins for the library
* buttons: left: A1
* right: A2
* set: A3
*/
#include "Tlc5940.h"
#include <LiquidCrystal.h>

/* declarations for the potentiometer */
const int potPin = A0;
int potInput;

/* declarations for the LCD */
LiquidCrystal lcd(8, 7, 6, 5, 4, 2);

/* declarations for the buttons */
const int leftButton = A1;
const int rightButton = A2;
const int setButton = A3;

/* declarations for the tlc5940 */
int currentOutputValue;

void printToLCD(int channel)
{
  lcd.clear(); 
  lcd.home();
  lcd.print("Channel: ");
  lcd.print(channel, DEC);
  lcd.setCursor(0, 1);
  int output = Tlc.get(channel);
  lcd.print("Output: ");
  lcd.print(output, DEC);
}

void generateSquareWave(int channel, int output)
{
  Tlc.set(channel, output);
  Tlc.update();
}


void setup()
{
  Tlc.init();
  
  lcd.begin(16, 2);
  
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(setButton, INPUT);

}

void loop()
{
  potInput = analogRead(potPin);
  currentOutputValue = map(potInput, 0, 1023, 0, 4095);
	
  int leftButtonPressed = digitalRead(leftButton);
  int rightButtonPressed = digitalRead(rightButton);
  int setButtonPressed = digitalRead(setButton);

  int currentChannel = 0;

  if (leftButtonPressed == HIGH && currentChannel != 0)
  {
    currentChannel--;
  }

  else if (rightButtonPressed == HIGH && currentChannel != 15)
	{
    currentChannel++;
  }
  
  if (setButtonPressed == HIGH)
  {
    generateSquareWave(currentChannel, currentOutputValue);
  }
  
  printToLCD(currentChannel);
}




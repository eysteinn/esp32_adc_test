#include <Arduino.h>
#include "hal/adc_types.h"

void setup() {
  Serial.begin(115200);
}

// https://askubuntu.com/questions/1403705/dev-ttyusb0-not-present-in-ubuntu-22-04
void loop2() {
  // Specify the analog pin you want to read from
  int analogPin = 34; // You can change this to the desired pin

  // Read the ADC value from the specified pin
  int adcValue = analogRead(analogPin);

  // Print the ADC value to the Serial Monitor
  /*Serial.print("ADC Value: ");
  Serial.println(adcValue);*/
adc_continuous_config();

  delay(1000); // Wait for 1 second before reading again
}

// lowest cycle 6.9

unsigned int i = 0;
int cycle=0*25e-3;
int loopduration_usec = cycle/255;

bool increasing;

void loop() {
  int dacValue = i;
  dacWrite(25, dacValue);

  if (increasing) {
    dacValue = (dacValue + 1) % 256; // Increment the DAC value
    if (dacValue == 255) {
      increasing = false; // Change direction when reaching the maximum value
    }
  } else {
    dacValue = (dacValue - 1) % 256; // Decrement the DAC value
    if (dacValue == 0) {
      increasing = true; // Change direction when reaching the minimum value
    }
  }
  i = dacValue;
  adc_continuous_new_handle()
  delayMicroseconds(100);
}
void loop3() {

  unsigned long startTime = micros(); // Record the start time
  //int dir = (i / 256) % 2; // 0 or 1
  i=i+1;  
  int dir = (i / 256) % 2;

  int tmp = i % 256;
  

  if (dir == 0) {
    dacWrite(25, tmp );
  } else {
    dacWrite(25, 254 - tmp);
  }
  

  unsigned long elapsedTime = micros() - startTime; // Calculate elapsed time
  unsigned long delayTime = loopduration_usec - elapsedTime; // loop duration - elapsed time
  Serial.print("DAC Value: ");
  Serial.print(dir);
  Serial.print("   ");
  Serial.println(i);
  if (loopduration_usec > elapsedTime) {
    delayMicroseconds(delayTime);
  }
}
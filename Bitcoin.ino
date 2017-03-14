/* SevSeg Counter Example
 
 Copyright 2016 Dean Reading
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 
 This example demonstrates a very simple use of the SevSeg library with a 4
 digit display. It displays a counter that counts up, showing deci-seconds.
*/

#include "SevSeg.h"
SevSeg sevseg;
bool stringComplete = false;
String inputString = "";

void setup() {
  Serial.begin(9600);
  byte numDigits = 4;
  byte digitPins[] = {9,10,11,12};
  byte segmentPins[] = {2,3,4,5,6,7,8,1};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_ANODE;
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
}

void loop() {
  sevseg.refreshDisplay();
}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == ' ') {  // Detect end of data with a ' ' character.
      stringComplete = true;
    }
  }
  if(stringComplete){
    Serial.println(inputString);
    sevseg.setNumber(inputString.toInt(), 1);
    inputString = "";
    stringComplete = false;
  }
}

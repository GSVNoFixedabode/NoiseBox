/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-hc-sr04-ultrasonic-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  Bluetooth library from https://github.com/pschatzmann/ESP32-A2DP
*********/
// Ultrasonic bits
const int trigPin = 26;
const int echoPin = 25;
int LED_BUILTIN1 = 2;
//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;
float distanceInch;

// Whistle bits
#include "BluetoothA2DPSource.h"
#include "toots.h"

BluetoothA2DPSource a2dp_source;
SoundData *data = new OneChannel8BitSoundData((int8_t*)toots_raw, toots_raw_len);

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode (LED_BUILTIN1, OUTPUT);
  bool state = true;

 // whistle bits  
 static std::vector<const char*> bt_names = {"BRV-BLADE","SRS-XB01"};
 a2dp_source.start(bt_names); 
 a2dp_source.set_auto_reconnect(true);
 // a2dp_source.start("BRV-BLADE");  
 //  a2dp_source.start("SRS-XB01");  
  a2dp_source.set_connected(state);
  Serial.println(state);
  a2dp_source.set_volume(240);
 // a2dp_source.write_data(data); 
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  if (distanceCm > 10 and distanceCm < 250) {
      Serial.print("Toot toot toot!");
      digitalWrite(LED_BUILTIN1, HIGH);
      a2dp_source.write_data(data); 
      delay(1800);
      a2dp_source.write_data(data); 
      delay(2000);
      digitalWrite(LED_BUILTIN1, LOW);
  }

  delay(500);
}

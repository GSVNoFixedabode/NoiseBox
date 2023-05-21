# NoiseBox
ESP32 with Ultrasonic sensor plugged in,
If distance below 250cm then send audio file via Bluetooth to Speaker
Details of Ultrasonic sensor usage here: https://RandomNerdTutorials.com/esp32-hc-sr04-ultrasonic-arduino/
Bluetooth library from https://github.com/pschatzmann/ESP32-A2DP
The sound array file (toot.h) can be prepared e.g. in the following way:
    Open any sound file in Audacity.
        Select Tracks -> Resample and select 44100
        Export -> Export Audio -> Header Raw ; Signed 8 bit PCM
    Convert to c file e.g. with "xxd -i file_example_WAV_1MG.raw file_example_WAV_1MG.c"
    add the const qualifier to the generated array definition. E.g const unsigned char file_example_WAV_1MG_raw[] = {
    Note: used 8-bit rather than 16bit as limited memory on my board. Also found using 16bit produced a very high noise floor.


![ESP32_Ultrasonic_bb](https://github.com/GSVNoFixedabode/NoiseBox/assets/13099660/6d1c9d3a-d694-4a83-b7d0-27a33b7d80af)

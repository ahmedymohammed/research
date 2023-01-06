#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <SD.h>

File myFile;


MPU6050 mpu;

// stime == the time spent since the Arduino started taking MPU readings | offtime == time between powering up the Arduino and taking the readings

float stime; 
int offtime;

void setup() 
{
  Serial.begin(115200);
  Serial.print("Initializing SD card...");
  // SD.begin(x) == initializes the SD card module. the CS pin on the SD card module has to be connected to pin (x) in the arduino (in out case, pin 4)
  while (!SD.begin(4)) {
    Serial.println("initialization failed!");
    delay(500);
  }
    Serial.println("initialization done.");
    


  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }


   mpu.setAccelOffsetX(-5685);
   mpu.setAccelOffsetY(-1537);
   mpu.setAccelOffsetZ(1049);
   
  delay(3000);
  
  // millis() returns the number of milli seconds spent since the Arduino's last restart
  offtime = millis();
}

void loop()
{

  stime = (millis()-offtime)/1000.0;
  Vector normAccel = mpu.readNormalizeAccel();
  Serial.println(stime, 5); 

// This part writes to the SD card module. You have to open a file first before writing to it, and you also need to close it after writing to it
// This part opens (or creates if not present) a file named DATA.txt and writes time, and the three accelerations to it in a comma-seperated values form

    myFile = SD.open("data.txt", FILE_WRITE);
    if (myFile) {
      myFile.print(stime, 5); myFile.print(", ");
      myFile.print(normAccel.XAxis, 5);myFile.print(", ");
      myFile.print(normAccel.YAxis, 5);myFile.print(", ");
      myFile.println(normAccel.ZAxis, 5);
      myFile.close();
    }
    else {Serial.println("Failed to save to SD card");}

    delay(100);
    

}

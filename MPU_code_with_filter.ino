#include <Wire.h>
#include <MPU6050.h>
#define WINDOW_SIZE 5

MPU6050 mpu;

// tacc == the sum of accelerations in 3 axes | taccn == filtered sum of accelerations | INDEX == an index of 0, 1, or 2 refers to x, y, and z accelerations, respectively
// SUM == refers to the summation of a number of consecutive acceleration readings depending on the window size
// READINGS == stores the last number of readings (depending on the window size) in the three axes | AVERAGED == averaged acceleration values in the three axes

double tacc;
double taccn;
int INDEX = 0;
double SUM [3];
double READINGS[3][WINDOW_SIZE];
double AVERAGED [3];

void setup() 
{
  Serial.begin(115200);

// Initialize the mpu
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }

  // If you want, you can set accelerometer offsets
   mpu.setAccelOffsetX(-5685);
   mpu.setAccelOffsetY(-1537);
   mpu.setAccelOffsetZ(1049);
  
 
}

void loop()
{

  //rawAccel reads the raw acceleration and normAccel outputs the acceleration in m/s^2
//  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();

//  Serial.print(" Xraw = ");
//  Serial.print(rawAccel.XAxis);
//  Serial.print(" Yraw = ");
//  Serial.print(rawAccel.YAxis);
//  Serial.print(" Zraw = ");
//  Serial.println(rawAccel.ZAxis);
  
//  Serial.print(" Xnorm = ");
//  Serial.print(normAccel.XAxis);
//  Serial.print(" Ynorm = ");
//  Serial.print(normAccel.YAxis);
//  Serial.print(" Znorm = ");
//  Serial.println(normAccel.ZAxis);
//  Serial.print("Total Acceleration: ");

// Calculate the averaged accelerations for the three axes

  for (int index=0; index<=2; index++){
     
  SUM[index] = SUM[index] - READINGS[index][INDEX];    
    switch (index){
      case 0:
      READINGS[index][INDEX] = normAccel.XAxis;
      SUM[index] = SUM[index] + normAccel.XAxis; /*Serial.print("X-acceleration: ");*/ break; 
      case 1:
      READINGS[index][INDEX] = normAccel.YAxis;
      SUM[index] = SUM[index] + normAccel.YAxis; /*Serial.print("Y-acceleration: ");*/ break;
      case 2:
      READINGS[index][INDEX] = normAccel.ZAxis;
      SUM[index] = SUM[index] + normAccel.ZAxis; /*Serial.print("Z-acceleration: "); */break; 
                  }
  INDEX = (INDEX+1) % WINDOW_SIZE;       
  AVERAGED[index] = SUM[index] / WINDOW_SIZE;
  //Serial.print(AVERAGED[index]);      // When this line is uncommented, it prints the averaged values of accelerations in x, y, and z for every for loop     
                                      } // End of for loop

  // Calculate the total averaged and normal accelerations
  
  tacc=sqrt(pow(AVERAGED[0],2) + pow(AVERAGED[1],2) + pow(AVERAGED[2],2));
  taccn=sqrt(pow(normAccel.XAxis,2) + pow(normAccel.YAxis,2) + pow(normAccel.ZAxis,2));

//    Serial.print(tacc);             //the first variable for plotting
//    Serial.print(",");              //seperator
//    Serial.println(taccn);          //the second variable for plotting including line break

      //Serial.println(normAccel.XAxis*0.9665);
      //Serial.print(" ");
      Serial.print("Filtered_Acceleration: ");
      Serial.println(AVERAGED[0]);
      delay(5);
}

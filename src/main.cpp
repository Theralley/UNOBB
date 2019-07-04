#include <Arduino.h>

#include <SoftwareSerial.h>
#include "TinyGPS++.h"
#include <SD.h>
#include <SPI.h>
#include<Wire.h>

//Define variables
unsigned long time;
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int fixed = 0;
int led = 13;
int chipSelect=4;

TinyGPSPlus gps;
SoftwareSerial SoftSerial(2, 3);
File mySensorData;

//LOOP
void setup()
{
//Printing to monitor
  //GPS
    pinMode(led, OUTPUT);
    SoftSerial.begin(9600);  // the SoftSerial baud rate
    Serial.begin(9600);      // the Serial port of Arduino baud rate.
  //Gyro/Acc
    Wire.begin();
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B);  // PWR_MGMT_1 register
    Wire.write(0);     // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
  //SD
    pinMode(10, OUTPUT);
    SD.begin(chipSelect);
  //Create a Textfile to SD-card
  mySensorData = SD.open("DataLogger.txt", FILE_WRITE);
  }

void loop() {
  float a = 180/3.141592;
{
  while (SoftSerial.available() > 0)
  gps.encode(SoftSerial.read());

  //Time print monitor
  time = millis();
  Serial.print(" | Time = "); Serial.print(time);

  //GPS print monitor
  if (gps.location.isUpdated())
  {
    fixed = 1;
    Serial.print(" | LAT = "); Serial.print(gps.location.lat(), 6);
    Serial.print(" | LNG = "); Serial.println(gps.location.lng(), 6);
    float fkmph = gps.speed.kmph(); // speed in km/hr
    Serial.print(" | Speed = "); Serial.println(fkmph);
    Serial.print(" | Altitude = ");
    Serial.println(gps.altitude.meters());
  }

  if(fixed ==0)
  {
     Serial.print(" | LAT = No Signal");
     Serial.print(" | LNG = No Signal");
     Serial.print(" | Speed = No Signal");
     Serial.print(" | Altitude = No Signal");
     digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(300);               // wait for a second
     digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    // delay(10);
  }

  //Accelerometer and gyro print monitor
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print(" | AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Temp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(10);

//Printing to SD card
  //Time
  mySensorData.print(" | Time = "); mySensorData.print(time);

  //GPS
  if (gps.location.isUpdated())
  {
    fixed = 1;
    mySensorData.print(" | LAT = "); mySensorData.print(gps.location.lat(), 6);
    mySensorData.print(" | LNG = "); mySensorData.println(gps.location.lng(), 6);
    mySensorData.print(" | Speed = "); mySensorData.println(gps.speed.kmph());
    mySensorData.print(" | Altitude = ");
    mySensorData.println(gps.altitude.meters());
  }

  if(fixed ==0)
  {
    mySensorData.print(" | LAT = No Signal");
    mySensorData.print(" | LNG = No Signal");
    mySensorData.print(" | Speed = No Signal");
    mySensorData.print(" | Altitude = No Signal");
  }

  //Accelerometer and Gyro
  mySensorData.print(" | AcX = "); mySensorData.print(AcX);
  mySensorData.print(" | AcY = "); mySensorData.print(AcY);
  mySensorData.print(" | AcZ = "); mySensorData.print(AcZ);
  mySensorData.print(" | Temp = "); mySensorData.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  mySensorData.print(" | GyX = "); mySensorData.print(GyX);
  mySensorData.print(" | GyY = "); mySensorData.print(GyY);
  mySensorData.print(" | GyZ = "); mySensorData.println(GyZ);
 }

}

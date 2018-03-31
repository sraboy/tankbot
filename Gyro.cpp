#include "Gyro.h"
#include <Wire.h>
#include <Arduino.h>

namespace Gyro {

  int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

  void Setup() {
    Wire.begin();
    Wire.beginTransmission(Addr);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Serial.println(F("MPU Setup complete"));
  }

  void Read() {
    Wire.beginTransmission(Addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);

    Wire.requestFrom(Addr, 14, true);
    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    Tmp = Wire.read() << 8 | Wire.read();
    GyX = Wire.read() << 8 | Wire.read();
    GyY = Wire.read() << 8 | Wire.read();
    GyZ = Wire.read() << 8 | Wire.read();

//    Serial.print("Accelerometer: ");
//    Serial.print("X = ");
//    Serial.print(AcX);
//    Serial.print(" | Y = ");
//    Serial.print(AcY);
//    Serial.print(" | Z = ");
//    Serial.println(AcZ);
//
//    Serial.print("Temperature: ");
//    Serial.print(" | Tmp = ");
//    Serial.println(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
//
//    Serial.print("Gyroscope: ");
//    Serial.print("X = "); Serial.print(GyX);
//    Serial.print(" | Y = "); Serial.print(GyY);
//    Serial.print(" | Z = "); Serial.println(GyZ);
//    Serial.println(" ");
  }

} //namespace Gyro


#include<Wire.h>
// defines pins numbers
const int trigPin = 25;
const int echoPin = 33;
const int trigPindown = 27;
const int echoPindown = 26; 
const int buzzer = 32;
const int MPU = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
//bool sound = true;

// defines variables
long duration;
int distance;
long durationdown; 
int distancedown;

int freq = 2000;
int channel = 0;
int resolution = 8;


void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(trigPindown, OUTPUT);
  pinMode(echoPindown, INPUT);
  pinMode(buzzer, OUTPUT);

  ledcSetup(channel, freq, resolution);
  ledcAttachPin(32, channel);

  //IMU
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor

  // Clears the trigPin
  digitalWrite(trigPindown, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPindown, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPindown, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationdown = pulseIn(echoPindown, HIGH);
  // Calculating the distance
  distancedown = durationdown * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Distance Down: "); 
  Serial.println(distancedown); 
  

  if(distance<50){
      sound();
    }
  if(distancedown>40 && distance<100){
      sounddown();
    }



Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ);
  
  //equation for temperature in degrees C from datasheet
  Serial.print("Temperature: "); Serial.print(Tmp / 340.00 + 36.53); Serial.println(" C ");

  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  delay(333);
    
}

//sound functions

void sound(){
  int dutyCycle;
  ledcWriteTone(channel, 1000);
  for (dutyCycle = 0; dutyCycle <= 55; dutyCycle=dutyCycle+10){
    //Serial.println(dutyCycle);
    ledcWrite(channel, 30);
    delay(10);
  }
  ledcWrite(channel, 0);
}

void sounddown(){
   int dutyCycle;
  ledcWriteTone(channel, 2000);
  for (dutyCycle = 0; dutyCycle <= 55; dutyCycle=dutyCycle+10){
    //Serial.println(dutyCycle);
    ledcWrite(channel, 30);
    delay(10);
  }
  ledcWrite(channel, 0);
}

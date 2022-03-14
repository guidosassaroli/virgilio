// defines pins numbers
const int trigPin = 25;
const int echoPin = 33;
const int trigPindown = 27;
const int echoPindown = 26; 
const int buzzer = 32;

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
  if(distancedown>40 && distancedown<100){
      sounddown();
    }

    
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

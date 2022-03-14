// defines pins numbers
const int trigPin = 2;
const int echoPin = 5;
const int trigPindown = 4;
const int echoPindown = 7; 
const int buzzer = 9;

//bool sound = true;

// defines variables
long duration;
int distance;
long durationdown; 
int distancedown;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(trigPindown, OUTPUT);
  pinMode(echoPindown, INPUT);
  pinMode(buzzer, OUTPUT);
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
  
  
  if(distance < 50){
    sound();

  }
  
  //delay(1000);  
  
  if(distancedown<100 and distancedown>40){
      sound2();
    }
    
    
}

void sound(){
  tone(buzzer, 1000); // Send 1KHz sound signal
  delay(500);       
  noTone(buzzer);
}

void sound2(){
  tone(buzzer, 400); // Send 0.3KHz sound signal
  delay(500);       
  noTone(buzzer);
}

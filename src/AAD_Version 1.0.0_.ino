/*
  AAD 1.0.0
  Arduino Automatized Door, written by Mombano e Carpento - didactic project
  If you use this code, you accept terms in the license.
  Last modify: 18/11/2026
*/

//Defining pin
#define photoPin A0
#define servoPin_1 10
#define servoPin_2 11

//Defining time costants
const int totalTime = 20000;
const int intercept = 500;
float angleTime = 11.11;

//Defining variables
bool servo_state = 0;
float intValue = 0;

//Opening function
void opening(){
  for(int cont=0;cont<=90;cont++){
    digitalWrite(servoPin_1, HIGH);
    digitalWrite(servoPin_2, HIGH);
    delayMicroseconds(intercept+angleTime*cont);
    digitalWrite(servoPin_1, LOW);
    digitalWrite(servoPin_2, LOW);
    delayMicroseconds(totalTime-(intercept+angleTime*cont));
  }
  servo_state = 1;
}

//Closing function
void closing(){
  for(int cont=90;cont>=0;cont--){
    digitalWrite(servoPin_1, HIGH);
    digitalWrite(servoPin_2, HIGH);
    delayMicroseconds(totalTime-(intercept+angleTime*cont));
    digitalWrite(servoPin_1, LOW);
    digitalWrite(servoPin_2, LOW);
    delayMicroseconds(intercept+angleTime*cont);
  }
  servo_state = 0;
}

//Ambient light detecting
void lightDetecting(){
  float analogValue = analogRead(photoPin);
  intValue = map(analogValue, 235, 1010, 0, 5);
}

void setup() {
  //Setting pin at the start of the Arduino
  pinMode(photoPin, INPUT_PULLUP); 
  pinMode(servoPin_1, OUTPUT);
  pinMode(servoPin_2, OUTPUT);
  //Setting serial monitor
  Serial.begin(9600);
}

void loop() {
  //This code runs repeadetly
  lightDetecting();
  if(intValue<2){
    if(servo_state==0){
      opening();
    }
    if(servo_state==1){
      digitalWrite(servoPin_1, LOW);
      digitalWrite(servoPin_2, LOW);
    }
  }
  if(intValue>=2){
    if(servo_state==1){
      closing();
    }
    if(servo_state==0){
      digitalWrite(servoPin_1, LOW);
      digitalWrite(servoPin_2, LOW);
    }
  }
}

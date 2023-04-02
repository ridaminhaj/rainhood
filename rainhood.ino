#define sensorPinL A3
#define sensorPinM A4
#define sensorPinH A5

const int maxVL = 100;
const int maxVM = 200;
const int maxVH = 300;

boolean isRain = false;
int rainMode = 0;


#include <AccelStepper.h>

const int stepsPerRevolution = 200;
const int stepsToOpen = 34;

const int dirPin = 2;
const int stepPin = 3;

#define motorInterfaceType 1

AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT);

  myStepper.setCurrentPosition(0);
  myStepper.setMaxSpeed(1000);
  myStepper.setAcceleration(50);
  myStepper.setSpeed(60);
  myStepper.moveTo(120);

  pinMode(sensorPinL, INPUT);
  pinMode(sensorPinM, INPUT);
  pinMode(sensorPinH, INPUT);
  pinMode(A0, OUTPUT);

}

void loop() {
  Serial.println(sensorOutput());

  if (isRain == true) {
    for (int i = 0; i < 3; i++){
      if (isRain == false) {
        break;
      }

      if (i == 2) {
        Serial.println("begin opening mechanism");
        while (myStepper.distanceToGo()!=0) {
          myStepper.runSpeedToPosition();
          analogWrite(A0, 100);
        }

        while (isRain == true) {
          Serial.println(sensorOutput());
          delay(1000);
        }

        Serial.println("begin closing mechanism");
        int currentPosition = myStepper.currentPosition();
        myStepper.moveTo(currentPosition-120);
        while(myStepper.distanceToGo()!=0){
          myStepper.runSpeedToPosition();
        }
        break;
      }

      delay(1000);
    }
  }
  delay(1000);
}

String sensorOutput() {
  int valL = analogRead(sensorPinL);
  int valM = analogRead(sensorPinM);
  int valH = analogRead(sensorPinH);

  if (valL > maxVL) {
    isRain = true;
    rainMode = 1;
  }

  else if (valL < maxVL/2) {
    isRain = false;
    rainMode = 0;
  }

  if (valM > maxVM){
    rainMode = 2;
  }

  if (valH > maxVH){
    rainMode = 3;
  }

  String percentval = String((valL*100)/maxVL);

  return (percentval + "%, which is in raw digital value " + valL);
}

int setUrgency() {
  int speed = 60;

  if (rainMode = 2){
    speed = 70;
  }

  if (rainMode = 3) {
    speed = 80;
  }

  myStepper.setSpeed(speed);

  return speed;
}

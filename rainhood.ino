#define sensorPin A0
int maxV = 660;
boolean isRain = false;

void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT);
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

        while (isRain == true) {
          Serial.println(sensorOutput());
          delay(1000);
        }

        Serial.println("begin closing mechanism");
        break;
      }

      delay(1000);
    }
  }
  delay(1000);
}

String sensorOutput() {
  int val = analogRead(sensorPin);

  if (val > 150) {
    isRain = true;
  }

  else if (val < 80) {
    isRain = false;
  }

  String percentval = String((val*100)/maxV);

  return (percentval + "%, which is in raw digital value " + val);
}

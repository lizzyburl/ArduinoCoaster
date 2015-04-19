#include <Time.h>
/* 
We will have to gather temperature sensor and light sensor data and write it to a csv file to train.

*/

// Sensors
const int lightSensorPin = 0, mugTemperatureSensor = 1;
const int okButton = 2, speakerPin = 8;
// Output
const int mugOnLED = 9;

// two-color LED constants
const int LEDOrangePin = 12;
const int LEDGreenPin = 11;
const int LEDon = 255;
const int LEDoff = 0;

int lightLevel, ledVal, cupIsOn = 0, tooHot=1;
long startTime;

float temp;
//define the tones to play with the buzzer 
const int tones[] = {440, 415}; // A, G#
const int numTones = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(mugOnLED, OUTPUT);
  pinMode(okButton, INPUT);
  Serial.begin(9600);
  // change two-color LED to output mode
  pinMode(greenPin, OUTPUT);
  pinMode(orangePin, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  lightLevel = analogRead(lightSensorPin);
  Serial.println(digitalRead(okButton));
  if (!digitalRead(okButton))
  {
     tooHot = -1; 
  }
  // If the mug is on
  if (IsCovered())
  {
    ledVal = 255;
    // If the mug was not previously on.
    if (!cupIsOn)
    {
      startTime = now();
      cupIsOn = 1;
    }
    float tempSensorReading = analogRead(mugTemperatureSensor);
    float mugVolt = (tempSensorReading * 5.0) / 1024.0;
    float mugTempF = GetTempInFFromVoltage(mugVolt);
    int elapsedTime = now() - startTime;
    WriteToCSV(mugTempF, elapsedTime, tooHot);
    // This is where we will write it to a cvs file.
  }
  else
  {
    // not covered and was previously covered
    if(cupIsOn) // TODO: && if temperature is too hot, play tone
    {
      PlayTone();
    }
    ledVal = 0;
    if (cupIsOn)
    {
      cupIsOn = 0;
    }
    
  }
  delay(1000);
  
}

void WriteToCSV(float mugTempF, int elapsedTime, int tooHot)
{
  Serial.print(tooHot);
  Serial.print(",");
  Serial.print(mugTempF);
  Serial.print(",");
  Serial.println(elapsedTime);
  delay(150);
}


float GetTempInFFromVoltage(float voltage)
{
  // 100 * 9 / 5
  return ((voltage - 0.5) * 180.0) + 32.00;
}

// If the mug is on the coaster
int IsCovered()
{
 if (lightLevel >200)
{
  return 1;
}
 return 0; 
}

void PlayTone()
{
  for (int i = 0; i < numTones; i++)
  {
    tone(speakerPin, tones[i]);
    delay(150);
  }
  noTone(speakerPin);
}


// provide the status variable as 'LEDon' to turn that color on, or 'LEDoff' to turn that color off
// ex: greenStatus = LEDon && orangeStatus = LEDoff would give a true green 
void LEDColor(orangeStatus, greenStatus)
{
    analogWrite(orangePin, orangeStatus);
    analogWrite(greenPin, greenStatus);
}

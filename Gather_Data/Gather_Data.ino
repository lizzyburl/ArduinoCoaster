#include <Time.h>
/* 
 We will have to gather temperature sensor and light sensor data and write it to a csv file to train.
 
 */

// Sensors
const int lightSensorPin = 0, mugTemperatureSensor = 1;
const int okButton = 2, speakerPin = 8;
boolean buttonState, lastButtonState;
// Output
const int mugOnLED = 9;

// two-color LED constants
const int LEDOrangePin = 11;
const int LEDGreenPin = 12;
const int LEDon = 255;
const int LEDoff = 0;

int lightLevel, ledVal, cupIsOn = 0, tooHot=1;
long startTime;
boolean tooHotToHandle = true;

float temp, prevTemp;
//define the tones to play with the buzzer 
const int tones[] = {
  440, 415}; // A, G#
const int happy_tones[] = {
  415, 440}; // A, G#
const int numTones = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(mugOnLED, OUTPUT);
  pinMode(okButton, INPUT);
  Serial.begin(9600);
  // change two-color LED to output mode
  pinMode(LEDGreenPin, OUTPUT);
  pinMode(LEDOrangePin, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  lightLevel = analogRead(lightSensorPin);
  //----- recently added 
  buttonState = digitalRead(okButton);
  float tempSensorReading = 0;

  // Recieve data from Node and write it to a String
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      Serial.println("Hot");
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println(""); 
    } 
  }  
  // -----
  Serial.println(digitalRead(okButton));
  if (!digitalRead(okButton))
  {
    tooHot = -1; 
  }
  if (IsCovered()) // If the mug is on
  {
    ledVal = 255;
    if (!cupIsOn) // If the mug was not previously on.
    {
      startTime = now();
      cupIsOn = 1;
    }
    int n = 10;
    while(n > 0)
    {
      float currentTemp = analogRead(mugTemperatureSensor);
      currentTemp = (currentTemp * 5.0) / 1024.0;
      currentTemp = GetTempInFFromVoltage(currentTemp);
      tempSensorReading += currentTemp;
      n--;
      delay(100);
    }
    tempSensorReading/=10.0;
    float dy = tempSensorReading - prevTemp;
    int elapsedTime = now() - startTime;
    float y = 0.008*tempSensorReading - 0.002*elapsedTime + 0.02519*dy - .61;
    Serial.print("y is:");
    Serial.println(y);
        Serial.print("mugTempF is:");
    Serial.println(tempSensorReading);
        Serial.print("elapsedTime is:");
    Serial.println(elapsedTime);
        Serial.print("dy is:");
    Serial.println(dy);
    if(y > 0)
    {
      //Serial.print("Too hot!");
      tooHotToHandle = true;
      LEDColor(LEDon, LEDoff);
    }
    else
    {
      //Serial.print("Okay to drink");
      LEDColor(LEDoff, LEDon);
      tooHotToHandle = false;
      PlayTone(tooHotToHandle);
    }
  }
  else
  {
    if(cupIsOn && tooHotToHandle) // not covered and was previously covered
    {
      PlayTone(tooHotToHandle);
    }
    ledVal = 0;
    LEDColor(LEDoff, LEDoff);
    if (cupIsOn)
    {
      cupIsOn = 0;
    }

  }

  prevTemp = tempSensorReading;
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
  return ((voltage - 0.5) * 180.0) + 32.00;
}

int IsCovered() // If the mug is on the coaster
{
  if (lightLevel >200)
  {
    return 1;
  }
  return 0; 
}

void PlayTone(boolean tooHot)
{
  for (int i = 0; i < numTones; i++)
  {
    if (tooHot) {
      tone(speakerPin, tones[i]);
    } else {
      tone(speakerPin, happy_tones[i]);
    }
    delay(150);
  }
  noTone(speakerPin);
}


// provide the status variable as 'LEDon' to turn that color on, or 'LEDoff' to turn that color off
// ex: greenStatus = LEDon && orangeStatus = LEDoff would give a true green 
void LEDColor(int orangeStatus, int greenStatus)
{
  analogWrite(LEDOrangePin, orangeStatus);
  analogWrite(LEDGreenPin, greenStatus);
}


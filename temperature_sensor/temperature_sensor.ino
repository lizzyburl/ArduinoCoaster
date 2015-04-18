// original code found at http://www.instructables.com/id/LM35-LED-Temperature-Bar/?ALLSTEPS
// more code found at https://learn.adafruit.com/tmp36-temperature-sensor/using-a-temp-sensor
// edits by Olivia Whitman 

float temp;
int tempPin = 0;//the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
int pin2 = 2;
int pin3 = 3;
int pin4 = 4;
int pin5 = 5;
int pin7 = 7;
int pin8 = 8;
int pin9 = 9;
int pin10 = 10;
void setup()
{
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin10, OUTPUT);
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 
}

void loop()
{
  temp = analogRead(tempPin);
 float voltage = temp * 5.0;
 voltage /= 1024.0; 
 
 // print out the voltage
 Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); Serial.println(" degrees F");
  Serial.println();
  if(temperatureC>=16.00){digitalWrite(pin10,HIGH);}
  if(temperatureC>=17.00){digitalWrite(pin9,HIGH);}
  if(temperatureC>=18.00){digitalWrite(pin8,HIGH);}
  if(temperatureC>=19.00){digitalWrite(pin7,HIGH);}
  if(temperatureC>=20.00){digitalWrite(pin5,HIGH);}
  if(temperatureC>=21.00){digitalWrite(pin4,HIGH);}
  if(temperatureC>=22.00){digitalWrite(pin3,HIGH);}
  if(temperatureC>=23.00){digitalWrite(pin2,HIGH);}
  delay(1000); // wait a second
  digitalWrite(pin10,LOW);
  digitalWrite(pin9,LOW);
  digitalWrite(pin8,LOW);
  digitalWrite(pin7,LOW);
  digitalWrite(pin5,LOW);
  digitalWrite(pin4,LOW);
  digitalWrite(pin3,LOW);
  digitalWrite(pin2,LOW);
  delay(1);
}


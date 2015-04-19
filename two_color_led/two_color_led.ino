int greenPin = 11;
int orangePin = 12;
int LEDon = 255;
int LEDoff = 0;

void setup()
{
 pinMode(greenPin, OUTPUT);
 pinMode(orangePin, OUTPUT); 
}

void loop(){
   
// supplying 255 to a pin will light up that color
  analogWrite(orangePin, LEDoff);
  analogWrite(greenPin, LEDon);
}

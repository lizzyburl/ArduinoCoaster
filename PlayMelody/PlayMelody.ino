// original code from https://learn.adafruit.com/adafruit-arduino-lesson-10-making-sounds/playing-a-scale
// edits made by Olivia Whitman

int speakerPin = 8;
 
int numTones = 2; /*10;*/
int tones[] = {440, 415}; //warning tone
//int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};*/
//            mid C  C#   D    D#   E    F    F#   G    G#   A
 
void setup()
{
  for (int i = 0; i < numTones; i++)
  {
    tone(speakerPin, tones[i]);
    delay(150);
  }
  noTone(speakerPin);
}
 
void loop()
{
}

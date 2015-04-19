int buttonPin = 2;
boolean buttonState;
boolean lastButtonState;

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


 void loop() {
   
   // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
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
} 

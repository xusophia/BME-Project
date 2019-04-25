int vibration1 = 6		// sets vibration1 to be D0 (Pin no. 1), digital

void setup() {
  pinMode(vibration1, OUTPUT);    // sets the digital pin 1 as output
  // may need to set pin automatically to be low
}

void forward() {

// If statement needed here, or in main. 
// Some type of while condition is needed here
  // These 4 lines turn the Pins on/off (duty cycle). 
  // Alternatively, use PWM. 	
while(1){
  digitalWrite(vibration1, HIGH); // sets the digital pin 13 on
  // input into 
  delay(1000);            // waits for a second 
  digitalWrite(vibration1, LOW);  // sets the digital pin 13 off
  delay(1000);            // waits for a second
 }
}

void main(){
// Call setup to set up pins digital output
	setup();
	forward();


	// while(1)
	// collect data

}

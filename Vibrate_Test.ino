int vibration1 = 6;
int xRead;
int yRead;
int zRead;
int xMinVal = 265; int yMinVal = 259;int zMinVal = 281;
int xMaxVal = 398; int yMaxVal = 393;int zMaxVal = 413;
int ave = 10;
int x_input;
int y_input;
int z_input;


void setup() {
  // put your setup code here, to run once:
   pinMode(vibration1, OUTPUT);    // sets the digital pin 1 as output
  // may need to set pin automatically to be low
  
  // Set up Analog Pins A0, A1, A2 for x, y, and z analog inputs
  pinMode(x_input, INPUT);
  pinMode(y_input, INPUT);
  pinMode(z_input, INPUT);
  
  // TIMER 1 for interrupt frequency 60.00060000600006 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 60.00060000600006 Hz increments
  OCR1A = 33332; // = 16000000 / (8 * 60.00060000600006) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 8 prescaler
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
}

void loop() {
  // put your main code here, to run repeatedly:
  setup();
  digitalWrite(vibration1, HIGH); // sets the digital pin 13 on
  // input into 
  delay(1000);            // waits for a second 
  digitalWrite(vibration1, LOW);  // sets the digital pin 13 off
  delay(1000);            // waits for a second
}

void Analog_Calculations(){
 	// Average 
 	xRead = xRead/ave;
 	yRead = yRead/ave;
 	zRead = zRead/ave;
 	// Convert to angles
  xAng = map(xRead, xMinVal, xMaxVal, -90, 90);
  yAng = map(yRead, yMinVal, yMaxVal, -90, 90);
  zAng = map(zRead, zMinVal, zMaxVal, -90, 90);
 }

// Timer 1 Interrupt Handler
// Collect data from 3 axis accelerometer
// declare global variables int xRead, yRead, zRead
ISR(Timer1_OVF_vect){
  xRead = 0;  // not sure about this hehe
  yRead = 0;
  zRead = 0;
	for(int i=0; i<ave ; i++){
    	xRead += analogRead(A0);
   		yRead += analogRead(A1);
    	zRead += analogRead(A2);
  	}
 }

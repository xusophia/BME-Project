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
()
{
  
  //start reading the button state
  buttonState = digitalRead(buttonPin);

  // if msg is sent by bluetooth from the app, write it on the console (not used in that project)
  /*
 myiShield.readConsole();
 String message = myiShield.incomingData();
 Serial.println(message);
 */
  
  
  // Start reading and calculating angles
  float VREF = 5.0;
  
  // To get those values, play with your accelerometer and put the min and max you find on every x,y,z position
  int xMinVal = 265; int yMinVal = 259;int zMinVal = 281;
  int xMaxVal = 398; int yMaxVal = 393;int zMaxVal = 413;

  int xRead=0, yRead=0, zRead=0;
  
  int xAng=0, yAng=0, zAng=0;
  double x=0, y=0, z=0;
  
  int ave = 10;

  // read raw values
  for(int i=0; i<ave ; i++)
  {
    xRead += analogRead(A0);
    yRead += analogRead(A1);
    zRead += analogRead(A2);
  }

  xRead = xRead/ave;
  yRead = yRead/ave;
  zRead = zRead/ave;

  // convert to angles
  xAng = map(xRead, xMinVal, xMaxVal, -90, 90);
  yAng = map(yRead, yMinVal, yMaxVal, -90, 90);
  zAng = map(zRead, zMinVal, zMaxVal, -90, 90);
  
  x = 57.2957795 * (atan2(-yAng, -zAng) + 3.14159265359);
  y = 57.2957795 * (atan2(-xAng, -zAng) + 3.14159265359);
  z = 57.2957795 * (atan2(-yAng, -xAng) + 3.14159265359);


  char xTempString[10];  //  Hold The Convert Data
  
  // convert position in string to display it
  dtostrf(x,3,2,xTempString); // dtostrf( [doubleVar] , [sizeBeforePoint] , [sizeAfterPoint] , [WhereToStoreIt] )
  String xString = String(xTempString);  // cast it to string from char 

    /*
  // wrtie value that will be read on the mobile device
  myiShield.writeConsole(xString); 
 */
  currentBackPos = x;

  //if the button is pressed set the value of base position to the current back position 
  // this sets a "normal" state that the code will then measure a difference from. 
  if (buttonState == HIGH) {  
    
 //   myiShield.writeConsole("button pressed"); 
    refPos = currentBackPos; 
    
    
    char bkpTempString[10];  //  Hold The Convert Data
    dtostrf(currentBackPos,3,2,bkpTempString); // dtostrf( [doubleVar] , [sizeBeforePoint] , [sizeAfterPoint] , [WhereToStoreIt] )
    String bkpString = String(bkpTempString);  // cast it to string from char 
//    myiShield.writeConsole("currentBackPos :");
//    myiShield.writeConsole(bkpString); 
    
    char bpTempString[10];  //  Hold The Convert Data
    dtostrf(refPos,3,2,bpTempString); // dtostrf( [doubleVar] , [sizeBeforePoint] , [sizeAfterPoint] , [WhereToStoreIt] )
    String bpString = String(bpTempString);  // cast it to string from char 
//    myiShield.writeConsole("refPos :");
//    myiShield.writeConsole(bpString); 
  } 
    
  //if backPos is in a bad postion
  if(currentBackPos > refPos + 20){
//    myiShield.writeConsole("wrong");
  
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
  else {
    if(currentBackPos > refPos + 10){
//      myiShield.writeConsole("warning");
    
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
    }
    else{
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, LOW);
      digitalWrite(LED3, LOW);
  
    }
  }
// add the code for the vibrating motor HERE
// ??? use the driver 
//figure out the threshhold then make a if and else statements regarding it 
// figure out how to change the voltage thar way 

  delay(2000);
  
}

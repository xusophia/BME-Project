#include <math.h>
#include "Boards.h"
#include <SPI.h>
//#include <Nordic_nRF8001.h>
//#include <RBL_nRF8001.h>
//#include "iShield.h"

//iShield myiShield;

// momentary switch
const int buttonPin = 2;

int LED1 = 3; // Red
int LED2 = 4; // Green
int LED3 = 5; // Yellow


int buttonState = 0; 

// Position set when the momentary witch is pressed
int currentBackPos;

// Value set as the "normal position" (= flat value on my accelerometer as mine is not solder so the angle is already "forward")
int refPos = 15;

//vibration motor digital pin
//int vibePin = 9;

void setup()
{
  /*
  // Init. and start BLE library.
  ble_begin();
  Serial.begin(9600); 
  ble_set_name("BLEShield");
  */  
  //pinMode(buzzerPin, OUTPUT);
    
  pinMode(LED1, OUTPUT); // Red
  pinMode(LED2, OUTPUT); // Green
  pinMode(LED3, OUTPUT); // Yellow
  
  digitalWrite(LED1,LOW); // Red
  digitalWrite(LED2,LOW); // Green
  digitalWrite(LED3,LOW); // Yellow

  pinMode(2, INPUT); // SwitchButton (to set "normal" position)
}

void loop()
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

  delay(2000);
  
}

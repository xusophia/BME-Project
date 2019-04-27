//Example AnalogRead() code
int vibration1 = 12;
int vibration2 = 11;

int i;

int val0;
int val1;
int val2;

int x_input = A0;
int y_input = A1;
int z_input = A2;


void setup() {
  Serial.begin(9600);           //  setup serial
  pinMode(vibration1, OUTPUT);    // sets the digital pin 1 as output
   //digitalWrite(vibration1, HIGH); 
    pinMode(vibration2, OUTPUT);    // sets the digital pin 1 as output
  // digitalWrite(vibration2, HIGH); 
}

void loop() {


  for ( i = 0; i<10; i++){
    val0 = 0;
    val1 = 0;
    val2 = 0;

    val0 += analogRead(A0);  // read the input pin
    val1 += analogRead(A1);
    val2 += analogRead(A2);

  }
  val0 = val0/10;         // calculates average
  val1 = val1/10;
  val2 = val2/10;
  Serial.print(val0+'\t');          // debug value
  Serial.print(val1 +'\t');
  Serial.println(val2 +'\t');

  // This detects is the gait is too far foward
  while (val0 !=0){
    while(  (270 >val0) ||( val0 >310)){
      digitalWrite(vibration1, HIGH); // sets the digital pin 13 on
      delay(1000);            // waits for a second 
      digitalWrite(vibration1, LOW);  // sets the digital pin 13 off
      delay(1000);     
      
      for ( i = 0; i<10; i++){
        val0 = 0;
        val1 = 0;
        val2 = 0;
        val0 += analogRead(A0);  // read the input pin
        val1 += analogRead(A1);
        val2 += analogRead(A2);
      }
      val0 = val0/10;
      val1 = val1/10;
      val2 = val2/10;
    }  
  }
  digitalWrite(vibration1, LOW); 
  for ( i = 0; i<10; i++){
        val0 = 0;
        val1 = 0;
        val2 = 0;
        val0 += analogRead(A0);  // read the input pin
        val1 += analogRead(A1);
        val2 += analogRead(A2);
      }
      val0 = val0/10;
      val1 = val1/10;
      val2 = val2/10;
}

 
 

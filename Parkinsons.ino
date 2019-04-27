//Example AnalogRead() code



void setup() {
  Serial.begin(9600);           //  setup serial
}

void loop() {
  int x_input = A0;
  int y_input = A1;
  int z_input = A2;

  //int val0 = 0;  // variable to store the value read
  //int val1 = 1;
  //int val2 = 2;
  int val0 = analogRead(A0);  // read the input pin
  Serial.println(val0);          // debug value

  int val1 = analogRead(A1);
  Serial.println(val1);

  int val2 = analogRead(A2);
  Serial.println(val2);

}

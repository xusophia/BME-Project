int vibration1 = 13;

void setup() {
  // put your setup code here, to run once:
   pinMode(vibration1, OUTPUT);    // sets the digital pin 1 as output
   digitalWrite(vibration1, HIGH); 
  // may need to set pin automatically to be low

}

void forward() {
  // put your main code here, to run repeatedly:
  setup();
  digitalWrite(vibration1, HIGH); // sets the digital pin 13 on
  // input into 
  delay(1000);            // waits for a second 
  digitalWrite(vibration1, LOW);  // sets the digital pin 13 off
  delay(1000);            // waits for a second
}
int main(){
// Call setup to set up pins digital output
  setup();
  forward();



}

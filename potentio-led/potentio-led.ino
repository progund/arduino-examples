int input_pin= A0; // Use A0 as input (from potentiometer)  
int led_pin = 9;  // Use pin 9 as output (for led, buzzer)
 
void setup() {
  pinMode(input_pin, INPUT);  //set potPin to be an input
  pinMode(led_pin, OUTPUT); //set LEDPin to be an OUTPUT
  Serial.begin(9600);      // turn on Serial Port
}
 
void loop() {
 int input = analogRead(input_pin);
 analogWrite(led_pin, input*256/1024);
}


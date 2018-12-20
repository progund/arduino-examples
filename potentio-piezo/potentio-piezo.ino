int input_pin= A0; // Use A0 as input (from potentiometer)  
int led_pin = 9;  // Use pin 9 as output (for led, buzzer)
 
void setup() {
  pinMode(input_pin, INPUT); // input_pin should be set to input
  pinMode(led_pin, OUTPUT);  // led_pin should be set to output
}
 
void loop() {
 int input = analogRead(input_pin);
 tone(led_pin, (input/10)*100, 10);
}


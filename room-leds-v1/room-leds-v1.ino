// Variables for our leds 
int green_led = 10;
int yellow_led = 11;
int red_led = 12;

// Button is using pin 7
int button_pin = 7;

// Which led to lit
int current_led  = red_led;

/*
 * blink (int led)
 * 
 * led - which pin to blink
 * 
 * Set a pin high and low (i e blinks)
 * 
 */
void blink(int led) {
  digitalWrite(led, HIGH);
  delay(20);                       
  digitalWrite(led, LOW);
  delay(20);        
}

/*
 * show_start_blink()
 * 
 * blinks all three leds. 
 * 
 * Shows the device is up and running and 
 * to make sure if all leds are working.
 * 
 */
void show_start_blink() {
  int i;
  for (i=0; i<5; i++) {
    blink(red_led);
    blink(yellow_led);
    blink(green_led);  
  }
}

/*
 * setup()
 * 
 * This function is invoked (once) when the device is starting up
 * 
 */
void setup() {
  // use all led pins as OUTPUT pins
  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(red_led, OUTPUT);

  Serial.begin(9600);

  show_start_blink();

  digitalWrite(current_led, HIGH);
}

/* 
 *  read_button
 *  
 *  pin - pin to read from
 *  
 *  returns 1 if button pressed, else 0
 *
 */
int read_button(int pin) {
  // set high and return the value read
  digitalWrite(pin, HIGH);
  return !digitalRead(pin);
}

void set_current_led() {

  // a very naive solution
  if (current_led == red_led) {
    current_led = yellow_led;
    
  } else if (current_led == yellow_led) {
    current_led = green_led;
    
  } else {
    current_led = red_led;
  } 

}

/* 
 *  loop()
 *  
 *  After setup this function is called repeatedly
 *  
 */
void loop() {

  delay(500);
  
  // if button pressed, take action. If not, do nothing
  if (read_button(button_pin)) {

    // Turn off current led - only one led at a time
    digitalWrite(current_led, LOW);
    
    // calculate the next led to lit
    set_current_led();

    digitalWrite(current_led, HIGH);
  }
  
  
  Serial.println(current_led);
}

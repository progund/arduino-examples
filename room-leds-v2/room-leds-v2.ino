enum leds {
  GREEN = 10 ,
  YELLOW = 11,
  RED = 12,
} ;

int current_led  = RED + 10;
int already_pressed = 0 ;
int button_pressed = 0;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);  
  Serial.println("Uh oh");
}

void blink(int led) {
  digitalWrite(led, HIGH);
  delay(200);                       // wait for a second
  digitalWrite(led, LOW);
  delay(200);                       // wait for a second
  
}

// the loop function runs over and over again forever
void loop() {
//  blink(red_led);
//  blink(yellow_led);
//  blink(green_led);

  digitalWrite(current_led, HIGH);
  delay(10);
  digitalWrite(7, HIGH);
  button_pressed = !digitalRead(7);
  
    // if button pressed
    if (button_pressed) {
      if (!already_pressed) { 
        digitalWrite(current_led, LOW);
        current_led = (current_led + 1) % 3 + 10;
        already_pressed = 1;
      }
    } else {
      already_pressed = 0;
    }

  

  
  Serial.print(current_led);
  Serial.print(" ");
  Serial.println(already_pressed);

}

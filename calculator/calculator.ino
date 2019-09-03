/*

    calculator.ino - use button and leds to calculate +

    This code is written with some pedagogical concerns in mind.
    The code is not in any way written to be optimal or flexible.
    A struct and an array would, as two examples, make the code way better.

    (c) Henrik Sandklef and Rikard Fröberg (juneday.se) 2019

    License: none, consider this code to be under Public Domain

*/

typedef struct led_button {
  int led;
  int button;
  int state;
  int prev_state;
  long change_time;
} _led_button;

led_button led_buttons[] = {
  {42, 43, 0}, // 1
  {40, 41, 0}, // 2
  {38, 39, 0}, // 3
  {36, 37, 0}, // 4
  {34, 35, 0}, // 5
  {32, 33, 0}, // 6
  {30, 31, 0}  // 7
};


#define STATE_ENTER_OP1 1
#define STATE_ENTER_OP2 2
#define STATE_SHOW_RES 3

int nr_led_buttons;
const int timeout = 10;  //ms
const int control_led = 50;
const int status_led = 52;
const int control_button = 51;
int control_state = STATE_ENTER_OP1;

int op1;
int op2;

/**********************************************************

   void setup()

   description:
    Sets up the hardware

 ***********************************************************/
void setup() {
  nr_led_buttons =  sizeof(led_buttons) / sizeof(led_button);

  reset_buttons(1);

  // Setup control
  pinMode(control_button, INPUT);
  pinMode(control_led, OUTPUT);
  pinMode(status_led, OUTPUT);
  
  // Setup Serial
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void reset_buttons(int blink) {
  int i;
  for (i = 0; i < nr_led_buttons; i++) {
    led_button *lb = &led_buttons[i];

    lb->change_time = millis();
    lb->state = 0;
    lb->prev_state = 0;

    pinMode(lb->led, OUTPUT);
    pinMode(lb->button, INPUT);

    if (blink != 0 ) {
      // blink led
      digitalWrite(lb->led, HIGH);
      delay(50);
      digitalWrite(lb->led, LOW);
    }
  }
  digitalWrite(status_led, LOW);
}


/**********************************************************

   int read_button(int button)

   parameters:
     button  - the pin to read the value from

   return:
     int - 1 if button is pressed, 0 otherwise

   description:
    reads and returns the INPUT pin value

 ***********************************************************/
int read_button(int button) {

  // Set pin to high (before read)
  digitalWrite(button, HIGH);

  // read and return the reversed value
  return !digitalRead(button);
}

/***********************************************************


 ***********************************************************/
void handle_button(led_button *ld) {
  int button = ld->button;
  int led = ld->led;
  long change_time = ld->change_time;
  int button_state;

  // Set led to LOW to not fuke things up when reading button
  digitalWrite(led, LOW);
  button_state = read_button(button);

  if (button_state == 0) {

    // Button is released
    if (ld->prev_state == 1 ) {
      // Released for the first time
      ld->change_time = millis();
      if (millis() - change_time > timeout ) {
        ld->state = !ld->state;
        ld->change_time = millis(); 
      }    
    }
    ld->prev_state = 0;

  } else if (button_state == 1) {

    // Button is pressed
    if (ld->prev_state == 0 ) {
      // Button is pressed is for the first time
      ld->change_time = millis();
    }
    ld->prev_state = 1 ;
  }

/*
  if (button == 31) {
    Serial.print(ld->state);
    Serial.print(" <== ");
    Serial.print(button);
    Serial.print(" [ ");
    Serial.print(ld->change_time);
    Serial.print("  ");
    Serial.print( (millis() - ld->change_time) > timeout );
    Serial.print(" ]    state: ");
    Serial.println(button_state);
  }
*/
  digitalWrite(led, ld->state);

/*
  if ( button_state ) {
    // if the user has pressed the button, send the character
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
*/

}

void blink_all(int times) {
  int i;
  int j;
  for (j = 0; j < times; j++) {
    for (i = 0; i < nr_led_buttons; i++) {
      led_button *lb = &led_buttons[i];
      digitalWrite(lb->led, HIGH);
    }
    delay(100);
    for (i = 0; i < nr_led_buttons; i++) {
      led_button *lb = &led_buttons[i];
      digitalWrite(lb->led, LOW);
    }
    delay(100);
  }


}



int read_led_buttons() {
  int i;
  int mult = 1;
  int res = 0;
  
  for (i = 0; i < nr_led_buttons; i++) {
//  for (i = nr_led_buttons-1; i >= 0; i--) {
     led_button *lb = &led_buttons[i];
     res += mult * lb->state;
     mult = mult * 2;
  }
  return res;  
}

void show_result(int res) {
  int i;
  int mult = 1;

  if ( res > 127 ) {
     digitalWrite(status_led, HIGH );   
  }

  Serial.print("result: ");

  for (i = 0; i < nr_led_buttons; i++) {
     led_button *lb = &led_buttons[i];
     digitalWrite(lb->led, res & 0x1 );
     Serial.print(" ");
     Serial.print(res & 0x01);
     res = res >> 1; 
  }
}

void handle_control_button() {
  int button_state;
  static long last_state;

  
  // Set led to LOW to not fuke things up when reading button
  digitalWrite(control_led, LOW);
  button_state = read_button(control_button);
  digitalWrite(control_led, control_state==STATE_SHOW_RES);

  Serial.print("handle: ");
  Serial.print(button_state);
  Serial.print("  state: ");
  Serial.print(control_state);
  Serial.print("  handle: ");
  Serial.println(control_state==STATE_SHOW_RES);

  if ( button_state == 1) {
    if (last_state == 0 ) {
      if ( control_state == STATE_ENTER_OP1 ) {
        control_state = STATE_ENTER_OP2;
        op1 = read_led_buttons();
        Serial.println(op1);
        Serial.println("  enter op2");
        reset_buttons(0);
        blink_all(2);
      } else if ( control_state == STATE_ENTER_OP2 ) {
        Serial.println(op2);
        Serial.println("enter show res");
        control_state = STATE_SHOW_RES;
        op2 = read_led_buttons();
        reset_buttons(0);
        Serial.print(op1);
        Serial.print(" + ");
        Serial.print(op2);
        Serial.print(" = ");
        Serial.println(op1 + op2);
        Serial.println("enter op 1");
        blink_all(5);
        show_result(op1+op2);
      } else if ( control_state == STATE_SHOW_RES ) {
        control_state = STATE_ENTER_OP1;
        blink_all(2);
        digitalWrite(status_led, LOW);
      }

      
    }
    last_state = 1;
  } else {
    last_state = 0;
    
    if ( control_state != STATE_SHOW_RES ) {
      // Handle the buttons
      int i;
      for (i = 0; i < nr_led_buttons; i++) {
        handle_button(&led_buttons[i]);
      }
    }
  }
  
}

/***********************************************************
    loop()

    After setup this function is called repeatedly

 ***********************************************************/
void loop() {

  // 3 repeats per second is ok, so sleep 300 ms
  // Probably an ok balance between responsiveness and repeat
  delay(100);

  handle_control_button();
  
}

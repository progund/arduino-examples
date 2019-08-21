/*
 *
 *  keyboard.ino - use button to send keys via USB
 *
 *  This code is written with some pedagogical concerns in mind.
 *  The code is not in any way written to be optimal or flexible.
 *  A struct and an array would, as two examples, make the code way better.
 *  
 *  (c) Henrik Sandklef and Rikard Fröberg (juneday.se) 2019
 * 
 *  License: none, consider this code to be under Public Domain
 * 
 */
#include "Keyboard.h"


// Variables for our leds
int led_L = 4;
int led_P = 5;
int led_S = 6;
int led_BackSpace = 7;
int led_Enter = 8;

// Variables for our button
int button_L = 9;
int button_P = 10;
int button_S = 11;
int button_BackSpace = 12;
int button_Enter = 13;


/**********************************************************
 * 
 * void setup()
 * 
 * description:
 *  Sets up the hardware 
 * 
 ***********************************************************/
void setup() {
  // Set the mode of our BUtton pins to INPUT
  pinMode(button_L, INPUT);
  pinMode(button_P, INPUT);
  pinMode(button_S, INPUT);
  pinMode(button_BackSpace, INPUT);
  pinMode(button_Enter, INPUT);

  // Set the mode of our Led pins to OUTPUT
  pinMode(led_L, OUTPUT);
  pinMode(led_P, OUTPUT);
  pinMode(led_S, OUTPUT);
  pinMode(led_BackSpace, OUTPUT);
  pinMode(led_Enter, OUTPUT);

  // Setup keyboard 
  Keyboard.begin();

  // Setup Serial 
  //  Serial.begin(9600);
}


/**********************************************************
 * 
 * int read_button(int button)
 * 
 * parameters:
 *   button  - the pin to read the value from
 * 
 * return:
 *   int - 1 if button is pressed, 0 otherwise
 * 
 * description:
 *  reads and returns the INPUT pin value
 * 
 ***********************************************************/
int read_button(int button) {

  // Set pin to high (before read)
  digitalWrite(button, HIGH);

  // read and return the reversed value
  return !digitalRead(button);
}

/***********************************************************
 *
 * void handle_button(int button, int led, int character) 
 * 
 * parameters:
 *   button  - the pin to read the value from
 *   led     - the led to lit if button is pressed
 *   character - the character to send to the computer connected via USB
 * 
 * description:
 *  if the button is pressed the led is lit and the character is sent via USB
 *  if the button is not pressed, nothing is done
 *
 ***********************************************************/
void handle_button(int button, int led, int character) {
 /*
  Serial.print(character);
  Serial.print(" ");
  Serial.print(button);
  Serial.print(" => ");
  Serial.println(read_button(button));
  */

  // Set led to LOW to not fuke things up when reading button
  digitalWrite(led,LOW); 

  if ( read_button(button) ) {
    // if the user has pressed the button, send the character
    Keyboard.write(character);    
    digitalWrite(led,HIGH);
  } else {
    digitalWrite(led,LOW); 
  }
  
}

/***********************************************************
 *  loop()
 *  
 *  After setup this function is called repeatedly
 *  
 ***********************************************************/
void loop() {

  // Handle the buttons
  handle_button(button_L, led_L, 'l');  
  handle_button(button_P, led_P, 'p');  
  handle_button(button_S, led_S, 's');  
  handle_button(button_BackSpace, led_BackSpace, '\b');  
  handle_button(button_Enter, led_Enter, '\n'); 

  // 3 repeats per second is ok, so sleep 300 ms
  // Probably an ok balance between responsiveness and repeat
  delay(300);
}

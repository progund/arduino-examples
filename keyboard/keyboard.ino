#include "Keyboard.h"

int pin_L = 8;
int pin_P = 9;
int pin_S = 10;
int pin_BackSpace = 11;
int pin_Enter = 12;

int led_L = 3;
int led_P = 4;
int led_S = 5;
int led_BackSpace = 6;
int led_Enter = 7;

void setup() {
  pinMode(pin_L, INPUT);
  pinMode(pin_P, INPUT);
  pinMode(pin_S, INPUT);
  pinMode(pin_BackSpace, INPUT);
  pinMode(pin_Enter, INPUT);
  pinMode(led_L, OUTPUT);
  pinMode(led_P, OUTPUT);
  pinMode(led_S, OUTPUT);
  pinMode(led_BackSpace, OUTPUT);
  pinMode(led_Enter, OUTPUT);
  Keyboard.begin();
  Serial.begin(9600);
}

int read_button(int button) {
  digitalWrite(button, HIGH);
  return !digitalRead(button);
}

void handle_pin(int button, int led, int character) {
 /* Serial.print(character);
  Serial.print(" ");
  Serial.print(button);
  Serial.print(" => ");
  Serial.println(read_button(button));
  */
  if ( read_button(button) ) {
    Keyboard.write(character);    
    digitalWrite(led,HIGH);
  } else {
    digitalWrite(led,LOW); 
  }
  
}

void loop() {
  handle_pin(pin_L, led_L, 'l');  
  handle_pin(pin_P, led_P, 'p');  
  handle_pin(pin_S, led_S, 's');  
  handle_pin(pin_BackSpace, led_BackSpace, '\b');  
  handle_pin(pin_Enter, led_Enter, '\n');  
  delay(300);
}

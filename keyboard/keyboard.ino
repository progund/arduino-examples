#include "Keyboard.h"

void setup() {
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {

  Keyboard.write('a');
  delay(1000);
}

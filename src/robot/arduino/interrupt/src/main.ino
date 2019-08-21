/*
   $B8wEE%m!<%?%j!<%(%s%3!<%@$rF0$+$7$F$_$k!*(B
*/
volatile unsigned int temp, counter = 0;
void setup() {
  Serial.begin (9600);

  pinMode(2, INPUT_PULLUP);

  pinMode(3, INPUT_PULLUP);
  //interupt$B$r%;%C%H%"%C%W$9$k(B
  //
  attachInterrupt(0, ai0, RISING);

  //
  attachInterrupt(1, ai1, RISING);
}

void loop() {
  // $B%+%&%s%?!<$NCM$r=PNO$9$k(B
  if ( counter != temp ) {
    Serial.println (counter);
    temp = counter;
  }
}

void ai0() {
  if (digitalRead(3) == LOW) {
    counter++;
  } else {
    counter--;
  }
}

void ai1() {
  if (digitalRead(2) == LOW) {
    counter--;
  } else {
    counter++;
  }
}

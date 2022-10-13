
void dot() {
  // Dot
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(1000);                     
  digitalWrite(LED_BUILTIN, LOW);   
  delay(1000);  
}

void dash() {
  // Dash
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(2000);                     
  digitalWrite(LED_BUILTIN, LOW);   
  delay(1000);
}


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  // H
  dot();
  dot();
  dot();
  dot();

  // E
  dot();

  // L
  dot();
  dash();
  dot();
  dot();
  
  // L
  dot();
  dash();
  dot();
  dot();

  // O
  dash();
  dash();
  dash();

  // I
  dot();
  dot();

  // M
  dash();
  dash();

  // U
  dot();
  dot();
  dash();

  delay(4000);
}



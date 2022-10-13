
void dot() {
  // Dot
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(500);                     
  digitalWrite(LED_BUILTIN, LOW);   
  delay(500);  
}

void dash() {
  // Dash
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(1500);                     
  digitalWrite(LED_BUILTIN, LOW);   
  delay(500);
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
  
  delay(1000);

  // E
  dot();

  delay(1000);
  
  // L
  dot();
  dash();
  dot();
  dot();
  
  delay(1000);
  
  // L
  dot();
  dash();
  dot();
  dot();

  delay(1000);
  
  // O
  dash();
  dash();
  dash();

  delay(3000);
  
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



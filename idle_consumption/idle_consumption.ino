//const unsigned int SERIAL_BAUD_RATE = 115200;
const unsigned int SERIAL_BAUD_RATE = 9600;


void setup() {
  delay(1000);
  Serial.begin(SERIAL_BAUD_RATE);
  while (!Serial)
    ;

  Serial.println("Algorithm: IDLE");
  Serial.println("Ready.");
}

void loop() {
  delay(10000);
}

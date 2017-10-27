 //int n=1275;
void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
}
void loop() {
  // read from port 1, send to port 0:
  int x = 17240;  // spaces are for readability only
  uint8_t LSB = x;  
  uint8_t MSB = x >> 8;
  Serial.write(MSB);
  Serial.write(LSB);
  delay(1500);
  }




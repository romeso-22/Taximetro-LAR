 //int n=1275;
void setup() {
  Serial.begin(9600);
}
void loop() {
  for(int i=0; i<25; i++){
  int x = i*1110;
  uint8_t LSB = x;  
  uint8_t MSB = x >> 8;
  Serial.write(MSB);
  Serial.write(LSB);
  delay(1500);
  }
  
  }




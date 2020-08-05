void setup() {
  Serial.begin(115200);
  uint8_t shiftNum = 5;
  uint8_t rowbit = B01111111;
  //uint8_t process_rowbit = (rowbit << (8 - shiftNum)) | (rowbit >> shiftNum); 
  uint8_t process_rowbit = rowbit >>= 1;
  Serial.println(process_rowbit,BIN);
}

void loop() {
  // put your main code here, to run repeatedly:

}

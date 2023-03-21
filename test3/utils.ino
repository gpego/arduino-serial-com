void stopData() {
   if (Serial.available() > 60) {
      // Sendinf STOP msg if the serial buffer is full
      Serial.print("STOP");
   }
}


void receiveData() {
   // Waiting for data availability
   if (Serial.available() < 4) {
      // error
      return;
   }

   // Reading data
   for (byte n = 0; n < 4; n++) {
      pcData[n] = Serial.read();
   }

   // TODO check CRC
   // Copying data
   for (byte n = 0; n < 4; n++) {
      inputData.pcLine[n] = pcData[n];
   }
   newData = true;
}


void decodeData() {
  switch(inputData.bufferData.name) {
    // cx
    case 0:
      // Calculate the error from the center of the image
      error_x = inputData.bufferData.value - 32;

      // Calculate the motor speeds
      leftSpeed = error_y * 5 + error_x * 3;
      rightSpeed = error_y * 5 - error_x * 3;

      break;

    //cy
    case 1:
      // Calculate the error from the center of the image
      error_y = - (inputData.bufferData.value - 20);

      // Calculate the motor speeds
      leftSpeed = error_y * 5 + error_x * 3;
      rightSpeed = error_y * 5 - error_x * 3;

      break;
  }
}


void motorsControl () {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enA, inputData.bufferData.value);
}


void displayData() {
  if (newData == false) {
      return;
  }

  // Printing values
  Serial.print("<Here it is ... ");
  Serial.print(inputData.bufferData.name);
  Serial.print(" ");
  Serial.print(inputData.bufferData.value);
  Serial.print(" ");
  Serial.println('>');
  newData = false;
  askForData = true;
}

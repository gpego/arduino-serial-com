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

  // Right motors
  analogWrite(enA_r, rightSpeed);
  analogWrite(enB_r, rightSpeed);
  if (rightSpeed > 5) {
    // Front-right
    digitalWrite(in1_r, LOW);
    digitalWrite(in2_r, HIGH);

    // Back-right
    digitalWrite(in3_r, LOW);
    digitalWrite(in4_r, HIGH);
  }
  else if (rightSpeed < -5) {
    // Front-right
    digitalWrite(in1_r, HIGH);
    digitalWrite(in2_r, LOW);

    // Back-right
    digitalWrite(in3_r, HIGH);
    digitalWrite(in4_r, LOW );
  }
  else {
    // Front-right
    digitalWrite(in1_r, LOW);
    digitalWrite(in2_r, LOW);

    // Back-right
    digitalWrite(in3_r, LOW);
    digitalWrite(in4_r, LOW );
    }
  }



  /*
          print(f"rightSpeed = {abs(rightSpeed)}")
        self.pwmA.ChangeDutyCycle(abs(rightSpeed));
        self.rightSpeed = rightSpeed
        if rightSpeed > 5:
            GPIO.output(self.In1A, GPIO.LOW)
            GPIO.output(self.In2A, GPIO.HIGH)
        elif rightSpeed < -5:
            GPIO.output(self.In1A, GPIO.HIGH)
            GPIO.output(self.In2A, GPIO.LOW)
        else:
            GPIO.output(self.In1A, GPIO.LOW)
            GPIO.output(self.In2A, GPIO.LOW)

        # Left motor
        print(f"leftSpeed = {abs(leftSpeed)}")
        self.pwmB.ChangeDutyCycle(abs(leftSpeed));
        self.leftSpeed = leftSpeed
        if leftSpeed > 5:
            GPIO.output(self.In1B, GPIO.HIGH)
            GPIO.output(self.In2B, GPIO.LOW)
        elif leftSpeed < -5:
            GPIO.output(self.In1B, GPIO.LOW)
            GPIO.output(self.In2B, GPIO.HIGH)
        else:
            GPIO.output(self.In1B, GPIO.LOW)
            GPIO.output(self.In2B, GPIO.LOW)

        sleep(t)
  */
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

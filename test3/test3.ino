// program to test receiving data from PC
// works with SendBinary.py

// the demo was developed to explore how to receive the
//     data needed to define a move for 3 stepper motors

//  in this demo no attempt is made to use it to drive any motors
//  the received data is just echoed back to the Python program


#define enA 9
#define in1 6
#define in2 7


void setup() {
  Serial.begin(115200);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //Serial.println("<Arduino is ready>>");
}

void loop() {
  // Sending STOP msg
  stopData();

  // Receiving data
  receiveData();

  // Decoding data
  decodeData();

  //analogWrite(enA, inputData.bufferData.value);
  motorsControl();

  // Displaying data
  displayData();
  //Serial.print(inputData.bufferData.value);

  delay(100);
}

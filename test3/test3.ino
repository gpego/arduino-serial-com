// program to test receiving data from PC
// works with SendBinary.py

// the demo was developed to explore how to receive the
//     data needed to define a move for 3 stepper motors

//  in this demo no attempt is made to use it to drive any motors
//  the received data is just echoed back to the Python program


// Left motors
// Front-left
#define enA_l 9
#define in1_l 6
#define in2_l 7

// Back-left
#define in3_l
#define in4_l
#define enB_l


// Right motors
// Front-right
#define enA_r
#define in1_r
#define in2_r

// Back-right
#define in3_r
#define in4_r
#define enB_r


void setup() {
  Serial.begin(115200);

  pinMode(enA_l, OUTPUT); pinMode(in1_l, OUTPUT); pinMode(in2_l, OUTPUT);
  pinMode(enB_l, OUTPUT); pinMode(in3_l, OUTPUT); pinMode(in4_l, OUTPUT);

  pinMode(enA_r, OUTPUT); pinMode(in1_r, OUTPUT); pinMode(in2_r, OUTPUT);
  pinMode(enB_r, OUTPUT); pinMode(in3_r, OUTPUT); pinMode(in4_r, OUTPUT);

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

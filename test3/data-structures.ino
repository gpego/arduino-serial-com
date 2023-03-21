short int error_x = 0, error_y = 0, leftSpeed = 0, rightSpeed = 0;

/*
Parameters:
  name:
    - cx: 0
    - cy: 1
  value:
    - position value (X axis): 0-63
    - position value (Y axis): 0-63
*/
struct moveItem {
    short int name;   // 2
    short int value;  // 2
};

  // and the struct is overlaid on an array to make it easy to receive data from the PC
  // the received data is copied byte by byte into pcLine
  //   and can then be used as, e.g. bufferData.totalMicros
union inputFromPC {
   moveItem bufferData;
   byte pcLine[4];
};

 // this creates a working instance of the Union
 // elements in it are referred to as, e.g. inputData.bufferData.totalMicros
inputFromPC inputData;

byte pcData[4];
boolean newData = false;
boolean askForData = true;
#include <DoubleJoy.h>

//#include <UnoJoy.h>
#include <Psx.h>
// gnd arancio/bianco
#define dataPin1 2  // marrone
#define cmndPin1 3  // marrone/bianco
#define attPin1 4   // azz/bianco ?
#define clockPin1 6 // verde

#define dataPin2 2
#define cmndPin2 3
#define attPin2 5
#define clockPin2 6

Psx psx1; 
Psx psx2; 

unsigned int psxData = 0; 

void setup(){
  psx1.setupPins(dataPin1, cmndPin1, attPin1, clockPin1, 10); 
  psx2.setupPins(dataPin2, cmndPin2, attPin2, clockPin2, 10); 
  setupUnoJoy();
  
  pinMode(13, OUTPUT);
}

void loop(){
  // Always be getting fresh data
  dataForController_t controllerData1 = getControllerData(psx1);
  dataForController_t controllerData2 = getControllerData(psx2);
  setControllerData(1, controllerData1);
  setControllerData(2, controllerData2);
}

dataForController_t getControllerData(Psx psx){
  psxData = psx.read();
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
  
  controllerData.triangleOn = (psxData & psxTri) != 0;
  controllerData.circleOn = (psxData & psxO) != 0;
  controllerData.squareOn = (psxData & psxSqu) != 0;
  controllerData.crossOn = (psxData & psxX) != 0;
  controllerData.dpadUpOn = (psxData & psxUp) != 0;
  controllerData.dpadDownOn = (psxData & psxDown) != 0;
  controllerData.dpadLeftOn = (psxData & psxLeft) != 0;
  controllerData.dpadRightOn = (psxData & psxRight) != 0;
  controllerData.l1On = (psxData & psxL1) != 0;
  controllerData.r1On = (psxData & psxR1) != 0;
  controllerData.selectOn = (psxData & psxSlct) != 0;
  controllerData.startOn = (psxData & psxStrt) != 0;
  controllerData.homeOn = 0; //psxData & psxTri;
  
  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use  
  //controllerData.leftStickX = analogRead(A0) >> 2;
  //controllerData.leftStickY = analogRead(A1) >> 2;
  //controllerData.rightStickX = analogRead(A2) >> 2;
  //controllerData.rightStickY = analogRead(A3) >> 2;
  // And return the data!
  return controllerData;
}

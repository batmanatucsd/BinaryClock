#include <Time.h>

#define POWER A0
#define SWITCH A1
#define UP A2
#define DOWN A3

// increments that are used to change time
#define MINUTES 60 
#define HOURS 3600

// global variables
bool isOn = true; // used to check if the button is pressed or not

// pin numbers for LED's
// use these arrays to access the pin numbers
// NOTE:
// char type is used. While int can be used too,
// I wanted to point out that most of the time
// when you code for microcontroller, 
// memory is a big issue, so you want to keep 
// the memory used as minimal as possible
char minutes[7] = {0, 1, 2, 3, 4, 5, 6};
char hours[6] = {7, 8, 9, 10, 11, 12}; 

int increment = MINUTES; // increment for changing time
int currentTime, digit; // use these variables to hold values when turning on LEDs 

// function declarations
void turnDigitOn(const char[], int, int);
void listenToButton(int);

////////////////////
// setup function //
void setup() {
  // set up all the buttons  
  pinMode(POWER, INPUT);
  // TODO:
  // set pin modes for all the other buttons

  // have all the buttons set to HIGH 
  digitalWrite(POWER, HIGH);
  // TODO:
  // do the same for all the other buttons

  pinMode(13, OUTPUT);

  // TODO:
  // set in modes for the LEDs

  setTime(12,0,0,4,27,14); // set time to noon April 27 2014
}

/////////////////////////
///// loop function /////
void loop() {
  static unsigned long lastTick = 0;

  // listen to buttons
  listenToButton(POWER);
  listenToButton(SWITCH);
  listenToButton(UP);
  listenToButton(DOWN);

  // TODO:
  // if isOn is true 
    // display time with LED:
	 
	// TURN MINUTE ON 
	// get minute 
	// get low digit 
	//
	// NOTE:
	// Notice that the digit variable defined above is global.
	// Use this variable in function turnDigitOn to turn the digit on.
	//
    // turn low digit on
	
	// get high digit
    // turn high digit on

	// TURN HOUR ON 
    // do the same thing that you did for minute
	// but with hour

  // if isOn is false 
    // turn off all the LED's
  

  // fixes internal clock offset
  // this is different for every board
  // might not have to do this if done on other board
  if(millis() - lastTick >= 1000) {
    lastTick = millis();
    adjustTime(1);
  }
}

////////////////////////////////
///// Function Definitions /////
////////////////////////////////
// turn LEDs for that digit 
void turnDigitOn(const char pin[], int start, int finish) {
	// TODO:
	// follow the given pseudo code 
	// use indices of pin to access the right pin number
	// use the global variable digit
}

/////////////////////////////////
// bution listner function 
void listenToButton(int button) {
  // check for button inputs
  if(digitalRead(button) == LOW) {
    while(digitalRead(button) == LOW); // while the button is hold down, do nothing

    switch(button) {
      case POWER: // turn LED's on and off
        isOn = !isOn;   
        break;

      case SWITCH: // chnage between hour and minute
        if(increment == MINUTES) // change increment accordingly
          increment = HOURS;
        else
          increment = MINUTES;
        break;

      case UP: // increment 
        adjustTime(increment); // reset time
        adjustTime(-second()); // reset seconds to 00
        break;

      case DOWN: // decrement
        adjustTime(-increment);
        adjustTime(-second());
        break;
    } // end of switch
  }
}



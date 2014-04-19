#include <Time.h>

#define POWER A0
#define SWITCH A1
#define UP A2
#define DOWN A3

#define MINUTES 60 // increments that are used to change time
#define HOURS 3600

// global variables
bool isOn = true; // used to check if the button is pressed or not

// pin numbers for LED's
char minutes[7] = {0, 1, 2, 3, 4, 5, 6};
char hours[6] = {7, 8, 9, 10, 11, 12}; 

int increment = MINUTES; // increment for changing time
int currentTime, digit; 

// function declarations
void turnDigitOn(const char[], int, int);
void listenToButton(int);

////////////////////
// setup function //
void setup() {
  // Serial.begin(19200); // set baud rate, data transmission rate
  // Serial.println(F_CPU);

  // set up all the buttons  
  pinMode(POWER, INPUT);
  pinMode(SWITCH, INPUT);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);

  // have all the buttons highs
  digitalWrite(POWER, HIGH);
  digitalWrite(SWITCH, HIGH);
  digitalWrite(UP, HIGH);
  digitalWrite(DOWN, HIGH);  

  pinMode(13, OUTPUT);

  // set pin modes for the LEDs
  for(int i=0; i<13; i++) 
    pinMode(i, OUTPUT);

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

  // if the power switch is on
  if(isOn) {
    // display time with LED
	// turn minute on
    currentTime = minute(); // get minute
	digit = currentTime%10; // get low digit
    turnDigitOn(minutes, 0, 4); // turn low digit
	digit = currentTime/10; // get high digit
    turnDigitOn(minutes, 4, 7); // turn high digit

	// turn hour on
    currentTime = hour(); // get hour
	digit = currentTime%10;
    turnDigitOn(hours, 0, 4); // turn low digit
	digit = currentTime/10;
    turnDigitOn(hours, 4, 6); // turn high digit
    
  } else { // if power button was pressed
    // turn off all the LED's
    for(int i=0; i<13; i++) 
      digitalWrite(i, LOW);
  }

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
  for(int i=start; i<finish; ++i) {
    if(digit%2 == 0)
      digitalWrite(pin[i], LOW);
    else
      digitalWrite(pin[i], HIGH);
      digit /= 2;    
  }
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



#include <Time.h>

#define POWER A0
#define SWITCH A1
#define UP A2
#define DOWN A3

#define MINUTES 60
#define HOURS 3600

// global variables
bool isOn = true;

// pin numbers for LED's
char minutes[7] = {0, 1, 2, 3, 4, 5, 6};
char hours[6] = {7, 8, 9, 10, 11, 12};

int increment = MINUTES; // increment for changing time
int currentTime; 

// function declarations
void turnLowBits(const char[], int);
void turnHighBits(const char[], int, int);
void turnMinutesOn(int);
void turnHoursOn(int);
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
  
  // // turn time on
  // turnMinutesOn(minute());
  // turnHoursOn(hour());
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
    currentTime = minute();
    turnLowBits(minutes, currentTime%10);
    turnHighBits(minutes, 7, currentTime/10);  

    currentTime = hour();
    turnLowBits(hours, currentTime%10);
    turnHighBits(hours, 6, currentTime/10);  
    // turnMinutesOn(minute()); // display minute
    // turnHoursOn(hour());  // display hour
    
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

// turn LEDs in the lower bit
// this function is called both in the 
// turnMinutesOn and turnHoursOn
void turnLowBits(const char bit[], int digit) {
  for(int i=0; i<4; ++i) { // 0 <= digit <= 9
    if(digit%2 == 0)
      digitalWrite(bit[i], LOW);
    else
      digitalWrite(bit[i], HIGH);
    digit /= 2;
  }
}

// turn LEDs in the higher bit
// this function is called both in the 
// turnMinutesOn and turnHoursOn
void turnHighBits(const char bit[], int max, int digit) {
  for(int i=4; i<max; ++i) {
    if(digit%2 == 0)
      digitalWrite(bit[i], LOW);
    else
      digitalWrite(bit[i], HIGH);
      digit /= 2;    
  }
}

///////////////////////////////////
// function for turning minute leds
void turnMinutesOn(int currentMinute) {
}

/////////////////////////////////
// function for turning hour leds
void turnHoursOn(int currentHour) {
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



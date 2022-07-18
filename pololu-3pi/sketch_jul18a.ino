/*
 * PID3piLineFollower - demo code for the Pololu 3pi Robot
 * 
 * This code will follow a black line on a white background, using a
 * PID-based algorithm.
 *
 * http://www.pololu.com/docs/0J21
 * http://www.pololu.com
 * http://forum.pololu.com
 *
 */
#define STOP 0
#define DOUBLE_SPEED 1
#define HALF_SPEED 2
#define TURN360 3
#define TURN180 4
// The following libraries will be needed by this demo
#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLEDs.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>

Pololu3pi robot;
int timeout = 0;
int speed_max = 100;
unsigned int sensors[5]; // an array to hold sensor values
unsigned int last_proportional = 0;
long integral = 0;

void do_all(int action);

// This include file allows data to be stored in program space.  The
// ATmega168 has 16k of program space compared to 1k of RAM, so large
// pieces of static data should be stored in program space.
#include <avr/pgmspace.h>

// A couple of simple tunes, stored in program space.
const char welcome[] PROGMEM = ">g32>>c32";
const char welcome2[] PROGMEM = ">c32>>d32";
const char go[] PROGMEM = "L16 cdegreg4";
const char music1[] PROGMEM = "arergrdrarergrdrarrarrergrrrdarrrerrgrrr";
const char music2[] PROGMEM = "!T240 L8 MS >e<eb>c>d>e16>d16>cba<aa>c>e";
const char plim1[] PROGMEM = ">g32";
const char plim2[] PROGMEM = ">C32";

// Initializes the 3pi, displays a welcome message, calibrates, and
// plays the initial music.  This function is automatically called
// by the Arduino framework at the start of program execution.
void setup()
{
  unsigned int counter; // used as a simple timer

  // This must be called at the beginning of 3pi code, to set up the
  // sensors.  We use a value of 2000 for the timeout, which
  // corresponds to 2000*0.4 us = 0.8 ms on our 20 MHz processor.
  robot.init(2000);

  while (!OrangutanPushbuttons::isPressed(BUTTON_B)){
    if(OrangutanPushbuttons::isPressed(BUTTON_A)){
      if(timeout > 0){
        timeout--;
        OrangutanBuzzer::playFromProgramSpace(plim1);
      }
      OrangutanPushbuttons::waitForRelease(BUTTON_A);
    }
    if(OrangutanPushbuttons::isPressed(BUTTON_C)){
      timeout++;
      OrangutanBuzzer::playFromProgramSpace(plim2);
      OrangutanPushbuttons::waitForRelease(BUTTON_C);
    }
  }

  // Always wait for the button to be released so that 3pi doesn't
  // start moving until your hand is away from it.
  OrangutanPushbuttons::waitForRelease(BUTTON_B);
  delay(1000);

  // Auto-calibration: turn right and left while calibrating the
  // sensors.
  for (counter=0; counter<80; counter++)
  {
    if (counter < 20 || counter >= 60)
      OrangutanMotors::setSpeeds(40, -40);
    else
      OrangutanMotors::setSpeeds(-40, 40);

    // This function records a set of sensor readings and keeps
    // track of the minimum and maximum values encountered.  The
    // IR_EMITTERS_ON argument means that the IR LEDs will be
    // turned on during the reading, which is usually what you
    // want.
    robot.calibrateLineSensors(IR_EMITTERS_ON);

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  OrangutanMotors::setSpeeds(0, 0);

  // Display calibrated values as a bar graph.
  while (!OrangutanPushbuttons::isPressed(BUTTON_B));
  OrangutanPushbuttons::waitForRelease(BUTTON_B);  

  // Play music and wait for it to finish before we start driving.
  OrangutanBuzzer::playFromProgramSpace(go);
  while(OrangutanBuzzer::isPlaying());
}

// The main function.  This function is repeatedly called by
// the Arduino framework.
void loop(){
  while (!OrangutanPushbuttons::isPressed(BUTTON_B)){
    // Get the position of the line.  Note that we *must* provide
    // the "sensors" argument to read_line() here, even though we
    // are not interested in the individual sensor readings.
    unsigned int position = robot.readLine(sensors, IR_EMITTERS_ON);

    // The "proportional" term should be 0 when we are on the line.
    int proportional = (int)position - 2000;

    // Compute the derivative (change) and integral (sum) of the
    // position.
    int derivative = proportional - last_proportional;
    integral += proportional;

    // Remember the last position.
    last_proportional = proportional;

    // Compute the difference between the two motor power settings,
    // m1 - m2.  If this is a positive number the robot will turn
    // to the right.  If it is a negative number, the robot will
    // turn to the left, and the magnitude of the number determines
    // the sharpness of the turn.  You can adjust the constants by which
    // the proportional, integral, and derivative terms are multiplied to
    // improve performance.
    int power_difference = proportional/20 + integral/10000 + derivative*3/2;

    // Compute the actual motor settings.  We never set either motor
    // to a negative value.
    int maximum = speed_max;
    if (power_difference > maximum)
      power_difference = maximum;
    if (power_difference < -maximum)
      power_difference = -maximum;

    //if (power_difference < 0)
      //OrangutanMotors::setSpeeds(maximum + power_difference, maximum);
    //else
      OrangutanMotors::setSpeeds(maximum, maximum - power_difference);

    // Quando os sensores 4 ou 0 estao no valor maximo
    // o pololu encontrou uma segunda pista
    if(sensors[4] == 1000){
      OrangutanBuzzer::playFromProgramSpace(plim1);
      do_all(DOUBLE_SPEED);
    }
    if(sensors[0] == 1000)
      OrangutanBuzzer::playFromProgramSpace(plim2);
      do_all(STOP);
  }
  
  OrangutanPushbuttons::waitForRelease(BUTTON_B);
  OrangutanMotors::setSpeeds(0, 0);
  
  while (!OrangutanPushbuttons::isPressed(BUTTON_B)){
    if(OrangutanPushbuttons::isPressed(BUTTON_A)){
      OrangutanPushbuttons::waitForRelease(BUTTON_A);
      OrangutanBuzzer::playFromProgramSpace(music1);
      while(OrangutanBuzzer::isPlaying());
    }
    if(OrangutanPushbuttons::isPressed(BUTTON_C)){
      OrangutanPushbuttons::waitForRelease(BUTTON_C);
      OrangutanBuzzer::playFromProgramSpace(music2);
      while(OrangutanBuzzer::isPlaying());
    }
  }
  OrangutanPushbuttons::waitForRelease(BUTTON_B);
  delay(1000);
}
void do_all(int action){
    if(action == STOP){
      delay(20);
      OrangutanMotors::setSpeeds(50, 50);
      delay(20);
      OrangutanMotors::setSpeeds(25, 25);
      delay(20);
      OrangutanMotors::setSpeeds(0, 0);
      delay(timeout*1000);
    }
    if(action == DOUBLE_SPEED){
      speed_max = 100;
      if(speed_max > 100)
        speed_max = 100;
    }
    if(action == HALF_SPEED){
      speed_max = 50;
      if(speed_max < 50)
        speed_max = 50;
    }
    if(action == TURN360){
      delay(timeout*1000);
    }
    if(action == TURN180){
      delay(timeout*1000);
    }
}

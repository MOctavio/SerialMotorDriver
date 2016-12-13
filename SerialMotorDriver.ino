String incomingData;
int joystick_x, joystick_y;
 /* defined the right motor control pins */
#define PIN_MOTOR_RIGHT_UP 7
#define PIN_MOTOR_RIGHT_DN 6
#define PIN_MOTOR_RIGHT_SPEED 10

/* defined the left motor control pins */
#define PIN_MOTOR_LEFT_UP 5
#define PIN_MOTOR_LEFT_DN 4
#define PIN_MOTOR_LEFT_SPEED 9

 /* defined two arrays with a list of pins for each motor */
unsigned char RightMotor[3] = {
  PIN_MOTOR_RIGHT_UP,
  PIN_MOTOR_RIGHT_DN,
  PIN_MOTOR_RIGHT_SPEED
};
unsigned char LeftMotor[3] = {
  PIN_MOTOR_LEFT_UP,
  PIN_MOTOR_LEFT_DN,
  PIN_MOTOR_LEFT_SPEED
};

void setup() {
  Serial.begin(9600);
  
  pinMode (PIN_MOTOR_RIGHT_UP, OUTPUT);
  pinMode (PIN_MOTOR_RIGHT_DN, OUTPUT);
  pinMode (PIN_MOTOR_LEFT_UP, OUTPUT);
  pinMode (PIN_MOTOR_LEFT_DN, OUTPUT);
}
 
void loop() {
  if (Serial.available() > 0) { 
    incomingData = Serial.readStringUntil('\n');
    int commaIndex = incomingData.indexOf(',');

    joystick_x = incomingData.substring(0, commaIndex).toInt();
    joystick_y = incomingData.substring(commaIndex+1).toInt();

//    Serial.println(incomingData);
//    Serial.print("X: ");
//    Serial.print(joystick_x);
//    Serial.print(", Y: ");
//    Serial.println(joystick_y);
  
    //  manage the right motor
    Wheel (RightMotor, joystick_y - joystick_x);
    //  manage the left motor
    Wheel (LeftMotor, joystick_y + joystick_x);
  }
}

/*
   speed control of the motor
   motor - pointer to an array of pins
   v - motor speed can be set from -100 to 100
*/
void Wheel (unsigned char * motor, int v) 
{
  if (v>100) v=100;
  if (v<-100) v=-100;
  if (v>0) {
    digitalWrite(motor[0], HIGH);
    digitalWrite(motor[1], LOW);
    analogWrite(motor[2], v*2.55);
  } else if (v<0) {
    digitalWrite(motor[0], LOW);
    digitalWrite(motor[1], HIGH);
    analogWrite(motor[2], (-v)*2.55);
  } else {
    digitalWrite(motor[0], LOW);
    digitalWrite(motor[1], LOW);
    analogWrite(motor[2], 0);
  }
}

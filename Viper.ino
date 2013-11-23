#include <AFMotor.h>

const int STEERING_INPUT_PIN = A15;
const int CENTER             = 512;
const int OFFSET             = 10;
const int RIGHT              = 990;
const int LEFT               = 80;

AF_DCMotor steeringMotor(3, MOTOR12_64KHZ);
AF_DCMotor driveMotor(4, MOTOR12_64KHZ);

String bluetoothInput = "";

int speed = 100;
int direction = 0;


int steeringStep = 50;

int currentSteering = 500;

void center()
{
  int steeringPosition = analogRead(STEERING_INPUT_PIN);
  bool centered = false;
  while(!centered)
  {
    steeringPosition = analogRead(STEERING_INPUT_PIN);
    if(steeringPosition < CENTER - OFFSET)
      {
        steeringMotor.run(BACKWARD);
      }
    else if(steeringPosition > CENTER + OFFSET)
      {
        steeringMotor.run(FORWARD);
      }
    else
      {
        steeringMotor.run(RELEASE);
        centered = true;
      }
  }
}

void left()
{
  int steeringPosition = analogRead(STEERING_INPUT_PIN);
  if(steeringPosition < LEFT)
    {
      steeringMotor.run(RELEASE);
    }
  else
    {
      steeringMotor.run(FORWARD);
    }
  delay(50); //TODO: can we do better?
  steeringMotor.run(RELEASE);

}

void right()
{
  int steeringPosition = analogRead(STEERING_INPUT_PIN);
  if(steeringPosition > RIGHT)
    {
      steeringMotor.run(RELEASE);
    }
  else
    {
      steeringMotor.run(BACKWARD);
    }
  delay(50); //TODO: can we do better?
  steeringMotor.run(RELEASE);
}

void forward(int speed)
{
    driveMotor.setSpeed(speed);
    driveMotor.run(FORWARD);
    delay(10);
    stop();
}

void backward(int speed)
{
    driveMotor.setSpeed(speed);
    driveMotor.run(BACKWARD);
    delay(10);
    stop();
}

void stop()
{
    driveMotor.run(RELEASE);
}

void setup() 
{
  steeringMotor.setSpeed(200);

  Serial1.begin(9600); // Blutooth
  Serial.begin(9600);  // Console

  bluetoothInput.reserve(200);
  speed = 0;
  stop();
  center();
  Serial1.print("Hi Malik I'm ready for your command.\n");
}

void loop() {
  
  
  while (Serial1.available()) 
  {
    //Serial.println("ok");
    char ch = (char)Serial1.read();
    control(ch);
  }
}
void control(char command)
{
   Serial.println(command);
   //Serial1.print("OK\n");
  if(command == 'f') {
    direction = 0;
    if(direction == 1)
      speed = 100;
    forward(255); //speed+= 10);
  }
  else if(command == 'b') {
    direction = 1;
    if(direction == 0)
      speed = 100;
    backward(255); //speed += 10);
  }
  else if(command == 'r') right();
  else if(command == 'l') left();
  else if(command == 'c') center();
  else stop();
}


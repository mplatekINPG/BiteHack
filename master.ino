#include <TimerOne.h>

#include <Encoder.h>

#define R_P_GAIN 1.0;
#define R_I_GAIN 0.0;
#define R_D_GAIN 2.0;

volatile Encoder left_enc(26, 28);
volatile Encoder right_enc(22, 24);

volatile int rpm = 0;

const int zout = A3; // z-axis of the accelerometer
const int yout = A2; // y-axis
const int xout = A1; // x-axis
int rightMotorPWM = 0;
int leftMotorPWM = 100;
int left_encoder;
int right_encoder;

int z = analogRead(zout);
int y = analogRead(yout);
int x = analogRead(xout);

void r_motor_pid(float setpoint)
{
  static int prev_enc_read = 0;
  int enc_read = right_enc.read();
  
  static float previous_error = 0;
  float error = setpoint;
  
}


void set_r_pwm(int16_t width)
{
  if(width > 255)
  {
    width = 255;
  }
  else if(width < - 255)
  {
    width = -255;
  }
  if(width > 0)
  {
    digitalWrite(32, HIGH);
    digitalWrite(30, LOW);
    analogWrite(3, width);
  }
  else if(width < 0)
  {
    width = - width;
    digitalWrite(32, LOW);
    digitalWrite(30, HIGH);
    analogWrite(3, width);
  }
  else
  {
    digitalWrite(32, LOW);
    digitalWrite(30, LOW);
    analogWrite(3, 0);
  }
}

void set_l_pwm(int16_t width)
{
  if(width > 255)
  {
    width = 255;
  }
  else if(width < - 255)
  {
    width = -255;
  }
  if(width > 0)
  {
    digitalWrite(34, HIGH);
    digitalWrite(36, LOW);
    analogWrite(11, width);
  }
  else if(width < 0)
  {
    width = - width;
    digitalWrite(34, LOW);
    digitalWrite(36, HIGH);
    analogWrite(11, width);
  }
  else
  {
    digitalWrite(34, LOW);
    digitalWrite(36, LOW);
    analogWrite(11, 0);
  }
}

void motor_pids_interrupt() {

  //left_encoder = left.read();
  //right_encoder = right.read();
  //0int z = analogRead(zout);
  //int y = analogRead(yout);
  //int x = analogRead(xout);
  static int prev_enc_read = 0;
  int enc_read = right_enc.read();
  rpm = enc_read - prev_enc_read;
  prev_enc_read = enc_read;


  //Serial.print("a");
  //OCR2A = rightMotorPWM * 2.56;
  //OCR2B = leftMotorPWM * 2.56;
}


void setup() {
  //FAST PWM left
  pinMode(3, OUTPUT);
  //FAST PWM right
  pinMode(11, OUTPUT);

  //ENA right
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  //ENA left
  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);

  //interruption
  //TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  //TCCR2B = _BV(CS22);
  Serial.begin(9600);
  //TIMSK2 = (TIMSK2 & B11111110) | 0x01;
   Timer1.initialize(10000);           // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(motor_pids_interrupt);
  /////////
  //set_r_pwm(350);
}



void loop() {

  // put your main code here, to run repeatedly:
  // print the sensor values:

  //Serial.print(left_encoder);
  //Serial.print("\t ");
  //Serial.print(right_encoder);
  // Serial.print(z);
  // Serial.print("\t ");
  // Serial.print(y);
  // Serial.print("\t");
  // Serial.print(x);
  Serial.println(rpm);









}

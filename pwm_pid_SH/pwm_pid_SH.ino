#include <PID_v1.h>

#include <AutoPID.h>


#include <math.h>

#include <TimerOne.h>

#define OUTPUT_MIN -255
#define OUTPUT_MAX 255
#define KP 1
#define KI 1
#define KD 0


#define SH0 A8
#define SH1 A9
#define SH2 A10
#define SH3 A11
#define SH4 A12
#define SH5 A13
#define SH6 A14
#define SH7 A15

float SHtoCM (int value) {
//  if (value < 510) 
//    return 10.0;
  float dyst = value*5/1023.0;
  if (dyst >= 0.4 && dyst < 0.5)
    return (-200*dyst+160);
  if (dyst >= 0.5 && dyst < 0.65)
    return (-67*dyst + 93);
  if (dyst >= 0.65 && dyst < 0.75)
    return (-100*dyst+115);
  if (dyst >= 0.75 && dyst < 0.9)
    return (-67*dyst + 90);
  if (dyst >= 0.9 && dyst <1.3)
    return (-25*dyst + 52.5);
  if (dyst >= 1.3 && dyst < 2.5)
    return (-10*dyst + 30);
  return 0;
}

double angle, setPoint = 0.0, outputVal;

//input/output variables passed by reference, so they are updated automatically
//AutoPID myPID(&angle, &setPoint, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

volatile int16_t left_motor_speed = 180;
volatile int16_t right_motor_speed = 180;

const int xout = A0; // z-axis of the accelerometer
const int yout = A1; // y-axis
const int zout = A2; // x-axis

volatile int x, y, z;


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
    if(width < 20)
      width = 20;
    digitalWrite(32, HIGH);
    digitalWrite(30, LOW);
    analogWrite(3, width);
  }
  else if(width < 0)
  {
    if(width > - 20)
      width = -20;
    
    width = - width;
    digitalWrite(32, LOW);
    digitalWrite(30, HIGH);
    analogWrite(3, width);
  }
  else
  {
    digitalWrite(32, LOW);
    digitalWrite(30, LOW);
    analogWrite(11, 200);
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
    if(width < 20)
      width = 20;
    digitalWrite(34, HIGH);
    digitalWrite(36, LOW);
    analogWrite(11, width);
  }
  else if(width < 0)
  {
    if(width > -20)
      width = -20;
    width = - width;
    digitalWrite(34, LOW);
    digitalWrite(36, HIGH);
    analogWrite(11, width);
  }
  else
  {
    digitalWrite(34, LOW);
    digitalWrite(36, LOW);
    analogWrite(11, 200);
  }
}

void SH_left (float SH_cm)
{
  int count = 0;
  if (SH_cm >= 8 && SH_cm <= 22)
  {
    while(count < 15)
    {
      set_r_pwm(right_motor_speed + (int)outputVal);
      set_l_pwm(0);
      count++;
    }
    set_l_pwm(left_motor_speed + (int)outputVal);
  }
}

void SH_right (float SH_cm)
{
  int count = 0;
  if (SH_cm >= 8 && SH_cm <= 22)
  {
    while(count < 15)
    {
      set_l_pwm(left_motor_speed + (int)outputVal);
      set_r_pwm(0);
      count++;
    }
    set_r_pwm(right_motor_speed + (int)outputVal);
  }
}

void SH_Stop (float SH_cm)
{
  if (SH_cm >=8 && SH_cm <= 22)
  {
    set_r_pwm(0);
    set_l_pwm(0);
  }
  delay(2000);
  set_r_pwm(right_motor_speed + (int)outputVal);
  set_l_pwm(left_motor_speed + (int)outputVal);
}

void setup() {
  pinMode(SH0, INPUT);
  pinMode(SH1, INPUT);
  pinMode(SH2, INPUT);
  pinMode(SH3, INPUT);
  pinMode(SH4, INPUT);
  pinMode(SH5, INPUT);
  pinMode(SH6, INPUT);
  pinMode(SH7, INPUT);
  
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

 // pinMode(A9, OUTPUT);
//  pinMode(A10, OUTPUT);

  Serial.begin(9600);
//  analogWrite(A9, 168);
//  analogWrite(A10, 168);

    //initialize the variables we're linked to

 // myPID.setTimeStep(10);
  
  

  
  /////////
  //set_r_pwm(350);
}



void loop() {

  
  
  int accY = analogRead(yout) - 346;
  int accZ = analogRead(zout) - 346;
  double accAngle = atan2(accY, accZ)*RAD_TO_DEG;
  angle = accAngle;

 // myPID.run();

  // OBROTY KOL //
  set_r_pwm(right_motor_speed + (int)outputVal);
  set_l_pwm(left_motor_speed + (int)outputVal);
 
 // Serial.println(angle);
  int SH0_volt = analogRead(SH0);
  int SH1_volt = analogRead(SH1);
  int SH2_volt = analogRead(SH2);
  int SH3_volt = analogRead(SH3);
  int SH4_volt = analogRead(SH4);
  int SH5_volt = analogRead(SH5);
  int SH6_volt = analogRead(SH6);
  int SH7_volt = analogRead(SH7);

  // VOLTAGE TO CM CONVERT //
  float SH0_cm = SHtoCM(SH0_volt);
  float SH1_cm = SHtoCM(SH1_volt);
  float SH2_cm = SHtoCM(SH2_volt);
  float SH3_cm = SHtoCM(SH3_volt);
  float SH4_cm = SHtoCM(SH4_volt);
  float SH5_cm = SHtoCM(SH5_volt);
  float SH6_cm = SHtoCM(SH6_volt);
  float SH7_cm = SHtoCM(SH7_volt);

  // PRINT DISTANCES - DO ZAKOMENTOWANIA POZNIEJ //
    Serial.print("SH0: ");
  Serial.println(SH0_cm);
    Serial.print("SH1: ");
  Serial.println(SH1_cm);
    Serial.print("SH2: ");
  Serial.println(SH2_cm);
    Serial.print("SH3: ");
  Serial.println(SH3_cm);
    Serial.print("SH4: ");
  Serial.println(SH4_cm);
    Serial.print("SH5: ");
  Serial.println(SH5_cm);
    Serial.print("SH6: ");
  Serial.println(SH6_cm);
    Serial.print("SH7: ");
  Serial.println(SH7_cm);
  delay(500);
  Serial.print("\n\n\n\n\n\n\n");
  delay(100);

//  SH_Stop(SH0_cm);
//  SH_Stop(SH1_cm);
//  SH_Stop(SH2_cm);
//  SH_Stop(SH3_cm);
//  SH_Stop(SH4_cm);
//  SH_Stop(SH5_cm);
//  SH_Stop(SH6_cm);
//  SH_Stop(SH7_cm);
  
}

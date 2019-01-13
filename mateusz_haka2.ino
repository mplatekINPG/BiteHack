#include <PID_v1.h>

#include <AutoPID.h>


#include <math.h>

#include <TimerThree.h>

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

#define buzzerPin 9

int accX, accY, accZ;

volatile int16_t left_motor_speed = 89; // 89; // 85, 155;
volatile int16_t right_motor_speed = 110; //110 // 102;

const int xout = A0; // z-axis of the accelerometer
const int yout = A1; // y-axis
const int zout = A2; // x-axis

volatile int x, y, z;

int tunes[] = {440, 440, 440, 349, 523, 440, 349, 523, 440, 0, 659, 659, 659, 698, 523, 415, 349, 523, 440, 0};
int times[] = {500, 500, 500, 350, 150, 500, 350, 150, 650, 500, 500, 500, 500, 350, 150, 500, 350, 150, 650, 500};

void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzerPin, note, duration);
}
int variableThatShowsHowManyTimerIterations=0;

void callback(){
  //accZ = analogRead(zout);
  //Serial.println(accZ);
variableThatShowsHowManyTimerIterations++;
if(variableThatShowsHowManyTimerIterations>20) variableThatShowsHowManyTimerIterations=0;
//beep(tunes[variableThatShowsHowManyTimerIterations],times[variableThatShowsHowManyTimerIterations]);
//  delay(50);

}

int SH0_volt = 0;
  int SH1_volt = 0;
  int SH2_volt = 0;
  int SH3_volt = 0;
  int SH4_volt = 0;
  int SH5_volt = 0;
  int SH6_volt = 0;
  int SH7_volt = 0;
  
  float SH0_cm = 0;
  float SH1_cm = 0;
  float SH2_cm = 0;
  float SH3_cm = 0;
  float SH4_cm = 0;
  float SH5_cm = 0;
  float SH6_cm = 0;
  float SH7_cm = 0;

  float SH0_bef = 1;
  float SH1_bef = 1;
  float SH2_bef = 1;
  float SH3_bef = 1;
  float SH4_bef = 1;
  float SH5_bef = 1;
  float SH6_bef = 1;
  float SH7_bef = 1;


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
AutoPID myPID(&angle, &setPoint, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);




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
    analogWrite(11, 100);
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
    analogWrite(11, 100);
  }
}

/*void SH_left (float SH_cm)
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
}*/
void SH_update()
{
  SH0_volt = analogRead(SH0);
  SH1_volt = analogRead(SH1);
  SH2_volt = analogRead(SH2);
  SH3_volt = analogRead(SH3);
  SH4_volt = analogRead(SH4);
  SH5_volt = analogRead(SH5);
  SH6_volt = analogRead(SH6);
  SH7_volt = analogRead(SH7);

  // VOLTAGE TO CM CONVERT //
  SH0_cm = SHtoCM(SH0_volt);
  SH1_cm = SHtoCM(SH1_volt);
  SH2_cm = SHtoCM(SH2_volt);
  SH3_cm = SHtoCM(SH3_volt);
  SH4_cm = SHtoCM(SH4_volt);
  SH5_cm = SHtoCM(SH5_volt);
  SH6_cm = SHtoCM(SH6_volt);
  SH7_cm = SHtoCM(SH7_volt);
}

void setup() {

  //Timer3.initialize(500000);
  //Timer3.attachInterrupt(callback); 

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

  myPID.setTimeStep(10);
  
  
  set_r_pwm(right_motor_speed);
  set_l_pwm(left_motor_speed);
   
  
  /////////
  //set_r_pwm(350);
}

int counter = 0;

void loop() {
//
  beep(tunes[variableThatShowsHowManyTimerIterations],times[variableThatShowsHowManyTimerIterations]);
  delay(50);

  accY = analogRead(yout) - 346;
  accZ = analogRead(zout) - 346;
//  double accAngle = atan2(accY, accZ)*RAD_TO_DEG;
//  angle = accAngle;

//  myPID.run();

  // OBROTY KOL //

  SH0_bef = SH0_cm; // przod lewy
  SH1_bef = SH1_cm; // przod prawy
  SH2_bef = SH2_cm; // przod prosto
  SH3_bef = SH3_cm;
  SH4_bef = SH4_cm;
  SH5_bef = SH5_cm; // tył tył
  SH6_bef = SH6_cm;
  SH7_bef = SH7_cm;

  SH_update();


  // PRINT DISTANCES - DO ZAKOMENTOWANIA POZNIEJ //
  
//   Serial.print("SH0: ");
//  Serial.println(SH0_cm);
//    Serial.print("SH1: ");
//  Serial.println(SH1_cm);
//    Serial.print("SH2: ");
//  Serial.println(SH2_cm);
//    Serial.print("SH3: ");
//  Serial.println(SH3_cm);
//    Serial.print("SH4: ");
//  Serial.println(SH4_cm);
//    Serial.print("SH5: ");
//  Serial.println(SH5_cm);
//    Serial.print("SH6: ");
//  Serial.println(SH6_cm);
//    Serial.print("SH7: ");
//  Serial.println(SH7_cm);
//  delay(500);
//  Serial.print("\n\n\n\n\n\n\n");
//  delay(1000); 


   set_r_pwm(right_motor_speed);
   set_l_pwm(left_motor_speed);

 if (SH0_cm >= 8 && SH0_cm <= 24)
    if (SH0_cm/SH0_bef < 1.2)
    {
//      set_r_pwm(0);
//      set_l_pwm(0);
//      delay(100);
      set_r_pwm((-1)*right_motor_speed-30);
      set_l_pwm(left_motor_speed+30);
 //     delay(200);
//      set_r_pwm(0);
//      set_l_pwm(0);
    }
    
  if (SH1_cm >= 8 && SH1_cm <= 24)
    if (SH1_cm/SH1_bef < 1.2)
    {
//      set_r_pwm(0);
//   
  if (SH2_cm >= 8 && SH2_cm <= 24)
    if (SH2_cm/SH2_bef < 1.2)
    {
//      set_r_pwm(0);
//      set_l_pwm(0);
//      delay(50);
//      int kier=0;
//      kier = random(0,1);
//      if (kier = 0)
//      {
        set_r_pwm(right_motor_speed+30);
        set_l_pwm((-1)*left_motor_speed-30);
//      }
//      else
//      {
//        set_r_pwm((-1)*right_motor_speed-30);
//        set_l_pwm(left_motor_speed+30);
//      }
////      delay(200);
//      set_r_pwm(0);
//      set_l_pwm(0);
    }
  if (SH5_cm >= 8 && SH5_cm <= 22.4)
  {
    if (SH5_cm/SH5_bef < 1.2)
    {
      set_r_pwm(right_motor_speed+50);
      set_l_pwm(left_motor_speed+60);
 //     delay(200);
    }
  }

  counter += 1;
  if(counter>8)
  {
    variableThatShowsHowManyTimerIterations++;
    if(variableThatShowsHowManyTimerIterations>20) variableThatShowsHowManyTimerIterations=0;
    counter = 0;
  }
  Serial.println("hehe");

}

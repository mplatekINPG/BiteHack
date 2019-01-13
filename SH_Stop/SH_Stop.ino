
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

void SH_Stop (float SH_cm)
{
  if (SH_cm >=8 && SH_cm <= 22)
  {
    set_r_pwm(0);
    set_l_pwm(0);
  }
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
}

void loop() {
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
  
  SH_Stop(SH0_cm);
  SH_Stop(SH1_cm);
  SH_Stop(SH2_cm);
  SH_Stop(SH3_cm);
  SH_Stop(SH4_cm);
  SH_Stop(SH5_cm);
  SH_Stop(SH6_cm);
  SH_Stop(SH7_cm);
  
}

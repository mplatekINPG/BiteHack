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

void setup()
{
  // JEDŹ PROSTO - nastawy Kuby
}

void loop()
{
  SH0_bef = SH0_cm; // przod lewy
  SH1_bef = SH1_cm; // przod prawy
  SH2_bef = SH2_cm; // przod prosto
  SH3_bef = SH3_cm;
  SH4_bef = SH4_cm;
  SH5_bef = SH5_cm;
  SH6_bef = SH6_cm;
  SH7_bef = SH7_cm;

  SH_update();

  if (SH0_cm >= 8 && SH0_cm <= 24)
    if (SH0_cm/SH0_bef < 1.2)
    {
      set_r_pwm(0);
      set_l_pwm(0);
      delay(200);
      set_r_pwm((-1)*right_motor_speed);
      set_l_pwm(left_motor_speed);
      delay(200);
      set_r_pwm(0);
      set_l_pwm(0);
    }
    
  if (SH1_cm >= 8 && SH1_cm <= 24)
    if (SH1_cm/SH1_bef < 1.2)
    {
      set_r_pwm(0);
      set_l_pwm(0);
      delay(200);
      set_r_pwm(right_motor_speed);
      set_l_pwm((-1)*left_motor_speed);
      delay(200);
      set_r_pwm(0);
      set_l_pwm(0);
    }

  if (SH2_cm >= 8 && SH2_cm <= 24)
    if (SH2_cm/SH2_bef < 1.2)
    {
      set_r_pwm(0);
      set_l_pwm(0);
      delay(200);
      randomSeed();
      kier = random(1);
      if (kier = 0)
      {
        set_r_pwm(right_motor_speed);
        set_l_pwm((-1)*left_motor_speed);
      }
      else
      {
        set_r_pwm((-1)*right_motor_speed);
        set_l_pwm(left_motor_speed);
      }
      delay(200);
      set_r_pwm(0);
      set_l_pwm(0);
    }
}


#define SH0 A0
#define SH1 A1
#define SH2 A2
#define SH3 A3
#define SH4 A4
#define SH5 A5
#define SH6 A6
#define SH7 A7

int SHtoCM (int value) {
  if (value < 10) value = 10;
  return ((67870.0 / (value - 3.0)) - 40.0);
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

/*
  int SH0_volt = 0;
  int SH1_volt = 0;
  int SH2_volt = 0;
  int SH3_volt = 0;
  int SH4_volt = 0;
  int SH5_volt = 0;
  int SH6_volt = 0;
  int SH7_volt = 0;

  int SH0_cm = 0;
  int SH1_cm = 0;
  int SH2_cm = 0;
  int SH3_cm = 0;
  int SH4_cm = 0;
  int SH5_cm = 0; 
  int SH6_cm = 0;
  int SH7_cm = 0; 
  */
  
  Serial.begin(9600);
}

void loop() {
  // ANALOG READ PART //
  int SH0_volt = analogRead(SH0);
  int SH1_volt = analogRead(SH1);
  int SH2_volt = analogRead(SH2);
  int SH3_volt = analogRead(SH3);
  int SH4_volt = analogRead(SH4);
  int SH5_volt = analogRead(SH5);
  int SH6_volt = analogRead(SH6);
  int SH7_volt = analogRead(SH7);

  // VOLTAGE TO CM CONVERT //
  int SH0_cm = SHtoCM(SH0_volt);
  int SH1_cm = SHtoCM(SH1_volt);
  int SH2_cm = SHtoCM(SH2_volt);
  int SH3_cm = SHtoCM(SH3_volt);
  int SH4_cm = SHtoCM(SH4_volt);
  int SH5_cm = SHtoCM(SH5_volt);
  int SH6_cm = SHtoCM(SH6_volt);
  int SH7_cm = SHtoCM(SH7_volt);

  // PRINT DISTANCES - DO ZAKOMENTOWANIA POZNIEJ //
    Serial.println("\nSH0: ");
  Serial.print(SH0_volt);
//    Serial.println("\nSH1: ");
//  Serial.print(SH1_cm);
//    Serial.println("\nSH2: ");
//  Serial.print(SH2_cm);
//    Serial.println("\nSH3: ");
//  Serial.print(SH3_cm);
//    Serial.println("\nSH4: ");
//  Serial.print(SH4_cm);
//    Serial.println("\nSH5: ");
//  Serial.print(SH5_cm);
//    Serial.println("\nSH6: ");
//  Serial.print(SH6_cm);
//    Serial.println("\nSH7: ");
//  Serial.print(SH7_cm);
  delay(1000);

  // REACTION WHEN DIST < 50 CM //
  

}

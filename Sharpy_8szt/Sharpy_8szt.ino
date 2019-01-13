//#include <Bounce2.h>
//Bounce debouncer = Bounce();

#define SH0 A0
#define SH1 A1
#define SH2 A2
#define SH3 A3
#define SH4 A4
#define SH5 A5
#define SH6 A6
#define SH7 A7

//// SOUND FREQS //
//#define buzzerPin 6
//#define buttonPin 3
//int count = 0;
//
//const int c = 261;
//const int d = 294;
//const int e = 329;
//const int f = 349;
//const int g = 391;
//const int gS = 415;
//const int a = 440;
//const int aS = 455;
//const int b = 466;
//const int cH = 523;
//const int cSH = 554;
//const int dH = 587;
//const int dSH = 622;
//const int eH = 659;
//const int fH = 698;
//const int fSH = 740;
//const int gH = 784;
//const int gSH = 830;
//const int aH = 880;
//
//
//void beep(int note, int duration)
//{
//  //Play tone on buzzerPin
//  tone(buzzerPin, note, duration);
//  delay(duration);
//  //Stop tone on buzzerPin
//  noTone(buzzerPin);
// 
//  delay(50);
//}
//
//void firstSection()
//{
//  beep(a, 500/2);
//  beep(a, 500/2);    
//  beep(a, 500/2);
//  beep(f, 350/2);
//  beep(cH, 150/2);  
//  beep(a, 500/2);
//  beep(f, 350/2);
//  beep(cH, 150/2);
//  beep(a, 650/2);
// 
//  delay(500/2);
// 
//  beep(eH, 500/2);
//  beep(eH, 500/2);
//  beep(eH, 500/2);  
//  beep(fH, 350/2);
//  beep(cH, 150/2);
//  beep(gS, 500/2);
//  beep(f, 350/2);
//  beep(cH, 150/2);
//  beep(a, 650/2);
// 
//  delay(500/2);
//}
// END OF SOUNDS //


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

void setup() {
  pinMode(SH0, INPUT);
  pinMode(SH1, INPUT);
  pinMode(SH2, INPUT);
  pinMode(SH3, INPUT);
  pinMode(SH4, INPUT);
  pinMode(SH5, INPUT);
  pinMode(SH6, INPUT);
  pinMode(SH7, INPUT);
  
//  pinMode(buttonPin, INPUT);
//  pinMode(24, OUTPUT);
//  digitalWrite(24, HIGH);
//  pinMode(buzzerPin, OUTPUT);
//
//  debouncer.attach(buttonPin);
//  debouncer.interval(50);
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
//  debouncer.update();
//  if (debouncer.read() == HIGH)
//  {   
//      count = 0;
//      Serial.println("HIGH\n"); 
//  }
//  if (debouncer.read() == LOW);
//  {   
//      count = 1;
//      Serial.println("LOW\n"); 
//  }
//  if (count == 0)
//    firstSection();

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

  

  // REACTION WHEN DIST < 50 CM //
  

}



#include <SoftwareSerial.h>

#define SH_RX 2
#define SH_TX 3

SoftwareSerial SH_bl(SH_RX, SH_TX);
int num = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SH_bl.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (num > 9) num = 0;
  Serial.println("Wysylanie po BT");
  SH_bl.write(num);
  delay(500);
  num++;
}

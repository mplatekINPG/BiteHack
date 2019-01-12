int speakerPin = 12;
int buttonPin = 4;

int play = 1;
int numTones = 10;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
//            mid C  C#   D    D#   E    F    F#   G    G#   A

int Pressed()
{
  int pressed = 0;
  if (digitalRead(4) == HIGH)
  {
    delay(100);
    pressed = 1;
  }
  else
    pressed = 0;

    return pressed;
}
 
void setup()
{
  pinMode(4, INPUT_PULLUP);
  for (int i = 0; i < numTones; i++)
  {
    tone(speakerPin, tones[i]);
    delay(500);
  }
  noTone(speakerPin);
}
 
void loop()
{
 while(play == 1)
 {
  for (int i = 0; i < numTones; i++)
  {
    if (Pressed() == 1)
    {
      play = 0;
      break;
    }
    tone(speakerPin, tones[i]);
    delay(500);
  }
  noTone(speakerPin);

  for (int i = numTones-1; i>=0; i--)
  {
    if (Pressed() == 1)
    {
      play = 0;
      break;
    }
    tone(speakerPin, tones[i]);
    delay(500);
  }
  noTone(speakerPin);
  }

  if (play == 0){
    if (Pressed() == 1)
      {
        delay(100);
        play = 1;
      }}
}


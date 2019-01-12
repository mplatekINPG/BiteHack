int czujnik = A1;   //pin analogowy A1 połączony z sygnałem z czujnika

void setup(){
  Serial.begin(9600);        //inicjalizacja monitora szeregowego
  Serial.println("Test czujnika odleglosci"); 
}

void loop(){
  int odl = analogRead(czujnik);      //odczytanie wartości z czujnika
  Serial.println(odl);                //wyświetlenie jej na monitorze

  delay(1000);                         //opóźnienie między kolejnymi odczytami
}

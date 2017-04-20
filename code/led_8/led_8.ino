void setup() {
 pinMode(0, OUTPUT);
 pinMode(1, OUTPUT);
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
}
void LED(int i)
{
    digitalWrite(i , HIGH);
    delay(250);
    digitalWrite(i , LOW);
    delay(250);
}
void loop() {
  for( int i = 0; i<=7; i++)
  {
    LED(i);
  }
  for(int i = 7; i>=0; i--)
  {
    LED(i);
  }
}

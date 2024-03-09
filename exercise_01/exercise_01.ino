// C++ code
//

#define LED1 13
#define LED2 11
#define ZEL 6
#define TLAC 4

int tl;
unsigned long start;

void my_delay(unsigned long time) 
{
  start = millis();
  while(millis() - start < time) 
  {
    tl = digitalRead(TLAC);
  
    digitalWrite(ZEL, tl);
  }
}

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(ZEL, OUTPUT);
  pinMode(TLAC, INPUT_PULLUP);
}

void loop()
{
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  
  my_delay(1000);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  
  my_delay(1000);
}

// C++ code
//

#define LED1 13
#define LED2 11
#define ZEL 6
#define TLAC 4

int tl;
unsigned long startBulb;
unsigned long bulbPassedTime;


unsigned long start;
unsigned long passedTime;

int machineOneState;
int machineTwoState;

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(ZEL, OUTPUT);
  pinMode(TLAC, INPUT_PULLUP);

  digitalWrite(ZEL, LOW);
  startBulb = millis();
  machineOneState = 0;
  
  
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  start = millis();
  machineTwoState = 0;
}

void loop()
{
  tl = digitalRead(TLAC);
  bulbPassedTime = millis() - startBulb;


  passedTime = millis() - start;
  
  
  
  switch (machineOneState) 
  {
    case 0:
      if (tl == LOW)
      {
          digitalWrite(ZEL, HIGH);
            startBulb = millis();
            machineOneState = 1;
      }
      break;
    case 1:
      if (tl == HIGH) 
      {
            machineOneState = 2;
      }
      break;
    case 2:
      if (bulbPassedTime > 2000) 
      {
          digitalWrite(ZEL, LOW);
            machineOneState = 0;
      }
      else if (tl == LOW)
        {
            digitalWrite(ZEL, LOW);
          machineOneState = 3;
        }
      break;
    case 3:
      if (tl == HIGH) 
      {
          machineOneState = 0;
      }
      break;
  }
  
  switch(machineTwoState) 
  {
    case 0:
      if (passedTime > 1000) 
      {
          digitalWrite(LED1, HIGH);
            digitalWrite(LED2, LOW);
            start = millis();
            machineTwoState = 1;
      }
      break;
    case 1:
      if (passedTime > 1000) 
      {
          digitalWrite(LED1, LOW);
            digitalWrite(LED2, HIGH);
            start = millis();
            machineTwoState = 0;
      }
      break;
  }
}

// C++ code
//

#define SEG_A 2
#define SEG_B 3
#define SEG_C 4
#define SEG_D 5
#define SEG_E 6
#define SEG_F 7
#define SEG_G 8
#define SEG_DP 9

#define TLAC 12

unsigned long passedTime;
unsigned long start;

unsigned long staggerStart;
unsigned long staggerPassedTime;

int machineState;

int poz;
int button_state;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_DP, OUTPUT);
  
  pinMode(TLAC, INPUT_PULLUP);
  
  start = millis();
  staggerStart = millis();
  
  machineState = 0;
  poz = 0;
}

void ukaz_cislo (int cislo) 
{
  digitalWrite(SEG_A, LOW);
  digitalWrite(SEG_B, LOW);
    digitalWrite(SEG_C, LOW);
    digitalWrite(SEG_D, LOW);
    digitalWrite(SEG_E, LOW);
    digitalWrite(SEG_F, LOW);
    digitalWrite(SEG_G, LOW);
    digitalWrite(SEG_DP, LOW);
  
    switch (cislo) 
    {
      case 0:
          digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
          break;
        case 1:
      digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
          break;
        case 2:
          digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
          digitalWrite(SEG_G, HIGH);
          break;
        case 3:
          digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
          digitalWrite(SEG_G, HIGH);
          break;
        case 4:
      digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
          digitalWrite(SEG_F, HIGH);
          digitalWrite(SEG_G, HIGH);
          break;
        case 5:
          digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_C, HIGH);
          digitalWrite(SEG_D, HIGH);
          digitalWrite(SEG_F, HIGH);
          digitalWrite(SEG_G, HIGH);
          break;
        case 6:
          digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_C, HIGH);
          digitalWrite(SEG_D, HIGH);
          digitalWrite(SEG_E, HIGH);
          digitalWrite(SEG_F, HIGH);
          digitalWrite(SEG_G, HIGH);
          break;
        case 7:
          digitalWrite(SEG_A, HIGH);
          digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
          break;
        case 8:
          digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
          digitalWrite(SEG_G, HIGH);
          break;
        case 9:
          digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_F, HIGH);
          digitalWrite(SEG_G, HIGH);
          break;
    }
}

void loop()
{
    button_state = digitalRead(TLAC);
    
    passedTime = millis() - start;
    staggerPassedTime = millis() - staggerStart;
  
    if (poz == 10) 
    {
      poz = 0;
    }
  else if (poz == -1)
    {
      poz = 9;
    }
  
    if (passedTime > 5) 
    {
      ukaz_cislo(poz);
        start = millis();
    }
  
    switch (machineState) 
    {
      case 0:
          if (button_state == LOW) 
          {
            machineState = 3;
          }
          else if (button_state == HIGH)
          {
              machineState = 1;
          }
          break;
        case 1:
          if (button_state == LOW) 
          {
            machineState = 2;
                staggerStart = millis();
          }
          break;
        case 2:
          if (staggerPassedTime > 100) 
          {
            machineState = 3;
                poz++;
          }
          else if (button_state == HIGH 
                     && staggerPassedTime <= 100) 
          {
            machineState = 1;
          }
          break;
        case 3:
          if (button_state == HIGH)
          {
              machineState = 4;
                staggerStart = millis();
          }
          break;
        case 4:
          if (staggerPassedTime > 100) 
          {
            machineState = 1;
          }
          else if (button_state == LOW
                     && staggerPassedTime <= 100) 
          {
              machineState = 3;
          }
          break;
    }
}

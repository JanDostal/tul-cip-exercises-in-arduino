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

#define SW_1 10
#define SW_2 11

unsigned long passedTime;
unsigned long start;

int machineState;

int poz;
int sw1_state;
int sw2_state;

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
  
  pinMode(SW_1, INPUT_PULLUP);
  pinMode(SW_2, INPUT_PULLUP);
  
  start = millis();
  
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
  
  /*for (int i = 9; i >= 0; i--) 
  {
    ukaz_cislo(i);
    delay(1000);
  }*/
    
  sw1_state = digitalRead(SW_1);
  sw2_state = digitalRead(SW_2);
    
  passedTime = millis() - start;
  
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
      if (sw1_state == LOW && sw2_state == LOW) 
      {
        machineState = 1;
      }
      else if (sw1_state == HIGH && sw2_state == LOW)
      {
        machineState = 2;
      }
      else if (sw1_state == HIGH && sw2_state == HIGH) 
      {
        machineState = 3;
      }
      else 
      {
        machineState = 4;
      }
      break;
    case 1:
      if (sw1_state == HIGH) 
      {
        machineState = 2;
        poz++;
      }
      else if (sw2_state == HIGH) 
      {
        machineState = 4;
        poz--;
      }
      break;
    case 2:
      if (sw2_state == HIGH) 
      {
        machineState = 3;
        poz++;
      }
      else if (sw1_state == LOW) 
      {
        machineState = 1;
        poz--;
      }
      break;
    case 3:
      if (sw1_state == LOW)
      {
        machineState = 4;
        poz++;
      }
      else if (sw2_state == LOW) 
      {
        machineState = 2;
        poz--;
      }
      break;
    case 4:
      if (sw2_state == LOW) 
      {
        machineState = 1;
        poz++;
      }
      else if (sw1_state == HIGH) 
      {
        machineState = 3;
        poz--;
      }
      break;
  }
}

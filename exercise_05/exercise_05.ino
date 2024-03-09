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

#define firstDisplay 11
#define secondDisplay 10

#define TLAC_5_CROWNS 12
#define TLAC_10_CROWNS 13

unsigned long firstDisplayPassedTime;
unsigned long firstDisplayStart;

unsigned long secondDisplayStart;
unsigned long secondDisplayPassedTime;

unsigned long staggerStart;
unsigned long staggerPassedTime;

unsigned long start;
unsigned long passedTime;

int machineState;

int displayRemainingTimeSeconds;
int remainingTimeSeconds;

int button_5_crowns_state;
int button_10_crowns_state;
bool wasMoneyInserted;

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
  
  pinMode(firstDisplay, OUTPUT);
  pinMode(secondDisplay, OUTPUT);
  
  pinMode(TLAC_5_CROWNS, INPUT_PULLUP);
  pinMode(TLAC_10_CROWNS, INPUT_PULLUP);
  
  firstDisplayStart = millis();
  secondDisplayStart = millis();
  staggerStart = millis();
  start = millis();
  
  machineState = 0;
  displayRemainingTimeSeconds = 0;
  remainingTimeSeconds = 0;
  wasMoneyInserted = false;
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

void displayOff() 
{
  digitalWrite(firstDisplay, 1);
    digitalWrite(secondDisplay, 1);
}

void loop()
{
    button_5_crowns_state = digitalRead(TLAC_5_CROWNS);
    button_10_crowns_state = digitalRead(TLAC_10_CROWNS);
    
    firstDisplayPassedTime = millis() - firstDisplayStart;
    secondDisplayPassedTime = millis() - secondDisplayStart;
    staggerPassedTime = millis() - staggerStart;
    passedTime = millis() - start;
  
    if (passedTime > 1000 && wasMoneyInserted == false)
    {
        if (remainingTimeSeconds <= 99) 
        {
          displayRemainingTimeSeconds--;
        }
        remainingTimeSeconds--;
      start = millis();
    }
  
    if (remainingTimeSeconds > 300) 
    {
      displayRemainingTimeSeconds = 300;
        remainingTimeSeconds = 300;
    }
  
    if (displayRemainingTimeSeconds > 99)
    {
      displayRemainingTimeSeconds = 99;
    }
  else if (remainingTimeSeconds == -1)
    {
      displayRemainingTimeSeconds = 0;
        remainingTimeSeconds = 0;
    }
  
    if (firstDisplayPassedTime > 30)
    {
        displayOff();
        digitalWrite(firstDisplay, 0);
      ukaz_cislo(displayRemainingTimeSeconds / 10);
        firstDisplayStart = millis();
    }
  
    if (secondDisplayPassedTime > 20) 
    {
        displayOff();
        digitalWrite(secondDisplay, 0);
      ukaz_cislo(displayRemainingTimeSeconds % 10);
        secondDisplayStart = millis();
    }
  
    switch (machineState) 
    {
      case 0:
          if (button_5_crowns_state == LOW && 
                button_10_crowns_state == HIGH) 
          {
            machineState = 1;
                staggerStart = millis();
          }
          else if (button_5_crowns_state == HIGH &&
                     button_10_crowns_state == LOW)
          {
              machineState = 2;
                staggerStart = millis();
          }
          break;
        case 1:
          if (staggerPassedTime > 100) 
          {
            machineState = 3;
                displayRemainingTimeSeconds += 5;
                remainingTimeSeconds += 5;
                wasMoneyInserted = true;
          }
          else if (button_5_crowns_state == HIGH 
                     && staggerPassedTime <= 100) 
          {
            machineState = 0;
          }
          break;
        case 2:
          if (staggerPassedTime > 100) 
          {
            machineState = 3;
                displayRemainingTimeSeconds += 10;
                remainingTimeSeconds += 10;
                wasMoneyInserted = true;
          }
          else if (button_10_crowns_state == HIGH 
                     && staggerPassedTime <= 100) 
          {
            machineState = 0;
          }
          break;
        case 3:
          wasMoneyInserted = false;
          if (button_5_crowns_state == HIGH && 
                button_10_crowns_state == HIGH)
          {
              machineState = 4;
                staggerStart = millis();
          }
          break;
        case 4:
          if (staggerPassedTime > 100) 
          {
            machineState = 0;
          }
          else if (
               ((button_5_crowns_state == HIGH && 
                button_10_crowns_state == LOW) ||
               (button_5_crowns_state == LOW && 
                button_10_crowns_state == HIGH))
                     && staggerPassedTime <= 100) 
          {
              machineState = 3;
          }
          break;
    }
}

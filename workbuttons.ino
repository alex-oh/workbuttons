//button pin constants
const int bWork = 2;
const int bScreen = 3;

//led pin constants
const int lg = 10;
const int ly = 11;
const int lr = 12;
int ledarray[3] = {lg, ly, lr};

//changing variables
int bWorkstate = 0;
int bScreenstate = 0;
// if workON is true, then you're working
bool workON = false;
//(if screenOFF is true, then the person has pressed the button and taken a break)
bool screenOFF = false;
int buttonarray[2] = {bWorkstate, bScreenstate};

int workPrevState = 0;
int screenPrevState = 0;

//timekeeping variables
unsigned long worklim = 8 * 3.6e6;
unsigned long timenow = 0;
unsigned long timetotal = 0;
unsigned long timestart = 0;

//prototypes
void blinkled(int led, int amount, int duration);
void blinkall(int amount, int duration);

void setup() {
  Serial.begin(9600);
  //initialize led and button pins
  for (int i = 0; i < 3; i++)
  {
    pinMode(ledarray[i], OUTPUT);
    blinkled(ledarray[i], 1, 300);
  }
  pinMode(bWork, INPUT);
  pinMode(bScreen, INPUT);
  blinkall(2, 400);
}

void loop() {
  bWorkstate = digitalRead(bWork);
  //work button - 8 hours countdown timer

  //test to make sure that each button press is recognized
  if (bWorkstate != workPrevState)
  {
    if (bWorkstate == 1){
      //turn on green led
      digitalWrite(lg, HIGH);
    }
    if (bWorkstate == 0){
      //turn off green led
      digitalWrite(lg, LOW);
    }
  }
  //work button code
  if (bWorkstate != workPrevState && bWorkstate == 1)
  {
    if (!workON)
    {
      //start countdown
      timestart = millis();
      workON = true; //toggle workON to be on
      digitalWrite(ly, HIGH);
    }
    else if (workON) //pause during the work day
    {
      //pause countdown and add to total
      timenow = millis();
      timetotal = timetotal + (timenow - timestart);
      workON = false;
      digitalWrite(ly, LOW);
      Serial.print("timetotal: ");
      Serial.print(timetotal/60000.0);
      Serial.print(" minutes");
      Serial.println();
    }
  }
  
  workPrevState = bWorkstate;
}

void blinkled(int led, int amount, int duration)
{
  for (int j = 0; j < amount; j++)
  {
    digitalWrite(led, HIGH);
    delay(duration);
    digitalWrite(led, LOW);
    delay(duration);
  }
}

void blinkall(int amount, int duration)
{
  for (int j = 0; j < amount; j++)
  {
    for(int i = 0; i < 3; i++)
    {
      digitalWrite(ledarray[i], HIGH);
    }
    delay(duration);
    for(int k = 0; k < 3; k++)
    {
      digitalWrite(ledarray[k], LOW);
    }
    delay(duration);
  }
}

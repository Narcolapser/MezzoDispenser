/*
   BYJ48 Stepper motor code
   Connect :
   IN1 >> D8
   IN2 >> D9
   IN3 >> D10
   IN4 >> D11
   VCC ... 5V Prefer to use external 5V Source
   Gnd
   written By :Mohannad Rawashdeh
  http://www.instructables.com/member/Mohannad+Rawashdeh/
     28/9/2013
  */

#include <Time.h>

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
#define B1   4
#define B2   2
long Steps = 0;
boolean Direction = true;// gre
unsigned long last_time;
unsigned long currentMillis;
long cur_step = 0;
long dispenseAmount = 1;
long dispenseTotal = 2048;
//int dispenseTimeFrame = 60 * 60 * 24 * 1000 // a day of microseconds.
long dispenseTimeFrame = 3600000;//60*60*1000; // an hour of microseconds.
long dispenseDelay = 2048 / 3600;
long PC = 0;
long cur_time;
long next_time;
long time;
time_t t = now();
void setup()
{
  Serial.begin(115200);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
  pinMode(B1, INPUT);
  // delay(1000);
  Serial.println("Ready");
}

void loop()
{
  cur_time = secondInDay();
  if(digitalRead(B1))
  {
    PC++;
  }
  else
  {
    PC = 0;
  }

  if(PC > 5)
  {
    PC = 0;
    dispenseTotal = getDispense();
    dispenseDelay=dispenseTimeFrame/dispenseTotal;//The time frame over which to dispense the amount to dispense.
  }

  if (cur_time >= next_time)
  {
    dispense(dispenseAmount);
    next_time = secondInDay() + dispenseDelay;
  }
  clearStep();
  
  Serial.print("Dispsing: ");
  Serial.print(dispenseTotal);
  Serial.print(" which comes to a step every ");
  Serial.print(dispenseDelay);
  Serial.print(". Next dispense is at ");
  Serial.print(next_time);
  Serial.print(" and the current time is ");
  Serial.println(cur_time);
  delay(100);
}

int getDispense()
{
  disp(15);
  delay(250);
  disp(0);
  delay(250);
  sweep(100);
  build(250);
  int val = 0;
  int complete = 0;

  Serial.println("Getting ready to register Dispensing!");

  while(complete < 500)
  {
    Serial.print("inside the dispensing loop. ");
    Serial.print(val);
    Serial.print(" ");
    Serial.println(complete);
    
    if(digitalRead(B1))
    {
      dispense(1);
      //stepper(1);
      //delay(2);
      val ++;
      complete = 0;
    }
    else
    {
      complete++;
    }
    if(complete>400)
    {
      disp(15);
    }else if(complete > 300)
    {
      disp(7);
    }else if(complete > 200)
    {
      disp(3);
    }else if(complete > 100)
    {
      disp(1);
    }else
    {
      disp(0);
    }
    delay(10);
  }
  Serial.print("Dispense amount retrieved!: ");
  Serial.println(val);

  sweep(50);
  flash(250);
  flash(250);
  disp(0);
  
  
  return val;
}

long secondInDay()
{
  /*t = now();
  int ret = second(t);
  ret += 60 * minute(t);
  ret += 3600 * hour(t);
  ret *= 1000;
  ret += micros();*/
  //return ret;
  return micros()/1000;
}

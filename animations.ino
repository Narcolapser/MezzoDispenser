void disp(int val)
{ 
  digitalWrite(IN1,val%2);
  val /= 2;
  digitalWrite(IN2,val%2);
  val /= 2;
  digitalWrite(IN3,val%2);
  val /= 2;
  digitalWrite(IN4,val%2);
}

void sweep(int val)
{
  disp(1);
  delay(val);
  disp(2);
  delay(val);
  disp(4);
  delay(val);
  disp(8);
  delay(val);
  disp(4);
  delay(val);
  disp(2);
  delay(val);
  disp(1);
  delay(val);
  disp(2);
  delay(val);
  disp(4);
  delay(val);
  disp(8);
  delay(val);
  disp(4);
  delay(val);
  disp(2);
  delay(val);
  disp(1);
  delay(val);
  disp(0);
}

void build(int val)
{
  disp(1);
  delay(val);
  disp(3);
  delay(val);
  disp(7);
  delay(val);
  disp(15);
  delay(val);
  disp(0);
}

void flash(int val)
{
  disp(0);
  delay(val);
  disp(15);
  delay(val);
  disp(0);
}


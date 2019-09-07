int ledPin1 =  1;
int ledPin2 =  2;
int ledPin3 =  3;
int ledPin4 =  4;
int ledPin5 =  5;
int ledPin6 =  6;
int ledPin7 =  7;
int ledPin8 =  8;

void setup()   {                
  pinMode(ledPin1, OUTPUT);  
  pinMode(ledPin2, OUTPUT);  
  pinMode(ledPin3, OUTPUT);  
  pinMode(ledPin4, OUTPUT);  
  pinMode(ledPin5, OUTPUT);  
  pinMode(ledPin6, OUTPUT);  
  pinMode(ledPin7, OUTPUT);  
  pinMode(ledPin8, OUTPUT);
}

void demo()
{
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin6, HIGH);
  digitalWrite(ledPin7, HIGH);
  digitalWrite(ledPin8, HIGH);
  delay(1000);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin6, LOW);
  digitalWrite(ledPin7, LOW);
  digitalWrite(ledPin8, LOW);
  delay(1000);
}

void num1()
{
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin5, HIGH);
}
void num2()
{
  digitalWrite(ledPin6, HIGH);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin8, HIGH);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(ledPin3, HIGH);
}
void num3()
{
  digitalWrite(ledPin6, HIGH);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin8, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
}
void num4()
{
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin8, HIGH);
  digitalWrite(ledPin7, HIGH);
}
void num5()
{
  digitalWrite(ledPin6, HIGH);
  digitalWrite(ledPin7, HIGH);
  digitalWrite(ledPin8, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
}
void num6()
{
  digitalWrite(ledPin6, HIGH);
  digitalWrite(ledPin7, HIGH);
  digitalWrite(ledPin8, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
}
void num7()
{
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin6, HIGH);
}
void num8()
{
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin6, HIGH);
  digitalWrite(ledPin7, HIGH);
  digitalWrite(ledPin8, HIGH);
}
void num9()
{
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin6, HIGH);
  digitalWrite(ledPin7, HIGH);
  digitalWrite(ledPin8, HIGH);
}
void num0()
{
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin6, HIGH);
  digitalWrite(ledPin7, HIGH);
}
void ponto()
{
  digitalWrite(ledPin1, HIGH);
}
void reset()
{
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin6, LOW);
  digitalWrite(ledPin7, LOW);
  digitalWrite(ledPin8, LOW);
}
void count()
{
  num0();
  delay(1000);
  reset();
  num1();
  delay(1000);
  reset();
  num2();
  delay(1000);
  reset();
  num3();
  delay(1000);
  reset();
  num4();
  delay(1000);
  reset();
  num5();
  delay(1000);
  reset();
  num6();
  delay(1000);
  reset();
  num7();
  delay(1000);
  reset();
  num8();
  delay(1000);
  reset();
  num9();
  delay(1000);
  reset();
  ponto();
  delay(1000);
  reset();
}

void loop()                     
{
  count();
}

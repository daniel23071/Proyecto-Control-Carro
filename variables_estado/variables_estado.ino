#include <AFMotor.h>
AF_DCMotor motor1(2); // Motor delantero-trasero

int TRIG1 = A0; // Salida
int ECHO1 = A1; // Entrada
int t1;
int d1;
float volt, po, dist;
float vel;
const float k1=0.34574, k2=-0.189878982, l1=0.56, l2=-0.19402, b1=1, b2=0;
float gt11=1.8048232,gt12=-0.9126776, gt21=1.043372906,gt22=0.041251142, kc=0.810766239076155;
double Setpoint1, error1;
float U = 0, z1= 0, z2=0;
float x1 = 0, x2 = 0, w1=0, w2=0, o1=0, o2=0, f1=0,f2=0;

void setup()
{
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);

  t1 = pulseIn(ECHO1, HIGH);
  d1 = t1 / 59;

  if (Serial.available() > 1)
  {
    dist = Serial.parseFloat();
  }

  if (d1 > dist)
  { 
    
    Setpoint1 = (dist * 255.0) / 15;
    error1 = Setpoint1*kc - (d1 * 255.0 / 15);
    U = error1 + (-k1*o1-k2*o2);

    z1=l1*Setpoint1;
    z2=l2*Setpoint1;
    x1=U*b1;
    x2=U*b2;

    w1=gt11*o1+gt12*o2;
    w2=gt21*o1+gt22*o2;
    
    f1=z1+x1+w1;
    f2=z2+x2+w2;

    o1=f1;
    o2=f2;

    if (U > 255)
    {
      U = 255;
    }
    else if (U < 0)
    {
      U = 255;
    }

    motor1.setSpeed(U);
    motor1.run(BACKWARD);
    Serial.print(millis() / 1000.0, 3);
    Serial.print("\t");
    Serial.print(d1);
    Serial.print("\t");
    Serial.print(Setpoint1);
    Serial.print("\t");
    Serial.print(abs(error1));
    Serial.print("\t");
    Serial.print(U);
    Serial.print("\t");
    Serial.print(z1);
    Serial.print("\t");      
    Serial.println(z2);
    delay(250);
  }
  else
  {
    Setpoint1 = (dist * 255.0) / 15;
    error1 = Setpoint1*kc - (d1 * 255.0 / 15);
    U = error1 + (-k1*o1-k2*o2);

    z1=l1*Setpoint1;
    z2=l2*Setpoint1;
    x1=U*b1;
    x2=U*b2;

    w1=gt11*o1+gt12*o2;
    w2=gt21*o1+gt22*o2;
    
    f1=z1+x1+w1;
    f2=z2+x2+w2;

    o1=f1;
    o2=f2;

    if (U > 255) 
    {
      U = 255;
    }
    if (error1 == 0)
    {
      U = 0;
    }

    if (U < 0) 
    {
      U = 255;
    }

    motor1.setSpeed(U);
    motor1.run(FORWARD);
    Serial.print(millis() / 1000.0, 3);
    Serial.print("\t");
    Serial.print(d1);
    Serial.print("\t");
    Serial.print(Setpoint1);
    Serial.print("\t");
    Serial.print(abs(error1));
    Serial.print("\t");
    Serial.print(U);
    Serial.print("\t");    
    Serial.print(z1);
    Serial.print("\t");      
    Serial.println(z2);
    delay(250);
  }
}
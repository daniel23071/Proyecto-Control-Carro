#include <AFMotor.h>
AF_DCMotor motor1(2); // Motor delantero-trasero

int TRIG1 = A0; // Salida
int ECHO1 = A1; // Entrada
int t1;
int d1;
float volt, po, dist;
float vel;
const float to = 0.324594257178526, sa = 1, s1 = -0.372242, ro = 1.198, r1 = -0.8741;
double Setpoint1, error1;
float U = 0, u_1 = 0, E = 0, E_1=0;
float y_1 = 0, y1 = 0;


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
    error1 = Setpoint1*to - (d1 * 255.0 / 15);
    E = abs(error1);
    y1 = ro*Setpoint1 + r1*y_1;
    U = sa*E - s1*u_1;

    E_1 = E;
    u_1 = U;
    y_1 = Setpoint1;

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
    Serial.println(U);
    delay(250);
  }
  else
  {
    Setpoint1 = (dist * 255.0) / 15;
    error1 = Setpoint1*to - (d1 * 255.0 / 15);
    E = abs(error1);
    y1 = ro*Setpoint1 + r1*y_1;
    U = sa*E - s1*u_1;

    E_1 = E;
    u_1 = U;
    y_1 = Setpoint1;

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
    Serial.println(U);
    delay(250);
  }
}

#include <AFMotor.h>
AF_DCMotor motor1(2); // Motor delantero-trasero

int TRIG1 = A0; // Salida
int ECHO1 = A1; // Entrada
int t1;
int d1;
float volt, po, dist;
float vel;

float U = 0;

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
    float Gc_num[] = {6.3458, 12.6658};
    float Gc_den[] = {1, 13.55};
    float Gc_input = (d1 * 255.0 / 15) * Gc_num[1] + U * Gc_num[0];
    float Gc_output = Gc_den[1] * (d1 * 255.0 / 15) + Gc_den[0] * U;
    
    U = Gc_input - Gc_output;
    
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
    Serial.print(dist * 255.0 / 15);
    Serial.print("\t");
    Serial.print(abs(dist * 255.0 / 15 - d1 * 255.0 / 15));
    Serial.print("\t");
    Serial.println(U);
    delay(250);
  }
  else
  {
    float Gc_num[] = {6.3458, 12.6658};
    float Gc_den[] = {1, 13.55};
    float Gc_input = (d1 * 255.0 / 15) * Gc_num[1] + U * Gc_num[0];
    float Gc_output = Gc_den[1] * (d1 * 255.0 / 15) + Gc_den[0] * U;
    
    U = Gc_input - Gc_output;

    if (U > 255) 
    {
      U = 255;
    }
    if (dist * 255.0 / 15 - d1 * 255.0 / 15 == 0)
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
    Serial.print(dist * 255.0 / 15);
    Serial.print("\t");
    Serial.print(abs(dist *255.0 / 15 - d1 * 255.0 / 15));
    Serial.print("\t");
    Serial.println(U);
    delay(250);
  }
}


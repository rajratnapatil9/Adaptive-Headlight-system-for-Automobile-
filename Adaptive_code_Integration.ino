#include <Servo.h>
Servo myservo;
Servo myservo1;
Servo myservo2;
Servo myservo3;

const int y        = A0;
int triggerPin = 7;             //triggering on pin 7
int echoPin = 8;

int light_val, press_val, alch_val, adxl_y_val, duration, distance;             //Adding duration and distance;

void setup() 
{
  Serial.begin(9600);
 
   myservo.attach(9);        //MJ-95 First
  myservo1.attach(10);      //small servo1
  myservo2.attach(11);      // MJ-95 second
  myservo3.attach(12);      // small servo2
  
  pinMode(triggerPin, OUTPUT);  //defining pins
  pinMode(echoPin, INPUT);
}
 
void loop()
{
  
//    myservo.write(50);
//    myservo2.write(70);
//    delay(1000);
//    myservo.write(-50);
//    myservo2.write(-70);
//    delay(1000);
    digitalWrite(triggerPin, HIGH);             //triggering the wave(like blinking an LED)
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);       //a special function for listening and waiting for the wave
    distance = (duration / 2) / 29.1;     //transforming the number to cm(if you want inches, you have to change the 29.1 with a suitable number
    delay(1000);
    Serial.print(distance);              //printing the numbers
    Serial.print("cm");                  //and the unit
    Serial.println(" ");
    Sensor_Read();
    servo_run();
}

void Sensor_Read() 
{


  
  adxl_y_val = analogRead(y);
  Serial.print("ADXL: ");
  Serial.print(adxl_y_val);
  Serial.print("\t");
  delay(1000);
}

void servo_run()
{
  if ((adxl_y_val > 320) && (adxl_y_val < 370))
  {
    Serial.println("In centre motor");
    myservo.write(90);
    myservo2.write(90);
    delay(1000);
  }
  else if (adxl_y_val >= 370)
  {
    Serial.println("In up motor");
    myservo.write(70);
    myservo2.write(110);
    delay(1000);
  }
  else if (adxl_y_val <= 320)
  {
    Serial.println("In dowm motor");
    myservo.write(110);
    myservo2.write(70);
    delay(1000);
  }

  if ((distance < 15) && (distance > 8))
  {
    Serial.println("In center motor");
    myservo1.write(100);
    myservo3.write(100);
    delay(1000);
    
  }
  else if (distance >= 15)
  {
    myservo1.write(120);              // tell servo to go to position in variable 'pos'
    myservo3.write(120);
    delay(1000);                       // waits 15ms for the servo to reach the position
  }
  else if (distance <= 8)
  {
    myservo1.write(80);               // tell servo to go to position in variable 'pos'
    myservo3.write(80);
   delay(1000);
  }
}





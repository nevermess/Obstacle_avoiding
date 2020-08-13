# include <Servo.h>
 

int servo_pin = 9;

long duration;
long dist;

int pingPin = 11;
int trigPin = 10;

Servo sweeper;


bool direction;
// 0 is left , 1 is right



long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}


void go_forward()
{
  
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
}

void go_back()
{
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(7,HIGH);
 
}

void turn_left()
{
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
}

void turn_right()
{
  
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(12,HIGH);
  delay(1000);
  digitalWrite(12,LOW);
}

void clr()
{
  digitalWrite(5,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
}


long get_dist()
{
  long dis;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  dis = microsecondsToCentimeters(duration); 
  
  return dis;
}

bool sweeping()
{
  clr();
  // servo starts from the right
  int left = 0;
  int right = 0;
  
  for(int i = 0; i<180;i+=10)
  {
    sweeper.write(i);
    delay(500);
    long d = get_dist();
    if(d<10)
    { if( i<90)                 // Depends upon the servo orientation
        right++;
     // left++; 
      else
      if( i>90 )
        left++;
      //right++;  
    }
   }
    Serial.print(" right ");
    Serial.print(right);
    Serial.print(" left " );
    Serial.print(left);
  if(left>right)
  return 0;
  else
  return 1;

}

void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  Serial.begin(9600);
  sweeper.attach(servo_pin);
  
  int pos = 0;
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(7,OUTPUT);
  
} 


void loop() {
  // put your main code here, to run repeatedly:
  sweeper.write(90);
  go_forward();
  dist = get_dist();
  if(dist < 10)
  {
    go_back();
    delay(100);
    clr();
  } 
  else if(dist > 10 && dist < 20)
  {  
    direction = sweeping();
    if(direction)
    {
      turn_left();
    }
    else
    {
      turn_right();
    }
    delay(500);
    clr();
  }

}

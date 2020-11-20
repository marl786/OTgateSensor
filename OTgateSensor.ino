#include <Servo.h>

Servo myservo1;
Servo myservo2;

const int trigPin = 5;
const int echoPin = 6;
const float pi=3.1462;

long duration;
float topd;
float bottomd;

int topangle;
int bottomangle;

int distance;
int d1;
int e;
int difference;

int pos1 = 0;
int pos2 = 0;


void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myservo1.attach(9);
  myservo2.attach(10);
  Serial.begin(9600);
}



void top(){
  digitalWrite(2, HIGH);
}
void bottom(){
  digitalWrite(3, HIGH);
}

void win(){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(1000);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(1000);
}


void loop() {
e=0;

  

  //top
  difference=0;
  myservo1.write(110);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
    
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Initial Distance: ");
  Serial.println(distance);
  d1=distance;              
  delay(300);
           
pos1=110;
  while (difference<=5 and difference>=-5 and pos1<=170){
    myservo1.write(pos1);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;
    Serial.print("Distance: ");
    Serial.println(distance);  
    Serial.print("Angle: "); 
    Serial.println(pos1);
    Serial.print("Difference: ");
    Serial.println(difference);            
    delay(300);

    pos1 += 1;

    difference=distance-d1;
    Serial.println("1st");
  }
  if (pos1!=171){
    topangle=pos1-110;
  }
  else {
    Serial.println("Object's top edge NOT FOUND. Increase the distance between object and sensor.");
    top();
    e=1;
  }

if (e!=1){
//bottom
  difference=0;
  myservo1.write(110);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
    
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Initial Distance: ");
  Serial.println(distance);
  d1=distance;              
  delay(300);
pos1=110;
while (difference<=5 and difference>=-5 and pos1>=50){
    myservo1.write(pos1);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;
    Serial.print("Distance: ");
    Serial.println(distance); 
    Serial.print("Angle: "); 
    Serial.println(pos1);
    Serial.print("Difference: ");
    Serial.println(difference);            
    delay(300);

    pos1 -= 1;

    difference=distance-d1;
    Serial.println("2nd");
  }
  if (pos1!=49){
    bottomangle=110-pos1;
  }
  else {
    Serial.println("Object's bottom edge NOT FOUND. Increase the distance between object and sensor.");
    bottom();
    e=1;
  }
}


if (e==0){
  Serial.print("TOP ANGLE");
  Serial.println(topangle);
  Serial.print("BOTTOM ANGLE");
  Serial.println(bottomangle);
  topd=d1*(sin(topangle*pi/180));
  bottomd=d1*(sin(bottomangle*pi/180));
  Serial.println(topd);
  Serial.println(bottomd);
  
  

  Serial.println("Calculating OBJECT's HEIGHT....");
  delay(300);
  Serial.print("Height:   ");
  Serial.print(topd+bottomd);
  Serial.print(" cm.");
  win();
}

  delay(10000);
}
  

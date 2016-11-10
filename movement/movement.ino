// Motors for tires, Connected on the H-bridge

// Left Motor
// 2 represents the positive side
// 3 represents the negative side
int motor_left[] = {2,3};

//Right Motor
// 7 represents the positive side
// 8 represents the negative side
int motor_right[] = {7, 8};


const int enablePin = 9;    // H-bridge enable pin for both motors
const int echoPin = 5;
const int trigPin = 4;
const int ledPin =  13;    // LED connected to digital pin 13

//Setup
void setup() {
  Serial.begin(9600);
  pinMode(motor_left, OUTPUT);
  Serial.begin(9600);
  pinMode(enablePin, OUTPUT);
  pinMode(motor_left[0], OUTPUT);
  pinMode(motor_left[1], OUTPUT);
  pinMode(motor_right[0], OUTPUT);
  pinMode(motor_right[1], OUTPUT);
}

// ————————————————————————— Loop
void loop() {

  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;
  analogWrite(E1, 153); // Run in half speed

  // The sensor is triggered by a HIGH pulse for 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  //convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  if (cm < 25){
    Serial.println ("Close Obstacle detected!" );
    Serial.println ("Obstacle Details:");
    Serial.print ("Distance From Robot is " );
    Serial.print ( distance);
    Serial.print ( " CM!");// print out the distance in centimeters.
    Serial.println (" The obstacle is declared a threat due to close distance. ");
    Serial.println (" Turning !");
    digitalWrite(motor_left[0], HIGH); 
    digitalWrite(motor_left[1], LOW);
    digitalWrite(motor_right[0], LOW);
    digitalWrite(motor_right[1], HIGH);
  }
  else{
    //Set the motors on
    digitalWrite(motor_left[0], HIGH); 
    digitalWrite(motor_left[1], LOW);
    digitalWrite(motor_right[0], HIGH);
    digitalWrite(motor_right[1], LOW);
  }
  
}

  long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;

}




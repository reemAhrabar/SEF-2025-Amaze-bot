int mazeArr[5][5][3] = {
{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
};

int const startingPosition[2] = {4,3};

int currentPosition[2] = {4,3};

double durationRight;
double durationLeft;
double durationFront;
double distanceRight;
double distanceLeft;
double distanceFront;  
double distances[3];

int trigRight = 22; // 3rd on right
int echoRight = 36; // 3rd on left
int trigFront = 21; // 6th on right
int echoFront = 34; // 5th on left
int trigLeft = 23; // 2nd on right
int echoLeft = 39; // 4th on left

// motor pins
int rightForward = 17;
int rightBackward = 16;
int leftForward = 26;
int leftBackward = 27;


void setup() {
  pinMode(trigRight, OUTPUT);
  pinMode(trigFront, OUTPUT);
  pinMode(trigLeft, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(echoRight, INPUT);
  pinMode(echoFront, INPUT);
  pinMode(echoLeft, INPUT);
}

void loop() {
    driveForward();
    delay(1000);
    stopDriving();
    updateDistances();
    if (distances[0] >= 9.7) {
      turnRight();
      delay(1000);
      stopDriving();
    }
    else if (distances[1] >= 9.7) {
      driveForward();
      delay(1000);
      stopDriving();
    }
    else if (distances[2] >= 9.7) {
      turnLeft();
      delay(1000);
      stopDriving();
    }
    else {
      while (distances[2] <= 9.7) {
        driveBackward();
        delay(1000);
        stopDriving();
        updateDistances();
      }
    }
}

void driveForward(){  // set pins to make robot drive forward
  digitalWrite(leftForward,HIGH);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightBackward,LOW);
}

void driveBackward(){  // set pins to make robot drive backward 
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,HIGH);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,HIGH);
}

void turnRight(){  // set pins to make robot turn right
  digitalWrite(leftForward,HIGH);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,HIGH);
}

void turnLeft(){  // set pins to make robot turn left
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,HIGH);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightBackward,LOW);
}

void stopDriving(){  // set pins to make robot stop
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,LOW);
}

void updateDistances() {
    digitalWrite(trigRight, LOW);
    digitalWrite(trigFront, LOW);
    digitalWrite(trigLeft, LOW);
    delayMicroseconds(10);
    // Sets the trigPins on HIGH state for 10 micro seconds
    digitalWrite(trigRight, HIGH);
    digitalWrite(trigFront, HIGH);
    digitalWrite(trigLeft, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigRight, LOW);
    digitalWrite(trigFront, LOW);
    digitalWrite(trigLeft, LOW);
    
    // Reads the echoPins, returns the sound wave travel time in microseconds
    durationRight = pulseIn(echoRight, HIGH);
    durationLeft = pulseIn(echoLeft, HIGH);
    durationFront = pulseIn(echoFront, HIGH);

    distanceRight = durationRight * 0.034 / 2;
    distances[0] = distanceRight;
    distanceLeft = durationLeft * 0.034 / 2;
    distances[1] = distanceLeft;
    distanceFront = durationFront * 0.034 / 2;
    distances[2] = distanceFront;
}

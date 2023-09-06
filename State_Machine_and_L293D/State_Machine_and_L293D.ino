// First, variables are created to store the state of the SENSORS
// They will be of integer type because they will store a number between 0 and 1023
int SEN_A = 0;
int SEN_B = 0;
int SEN_C = 0;

// Number of Sensors to read
const int numSen = 3;
// Current state
int state = 1;
// Array to store the readings
int reading[numSen];
// Variables to store the state values
// 0 for NO TURN, 1 for RIGHT, and 2 for LEFT
int state_1;
int state_2;
int state_3;
int state_4;
int state_5;

void setup() {
  // Declare pins as input or output as appropriate
  // D4 for IN1
  pinMode(4, OUTPUT);
  // D5 for ENABLE
  pinMode(5, OUTPUT);
  // D6 for IN2
  pinMode(6, OUTPUT);
  // D9 for the red LED - LEFT TURN
  pinMode(9, OUTPUT);
  // D10 for the green LED - RIGHT TURN
  pinMode(10, OUTPUT);
  // D11 for ALERT - Sequence Detection
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  // Set all outputs to 0V with LOW
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void loop() {
  // Read analog signals from the SENSORS
  // and store their values in the variables SEN_A, SEN_B, and SEN_C
  // the value will be 0 if the SENSOR detects nothing
  // and 1023 if it detects something
  SEN_A = analogRead(3);
  SEN_B = analogRead(2);
  SEN_C = analogRead(1);
  reading[0] = SEN_A;
  reading[1] = SEN_B;
  reading[2] = SEN_C;
  int result;
  // Check the number of readings
  if (state == 1) {
    result = evaluate_state(reading);
    // Serial.print("state 1 = ");
    // Serial.println(result);
    state_1 = result;
    state++;
  }
  else if (state == 2) {
    result = evaluate_state(reading);
    // Serial.print("state 2 = ");
    // Serial.println(result);
    state_2 = result;
    state++;
  }
  else if (state == 3) {
    result = evaluate_state(reading);
    // Serial.print("state 3 = ");
    // Serial.println(result);
    state_3 = result;
    state++;
  }
  else if (state == 4) {
    result = evaluate_state(reading);
    // Serial.print("state 4 = ");
    // Serial.println(result);
    state_4 = result;
    state++;
  }
  else if (state == 5) {
    result = evaluate_state(reading);
    // Serial.print("state 5 = ");
    // Serial.println(result);
    state_5 = result;
    state++;
  }
  if (state >= 6) {
    // Check the LEFT-RIGHT-RIGHT-LEFT-RIGHT sequence
    if (state_1 == 2 && state_2 == 1 && state_3 == 1 && state_4 == 2 && state_5 == 1) {
      Serial.println("SEQUENCE DETECTED!");
      // Create a sequence for the lamp connected to pin D11
      // to turn on and off for 3 seconds
      digitalWrite(11, HIGH); // ALERT
      delay(600);
      digitalWrite(11, LOW);
      delay(600);
      digitalWrite(11, HIGH);
      delay(600);
      digitalWrite(11, LOW);
      delay(600);
      digitalWrite(11, HIGH);
      delay(600);
      digitalWrite(11, LOW);
    }
    // Update values for the next reading
    result = evaluate_state(reading);
    // Serial.print("state = ");
    // Serial.println(result);
    state_1 = state_2;
    state_2 = state_3;
    state_3 = state_4;
    state_4 = state_5;
    state_5 = result;
    state++;
  }
}

int evaluate_state(int reading[]) {
  // This function takes an input vector containing the positions of the SENSORS,
  // evaluates the conditions given by the STATE TABLE for the 3 SENSORS
  // and determines the direction of rotation, either LEFT, RIGHT, or NO TURN

  // First, declare vectors representing the STATE TABLE provided in the README.md
  int NOturn[numSen] = {0,  0,  0};
  int LEFT1[numSen] =   {0,  0, 1023};
  int RIGHT1[numSen] =   {0, 1023, 0};
  int LEFT2[numSen] =   {0, 1023, 1023};
  int LEFT3[numSen] =   {1023, 0, 0};
  int RIGHT2[numSen] =   {1023, 0, 1023};
  int RIGHT3[numSen] =   {1023, 1023, 0};
  int RIGHT4[numSen] =   {1023, 1023, 1023};
  int rotation;

  if (reading[0] == NOturn[0] && reading[1] == NOturn[1] && reading[2] == NOturn[2]) {
    Serial.println("The motor does NOT TURN");
    delay(5000);
    rotation = 0;
    return rotation;
  }
  else if (reading[0] == LEFT1[0] && reading[1] == LEFT1[1] && reading[2] == LEFT1[2]) {
    Serial.println("LEFT TURN");
    leftTurn();
    rotation = 2;
  }
  else if (reading[0] == RIGHT1[0] && reading[1] == RIGHT1[1] && reading[2] == RIGHT1[2]) {
    Serial.println("RIGHT TURN");
    rightTurn();
    rotation = 1;
  }
  else if (reading[0] == LEFT2[0] && reading[1] == LEFT2[1] && reading[2] == LEFT2[2]) {
    Serial.println("LEFT TURN");
    leftTurn();
    rotation = 2;
  }
  else if (reading[0] == LEFT3[0] && reading[1] == LEFT3[1] && reading[2] == LEFT3[2]) {
    Serial.println("LEFT TURN");
    leftTurn();
    rotation = 2;
  }
  else if (reading[0] == RIGHT2[0] && reading[1] == RIGHT2[1] && reading[2] == RIGHT2[2]) {
    Serial.println("RIGHT TURN");
    rightTurn();
    rotation = 1;
  }
  else if (reading[0] == RIGHT3[0] && reading[1] == RIGHT3[1] && reading[2] == RIGHT3[2]) {
    Serial.println("RIGHT TURN");
    rightTurn();
    rotation = 1;
  }
  else if (reading[0] == RIGHT4[0] && reading[1] == RIGHT4[1] && reading[2] == RIGHT4[2]) {
    Serial.println("RIGHT TURN");
    rightTurn();
    rotation = 1;
  }
  
  return rotation;
}

void rightTurn() {
  // Function to activate the L293D and turn the motor to the RIGHT for 3 out of 10 seconds
  digitalWrite(4, HIGH); // IN_1
  digitalWrite(5, HIGH); // ENABLE
  digitalWrite(6, LOW); // IN_2
  digitalWrite(10, HIGH); // LED RIGHT
  // Set a delay of 3 seconds
  delay(3000);
  // Then deactivate the motor for 7 seconds to complete the 10 seconds
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(3000);
  digitalWrite(10, LOW);
}

void leftTurn() {
  // Function to activate the L293D and turn the motor to the LEFT for 2 out of 10 seconds
  digitalWrite(6, HIGH); // IN_1
  digitalWrite(5, HIGH); // ENABLE
  digitalWrite(4, LOW); // IN_2
  digitalWrite(9, HIGH); // LED LEFT
  // Set a delay of 2 seconds
  delay(2000);
  // Then deactivate the motor for 8 seconds to complete the 10 seconds
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(4000);
  digitalWrite(9, LOW);
}

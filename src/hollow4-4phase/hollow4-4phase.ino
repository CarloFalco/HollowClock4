// Motor and clock parameters
// 2048 * 90 / 12 = 15360
//#define STEPS_PER_ROTATION 15360 // Steps for a full rotation of the minute rotor
#define STEPS_PER_MINUTE 256 //  15360/60 steps for a full rotation of the minute rotor
// Delay for a single step of the stepper motor
int delaytime = 4;

// Ports used to control the stepper motor
// If your motor rotates in the opposite direction, adjust these values
int port[4] = {2, 3, 4, 5};

// Sequence of stepper motor control
// Each row represents a phase, and each column represents a pin state
int seq[4][4] = {
  {  LOW,  LOW, HIGH,  LOW},    // Phase 1
  {  LOW,  HIGH, LOW,  LOW},    // Phase 2
  { HIGH,  LOW,  LOW,  LOW},    // Phase 3
  {  LOW,  LOW,  LOW, HIGH}     // Phase 4
};

unsigned long Count;
unsigned long PreviousCount = 0;

// Function prototypes
void rotate(int);


void setup() {
  // Serial.begin(9600);  // Initialize serial communication for debugging
  // Set pin modes for motor control
  pinMode(port[0], OUTPUT);
  pinMode(port[1], OUTPUT);
  pinMode(port[2], OUTPUT);
  pinMode(port[3], OUTPUT);
}

void loop() {

  // Task every 60 seconds
  Count = millis();   // Get current time in milliseconds
  // Execute task if 60 seconds have passed since the last execution
  if (Count - PreviousCount > 60000)
  {
    PreviousCount = Count;    // Update previous execution time
    rotate(STEPS_PER_MINUTE); // Move by one minute
  }

}

/* --------- FUNCTION ------------- */
// Function to rotate the stepper motor
// Parameters:
// - step: Number of steps to rotate the motor (positive for clockwise, negative for counterclockwise)
void rotate(int step) {
  static int phase = 0;   // Initialize phase
  int i, j;
  int delta = (step > 0) ? 1 : 3; // Determine direction of rotation
  int dt = 20;    // Initial delay between steps

  step = (step > 0) ? step : -step; // Ensure step count is positive
  for(j = 0; j < step; j++) {
    phase = (phase + delta) % 4;   // Update phase
    // Set pin states according to current phase
    for(i = 0; i < 4; i++) {
      digitalWrite(port[i], seq[phase][i]);
    }
    delay(dt);    // Wait before next step
    if(dt > delaytime) dt--;  // Decrease delay time
  }

  // Cut power to motor
  for(i = 0; i < 4; i++) {
    digitalWrite(port[i], LOW);
  }
}

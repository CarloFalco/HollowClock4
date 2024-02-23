// Motor and clock parameters
// 2048 * 90 / 12 = 15360
//#define STEPS_PER_ROTATION 15360 // steps for a full turn of minute rotor
#define STEPS_PER_MINUTE 256 //  15360/60 steps for a full turn of minute rotor
// wait for a single step of stepper
int delaytime = 4;

// ports used to control the stepper motor
// if your motor rotate to the opposite direction, 
int port[4] = {2, 3, 4, 5};

// sequence of stepper motor control

int seq[4][4] = {
  {  LOW,  LOW, HIGH,  LOW},
  {  LOW,  HIGH, LOW,  LOW},
  { HIGH,  LOW,  LOW,  LOW},
  {  LOW,  LOW,  LOW, HIGH}
};

unsigned long Count;
unsigned long PreviousCount = 0;

// In this part are put the prototypes of the functions
void rotate(int);


void setup() {
  Serial.begin(9600);
  pinMode(port[0], OUTPUT);
  pinMode(port[1], OUTPUT);
  pinMode(port[2], OUTPUT);
  pinMode(port[3], OUTPUT);
}

void loop() {

  // TASK 60s
  Count = millis();
  if (Count - PreviousCount > 60000)
  {
    PreviousCount = Count;
    rotate(STEPS_PER_MINUTE); // move by one minute
  }

}

/* --------- FUNCTION ------------- */
// This part includes all the definitions of the functions
void rotate(int step) {
  static int phase = 0;
  int i, j;
  int delta = (step > 0) ? 1 : 3;
  int dt = 20;

  step = (step > 0) ? step : -step;
  for(j = 0; j < step; j++) {
    phase = (phase + delta) % 4;
    for(i = 0; i < 4; i++) {
      digitalWrite(port[i], seq[phase][i]);
    }
    delay(dt);
    if(dt > delaytime) dt--;
  }

  // power cut
  for(i = 0; i < 4; i++) {
    digitalWrite(port[i], LOW);
  }
}
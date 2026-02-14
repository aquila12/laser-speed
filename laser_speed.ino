const int start = 20; // PF5
const int stop = 21;  // PF4
const int pulse = 18; // PF7

void setup() {
  // put your setup code here, to run once:
  pinMode(start, INPUT);
  pinMode(stop, INPUT);
  pinMode(19, OUTPUT);  // Shielding
  pinMode(pulse, INPUT);

  Serial.begin(9600); // Pro micro ignores baud rate
  while(!Serial);     // Wait for serial to be ready (why not in Serial.begin Arduino, huh?)

  Serial.println("t0,t1,dt,N");
}

// PF 4, 5, 6
#define START (PINF & bit(5))
#define READ_PINF (pinf = PINF)
#define STOP (!(pinf & bit(5)))
#define PULSE (pinf & bit(7))

void loop() {
  unsigned long pulses = 0;
  byte high_count = 0;
  byte pinf;

  // Serial.println("WAIT");

  while(!START);
  const unsigned long t0 = micros();

  // Serial.println("START");

  while(1) {
    READ_PINF;
    if(STOP) break;

    if(PULSE) {
      READ_PINF;
      if(STOP) break;

      if(PULSE) ++pulses;

      while(READ_PINF && !STOP && PULSE);
      if(STOP) break;
    }
  }
  const unsigned long t1 = micros();
  const unsigned long dt = t1 - t0;

  // Serial.println("STOP");

  Serial.print(t0); Serial.print(",");
  Serial.print(t1); Serial.print(",");
  Serial.print(dt); Serial.print(",");
  Serial.print(pulses); Serial.println();
}

const int start = 20;
const int stop = 21;
const int pulse = 4;  // ICP1

void setup() {
  // put your setup code here, to run once:
  pinMode(start, INPUT);
  pinMode(stop, INPUT);
  pinMode(pulse, INPUT);

  Serial.begin(9600); // Pro micro ignores baud rate

  // Enable input capture with noise canceler
  TCCR1B |= bit(ICNC1) || bit(ICES1);

  // // Connect the ICP pin as the capture source
  ACSR &= ~bit(ACIC);
}

void loop() {
  unsigned long pulses = 0;

  while(!digitalRead(start));
  const unsigned long t0 = micros();
  TIFR1 |= bit(ICF1);

  while(!digitalRead(stop)) {
    if(!(TIFR1 & bit(ICF1))) {
      TIFR1 |= bit(ICF1);
      ++pulses;
    }
  }

  const unsigned long t1 = micros();

  Serial.print("t0: "); Serial.println(t0);
  Serial.print("t1: "); Serial.println(t1);
  Serial.print("dt: "); Serial.println(t1 - t0);
  Serial.print("N:  "); Serial.println(pulses);
}

const int start = 20;
const int stop = 21;
const int pulse = 19;

void setup() {
  // put your setup code here, to run once:
  pinMode(start, INPUT);
  pinMode(stop, INPUT);
  pinMode(pulse, INPUT);

  Serial.begin(9600); // Pro micro ignores baud rate

  Serial.println("t0,t1,dt,N");
}

void loop() {
  unsigned long pulses = 0;
  byte high_count = 0;
  byte last_pulse_value = 0, pulse_value;

  while(!digitalRead(start));
  const unsigned long t0 = micros();

  while(!digitalRead(stop)) {
    pulse_value = digitalRead(pulse);
    pulse_value &= digitalRead(pulse);

    if(pulse_value && !last_pulse_value) ++pulses;

    last_pulse_value = pulse_value;
  }

  const unsigned long t1 = micros();
  const unsigned long dt = t1 - t0;

  Serial.print(t0); Serial.print(",");
  Serial.print(t1); Serial.print(",");
  Serial.print(dt); Serial.print(",");
  Serial.print(pulses); Serial.println();
}

#include <TVout.h>
#include <fontALL.h>

#define W 136
#define H 96

TVout tv;
//Insert your callsign here padded however you like
char callsign[] = "...KU0HN... ";
//Insert your talkaround message here.
char talkaround[] = "...Talkaround on 146.52MHz... ";
byte ledState = LOW;

void setup()  {
  tv.begin(NTSC, W, H);
  initOverlay();
  tv.select_font(font8x8);
  tv.fill(0);
}

// Initialize ATMega registers for video overlay capability.
// Must be called after tv.begin().
void initOverlay() {
  TCCR1A = 0;
  // Enable timer1.  ICES0 is set to 0 for falling edge detection on input capture pin.
  TCCR1B = _BV(CS10);

  // Enable input capture interrupt
  TIMSK1 |= _BV(ICIE1);

  // Enable external interrupt INT0 on pin 2 with falling edge.
  EIMSK = _BV(INT0);
  EICRA = _BV(ISC01);
}

// Required to reset the scan line when the vertical sync occurs
ISR(INT0_vect) {
  display.scanLine = 0;
}


void loop() {
  printMessage(callsign);
  delay(30000);
  tv.fill(0);
  printMessage(talkaround);
  tv.fill(0);
  delay(30000);
}

void printMessage(char message[]) {
  int index = 0;
//  char saveChar;
//  saveChar = message[index+22];

  for(int x=64;x>=0;x--) {
    if (x<64) {
      tv.delay_frame(1);
    } 
    tv.print(x, 87, message+index);
  }

  message[index+22] = saveChar;
  index++;
  if (index > 45) {
    index = 0;
  }
}

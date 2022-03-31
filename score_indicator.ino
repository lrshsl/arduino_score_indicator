EVENSEG_OUTPUTS 8
#define SIGNAL_INPUT 11
#define REFRESH_RATE 100

const int g_outputs[NB_SEVENSEG_OUTPUTS] = {2,3,4,5,6,7,8,9};   // 'NB_S...OUTPUTS' used as check
int sig, score;

void number_on_sevensegment(int outputs[], int len=0, int n=0) {
  int graphics[12][8] = {
    {1,1,1,0,1,1,1,0},
    {0,0,1,0,0,1,0,0},
    {1,0,1,1,1,0,1,0},
    {1,0,1,1,0,1,1,0},
    {0,1,1,1,0,1,0,0},
    {1,1,0,1,0,1,1,0},
    {1,0,1,1,1,1,1,0},
    {1,0,1,0,0,1,0,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,0,1,1,0},
    
    {0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1}
  };
  for (int i; i<len; i++) {
    digitalWrite(outputs[i], graphics[n][i]);
  };
}

void show_nb(int n) {number_on_sevensegment(g_outputs, NB_SEVENSEG_OUTPUTS, n);}


/*************************************************************************************
---------------------------------------- main ----------------------------------------
*************************************************************************************/

// Setup
void setup() {
  
  // In-/Output deklaration
  for (int i=2; i<NB_SEVENSEG_OUTPUTS+2+1; i++) {
    pinMode(i, OUTPUT);      // Output: 2-9, 10
  };
  pinMode(SIGNAL_INPUT, INPUT);

  // Quick confirmation animation
  int state;
  for (int i=0; i<6; i++) {
    state = (i%2==0) ? 11: 10;
    show_nb(state);    // all pins HIGH/LOW
    delay(100);
  };

  delay(500);
  show_nb(0);
  
  Serial.begin(9600);
}

// Main loop
void loop() {
  // Input
  sig = digitalRead(SIGNAL_INPUT);
  while (digitalRead(SIGNAL_INPUT)) {delay(REFRESH_RATE);};     // interrupts the main loop
  
  // Logic

  // Output
  if (sig) {
    score += 1;
    show_nb(score%10);
  };
  
  delay(REFRESH_RATE);
}

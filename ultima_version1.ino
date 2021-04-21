int SER  = 2;
int RCLK = 3;
int SRCLK = 4;
#define TEMPO 150

void ledWrite(int ALed, int BLed, int CLed, int DLed, int ELed, int FLed, int GLed, int HLed){
   shiftOut(SER, SRCLK, LSBFIRST, HLed);
   shiftOut(SER, SRCLK, LSBFIRST, GLed);
   shiftOut(SER, SRCLK, LSBFIRST, FLed);
   shiftOut(SER, SRCLK, LSBFIRST, ELed);
   shiftOut(SER, SRCLK, LSBFIRST, DLed);
   shiftOut(SER, SRCLK, LSBFIRST, CLed);
   shiftOut(SER, SRCLK, LSBFIRST, BLed);
   shiftOut(SER, SRCLK, LSBFIRST, ALed);
   digitalWrite(RCLK, HIGH);
   digitalWrite(RCLK, LOW);
}

void setup(){
   pinMode(SER, OUTPUT);
   pinMode(RCLK, OUTPUT);
   pinMode(SRCLK, OUTPUT);
}

void loop(){
  
  //DIAGONALES INTERCALADAS
  ledWrite(B10000000,B01000000,B00100000,B00010000,B00001000,B00000100,B00000010,B00000001); delay(TEMPO);
  ledWrite(B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000); delay(TEMPO);

  
  //ASÍ SACAMOS EL 5:
  //ledWrite(B01111110,255,B11000111,B00000111,B11111110,B11100000,255,255); delay(TEMPO);
  
  //ASÍ PRENDEMOS TODOS:
  //ledWrite(255,255,255,255,255,255,255,255); delay(TEMPO);  
}
//Variable global
int opcion = 0;
int SER  = 2;
int RCLK = 3;
int SRCLK = 4;
#define TEMPO 150

void setup(){
   pinMode(SER, OUTPUT);
   pinMode(RCLK, OUTPUT);
   pinMode(SRCLK, OUTPUT);
   Serial.begin(9600);//Inicializar Serial
   Serial.println(" ");
   Serial.println("1. Patron 1.");
   Serial.println("2. Verificacion.");
   Serial.println("3. Imagen.");
   Serial.println("4. Publik.");
   Serial.println("Seleccione una opcion: ");
}

void loop(){
  
    //Condicion que pregunta si hay datos
    if(Serial.available()>0){
   
      opcion = Serial.parseInt(); //Lealo como INT
      
      Serial.print("opcion seleccionada: ");
      Serial.print(opcion);
   }
  switch(opcion){
    
  case 1:
    Serial.println("Prueba 1");
    patron1();
    break;
    
  case 2:
    Serial.println("Prueba 2");
    verificacion();
    break;
    
  case 3:
  	Serial.println("Prueba 3");
 	break;
    
  case 4:
  	Serial.println("Prueba 4");
  	break;
  }
}

void ledWrite(int ALed, int BLed, int CLed, int DLed, int ELed, int FLed, int GLed, int HLed){
  //Funcion para escribir en la matriz
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

void patron1 (){//ASÍ SACAMOS EL 5:
  ledWrite(B01111110,255,B11000111,B00000111,B11111110,B11100000,255,255); delay(TEMPO); 
}

void verificacion(){//ASÍ PRENDEMOS TODOS:
  ledWrite(255,255,255,255,255,255,255,255); delay(TEMPO);  
}

void patron2(){//DIAGONALES INTERCALADAS
  ledWrite(B10000000,B01000000,B00100000,B00010000,B00001000,B00000100,B00000010,B00000001); delay(TEMPO);
  ledWrite(B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000); delay(TEMPO);
}
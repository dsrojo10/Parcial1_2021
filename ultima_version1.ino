//VARIABLES GLOBALES MANEJO DEL CHIP
int opcion = 0;
int SER  = 2;
int RCLK = 3;
int SRCLK = 4;
#define TEMPO 150
/////////////////////////////////////////////////////////////////////////////////////////

//VARIABLES GOBLALES PARA MANEJO DEL ARREGLO DINAMICO
int aux = 0;
int num = 0; //Cantidad de patrones (P4)
int retardo = 0; //Retardo entre patrones (P4)
int iter = 0; //Iterador (P4)
int* list; 
size_t count;
size_t capacity;
#define PAUSE 1500
///////////////////////////////////////////////////////////

//FUNCIONES MANEJO DEL CHIP
void ledWrite(int ALed, int BLed, int CLed, int DLed, int ELed, int FLed, int GLed, int HLed){//Funcion para encender los ledes deseados
   shiftOut(SER, SRCLK, LSBFIRST, HLed); //Fila mas arriba
   shiftOut(SER, SRCLK, LSBFIRST, GLed);
   shiftOut(SER, SRCLK, LSBFIRST, FLed); //    ...
   shiftOut(SER, SRCLK, LSBFIRST, ELed);
   shiftOut(SER, SRCLK, LSBFIRST, DLed); //    ...
   shiftOut(SER, SRCLK, LSBFIRST, CLed);
   shiftOut(SER, SRCLK, LSBFIRST, BLed); //    ...
   shiftOut(SER, SRCLK, LSBFIRST, ALed); //Fila mas baja
   digitalWrite(RCLK, HIGH);
   digitalWrite(RCLK, LOW);
}

void patron1 (){//ASÍ SACAMOS EL 5:
  ledWrite(B01111110,255,B11000111,B00000111,B11111110,B11100000,255,255); delay(TEMPO); 
}

void verificacion(){//ASÍ PRENDEMOS TODOS:
  ledWrite(255,255,255,255,255,255,255,255); delay(TEMPO);  
}

void patron2(){//DIAGONALES INTERCALADAS (Usada para pruebas)
  ledWrite(B10000000,B01000000,B00100000,B00010000,B00001000,B00000100,B00000010,B00000001); delay(TEMPO);
  ledWrite(B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000); delay(TEMPO);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//FUNCIONES PARA MANEJO DEL ARREGLO DINAMICO
void CreateList(size_t _capacity) {// Crear una nueva lista
  list = new int[_capacity];
  capacity = _capacity;
  count = 0;
}


void AddItem(int item) {// Añadir elemento al final de la lista
  ++count;
    
  if (count > capacity)
  {
    size_t newSize = capacity * 2;
    resize(newSize);
  } 

  list[count - 1] = item;
}


void RemoveTail() {// Eliminar ultimo elemento de la lista
  --count;
}

void Trim() {// Reducir capacidad de la lista al numero de elementos
  resize(count);
}

void resize(size_t newCapacity) {// Reescalar lista
  int* newList = new int[newCapacity];
  memmove(newList, list, count  * sizeof(int));
  delete[] list;
  capacity = newCapacity;
  list = newList;
}

void printList() {// Muestra la lista por Serial para debug
  Serial.print("Capacity:");
  Serial.print(capacity);

  Serial.print("  Count:");
  Serial.print(count);

  Serial.print("  Items:");
  for (size_t index = 0; index < count; index++)
  {
    Serial.print(list[index]);
    Serial.print(' ');
  }
  Serial.println();
}

void askData() {//Pide los datos para guardarlos en el arreglo
	Serial.println("Lista con 8 elementos");
    CreateList(8); 
    Serial.println();

    for(int i=0; i<8; i++){
      //Serial.println();
      Serial.print("Introducir la fila #");
      Serial.print(i+1);
      Serial.print(": ");delay(PAUSE);
      aux = Serial.parseInt();
      Serial.println(aux);
      AddItem(aux);
    }  
}

void askData4() {//Pide los datos para guardarlos en el arreglo (P4)
	Serial.println("Cuantos patrones va a ingresar?");delay(PAUSE);
  	num = Serial.parseInt();
  	Serial.println(num);
    CreateList((num*8));
    Serial.println();

    for(int i=0; i<(num*8); i++){
      //Serial.println();
      Serial.print("Introducir la fila #");
      Serial.print(i+1);
      Serial.print(": ");delay(PAUSE);
      aux = Serial.parseInt();
      Serial.println(aux);
      AddItem(aux);
    }  
}
////////////////////////////////////////////////////////////////


//FUNCIONES CONVENCIONALES
void setup(){
   pinMode(SER, OUTPUT);
   pinMode(RCLK, OUTPUT);
   pinMode(SRCLK, OUTPUT);
   Serial.begin(9600);//Inicializar Serial
   int op = 0;
  
  //PREGUNTA SI DESEA AGREGAR UNA MATRIZ (P3)
   Serial.println("Desea crear una matriz propia para el punto 3?");
   Serial.println("1. SI ----- 2. NO"); delay(PAUSE);
   op = Serial.parseInt();
   Serial.println(op);
  
   if(op==1){
		askData();
        printList();
   }
  
  //PREGUNTA SI DESEA AGREGAR MÁS DE UNA MATRIZ (P4)
  Serial.println("Desea crear una o mas matrices propias para el punto 4?");
  Serial.println("1. SI ----- 2. NO"); delay(PAUSE);
  op = Serial.parseInt();
  Serial.println(op);
  
  if(op==1){
    Serial.println("Que retardo quiere entre patrones: "); delay(PAUSE);
    retardo = Serial.parseInt();
    Serial.println(retardo);
	askData4();
    printList();
    Serial.println();
    Serial.println(retardo);
  }
  
   Serial.println();
   Serial.println("1. Patron 1.");
   Serial.println("2. Verificacion.");
   Serial.println("3. Imagen (PARA ESTE PUNTO MIRAR EL MANUAL...).");
   Serial.println("4. Publik (PARA ESTE PUNTO MIRAR EL MANUAL...).");
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
    //ledWrite(list[0],list[1],list[2],list[3],list[4],list[5],list[6],list[7]); delay(TEMPO);
    ledWrite(list[iter],list[(iter+1)],list[(iter+2)],list[(iter+3)],list[(iter+4)],list[(iter+5)],list[(iter+6)],list[(iter+7)]); delay(TEMPO);
  	Serial.println("Prueba 3");
 	break;
    
  case 4:
  	Serial.println("Prueba 4");
    for(int i=0; i<(num*8); i+=8){
      ledWrite(list[iter],list[(iter+1)],list[(iter+2)],list[(iter+3)],list[(iter+4)],list[(iter+5)],list[(iter+6)],list[(iter+7)]); delay(TEMPO);
      iter+=8;
      retardo = retardo*1000;
      delay(retardo);    
    }
  	break;
  }
}
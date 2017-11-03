#include "Keypad.h"     
String pin;
int usuario;
int user;
int digit1 = 11; //Pin 1 del display 
int digit2 = 12; //Pin 2 
//int digit3 = 9; //Pin 6 
//int digit4 = 6; //Pin8 
//int digit5 = 13;// Pin 1 del display 
int tipo_tarifa = 5;
long T0=0;
int segA = A1; //Pin 14 
int segB = 3; //Pin 16 
int segC = 4; //Pin 13 
int segD = 5; //Pin 3 
int segE = A0; //Pin 5 
int segF = A2; //Pin 11 
int segG = A3; //Pin 15 
int inboton;
     const byte Filas = 3;          //3 filas
     const byte Cols = 1;           //1 columnas

     byte Pins_Filas[] = {7, 8, 9};     //Pines Arduino para las filas
     byte Pins_Cols[] = {10};     // Pines Arduinopara las columnas
     char Teclas [ Filas ][ Cols ] = // mapeo
          {
              {'1'},
              {'2'},
              {'3'},
          };
          // mapeo de teclado matricial
     Keypad Teclado1 = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);
   int ledlibre = A4;
   int ledocupado = A5;  
   int go_stop=13;
     void setup()
        {             
          Serial.begin(9600) ; 
        pinMode(segA, OUTPUT);
        pinMode(segB, OUTPUT);
        pinMode(segC, OUTPUT);
        pinMode(segD, OUTPUT);
        pinMode(segE, OUTPUT);
        pinMode(segF, OUTPUT);
        pinMode(segG, OUTPUT);

      pinMode(digit1, OUTPUT);
      pinMode(digit2, OUTPUT);
      pinMode (ledlibre, OUTPUT);
      pinMode(ledocupado, OUTPUT);
      pinMode (go_stop, INPUT); //Entrada del boton de inicio/final
attachInterrupt(0, detectapulso, FALLING);
        
          }

     void loop()
        {
          //detectapulso();
          imprime((tipo_tarifa*10)+tarifatotal());       
        }


void detectapulso (){ //Cada vez que detecta el pulso en inicio o parada
                      //incrementa en uno
  if(millis()>T0 +250 ){
    inboton++ ;
    cuentaboton();
  T0=millis();
  }
  
  }
void cuentaboton(){ // cada vez que se toca el boton de inicio o el de parada, aumenta la el contador. 
                    //Cuando es impar es porque se inicio y cuando es impar es porque termino el viaje
  if (inboton%2==0){ 
     digitalWrite(ledlibre, HIGH);
     digitalWrite(ledocupado, LOW);
    }
  else{
    digitalWrite(ledlibre, LOW);
    digitalWrite(ledocupado, HIGH);
    }
}

        
  int tarifatotal(){
        char pulsacion = Teclado1.getKey() ;
       String valor = (String)pulsacion;// convertimos el char a int y restamos 48 segun codigo ascii
      //int largo=valor.length();
     pin=pin+valor;
    int largo=pin.length();
    if (largo<4){
       //pin=pin+valor;
       //int user = pin.toInt();
       Serial.println(pin);
       Serial.println(largo); 
       }
     if(largo>3){ 
    pin = "";
  }
  int user = pin.toInt();
      switch (user) {
      case 213:
        usuario = 1;
        break;
      case 233:
        usuario = 2;
        break;
      case 323:
        usuario = 3;
        break;
      case 122:
        usuario = 4;
        break;
      case 113:
        usuario = 5;
        break;
      default:
      usuario = 0;
        }
      return usuario;
    }
      
void imprime(int num){
    #define DISPLAY_BRIGHTNESS  1500
    
    #define DIGIT_ON  HIGH
    #define DIGIT_OFF  LOW
       
       

      long beginTime = millis();//tiempo que va a estar encendido cada display

    for(int digit = 2 ; digit > 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch(digit) {
    case 1:
      digitalWrite(digit1, DIGIT_ON);
      break;
    case 2:
      digitalWrite(digit2, DIGIT_ON);
      break;
    }
    //Turn on the right segments for this digit
    tecla_pulsada(num % 10);// toma el digito más a la derecha del dato y lo envia a imprimir
    num /= 10;// aplaica división entera para ahora imprimir el sigueinte dígito del dato

    delayMicroseconds(DISPLAY_BRIGHTNESS); //Encendidod por un instante
    
    tecla_pulsada(10);

    //Apagar todos los digitos
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
   
  }

  while( (millis() - beginTime) < 12) ; //Espera de tiempo para volver a imprimir
  }

//void lightNumber(int numberToDisplay)
 void tecla_pulsada(int datodesplegado){
       #define SEGMENT_ON  LOW
       #define SEGMENT_OFF HIGH
   
   switch (datodesplegado) {
      case 0:
        digitalWrite(segA, SEGMENT_ON);
        digitalWrite(segB, SEGMENT_ON);
        digitalWrite(segC, SEGMENT_ON);
        digitalWrite(segD, SEGMENT_ON);
        digitalWrite(segE, SEGMENT_ON);
        digitalWrite(segF, SEGMENT_ON);
        digitalWrite(segG, SEGMENT_OFF);
        break;
      case 1:
        digitalWrite(segA, SEGMENT_OFF);
        digitalWrite(segB, SEGMENT_ON);
        digitalWrite(segC, SEGMENT_ON);
        digitalWrite(segD, SEGMENT_OFF);
        digitalWrite(segE, SEGMENT_OFF);
        digitalWrite(segF, SEGMENT_OFF);
        digitalWrite(segG, SEGMENT_OFF);
        break;
      case 2:
        digitalWrite(segA, SEGMENT_ON);
        digitalWrite(segB, SEGMENT_ON);
        digitalWrite(segC, SEGMENT_OFF);
        digitalWrite(segD, SEGMENT_ON);
        digitalWrite(segE, SEGMENT_ON);
        digitalWrite(segF, SEGMENT_OFF);
        digitalWrite(segG, SEGMENT_ON);
        break;
      case 3:
        digitalWrite(segA, SEGMENT_ON);
        digitalWrite(segB, SEGMENT_ON);
        digitalWrite(segC, SEGMENT_ON);
        digitalWrite(segD, SEGMENT_ON);
        digitalWrite(segE, SEGMENT_OFF);
        digitalWrite(segF, SEGMENT_OFF);
        digitalWrite(segG, SEGMENT_ON);
        break;
      case 4:
        digitalWrite(segA, SEGMENT_OFF);
        digitalWrite(segB, SEGMENT_ON);
        digitalWrite(segC, SEGMENT_ON);
        digitalWrite(segD, SEGMENT_OFF);
        digitalWrite(segE, SEGMENT_OFF);
        digitalWrite(segF, SEGMENT_ON);
        digitalWrite(segG, SEGMENT_ON);
        break;
      case 5:
        digitalWrite(segA, SEGMENT_ON);
        digitalWrite(segB, SEGMENT_OFF);
        digitalWrite(segC, SEGMENT_ON);
        digitalWrite(segD, SEGMENT_ON);
        digitalWrite(segE, SEGMENT_OFF);
        digitalWrite(segF, SEGMENT_ON);
        digitalWrite(segG, SEGMENT_ON);
        break;
      case 10:
        // turn all the LEDs off:
        digitalWrite(segA, SEGMENT_OFF);
        digitalWrite(segB, SEGMENT_OFF);
        digitalWrite(segC, SEGMENT_OFF);
        digitalWrite(segD, SEGMENT_OFF);
        digitalWrite(segE, SEGMENT_OFF);
        digitalWrite(segF, SEGMENT_OFF);
        digitalWrite(segG, SEGMENT_OFF);
        
    }
  }

 
     
// Serial.println(pin);
// Serial.println(largo); 


          

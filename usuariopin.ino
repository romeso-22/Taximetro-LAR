#include "Keypad.h"     
String pin;
int usuario;
int user;
int digit1 = A3; //Pin 1 del display. Eagle pin 17
int digit2 = A2; //Pin 2. Eagle pin 18
int tipo_tarifa = 1; // Eagle pin 3
long T0;
int segA = 9; //Pin 14. Eagle pin 24
int segB = 10; //Pin 16 . Eagle pin 5
int segC = 11; //Pin 13 . Eagle pin 6
int segD = 12; //Pin 3 . Eagle pin 11
int segE = 13; //Pin 5 . Eagle pin 23
int segF = A0; //Pin 11 . Eagle pin 25
int segG = A1; //Pin 15 . Eagle pin 26
int inboton;
     const byte Filas = 3;          //3 filas. 
     const byte Cols = 1;           //1 columnas

     byte Pins_Filas[] = {7, 6, 5};     //Pines Arduino para las filas. Eagle pin  (11), 14(12), 15(13)
     byte Pins_Cols[] = {8};     // Pines Arduinopara las columnas. Eagle pin 16(10)
     char Teclas [ Filas ][ Cols ] = // mapeo
          {
              {'1'},
              {'2'},
              {'3'},
          };
          // mapeo de teclado matricial
     Keypad Teclado1 = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);
   int ledlibre = A4; // Eagle pin 27
   int ledocupado = A5; // Eagle pin 28
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
      attachInterrupt(0, detectapulso, FALLING); // Eagle pin 4  //Entrada del boton de inicio/final (PIN D2)
          digitalWrite(ledlibre, HIGH);
    digitalWrite(ledocupado, LOW);
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
        if (user!= 213||user!= 233||user!= 323||user!= 122||user!= 113){
            usuario = 8;
          }
        if (largo<3 )
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
      case 8:
        digitalWrite(segA, SEGMENT_OFF);
        digitalWrite(segB, SEGMENT_OFF);
        digitalWrite(segC, SEGMENT_OFF);
        digitalWrite(segD, SEGMENT_OFF);
        digitalWrite(segE, SEGMENT_OFF);
        digitalWrite(segF, SEGMENT_OFF);
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


          

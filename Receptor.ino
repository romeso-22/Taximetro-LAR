//Receptor de tarifa-emisor al módulo de audio
#include <Wtv020sd16p.h>

int resetPin = 4;  // Pin reset modulo
int clockPin = 5;  // Pin de clk del modulo 
int dataPin = 6;  // Pin de datos del modulo 
int busyPin = 7;  // Pin "busy" del modulo 

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);

void setup() {
  //Inicialización del modulo
  wtv020sd16p.reset();
  Serial.begin(9600);

}

void loop() {

  
  if(Serial.available() > 1) { // llegada de bytes
    uint8_t MSB = Serial.read();//primero llega el MSB
    uint8_t LSB = Serial.read();// segundo llega el LSB
    int numero = (MSB << 8) | LSB;// acomodamos el "word" que ha llegado, aplicado un shift left de 8 bits y un or para acomodar los 2 bytes
    Serial.println(numero);
    delay(1500);

  int DUmillar = numero/ 1000;
  int decmillar = numero/10000;
  int millares = (numero-(decmillar*10000))/1000;
  int centenas = (numero-(decmillar*10000+millares*1000))/100;
  int decenas = (numero- (decmillar*10000+millares*1000 + centenas*100))/10;
 // int unidades=numero-(decmillar*10000+millares*1000 + centenas*100 + decenas*10 );
  
  Serial.println(decmillar);
  Serial.println(millares);
  Serial.println(centenas);
  Serial.println(decenas);
 // Serial.println(unidades);
//delay(1500);


//int voz1;
//int voz2;
//int voz3;
int voz4;


    switch (decenas) {
    case 0: 
      voz4 = 44;
      break;
    case 1:
      voz4 = 10;
      break;
    case 2:
      voz4 = 20;
      break;
    case 3:
      voz4 = 30;
    break;
    case 4:
      voz4 = 40;
      break;
    case 5:
      voz4 = 50;
      break;
    case 6:
      voz4 = 60;
      break;
    case 7:
      voz4 = 70;
      break;
    case 8:
      voz4 = 80;
      break;
    case 9:
      voz4 = 90;
      break;
    default: 
      voz4 = 44;
    break;
   
  }

   switch (centenas) {
     case 0:
      voz3 = 44;
      break;
     case 1:
     if (decenas==0){
      voz3 = 100;
      }
      else {
        voz3 = 101; 
        }
      break;
    case 2:
      voz3 = 200;
      break;
    case 3:
      voz3 = 300;
    break;
    case 4:
      voz3 = 400;
      break;
    case 5:
      voz3 = 500;
      break;
    case 6:
      voz3 = 600;
      break;
    case 7:
      voz3 = 700;
      break;
    case 8:
      voz3 = 800;
      break;
    case 9:
      voz3 = 900;
      break;
    default: 
      voz3 = 44;
    break;
  }
     switch (DUmillar) {
     case 00:
      voz2 = 44;
      voz1 = 44;
     break;
     case 01:
      voz1 = 44;
      voz2 = 1000;
      break;
    case 02:
      voz1 = 2;
      voz2 = 1000;
      break;
    case 03:
      voz1 = 3;
      voz2 = 1000;
      break;
    case 04:
      voz1 = 4;
      voz2 = 1000;
      break;
    case 05:
      voz1 = 5;
      voz2 = 1000;
      break;
    case 06:
      voz1 = 6;
      voz2 = 1000;
      break;
    case 07:
      voz1 = 7;
      voz2 = 1000;
      break;
    case 08:
      voz1 = 8;
      voz2 = 1000;
      break;
    case 09:
      voz1 = 9;
      voz2 = 1000;
      break;
    case 10:  
      voz1 = 10;
      voz2 = 1000;
      break;
    case 11: 
      voz1 = 11;
      voz2 = 1000;
      break;
    case 12:  
      voz1 = 12;
      voz2 = 1000;
      break;
    case 13:  
      voz1 = 13;
      voz2 = 1000;
      break;
    case 14:  
      voz1 = 14;
      voz2 = 1000;
      break;
    case 15:  
      voz1 = 15;
      voz2 = 1000;
      break;
    case 16:  
      voz1 = 16;
      voz2 = 1000;
      break;
    case 17:  
      voz1 = 17;
      voz2 = 1000;
      break;
    case 18:  
      voz1 = 18;
      voz2 = 1000;
      break;
    case 19:  
      voz1 = 19;
      voz2 = 1000;
      break;
    case 20:
      voz1 = 20;
      voz2 = 1000;
      break;
    case 21:
      voz1 = 21;
      voz2 = 1000;
      break;
    case 22:
      voz1 = 22;
      voz2 = 1000;
      break;
    case 23:
      voz1 = 23;
      voz2 = 1000;
      break;
    case 24:
      voz1 = 24;
      voz2 = 1000;
      break;
    case 25:
      voz1 = 25;
      voz2 = 1000;
      break;
    case 26:
      voz1 = 26;
      voz2 = 1000;
      break;
    case 27:
      voz1 = 27;
      voz2 = 1000;
      break;
    case 28:
      voz1 = 28;
      voz2 = 1000;
      break;
    case 29:
      voz1 = 29;
      voz2 = 1000;
      break;
    case 30:
      voz1 = 30;
      voz2 = 1000;
      break;
    case 40:
      voz1 = 40;
      voz2 = 1000;
      break;
    default: 
      voz1 = 44;
      voz2 = 44;
      break;
  }//switch
  
  }//if
 
 // playvoice(miles) voz1
 // playvoice "mil" voz2
 // playvoice centenas voz3
 // playvoice decenas voz4

   wtv020sd16p.playVoice(voz1);
   wtv020sd16p.playVoice(voz2);
   wtv020sd16p.playVoice(voz3);
   wtv020sd16p.playVoice(voz4);
  
}}//loop

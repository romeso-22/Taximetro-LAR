#include "SoftwareSerial.h"
#include <Wtv020sd16p.h>
#include "Adafruit_Thermal.h"

#include "SoftwareSerial.h"
#define TX_PIN A5 // rx de la impr
#define RX_PIN A4 // tx de la imp

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

int voz1;
int voz2;
int voz3;
int voz4;
int resetPin = 8;  // The pin number of the reset pin.
int clockPin = 5;  // The pin number of the clock pin.
int dataPin = 6;  // The pin number of the data pin.
int busyPin = 7;  // The pin number of the busy pin.

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);
//SoftwareSerial  mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
//Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

void setup() {
   mySerial.begin(9600);  // Initialize SoftwareSerial
  printer.begin();        // Inicia la impresora
  //Initializes the module audio
  wtv020sd16p.reset();
  Serial.begin(9600);

  ////impresora
  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

//  mySerial.begin(9600);  // Initialize SoftwareSerial
//  printer.begin();        // Inicia la impresora
    
}
  void loop() {
  
   if(Serial.available() > 1) { // if two bytes have arrived
    uint8_t MSB = Serial.read();
    uint8_t LSB = Serial.read();
    int numero = (MSB << 8) | LSB;
    Serial.println(numero);
    delay(1500);
  seleccion_audio(numero);
    }
}//aqui termina loop



int seleccion_audio(int numero){
  

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
    case 8:
      voz1 = 8;
      voz2 = 1000;
      break;
    case 9:
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
  }//aqui termina switch
  
  //aqui termina if
 
 // playvoice(miles) voz1
 // playvoice "mil" voz2
 // playvoice centenas voz3
 // playvoice decenas voz4
  printer.wake(); 
  printer.boldOn();
  printer.feed(1);
  printer.println(F(" "));
  printer.println(F("____________"));
  printer.println(F("Te quiero mucho mi amor"));
  printer.justify('L');
  printer.println(F("El proyecto ya sirve!!!"));
  printer.println(F("Nos felicito porque lo logramos :D"));
  printer.print(F("(Sin Luis)"));
  
 // printer.print(numero);
  printer.print(F("<3 "));
  printer.feed(2);
  printer.boldOff();
  printer.sleep();      // Apagado de impresero
  //printer.wake();       // Encendido de impresora para imprimir de nuevo
  //printer.setDefault(); // Reset de configuración
  
   wtv020sd16p.playVoice(voz1);
   delay(1000);
   wtv020sd16p.playVoice(voz2);
   delay(500);
   wtv020sd16p.playVoice(voz3);
   delay(1000);
   wtv020sd16p.playVoice(voz4);
   delay(1000);
   
  
}

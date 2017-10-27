#include "Adafruit_Thermal.h"

#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

void setup() {

  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  mySerial.begin(9600);  // Initialize SoftwareSerial
  printer.begin();        // Inicia la impresora

/*
Comandos aceptables:
printerln("X") imprime la palabra X
printer.justify('X') con X igual a R,L o C -justifica al centro derecha o izquierda-
printer.doubleHeightOn(); enciende para empezar a imprimer al doble de altura
printer.doubleHeightOff(); apaga " " "
printer.setSize('X'); define el tamaño de impresion con X igual a S, M o L
printer.boldOn(); enciende texto en negrita
printer.boldOff(); apaga " " "
printer.underlineOn(); enciende impresión subrayada
printer.underlineOff(); apaga " " "
 printer.feed(x); pasa el papel directo po x espacios (alimenta)
*/

//Prueba para avance final de LAB//
  printer.boldOn();
  printer.feed(1);
  printer.println(F(" "));
  printer.println(F("_______"));
  printer.println(F("Fecha: 27/10/17"));
  printer.println(F("Concecionario:"));
  printer.justify('C');
  printer.println(F("Juan Scott Chaves"));
  printer.justify('L');
  printer.println(F("Placa: 1234"));
  printer.println(F("Distancia recorrida: 1.2Km"));
  printer.println(F("Tarifa: 950 c"));
  printer.println(F("Tiempo de viaje: 8 min"));
  printer.println(F("Integrantes:"));
  printer.justify('C');
  printer.println(F("Romell Melendez"));
  printer.println(F("Luis Navarro"));
  printer.println(F("Angelica Aiza"));  
  printer.justify('L');
  printer.setSize('M'); 
  printer.println(F("Avance Final Proyecto"));
  printer.feed(1);
  printer.boldOff();

  printer.sleep();      // Apagado de impresero
  delay(3000);         // Se apaga 3 segundos
  printer.wake();       // Encendido de impresora para imprimir de nuevo
  printer.setDefault(); // Reset de configuración
}

void loop() {
}

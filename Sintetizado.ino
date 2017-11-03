/* Multiplexación para dos displays de 4 dígitos cada uno, funcionando con 5 dígitos en total */


unsigned long previo=0;
unsigned long previo2=0;
volatile int contador = 0;   // Variable contador de pulsos
long n = contador ;
long T0 = 0 ;  // Variable global para tiempo
int clk_carro=A2;// pin de entrada del reloj del carro
int t_espera = 5000;
int estado=0;
int tarifa_basica = 690;

int digit1 = 11; //Pin 1 del display 
int digit2 = 10; //Pin 2 
int digit3 = 9; //Pin 6 
int digit4 = 6; //Pin8 
int digit5 = 13;// Pin 1 del display 
//Pinout para arduino UNO

int segA = A1; //Pin 14 
int segB = 3; //Pin 16 
int segC = 4; //Pin 13 
int segD = 5; //Pin 3 
int segE = A0; //Pin 5 
int segF = 7; //Pin 11 
int segG = 8; //Pin 15 
//String tarifa;
void setup() { 
pinMode(2, INPUT);
pinMode(A2, INPUT);
attachInterrupt( 0, Conteo, FALLING);//interrupcion (pulso del carro)
//attachInterrupt( 1, Over, FALLING);//interrupcion (pulso del carro)

  //Asignación de salidas, segmentos y dígitos correspondientes
  Serial.begin(9600);  
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT); 
  pinMode(digit5, OUTPUT);
  
}
//Si hay datos en el puerto serial, los lee guarda en una variable (tarifa) y llama a la funcion de impresión en el display
void loop() {
  RecorridoExtra();
long  pago=tarifa(contador);
  displayNumber(pago);
 // llegada();
}


 /*void Over(){
  
  if(estado%2==0){// para iniciar el viaje
  contador=0;
  estado++;
  }
  else{}// para parar el viaje
  byte LSB = contador;  
  byte MSB = contador >> 8;
  Serial.write(MSB);
  Serial.write(LSB);
  estado++;
  }
*/
void RecorridoExtra(){
 // Serial.println(contador);
  //Serial.write(contador);//imprimimos tarifa
  unsigned long actual=millis();
   if (n != contador)// si la tarifa ha cambiado, se imprime
           {  // Serial.println(contador);// imprimimos la tarifa
              // Serial.write(contador);
               n = contador ;//actualizamos la tarifa
           }
  if(digitalRead(clk_carro)==LOW){// el carro se detuvo y el clk se quedo en el estado asignado (high o low)
  if(actual-previo>=t_espera && digitalRead(clk_carro)==LOW){// si han pasado más de 5 seg y sigue en el mismo estado...
  contador++;// cuenta uno más a causa de la espera
  previo=actual;  // actualiza el tiempo de espera 
  }}
  }

int tarifa(long cuenta){
  int factura;
    if(cuenta <= 1000){
      factura=tarifa_basica ;
      }
  if(cuenta>1000){
    factura=tarifa_basica +(cuenta-1000);
    }
  return factura;
  }  

void Conteo() // conteo por interrupcion de clk del carro
   {
       if ( millis() > T0 )//eliminación de rebote
          {   contador++ ;// conteo de pulso (tarifa)
              T0 = millis(); // actualización para el rebote
          }
    }

void displayNumber(long toDisplay) {  // funcion para impresion
#define DISPLAY_BRIGHTNESS  1000

#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

  long beginTime = millis();

  for(int digit = 5 ; digit > 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch(digit) {
    case 1:
      digitalWrite(digit1, DIGIT_ON);
      break;
    case 2:
      digitalWrite(digit2, DIGIT_ON);
      break;
    case 3:
      digitalWrite(digit3, DIGIT_ON);
      break;
    case 4:
      digitalWrite(digit4, DIGIT_ON);
      break;
    case 5:
      digitalWrite(digit5, DIGIT_ON);
      break;
    }

    //Turn on the right segments for this digit
    lightNumber(toDisplay % 10);// toma el digito más a la derecha del dato y lo envia a imprimir
    toDisplay /= 10;// aplaica división entera para ahora imprimir el sigueinte dígito del dato

    delayMicroseconds(DISPLAY_BRIGHTNESS); //Encendidod por un instante

    //Apagado de digito
    lightNumber(10); 

    //Apagar todos los digitos
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
    digitalWrite(digit5, DIGIT_OFF);
  }

  while( (millis() - beginTime) < 12) ; //Espera de tiempo para volver a imprimir
}

//Asignación de segmentos encendidod
void lightNumber(int numberToDisplay) {// funcion que asigna los segmentos correspondientes a cada numero

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

  switch (numberToDisplay){
/*Casos para cada dígito, se asignan los segmentos respectivos encendidos y apagados*/
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

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 10:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;
  }
}


 
//constantes de contador y tiempos
unsigned long previo=0;
unsigned long previo2=0;
volatile int contador = 0;   // Variable contador de pulsos
long n = contador ;
long T0 = 0 ;  // Variable global para tiempo
long T1=0;
int clk_carro = 4;// pin de entrada del reloj del carro
//constantes para modificar y adaptar el auto
int t_espera = 1300;
float tarifa_extra=610;
int tarifa_basica = 640;
int estado=1;
int pulsoskm = 500;// pulsos que se dan por kilometro (deben ser medidos)
float otr= tarifa_extra/pulsoskm;//ajute de precio por pulos
int cte = (10/otr);//ajuste de precio por pulso
long tiempo_de_viaje;




//Constantes para displyas
int digit1 = 12; //Pin 1 del display cambie eagle era un 11
int digit2 = 11; //Pin 2 
int digit3 = 10; //Pin 6 cambiados era 6 es 12 en eagle
int digit4 = 9; //Pin8  cambiados era 9 es 15 en eagle
int digit5 = 8;// Pin 1 del display cambie eagle era un 13
//Pinout de arduino
int segA = A1; //Pin 14 
int segB = 13; //Pin 16 
int segC = A2; //Pin 13 
int segD = A3; //Pin 3 
int segE = A5; //Pin 5 
int segF = A4; //Pin 11 
int segG = A0; //Pin 15 
//String tarifa;
void setup() { 
pinMode(2, INPUT);
pinMode(clk_carro, INPUT);
attachInterrupt( 0, Conteo, FALLING);//interrupcion (pulso del carro)
attachInterrupt( 1, Over, FALLING);//interrupcion inicio/fin

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
Serial.println(otr);
Serial.println(cte);
}
//Si hay datos en el puerto serial, los lee guarda en una variable (tarifa) y llama a la funcion de impresión en el display
void loop() { 
 if(estado%2==0){ 
 //tiempo_de_viaje= millis(); 
 RecorridoExtra();
 long  pago=tarifa(contador);
 displayNumber(pago);
 }
 else{
  tiempo_de_viaje=0;
  contador=0;
  displayNumber(0);
  }
}

 void Over(){
   if ( millis() > T1  + 250)
         {
          estado++;        
          if(estado%2!=0){
            long  pago=tarifa(contador);
  uint8_t LSB = pago;  
 uint8_t MSB = pago >> 8;
  //Serial.println(pago);
 Serial.write(MSB);
  Serial.write(LSB);


  
            }
          } 
          T1 = millis();
          }
  
 

void RecorridoExtra(){
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
    if(cuenta <= pulsoskm){// si ha recorrido menos de un kilometro
      factura=tarifa_basica ;//imprime solo tarifa basica
      }
  if(cuenta>pulsoskm){
    factura=tarifa_basica +(10*((cuenta-pulsoskm)/cte));// si ha recorrido más de un kilometro imprime la basica más el ajuste  (algoritmo)    
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

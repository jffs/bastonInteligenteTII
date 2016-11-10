#include <SoftwareSerial.h>
byte pinOutPWM = 6;

SoftwareSerial bluetooth(3, 2); // RX, TX conectar al modulo, el pin 2 al transmisor y el 3 al receptor
long distancia_enfrente,distancia_arriba,distancia_arriba_ant=0,distancia_enfrente_ant=0;
long tiempo,tiempo2;
String enfrente= "Enfrente a ";
String cm=" centimetros";
String arriba= "Arriba a ";
String metro=" metros";
int decena, centena;
void setup(){
  Serial.begin(9600);
  bluetooth.begin(9600); 
  pinMode(pinOutPWM, OUTPUT);
  /*Primer sensor*/
  pinMode(9, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico TRIG*/
  pinMode(8, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido ECHO*/
  /*Segundo sensor*/
  pinMode(4, OUTPUT); /*activación del pin 4 como salida: para el pulso ultrasónico TRIG*/
  pinMode(5, INPUT); /*activación del pin 5 como entrada: tiempo del rebote del ultrasonido ECHO*/
}

void loop(){
  digitalWrite(9,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(9, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tiempo=pulseIn(8, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante*/
  distancia_enfrente= int(0.017*tiempo); /*fórmula para calcular la distancia obteniendo un valor entero*/
  /*Monitorización en centímetros por el monitor serial*/
  //La distancia se envia cuando es multiplo de 10
  
  if ((distancia_enfrente!=distancia_enfrente_ant)&&(distancia_enfrente > 3) && (distancia_enfrente < 300) && (distancia_enfrente%5==0)){
    distancia_enfrente_ant=distancia_enfrente;
    if (distancia_enfrente<100){
     // analogWrite(pinOutPWM, 255);
           Serial.println(enfrente +distancia_enfrente+ cm);
      bluetooth.println(enfrente +distancia_enfrente+ cm);

    }
    else{
      // analogWrite(pinOutPWM, 127);
       decena=distancia_enfrente%100;
       centena=distancia_enfrente/100;
      //distancia=distancia/100;
      bluetooth.println(enfrente +centena+','+decena+ metro);
      Serial.println(enfrente +centena+','+decena+ metro);
      }
    }
 // bluetooth.println("holas");
  //delay(500);

  
  digitalWrite(4,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(4, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tiempo2=pulseIn(5, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante*/
  distancia_arriba= int(0.017*tiempo2); /*fórmula para calcular la distancia obteniendo un valor entero*/
  /*Monitorización en centímetros por el monitor serial*/
 

  if ((distancia_arriba!=distancia_arriba_ant)&&(distancia_arriba > 3) && (distancia_arriba < 300)&&(distancia_arriba%5==0)){
      distancia_arriba_ant=distancia_arriba;
      if (distancia_arriba<100){
        bluetooth.println(arriba +distancia_arriba+ cm);
        Serial.println(arriba +distancia_arriba+ cm);
      }
        else{
          decena=distancia_arriba%100;
          centena=distancia_arriba/100;
          //distancia2=distancia2/100;
          bluetooth.println(arriba +centena+','+decena+ metro);
    Serial.println(arriba +centena+','+decena+ metro);
            }

  }
     // bluetooth.println("holas");
  delay(500);
}
  

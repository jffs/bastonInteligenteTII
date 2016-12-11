#include <SoftwareSerial.h>
byte pinOutPWM = 6;
 /* le mandamos 3 5 7 9 para distancias de       
  5 a 15 cmm ->9 
  15 a 30 cmm ->7
  30 a 45 cmm -> 5
  45 a 60 cmm ->3 */
  
SoftwareSerial bluetooth(3, 2); // RX, TX conectar al modulo, el pin 2 al transmisor y el 3 al receptor
long distancia_enfrente,distancia_arriba,distancia_arriba_ant=0,distancia_enfrente_ant=0;
long tiempo,tiempo2;
String enfrente= "Enfrente a ";
String cm=" centimetros";
String arriba= "Arriba a ";
String metro=" metros";
int decena, centena;
int vibracion_nivel;
void setup(){
  Serial.begin(9600);
  bluetooth.begin(9600); 
  pinMode(pinOutPWM, OUTPUT);
  /*Primer sensor*/
  pinMode(9, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico TRIG*/
  pinMode(8, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido ECHO*/
  /*Segundo sensor*/
  pinMode(5, OUTPUT); /*activación del pin 4 como salida: para el pulso ultrasónico TRIG*/
  pinMode(4, INPUT); /*activación del pin 5 como entrada: tiempo del rebote del ultrasonido ECHO*/
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
  
  if ((distancia_enfrente!=distancia_enfrente_ant)&&(distancia_enfrente > 3) && (distancia_enfrente < 100) && (distancia_enfrente%5==0)){
    distancia_enfrente_ant=distancia_enfrente;
    if (distancia_enfrente>=5 && distancia_enfrente <15) 
      vibracion_nivel=9;
    else
      if (distancia_enfrente>=15 && distancia_enfrente<30) 
        vibracion_nivel=7;
      else
        if (distancia_enfrente>=30 && distancia_enfrente <45)
          vibracion_nivel=5;
        else
          if (distancia_enfrente>=45 && distancia_enfrente <65) 
            vibracion_nivel=3;
          else
            vibracion_nivel=0;

    int velocidad=map(vibracion_nivel,'0','9',0,125);
    analogWrite(pinOutPWM, velocidad);
    Serial.println(enfrente +distancia_enfrente+ cm);
    bluetooth.println(enfrente +distancia_enfrente+ cm);
   }
  
  digitalWrite(5,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(5, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tiempo2=pulseIn(4, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante*/
  distancia_arriba= int(0.017*tiempo2); /*fórmula para calcular la distancia obteniendo un valor entero*/
  /*Monitorización en centímetros por el monitor serial*/
 

  if ((distancia_arriba!=distancia_arriba_ant)&&(distancia_arriba > 3) && (distancia_arriba < 100)&&(distancia_arriba%5==0)){
      distancia_arriba_ant=distancia_arriba;
      bluetooth.println(arriba +distancia_arriba+ cm);
      Serial.println(arriba +distancia_arriba+ cm);
  }
     // bluetooth.println("holas");
  delay(500);
}
  

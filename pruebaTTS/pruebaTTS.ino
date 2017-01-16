
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(2, 3); // RX, TX conectar al modulo, el pin 2 al transmisor y el 3 al receptor
unsigned char cuenta;
void setup() {
    bluetooth.begin(9600); /*Inicialización del bluetooth a un baud de 9600*/
    cuenta=1; //Contador
}

void loop() {
  while(cuenta<11){
    bluetooth.println(cadena); //enviar el valor del contador por BT
    delay(1000); //esperar 1 segundo
    cuenta++; //incrementer el contador
  }
  cuenta=1; //volver a iniciarlo
}

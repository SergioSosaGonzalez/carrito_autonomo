
#include <SoftwareSerial.h>
String message;
 
//Alias para pines de control de Motor Derecho
int pwmtoder = 10;
int mtoder = 12;
int pwmvalder = 197; //Esta variable es la que se modifica para variar la velocidad de giro del motor. Va de 0 a 255, siendo 0 el mínimo y 255 el máximo
//Alias para pines de control de Motor Izquierdo
int pwmtoizq = 11;
int mtoizq = 13;
int pwmvalizq = 197; //Esta variable es la que se modifica para variar la velocidad de giro del motor. Va de 0 a 255, siendo 0 el mínimo y 255 el máximo

int ubicacion;

//Funciones
void adelante(int tiempo);
void atras(int tiempo);
void giroderecha();
void giroizquierda();
void derecha(int tiempo);
void izquierda(int tiempo);
void detener();
void ubicate();
void movimientosAuto();

void setup() {
  //configuración de los sensores de proximidad
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  
  //configuración del bluetooth
  pinMode(0, OUTPUT);
  
  // initialize the serial communications:
  Serial.begin(9600);
  digitalWrite(0,LOW);
  //activar bluetooth
  delay(1000);
  digitalWrite(0,HIGH);
  
  // configuración inicial del carrito
  pinMode(pwmtoizq, OUTPUT); 
  pinMode(mtoizq, OUTPUT);
  pinMode(pwmtoder, OUTPUT);
  pinMode(mtoder, OUTPUT);
  digitalWrite(pwmtoizq, LOW);
  digitalWrite(mtoizq, LOW);
  digitalWrite(pwmtoder, LOW);
  digitalWrite(mtoder, LOW);
  delay(100);
}

void loop() {
    //Acciones autonomas
    //movimientosAuto();
    movimientosSensoresAbajo();
    delay(250);
}

void adelante(int tiempo)
{
 analogWrite(pwmtoder, pwmvalder);
 analogWrite(pwmtoizq, pwmvalizq);
 digitalWrite(mtoder, HIGH);
 digitalWrite(mtoizq, HIGH);
 delay(tiempo);
 detener();
}

void atras(int tiempo)
{
 analogWrite(pwmtoder, pwmvalder);
 analogWrite(pwmtoizq, pwmvalizq);
 digitalWrite(mtoder, LOW);
 digitalWrite(mtoizq, LOW);
 delay(tiempo);
 detener();
}

void giroderecha()
{
 analogWrite(pwmtoder, 0);
 analogWrite(pwmtoizq, 0);
 digitalWrite(mtoder, LOW);
 digitalWrite(mtoizq, HIGH);
}

void derecha(int tiempo)
{
 analogWrite(pwmtoder, 0);
 analogWrite(pwmtoizq, pwmvalizq);
 digitalWrite(mtoder, HIGH);
 digitalWrite(mtoizq, LOW);
 delay(tiempo);
 detener();
}

void giroizquierda()
{
 analogWrite(pwmtoder, pwmvalder);
 analogWrite(pwmtoizq, 0);
 digitalWrite(mtoder, LOW);
 digitalWrite(mtoizq, HIGH);
}
void izquierda(int tiempo)
{
 analogWrite(pwmtoder, pwmvalder);
 analogWrite(pwmtoizq, 0);
 digitalWrite(mtoder, LOW);
 digitalWrite(mtoizq, HIGH);
 delay(tiempo);
 detener();
}
void detener()
{
 analogWrite(pwmtoder, 0);
 analogWrite(pwmtoizq, 0);
}

void movimientosSensoresAbajo(){
  int sensorValue0 = digitalRead(2); 
  int sensorValue1 = digitalRead(3);
  if(sensorValue0 == HIGH && sensorValue1 == HIGH ) {
    adelante(1000);
  }
  if(sensorValue0 == HIGH && sensorValue1 == LOW ) {
    atras(1000);
    derecha(1000); 
  }
  if(sensorValue0 == LOW && sensorValue1 == HIGH) {
    atras(1000);
    izquierda(1000);
  }   
}

void movimientosAuto() 
{
  ubicacion = ubicar();   //Lee distancia de frente
  if (ubicacion == 7) {            
    detener();
  } else {
    gira(ubicacion);
  }              
}

void gira(int dir) 
{
  switch(dir) {
    case 1:
      giroizquierda();     //gira izq este
      delay(500);   //90 grados
      break;
    case 2:
      derecha(250);     //gira izq noreste
      break;
    case 3:
      adelante(250);  //recto
      break;
    case 4:
      izquierda(250);    //gira der noroeste
      break;
    case 5:
      giroderecha();    //gira der oeste
      delay(500);  //90 grados
      break;
    case 6:
      atras(500);
      break;
  }
}

int ubicar() 
{
   int sensorDerecho   = digitalRead(6);
   int sensorCentro    = digitalRead(5);
   int sensorIzquierdo = digitalRead(4);
   int sentido = 0;
   //Serial.println(" izquierda " + String(sensorIzquierdo) + ", centro " + String(sensorCentro) + ", derecha " + String(sensorDerecho));
   if      (sensorDerecho == HIGH && sensorCentro == HIGH && sensorIzquierdo == HIGH ){
      sentido = 3;
   }else if(sensorDerecho == HIGH && sensorCentro == HIGH && sensorIzquierdo == LOW){
      sentido = 4;
   }else if(sensorDerecho == HIGH && sensorCentro == LOW && sensorIzquierdo == LOW){
      sentido = 4;
   }else if(sensorDerecho == HIGH && sensorCentro == LOW && sensorIzquierdo == HIGH){
       sentido = 6;
   }else if(sensorDerecho == LOW && sensorCentro == HIGH && sensorIzquierdo == HIGH){
       sentido = 2;
   }else if(sensorDerecho == LOW && sensorCentro == LOW && sensorIzquierdo == HIGH){
      sentido = 2;
   }else if(sensorDerecho == LOW && sensorCentro == HIGH && sensorIzquierdo == LOW){
      sentido = 6;
   }else{
      sentido = 7;
   }
   String results[8] = { "0", "1", "izquierda", "centro", "derecha", "5", "atras", "detener" }; 
   Serial.println(results[sentido]);
   return sentido;
}


#include <SoftwareSerial.h>
String message;
 
//Alias para pines de control de Motor Derecho
int pwmtoder = 10;
int mtoder = 12;
int pwmvalder = 197; //Esta variable es la que se modifica para variar la velocidad de giro del motor. Va de 0 a 255, siendo 0 el mínimo y 255 el máximo
//Alias para pines de control de Motor Izquierdo
int pwmtoizq = 10;
int mtoizq = 12;
int pwmvalizq = 197; //Esta variable es la que se modifica para variar la velocidad de giro del motor. Va de 0 a 255, siendo 0 el mínimo y 255 el máximo

//Funciones
void adelante();
void atras();
void giroderecha();
void giroizquierda();
void derecha();
void izquierda();
void detener();

void setup() {
  //configuración de los sensores de proximidad
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

  //control por voz
  if(Serial.available()>0){
    message = Serial.readString();
    if(message == "adelante"){
      adelante();
   }
   else if(message == "retroceder"){
      atras();
    }
    else if(message == "derecha"){
      derecha();
      delay(900);
      adelante();
    }
    else if(message == "izquierda"){
      izquierda();
      delay(900);
      adelante();
    }
   else if(message == "detener"){
      detener();
    }
  }
    // leer entrada en los sensores de proximidad:
    int sensorValue0 = digitalRead(4);
    int sensorValue1 = digitalRead(5);
    int sensorValue2 = digitalRead(6);
     if         (sensorValue0 == HIGH){
     Serial.println("izquierda " + sensorValue0);
     }
     if         (sensorValue1 == HIGH){
     Serial.println("centro " + sensorValue1);
     }
     if         (sensorValue2 == HIGH){
     Serial.println("derecha " + sensorValue2);
     }
    //Acciones autonomas
    if (sensorValue1 == HIGH)
    {
        adelante();
    } else {
      atras();
      delay(1500);
      detener();
    }
    if (sensorValue0 == HIGH)
    {
        adelante();
    } else {
      atras();
      delay(1500);
      izquierda();
    } 
    if (sensorValue2 == HIGH)
    {
        adelante();
    } else {
      atras();
      delay(1500);
      derecha();
    }
    delay(500); // tiempo de estabilidad
}

void adelante()
{
 analogWrite(pwmtoder, pwmvalder);
 analogWrite(pwmtoizq, pwmvalizq);
 digitalWrite(mtoder, HIGH);
 digitalWrite(mtoizq, HIGH);
}

void atras()
{
 analogWrite(pwmtoder, pwmvalder);
 analogWrite(pwmtoizq, pwmvalizq);
 digitalWrite(mtoder, LOW);
 digitalWrite(mtoizq, LOW);
}

void giroderecha()
{
 analogWrite(pwmtoder, pwmvalder);
 analogWrite(pwmtoizq, pwmvalizq);
 digitalWrite(mtoder, LOW);
 digitalWrite(mtoizq, HIGH);
}

void derecha()
{
 analogWrite(pwmtoder, 0);
 analogWrite(pwmtoizq, pwmvalizq);
 digitalWrite(mtoder, LOW);
 digitalWrite(mtoizq, HIGH);
}

void giroizquierda()
{
 analogWrite(pwmtoder, pwmvalder);
 analogWrite(pwmtoizq, pwmvalizq);
 digitalWrite(mtoder, HIGH);
 digitalWrite(mtoizq, LOW);
}
void izquierda()
{
 analogWrite(pwmtoder, pwmvalder);
 analogWrite(pwmtoizq, 0);
 digitalWrite(mtoder, HIGH);
 digitalWrite(mtoizq, LOW);
}
void detener()
{
 analogWrite(pwmtoder, 0);
 analogWrite(pwmtoizq, 0);
}

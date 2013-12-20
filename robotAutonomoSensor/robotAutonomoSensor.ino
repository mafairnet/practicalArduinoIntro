#include <ZumoMotors.h>

//Salida del led
#define LED_PIN 13
#define HIGH_SPEED 400
#define REGULAR_SPEED 200
#define LOW_SPEED 150
#define NO_SPEED 0
#define SPEED_CORRECTION 35
#define ULTRASONICO 2

//Variable para manejar lso motores
ZumoMotors motors;

//Funcion en la que realizo la configuracion del arduino
void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

//Funcion que se realiza siempre
void loop()
{
  //Debo obtener una lectura de lo que hay enfrente
  //se utilizan datos long debido a la respuesta del ultrasonido
  long duracion, cm, cmDer, cmIzq;
  
  //Obtenemos la duracion
  duracion = lectura();
  
  // convertimos el tiempo que nos da el pulse in en distancia
  cm = msCentimetros(duracion);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  //Si no hay nada avanzo
  if(cm >= 20)
  {
    digitalWrite(LED_PIN, LOW);
    adelante();
  }
  else
  {
    //Si hay algo paro
    digitalWrite(LED_PIN, HIGH);
    para();
    
    //Doy una vuelta a la derecha
    vueltaDerecha();
    
    //Obtenemos la duracion
    duracion = lectura();
    
    // convertimos el tiempo que nos da el pulse in en distancia
    cmDer = msCentimetros(duracion);
    
    //Volvemos a nuestra ubicacion inicial
    vueltaIzquierda();
    
    //Damos una vuelta a la izquierda
    vueltaIzquierda();
    
    //Obtenemos la duracion
    duracion = lectura();
    
    // convertimos el tiempo que nos da el pulse in en distancia
    cmIzq = msCentimetros(duracion);
    
    //Volvemos a nuestra posicion inical
    vueltaDerecha();
    
    //Si la hay un objeto mas cercano a la derecha que a la izquierda
    if(cmIzq > cmDer)
    {
      //Doy una vuelta a la izquierda
      vueltaIzquierda();
    }
    //De lo contrario
    else
    {
      //Doy una vuelta a la derecha
      vueltaDerecha();
    }
  }
  //Hago una pausa de 100 milisegundos para seguir sobteniendo datos de los sensores
  delay(100);
}

//Funcion que mueve el robot hacia adelante
void adelante()
{
  motors.setLeftSpeed(HIGH_SPEED);
  motors.setRightSpeed(HIGH_SPEED-SPEED_CORRECTION);
}

//Funcion que para el robot
void para()
{
  motors.setLeftSpeed(NO_SPEED);
  motors.setRightSpeed(NO_SPEED);
}

//Funcion que da vuelta a la derecha al robot
void vueltaDerecha()
{
  for (int speed = 0; speed <= REGULAR_SPEED; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(-speed);
    delay(2);
  }
  for (int speed = REGULAR_SPEED; speed <= 0; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(-speed);
    delay(2);
  }
}

//Funcion que da vuelta a la izquierda al robot
void vueltaIzquierda()
{
  for (int speed = 0; speed <= REGULAR_SPEED; speed++)
  {
    motors.setLeftSpeed(-speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
  for (int speed = REGULAR_SPEED; speed <= 0; speed++)
  {
    motors.setLeftSpeed(-speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
}

//Funcion que calcula la distancia en CM
long msCentimetros(long microsegundos)
{
  //La velocidad del sonido es 340 m/s o 29 microsegundos por centímetro.
  //El sonido llega hasta el objeto, rebota y regresa como eco por lo que
  //solo es necesario tomar la distancia así que primero dividimos entre 29
  //y posteriormente entre 2
  return microsegundos / 29 / 2;
}

//Funcion que realiza la lectura del ultrasonico
long lectura()
{
  //Se manda un pulso bajo de 5 microsegundos para asegurar que siempre se inicie en bajo
  //después se manda un pulso alto de 15 microsegundos que sirve para iniciar las mediciones
  pinMode(ULTRASONICO, OUTPUT);
  digitalWrite(ULTRASONICO, LOW);
  delayMicroseconds(5);
  digitalWrite(ULTRASONICO, HIGH);
  delayMicroseconds(15);
  digitalWrite(ULTRASONICO, LOW);
    
  //Se utiliza el mismo pin para recibir el eco así que lo cambiamos de salida a entrada
  //y utilizamos la variable duracion para recibir el valor que nos da el ultrasonico
  pinMode(ULTRASONICO, INPUT);
  return pulseIn(ULTRASONICO, HIGH);
}

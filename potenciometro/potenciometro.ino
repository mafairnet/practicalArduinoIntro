/* Control de intesidad de luz
 * Este programa muestra como controlar la intensidad de luz de un led
 * usando el ADC del Arduino y el PWM.
 */

//Se define una variable para manejar el numero de pin del led
int led0Pin = 9;

//Se define una variable para manejar el numero de pin del pueto analogico
int analogSensor0 = 0;

//Variables donde almacenamos el voltaje obtenido por el puerto analogico
float sensorValue;
float voltage;

//Esta funcion establece la configuracion del Arduino
void setup()
{
  //Se establece el puerto serial a una conexion de 9600 baudios por segundo
  Serial.begin(9600);
  
  //Se indica que el pin del led sera un puerto de salida digital
  pinMode(led0Pin, OUTPUT);
}

//Esta funcion es ejecutada infinitamente por el Arduino
void loop()
{
  //Leemos el puerto analogico y almacenamos su valor
  sensorValue = analogRead(analogSensor0);
  
  //Convertimos la cantidad obtenida a voltaje con una regla de 3
  voltage = (5.0 * sensorValue)/1024.0;
  
  //Indicamos con la cantidad de voltaje obtenida cual sera la intensidad de luz led
  analogWrite(led0Pin, sensorValue);
  
  //Imprimimos la cantidad de voltaje obtenida en el puerto serial
  Serial.print("Voltaje: ");
  Serial.println(voltage);
  
  //Esperamos medio segundo para volver a leer el puerto analogico
  delay(500);
}

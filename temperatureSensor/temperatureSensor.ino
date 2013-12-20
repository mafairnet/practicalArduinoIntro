/* Sensor de Temperatura
 * Este programa muestra como controlar obtener la temperatura del ambiene
 * usando un sensor LM35, el ADC del Arduino y el PWM.
 */

//Se define una variable para manejar el numero de pin del led
int led0Pin = 9;

//Variables donde almacenamos el voltaje obtenido por
//el puerto analogico
int analogSensor0 = 0;
float temperature;

//Cantidad de brillo del led
int brightness = 0;

//Esta funcion establece la configuracion del Arduino
void setup()
{
  //Se establece el puerto serial a una conexion de 9600 baudios
  //por segundo
  Serial.begin(9600);
  
  //Se indica que el pin del led sera un puerto de salida digital
  pinMode(led0Pin, OUTPUT);
}

//Esta funcion es ejecutada infinitamente por el Arduino
void loop()
{ 
  //Leemos el puerto analogico y almacenamos su valor
  temperature = analogRead(analogSensor0);
  
  //Indicamos con la cantidad de voltaje obtenida cual sera la
  //intensidad de luz led
  brightness = temperature;
  analogWrite(led0Pin, brightness);
  
  //Convertimos la cantidad obtenida a temperatura con una regla de 3
  temperature = (5.0 * temperature * 100.0)/1024.0;
  
  //Imprimimos la cantidad de temperatura obtenida en el puerto serial
  Serial.print("Temperatura (Celsius): ");
  Serial.println((byte)temperature);
  
  //Esperamos medio segundo para volver a leer el puerto analogico
  delay(500);
}

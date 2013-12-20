/* Hello World!
 * Este programa muestra como prender/apagar un led y a la vez mostrar a traves del puerto del Arduino 
 * un Hola MUndo.
 */
 
 //Se define una variable para manejar el numero del pin del led
int led = 13;

//Esta funcion establece la configuracion del Arduino
void setup()
{
  //Se indica que el pin del led sera un puerto de salida digital
  pinMode(led, OUTPUT);
  //Se establece el puerto serial a una conexion de 9600 baudios por segundo
  Serial.begin(9600);
}

//Esta funcion es ejecutada infinitamente por el Arduino
void loop()
{
  //Se prende el led indicando que el puerto debe estar en estado alto
  digitalWrite(led, HIGH);
  //Se imprime en el puerto serial una cadena con "Hello World"
  Serial.println("Hello world!");
  //Se pide al Arduino que no realice nada durante 1 segundo
  delay(1000);
  //Se prende el led indicando que el puerto debe estar en estado bajo
  digitalWrite(led, LOW); 
  //Se pide al Arduino que no realice nada durante 4 segundos
  delay(4000);
}

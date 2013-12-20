/* Alarma con Control RFID
 * Este programa mite una alarma activada/desactivada por un RFID
 * y envia los datos obtenidos por los sensores via Serial.
 */
//Pin elegido para leer sensor 1
int sensorPin1 = A0;

//Pin elegido para el led del arduino
int rfidResetPin = 13;

//Pin elegido para la alarma
int alarmPin = 11;

//Pin elegido para el led del arduino
int alarmStatusPin = 12;

//Variable para almacenar el valor obtenido del sensor
int sensorValue = 0;

//Variable para almacenar si la alarma esta activa
boolean alarmActive = false;

//Variable que almacena el valor del TAG RFID leido
char tagString[13];

//Variables que registran los TAGS RFID
char tag1[13] = "XXXXXXXXXXXX";
char tag2[13] = "XXXXXXXXXXXX";
char tag3[13] = "XXXXXXXXXXXX";

//Esta funcion establece la configuracion del Arduino
void setup() {
  //Declaramos el pin del reset como salida y lo encendemos
  pinMode(rfidResetPin, OUTPUT);
  digitalWrite(rfidResetPin, HIGH);
  
  //Declaramos el pin del estado de alarma como salida y lo apagamos
  pinMode(alarmPin, OUTPUT);
  digitalWrite(alarmPin, LOW);
  
  //Declaramos el pin del estado de alarma como salida y lo apagamos
  pinMode(alarmStatusPin, OUTPUT);
  digitalWrite(alarmStatusPin, LOW);
  
  //Iniciamos la conexion serial
  Serial.begin(9600);
}

//Esta funcion es ejecutada infinitamente por el Arduino
void loop() {
  //Leo el puerto serial para saber si hay un TAGRFID
  readSerial();
  
  //Para pruebas lo imprimo en el puerto serial
  /*if(strlen(tagString) != 0)
  {
    Serial.println("TAG");
    Serial.print(tagString);
  }*/
  
  //Checo si el ID del TAG esta registrado
  checkTag(tagString);
  
  //Limpio el arreglo de caracteres para poder leer de nuevo
  clearTag(tagString);
  
  //Reinicio el lector RFID
  resetReader();
  
  //Si el estado de la alarma esta activo
  if(alarmActive)
  {
    //Leo el valor del sensor
    sensorValue = analogRead(sensorPin1);
    //Si el valor es mayor a 950
    if(sensorValue<950)
    {
      //Enciendo el buzzer de la alarma
      digitalWrite(alarmPin, HIGH);
    }
    //En caso contrario
    else
    {
      //Apago el buzzer de la alarma
      digitalWrite(alarmPin, LOW);
    }
    
    //Imprimo la cantidad obtenida por el sensor
    Serial.println(sensorValue);
    
    //Pausamos la lectura por 500ms
    delay(500);
  }
  //En caso contrario
  else
  {
    //Mantengo el buzzer apagado
    digitalWrite(alarmPin, LOW);
  }
}

//Funcion que le el puerto serial
void readSerial()
{
  //Indice del arreglo de caracteres que almacena el TAG
  int index = 0;
  
  //Almaceno un booleano indicando si estoy leyendo o no un rfid
  boolean reading = false;
  
  //Si hay datos en el puerto serial
  while(Serial.available())
  {
    //Leo cada caracter envaido al serial
    int readByte = Serial.read(); //read next available byte
    
    //Si el caracter es igual a 2 la cadena inicia
    if(readByte == 2) reading = true;
    
    //Si el caracter es igual a 3 la cadena finaliza
    if(readByte == 3) reading = false;

    //Si el caracter no es el inicio,  no estoy leyendo o diferente de 10 o 13
    if(reading && readByte != 2 && readByte != 10 && readByte != 13)
    {
      //Almaceno el caracter en el arreglo de la cadena del tag
      tagString[index] = readByte;
      
      //Avanco en el indicie del arreglo de caracteres que almacena el TAG
      index ++;
    }
  }
}

//Funcion que envia una señal para reiniciar el lector RFID
void resetReader(){
  //Envio 0 volts para el pin del RFID
  digitalWrite(rfidResetPin, LOW);
  
  //Envio 5 volts para el pin del RFID
  digitalWrite(rfidResetPin, HIGH);
  
  //Hago una pausa de 150ms
  delay(500);
}

//Funcion para limpiar el arreglo de caracteres
void clearTag(char one[]){
  //Relleno el arreglo donde se almacena el ID del TAG con puros ceros 
  for(int i = 0; i < strlen(one); i++){
    one[i] = 0;
  }
}

//Funcion para conparar dos cadenas de caracteres
boolean compareTag(char one[], char two[]){

  //Si el arreglo donde se almacena el ID del TAG contiene ceros retorno falso
  if(strlen(one) == 0) return false;

  //Comparo caracter por caracter de los dos arreglos
  for(int i = 0; i < 12; i++){
    //Si los dos son diferentes retorno falso
    if(one[i] != two[i]) return false;
  }

  //Si llego a este punto retorno verdadero
  return true;
}

//Funcion que checa si el tag es valido
void checkTag(char tag[]){

  //Si esta vacia no necesito continuar
  if(strlen(tag) == 0) return;
  
  //Si es igual al TAG1
  if(compareTag(tag, tag1) || compareTag(tag, tag2) || compareTag(tag, tag3))
  {
    //Activo/Desactivo la alarma
    alarmActive = !alarmActive;
    if(alarmActive)
    {
      digitalWrite(alarmStatusPin, HIGH);
      //Serial.println("Alarma activada");
    }
    else
    {
      digitalWrite(alarmStatusPin, LOW);
      //Serial.println("Alarma desactivada");
    }

  }

}


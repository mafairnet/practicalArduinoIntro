/*
 * Codigo Morse
 *
 * Este programa traduce una cadena de caracteres en codigo morse 
 * y lo interpreta con un led.
 */

//Se define una variable para manejar el numero del pin del led0
int led0Pin = 13;
//Se define una variable para manejar el numero del pin del led1
int led1Pin = 2;
//Se define una variable para manejar el numero del pin del buzzer
int buzzer = 3;

//Se declara una variable con la duracion de la pulsacion del punto
int dotDelay = 200;

//Se define un arreglo con la tabla de equivalencia del alfabeto
char* letters[] =
{
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};

//Se define un arreglo con la tabla de equivalencia de los numeros
char* numbers[] =
{
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", //0-6
  "--...", "---..", "----." //7-9
};

//Esta funcion establece la configuracion del Arduino
void setup()
{
  //Se indica que los pines de los led y el buzzer seran puerto de salida digital
  pinMode(led0Pin, OUTPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  //Se establece el puerto serial a una conexion de 9600 baudios por segundo
  Serial.begin(9600);
}

//Esta funcion es ejecutada infinitamente por el Arduino
void loop()
{
  char ch;
  //Si se recibe algo en el puerto serial
  if (Serial.available())
  {
    //Leemos cada caracter obtenido en el puerto serial
    ch = Serial.read();
    //Si el caracter es letra minuscula
    if (ch >= 'a' && ch <= 'z')
    {
      flashSequence(letters[ch - 'a']);
    }
    //Si el caracter es letra mayucula
    else if (ch >= 'A' && ch <= 'Z')
    {
      flashSequence(letters[ch - 'A']);
    }
    //Si el caracter es digito
    else if (ch >= '0' && ch <= '9')
    {
      flashSequence(numbers[ch - '0']);
    }
    //Si es pecacio
    else if (ch == ' ')
    {
      //Transmito espacio
      delay(dotDelay * 4);
    }
  }
}

//Funcion que permite trasnmitir la secuencia de caracteres
//en codigo Morse
void flashSequence(char* sequence)
{
  //Iniciamos una variable en 0
  //para recorrer la secuencia de caracteres
  int i = 0;
  //Mientras la secuencia sea diferente de null
  while (sequence[i] != NULL)
  {
    //Indico si es punto o raya
    flashDotOrDash(sequence[i]);
    //Aumento i para ir avanzando en el arreglo
    i++;
  }
  //Espacio entre letras
  delay(dotDelay * 3);
}

//Funcion que indica si transmitir punto o guion
void flashDotOrDash(char dotOrDash)
{
  //Establecemos los led y el buzzer en estado alto
  digitalWrite(led0Pin, HIGH);
  digitalWrite(led1Pin, HIGH);
  digitalWrite(buzzer, HIGH);
  //Si es punto
  if (dotOrDash == '.')
  {
    //Espero el tiempo indicado para indicar que es un punto
    delay(dotDelay);
  }
  //Si es guion
  else
  {
    //Espero el tiempo indicado para indicar que es un guion
    delay(dotDelay * 3);
  }
  //Establecemos los led y el buzzer en estado bajo
  digitalWrite(led0Pin, LOW);
  digitalWrite(led1Pin, LOW);
  digitalWrite(buzzer, LOW);
  //Tiempo de espera entre secuencia de caracteres
  delay(dotDelay);
}

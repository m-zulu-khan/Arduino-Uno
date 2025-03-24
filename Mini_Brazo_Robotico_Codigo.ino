#include <Servo.h> // Incluye la biblioteca para controlar servomotores

Servo servo_0; // Declaración del objeto para controlar el primer servo
Servo servo_1; // Declaración del objeto para controlar el segundo servo
Servo servo_2; // Declaración del objeto para controlar el tercer servo
Servo servo_3; // Declaración del objeto para controlar el cuarto servo

// Definición de pines analógicos para los potenciometros
int sensorPin0 = A0; 
int sensorPin1 = A1;
int sensorPin2 = A2; 
int sensorPin3 = A3; 

// Variables utilizadas en el programa
int count0, arrayStep, arrayMax, countverz, Taster, stepsMax, steps, time = 1000, del = 1000, temp;
unsigned int verz = 0;

long previousMillis1 = 0;
long previousMillis2 = 0;
long previousMillis3 = 0;
long previousMillis4 = 0;
long previousMicros = 0;
unsigned long currentMillis = millis();
unsigned long currentMicros = micros();

// Definición de arreglos para almacenar datos
int Delay[7] = {0, 0, 1, 3, 15, 60, 300}; // Mapeo de valores de potenciómetro a retraso en segundos
int SensVal[4]; // Almacena los valores de los sensores
float dif[4], ist[4], sol[4], dir[4]; // Variables para cálculos de diferencia y posición
int joint0[180]; // Almacena posiciones del servo 0
int joint1[180]; // Almacena posiciones del servo 1
int joint2[180]; // Almacena posiciones del servo 2
int joint3[180]; // Almacena posiciones del servo 3
int top = 179; // Índice máximo para los arreglos
boolean playmode = false, Step = false; // Modo de reproducción y paso

// Configuración inicial del programa
void setup()
{
  pinMode(4, INPUT); // Configura el pin digital 4 como entrada
  pinMode(6, INPUT); // Configura el pin digital 6 como entrada
  pinMode(13, OUTPUT); // Configura el pin digital 13 como salida
  digitalWrite(13, HIGH); // Enciende el LED en el pin digital 13
  servo_0.attach(3); // Asocia el servo_0 al pin digital 3
  servo_1.attach(5); // Asocia el servo_1 al pin digital 10
  servo_2.attach(11); // Asocia el servo_2 al pin digital 9
  servo_3.attach(12); // Asocia el servo_3 al pin digital 11
  Serial.begin(115200); // Inicia la comunicación serial con una velocidad de 115200 baudios
  Serial.println("mini robot ready..."); // Imprime mensaje de inicio en el puerto serial
  digitalWrite(13, LOW); // Apaga el LED en el pin digital 13
}

// Bucle principal del programa
void loop()
{
  currentMillis = millis(); // Obtiene el tiempo actual en milisegundos
  currentMicros = micros(); // Obtiene el tiempo actual en microsegundos
  Button(); // Llama a la función Button() para manejar el botón

  // Sección de código para el modo manual...
  if (!playmode)
  {
    if (currentMillis - previousMillis1 > 25)
    {
      if (arrayStep < top)
      {
        previousMillis1 = currentMillis;
        readPot(); // Lee los valores de los potenciómetros
        mapping(); // Mapea los valores a milisegundos para los servos
        move_servo(); // Establece la nueva posición del servo
      }
    }
  }

  // Sección de código para el modo de reproducción...
  else if (playmode)
  {
    if (Step)
    {
      digitalWrite(13, HIGH); // Enciende el LED en el pin digital 13
      if (arrayStep < arrayMax)
      {
        arrayStep += 1;
        Read();
        calculate();
        Step = 0;
        digitalWrite(13, LOW); // Apaga el LED en el pin digital 13
      }
      else
      {
        arrayStep = 0;
        calc_pause();
        countverz = 0;
        while (countverz < verz)
        {
          countverz += 1;
          calc_pause();
          digitalWrite(13, HIGH); delay(25);
          digitalWrite(13, LOW); delay(975);
        }
      }
    }
    else
    {
      if (currentMicros - previousMicros > time)
      {
        previousMicros = currentMicros;
        play_servo();
      }
    }
  }

  // Bucle de espera hasta que se presione el botón de pausa...
  while (digitalRead(4) == false)
  {
    digitalWrite(13, HIGH); delay(500);
    digitalWrite(13, LOW); delay(500);
  }

  // Comentario: Sección de salida de texto por el puerto serial (comentada para mayor concisión)
  // ...
}

// Función para calcular el retraso entre movimientos
void calc_pause()
{
  readPot();
  temp = SensVal[3];
  if (temp < 0) temp = 0;
  temp = map(temp, 0, 680, 0, 6);
  verz = Delay[temp]; // verz = retraso en segundos
}

// Función para leer valores de los potenciómetros
void readPot()
{
  SensVal[0] = analogRead(sensorPin0);
  SensVal[1] = analogRead(sensorPin1);
  SensVal[2] = analogRead(sensorPin2);
  SensVal[3] = analogRead(sensorPin3);
}

// Función para mapear valores de los potenciómetros a milisegundos
void mapping()
{
  ist[0] = map(SensVal[0], 150, 900, 600, 2400); // drehen
  ist[1] = map(SensVal[1], 1000, 100, 550, 2400); // Schulter
  ist[2] = map(SensVal[2], 120, 860, 400, 2500); // Hand
  ist[3] = map(SensVal[3], 1023, 0, 500, 2500); // Zange
}

// Función para almacenar posiciones en los arreglos
void record()
{
  joint0[arrayStep] = ist[0];
  joint1[arrayStep] = ist[1];
  joint2[arrayStep] = ist[2];
  joint3[arrayStep] = ist[3];
}

// Función para leer posiciones desde los arreglos
void Read()
{
  sol[0] = joint0[arrayStep];
  sol[1] = joint1[arrayStep];
  sol[2] = joint2[arrayStep];
  sol[3] = joint3[arrayStep];
}

// Función para mover los servos
void move_servo()
{
  servo_0.writeMicroseconds(ist[3]);
  servo_1.writeMicroseconds(ist[2]);
  servo_2.writeMicroseconds(ist[0]);
  servo_3.writeMicroseconds(ist[1]);
}

// Función para calcular pasos individuales
void calculate()
{
  dif[0] = abs(ist[0] - sol[0]);
  dif[1] = abs(ist[1] - sol[1]);
  dif[2] = abs(ist[2] - sol[2]);
  dif[3] = abs(ist[3] - sol[3]);

  stepsMax = max(dif[0], dif[1]);
  stepsMax = max(stepsMax, dif[2]);
  stepsMax = max(stepsMax, dif[3]);

  if (stepsMax < 500)
    del = 1200;
  else
    del = 600;

  if (sol[0] < ist[0]) dir[0] = 0 - dif[0] / stepsMax;
  else
    dir[0] = dif[0] / stepsMax;
  if (sol[1] < ist[1]) dir[1] = 0 - dif[1] / stepsMax;
  else
    dir[1] = dif[1] / stepsMax;
  if (sol[2] < ist[2]) dir[2] = 0 - dif[2] / stepsMax;
  else
    dir[2] = dif[2] / stepsMax;
  if (sol[3] < ist[3]) dir[3] = 0 - dif[3] / stepsMax;
  else
    dir[3] = dif[3] / stepsMax;
}

// Función para mover los servos durante la reproducción
void play_servo()
{
  steps += 1;
  if (steps < stepsMax)
  {
    if (steps == 20) time = del * 4;
    else if (steps == 40) time = del * 3;
    else if (steps == 80) time = del * 2;
    else if (steps == 100) time = del - 1;

    if (steps == stepsMax - 200) time = del * 2;
    else if (steps == stepsMax - 80) time = del * 3;
    else if (steps == stepsMax - 40) time = del * 4;
    else if (steps == stepsMax - 20) time = del * 5;

    ist[0] += dir[0];
    ist[1] += dir[1];
    ist[2] += dir[2];
    ist[3] += dir[3];

    servo_0.writeMicroseconds(ist[3]);
    servo_1.writeMicroseconds(ist[2]);
    servo_2.writeMicroseconds(ist[0]);
    servo_3.writeMicroseconds(ist[1]);
  }
  else
  {
    Step = 1;
    steps = 0;
  }
}

// Función para imprimir los datos grabados por el puerto serial
void data_out()
{
  int i = 0;
  while (i < arrayMax)
  {
    digitalWrite(13, HIGH);
    i += 1;
    Serial.print(joint0[i]); Serial.print(", ");
  }
  Serial.println("Joint0");
  i = 0;
  while (i < arrayMax)
  {
    digitalWrite(13, HIGH);
    i += 1;
    Serial.print(joint1[i]); Serial.print(", ");
  }
  Serial.println("Joint1");
  i = 0;
  while (i < arrayMax)
  {
    digitalWrite(13, HIGH);
    i += 1;
    Serial.print(joint2[i]); Serial.print(", ");
  }
  Serial.println("Joint2");
  i = 0;
  while (i < arrayMax)
  {
    digitalWrite(13, HIGH);
    i += 1;
    Serial.print(joint3[i]); Serial.print(", ");
  }
  Serial.println("Joint3");
}

// Función para manejar el botón
void Button()
{
  if (digitalRead(6) == false)
  {
    delay(1);
    if (digitalRead(6) == true)
    {
      if (Taster == 0)
      {
        Taster = 1;
        previousMillis3 = currentMillis;
      }
      else if ((Taster == 1) && (currentMillis - previousMillis3 < 250))
      {
        Taster = 2;
      }
    }
  }

  if ((Taster == 1) && (currentMillis - previousMillis3 > 1000))
  {
    arrayStep += 1;
    arrayMax = arrayStep;
    record();
    Taster = 0;
    playmode = false;
    Serial.print("Record Step: "); Serial.println(arrayStep);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
  }
  else if (Taster == 2)
  {
    arrayStep = 0;
    playmode = true;
    Taster = 0;
    Step = 1;
    Serial.println("playmode ");
    data_out();
    delay(250);
    digitalWrite(13, LOW);
  }

  if (currentMillis - previousMillis3 > 2000)
  {
    Taster = 0;
  }
}

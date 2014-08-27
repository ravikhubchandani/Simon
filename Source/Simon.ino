// Secuencia generada, minimo 3 máximo 30
int Buffer[30];
int nivel = 3;
int puntuacion = 0;

// Posiciones de los LED
int LED1 = 5;
int LED2 = 6;
int LED3 = 9;
int LED4 = 10;

// Posiciones de los pulsadores
int A = 2;
int B = 4;
int C = 7;
int D = 8;

// Altavoz
int SPK = 11;

// Variables auxiliares que se usan en el codigo
int i = 0;
int correcto = 1;
int bPulsado = 0;
int boton;
int frecuencia = 1046;

void setup()
{
  pinMode(LED1, OUTPUT);
  analogWrite(LED1, LOW);
  pinMode(LED2, OUTPUT);
  analogWrite(LED2, LOW);
  pinMode(LED3, OUTPUT);
  analogWrite(LED3, LOW);
  pinMode(LED4, OUTPUT);
  analogWrite(LED4, LOW);
  // Configuramos el modo de funcionamiento de los pines para los LEDs y los pulsadores
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
  pinMode(D, INPUT);
  
  pinMode(SPK, OUTPUT);
  
  // Inicializar el generador de numeros aleatorios
  randomSeed(analogRead(0));
  
  Serial.begin(9600);
  Serial.write(4);
  delay(100);
  Serial.write(12);
  delay(100);
  // Borramos el contenido de la pantalla y hacemos que no aparezca el cursor
  tone(SPK, 512, 600);
  delay(600);
  tone(SPK, 1000, 600);
  delay(600);
  tone(SPK, 1300, 600);
  delay(600);
  // Generamos una melodía al comienzo y mostramos un mensaje por la pantalla
  Serial.write("Juego de Simon");
  delay(2000);
}

void loop()
{
  // Borramos el contenido de la pantalla y mostramos un mensaje en pantalla con la ronda actual
  Serial.write(12);
  delay(100);
  Serial.write("Ronda: ");
  delay(100);
  Serial.print(nivel-2);
  delay(100);
  // Generamos una secuencia aleatoria de LEDs encendidos que empieza en 3
  // y se va incrementando con su correspondiente tono, y guardamos la secuencia
  for(i=0; i<nivel; i++)
  {
    switch (random(1, 5))
    {
      case 1:
        Buffer[i] = LED1;
        
        analogWrite(LED1, 255);
        tone(SPK, 750, 950);
        delay(1000);
        analogWrite(LED1, 0);
        
        break;
      case 2:
        Buffer[i] = LED2;
        
        analogWrite(LED2, 255);
        tone(SPK, 880, 950);
        delay(1000);
        analogWrite(LED2, 0);
        
        break;
      case 3:
        Buffer[i] = LED3;
        
        analogWrite(LED3, 255);
        tone(SPK, 1046, 950);
        delay(1000);
        analogWrite(LED3, 0);
        
        break;
      case 4:
        Buffer[i] = LED4;
        
        analogWrite(LED4, 255);
        tone(SPK, 1200, 950);
        delay(1000);
        analogWrite(LED4, 0);
        
        break;
    }
    delay(500);
  }
  
  // Esperamos a que se introduzca una secuencia
  correcto = 1;
  i = 0;
  while((correcto == 1) && (i < nivel))
  {
    bPulsado = 0;
    
    while (bPulsado == 0)
    // Este bucle es necesario para que no se avance hasta que no se pulse un boton
    {
      if(digitalRead(A) == LOW)
      {
        bPulsado = LED1;
        boton = A;
        frecuencia = 750;
      }
      else if(digitalRead(B) == LOW)
      {
        bPulsado = LED2;
        boton = B;
        frecuencia = 880;
      }
      else if(digitalRead(C) == LOW)
      {
        bPulsado = LED3;
        boton = C;
        frecuencia = 1046;
      }
      else if(digitalRead(D) == LOW)
      {
        bPulsado = LED4;
        boton = D;
        frecuencia = 1200;
      }
    }
	// Cuando pulsamos un botón suena el tono asociado además de encenderse el LED correspondiente
    analogWrite(bPulsado, 255);
    while(digitalRead(boton) == LOW){
      tone(SPK, frecuencia, 1);
    }
    analogWrite(bPulsado, 0);
    // Si la secuencia es correcta, se aumenta el nivel, sino se llama a la función GAME_OVER
    if(bPulsado != Buffer[i])
    {
      correcto = 0;
      GAME_OVER();
    }
    
    bPulsado = 0;    
    i++;
    
    delay(500);
  }
  // Si la secuencia fue correcta, se acumula la puntuación de la ronda
  if(correcto == 1)
  {
    puntuacion += 10*nivel;
    
    if(nivel < 30)
      nivel++;
  }
  else nivel = 3;
}


// Enciende y apaga todos los LEDs y suena una melodía
void GAME_OVER()
{
  int i;
  Serial.write(12);
  delay(100);
  Serial.write("GAME OVER");
  delay(100);
  
  for(i=0; i<5; i++)
  {
    analogWrite(LED1, 255);  
    analogWrite(LED2, 255);
    analogWrite(LED3, 255);
    analogWrite(LED4, 255);
    tone(SPK, 512, 400);
    
    delay(100);
    
    analogWrite(LED1, 0);
    analogWrite(LED2, 0);
    analogWrite(LED3, 0);
    analogWrite(LED4, 0);
    
    delay(100);
  }  
  
   delay(2000);
   escribir();
   delay(3000);
   // Se llama a la función escribir
  
   Serial.write(12);
   delay(100);
   Serial.write("Reinicio en: ");
   delay(100);
   // Se borra lo que había en pantalla y se muestra un mensaje en pantalla con
   // una cuenta atrás para el reinicio del programa
   for (i = 3; i>0; i--){
      Serial.print(i);
      delay(1000);
      if (i != 1){
         Serial.write(8); 
         delay(100);
      } 
   }
   puntuacion=0;
}

// Se muestra un mensaje en pantalla con el nivel alcanzado y la puntuación conseguida
void escribir()
{
  Serial.write(12);
  delay(100);
  Serial.write("Nivel : ");
  delay(100);
  Serial.print(nivel-2);
  delay(100);
  
  Serial.write(13);
  delay(100);
  Serial.write("Puntuacion : ");
  delay(100);
  Serial.print(puntuacion);
  delay(100);
}

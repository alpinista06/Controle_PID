 #define COM_MEDIA_MOVEL
//#define FILTRO_ANALOGICO

double P, I = 0, pi = 0;
double erro;
double pot;
double ldr;
double last, delta;
double led = 9;
double fotoresistor = A0;
double potenciometro = A1;


void setup() {
  Serial.begin(115200);
  pinMode(fotoresistor, INPUT);
  pinMode(potenciometro, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  erro = 0;
  pot = 0;
  ldr = 0;

#ifdef COM_MEDIA_MOVEL
  for (int ii = 0; ii < 10; ii++) {
    pot += (double) (analogRead(potenciometro) >> 2) / 10;
    ldr += (double) (analogRead(fotoresistor) >> 2) / 10;
    erro += (pot - ldr) / 10.0;
  }
#endif

#ifdef FILTRO_ANALOGICO
  pot = (analogRead(potenciometro) >> 2);
  ldr = (analogRead(fotoresistor) >> 2);
  erro = pot - ldr;
#endif

  delta = (millis() - last) / 1000.0;
  last = millis();
  P = (erro * 0.3) ;
  I += ((erro * 7) * delta );
  pi = P + I ;


  pi = pi < 0 ? 0 : pi; // se pi<0 ele recebe 0
  pi = pi > 255 ? 255 : pi; // se pi>255 ele recebe 255



  analogWrite(led, pi);

  Serial.print(pot);
  Serial.print(" ");
  Serial.print(ldr);
  Serial.print(" ");
  Serial.print(pi);
  Serial.print(" ");
  Serial.print(erro);
  Serial.print(" ");
  Serial.println(I);


}

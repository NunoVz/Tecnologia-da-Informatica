//Variaveis
int ledpin1 = 6;
int ledpin2 = 7;
int ledpin3 = 8;
int ledpin4 = 9;
int ledpin5 = 10; 
int buttonPin = 5;
int n = 0;
int lastbuttonState= HIGH;
int buttonState;
int num;
unsigned long debounceDelay = 5;
unsigned long lastDebounceTime = 0;
unsigned long resettime= 1000;

//Inicio do Jogo
void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  for (int i=6; i<=10; i++){
    pinMode(i, OUTPUT);}
  pinMode(buttonPin, INPUT_PULLUP);
}


//Jogo
void loop()
{ 
  gera_num();
  unsigned long time = millis();
  Serial.println("Tem 15 segundos para advinhar o numero");
  while((millis() - time) < 15000){
// Debounce
    int reading = digitalRead(buttonPin);
    if (reading != lastbuttonState){
     lastDebounceTime= millis();
       }
    if ((millis()-lastDebounceTime)> debounceDelay){
      if (reading!= buttonState){
        buttonState=reading;
          if (buttonState != HIGH){
            if(n<=31){
              n++;
              Serial.println(n);
            }
            else{
              n=0;
              Serial.println(n);
            }
        }
      }
    }
    // Se premir o botão durante 1 seg da reset
    lastbuttonState=reading;
    if ((millis()-lastDebounceTime)>resettime){
        if (buttonState == LOW){
        n=0;
        Serial.println("O programa vai ser resetado");
        delay(1000);
        loop();
        }
     }
    }
  if(num==(n)){
   Serial.println("Ganhou, congratz!!!!!");
    n=0;
    //Acende as leds de forma sequencial
    for (int i=6; i<=10; i++){
      digitalWrite(i, 1);
      delay(200);
      digitalWrite(i, 0);
      delay(200);
      }
  }
 else{
   Serial.print("Falhou o numero correto era:");
   Serial.print(num);
   Serial.println();
   n=0;
 }
}

//Função que gera um Nº Aleatorio e acende as leds
void gera_num(){
  num=random(1,32);
  digitalWrite(6, num % 2);
  digitalWrite(7, (num >> 1) % 2);
  digitalWrite(8, (num >> 2) % 2);
  digitalWrite(9, (num >> 3) % 2);
  digitalWrite(10, (num >> 4) % 2);
}

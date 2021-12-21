//------------------------------Debounce-------------------------
int lastbuttonState_AND= HIGH;
int lastbuttonState_OR= HIGH;
int lastbuttonState_XOR= HIGH;
unsigned long debounceDelay = 15;
unsigned long lastDebounceTime_AND = 0;
unsigned long lastDebounceTime_OR= 0;
unsigned long lastDebounceTime_XOR = 0;
int buttonState_AND,buttonState_OR,buttonState_XOR;
//--------------------------------Jogo-----------------------------
int numero_random;
int base,target,lido;
int primeiro_bit,segundo_bit;
int o;
String a;
unsigned long time;
unsigned long tempo_de_jogo=60000;

void setup()
{
  Serial.begin(9600);
  for (int i=8; i<=11; i++){
    pinMode(i, OUTPUT);}
  for (int i=2; i<=4; i++){
    pinMode(i, INPUT_PULLUP);}
  instrucoes();
  randomSeed(analogRead(0));
}



void loop(){ 
  //Geração de numeros aleatórios  
  target=gera_num();
  base=gera_num();
  //Operações permitidas
  operacoes();
  //Instruções/Objetivos para o jogo 
  int segundos = tempo_de_jogo/1000;
  //Serial.println("Valor Base:"+String(target, BIN)); ---> No tinkercad o codigo nao corre corretamente usando esta forma de representar o valor target
  Serial.print("Valor Target: ");
  Serial.println(target,BIN);
  //Serial.println(target,BIN);
  Serial.println("Valor Base:"+String(base, BIN));
  Serial.println("Tem " + String(segundos) + " segundos para advinhar o numero");
  Serial.println("Introduza um valor:");
  
  //Condição de tempo
  time = millis();
  while((millis() - time) < tempo_de_jogo){
    luzes();
    ler_serial();
    if (primeiro_bit==1){
      botao_XOR();
    }
    if(segundo_bit==1){
      botao_AND();
    }
    botao_OR();
    //Vitoria
    if(base==target){
     Serial.println("Ganhou, congratz!!!!!");
     delay(2500);
     limpar_serial();
     break;

    }
    
  }
  //Derrota(Acabou o tempo)
  if(base!=target){
    Serial.println("O tempo acabou, better luck next time");
  }     
  delay(2500);
  limpar_serial();
} 


//A cada 1/4 de tempo de jogo que passa uma luz apaga.
void luzes(){
  if ((millis()-time)==100){
    for (int i=8; i<=11; i++){
      digitalWrite(i, 1);}
  }
  if((millis() - time) == (tempo_de_jogo- 1000)){
    digitalWrite(8,0);
  }
  for(int i=1;i<=3;(i++)){
    if((millis() - time) == (tempo_de_jogo *(i*0.25))){
    digitalWrite((12-i),0);
    }
  }
}


//------------Debounce dos botoes e as suas respetivas operações
void botao_AND(){
  int reading_AND = digitalRead(4);
    if (reading_AND != lastbuttonState_AND){
     lastDebounceTime_AND= millis();
       }
    if ((millis()-lastDebounceTime_AND)> debounceDelay){
      if (reading_AND!= buttonState_AND){
        buttonState_AND=reading_AND;
          if (buttonState_AND != HIGH){
            base=base & lido;
            Serial.println("Valor calculado:"+String(base,BIN));
            if(base!= target){
              Serial.println("Introduza um valor:");
            }
        }
      }
    }
    lastbuttonState_AND=reading_AND;
}



void botao_OR(){
  int reading_OR = digitalRead(3);
    if (reading_OR != lastbuttonState_OR){
     lastDebounceTime_OR= millis();
       }
    if ((millis()-lastDebounceTime_OR)> debounceDelay){
      if (reading_OR!= buttonState_OR){
        buttonState_OR=reading_OR;
          if (buttonState_OR != HIGH){
            base=base | lido;
            Serial.println("Valor calculado:"+String(base,BIN));
            if(base!= target){
              Serial.println("Introduza um valor:");
            }
        }
      }
    }
    lastbuttonState_OR=reading_OR;
}


void botao_XOR(){
  int reading_XOR = digitalRead(2);
    if (reading_XOR != lastbuttonState_XOR){
     lastDebounceTime_XOR= millis();
       }
    if ((millis()-lastDebounceTime_XOR)> debounceDelay){
      if (reading_XOR!= buttonState_XOR){
        buttonState_XOR=reading_XOR;
          if (buttonState_XOR != HIGH){
            base=base ^ lido;
            Serial.println("Valor calculado:"+String(base,BIN));
            if(base!= target){
              Serial.println("Introduza um valor:");
            }
        }
      }
    }
    lastbuttonState_XOR=reading_XOR;
}

//-----------------------Função que retorna um numero aleatório
int gera_num(){
  randomSeed(analogRead(0));
  numero_random=random(1,256);
  return numero_random;
}

//-------------Se algo for enviado no Serial monitor vai ser lido e atribuido a uma variavel
void ler_serial(){
  if (Serial.available()>0){
    a= Serial.readStringUntil('\n');
    lido=a.toInt();
    Serial.println("Valor lido:"+String(lido,BIN));
    Serial.println("Prima um operador");
  }
}


void operacoes(){
    o=random(1,4);
    primeiro_bit=bitRead(o,0);
    segundo_bit=bitRead(o,1);
  Serial.print("Operacoes permitidas:");
    if (primeiro_bit==1){
      Serial.print("XOR-VERMELHO, ");
    }
    if (segundo_bit==1){
      Serial.print("AND-AMARELO, ");
    }
    Serial.println("OR-BRANCO");
}
void instrucoes(){
  Serial.println(" -------------------------------------------------------");
  Serial.println("| O jogo consiste em tentar chegar ao valor target|"); 
  Serial.println("|atraves das operacoes disponiveis. Cada luz led        |");
  Serial.println("|representa 1/4 do tempo decorrido, execepto a luz      |");
  Serial.println("|vermelha que se ira apagar quando faltar 1 segundo.    |");
  Serial.println("|------------------------Botoes-------------------------|");
  Serial.println("|AND--->Amarelo   OR--->Branco   XOR--->Vermelho|");
  Serial.println("|-------------------------------------------------------|");
  Serial.println("|O jogo ira comecar dentro de 5 segundos boa sorte.     |");
  Serial.println(" -------------------------------------------------------");
  delay(5000);
}
void limpar_serial(){
  for (int i=0; i<=10; i++){
    Serial.println("\n");}
}

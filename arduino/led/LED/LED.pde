const int BOTAO = 2; 
const int LED =  13; 

int estadoBotao = 0;

void setup() {
  pinMode(LED, OUTPUT);      
  pinMode(BOTAO, INPUT);     
}

void loop(){

  estadoBotao = digitalRead(BOTAO);

  if (estadoBotao == HIGH) {      
    digitalWrite(LED, HIGH);  
  } 
  else {
    digitalWrite(LED, LOW); 
  }
}

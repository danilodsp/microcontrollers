int saida1 = 2; //pino 2 no Arduino
int saida2 = 3; //pino 3 no Arduino
int saida3 = 4; //pino 4 no Arduino

void setup(){
  pinMode(saida1, OUTPUT); //Saída 1
  pinMode(saida2, OUTPUT); //Saída 2
  pinMode(saida3, OUTPUT); //Saída 3
  Serial.begin(9600); //9600bps na serial
}

void loop(){
  // GERANDO AS SAÍDAS
  // Gera a primeira saída (58bits)
  long int num11 = random(67108864,134217728);
  long int num12 = random(67108864,134217728);
  Serial.print(num11,BIN);
  Serial.println(num12,BIN);
  delay(1000);
  // Gera a segunda saída (58bits)
  long int num21 = random(67108864,134217728);
  long int num22 = random(67108864,134217728);
  Serial.print(num21,BIN);
  Serial.println(num22,BIN);
  delay(1000);
  // Gera a terceira saída (58bist)
  long int num31 = random(67108864,134217728);
  long int num32 = random(67108864,134217728);
  Serial.print(num31,BIN);
  Serial.println(num32,BIN);
  delay(1000);
  
  // ---- A partir daqui falta ajustar, está com erros. ----
  
  // CRIPTOGRAFIA
  // Criptografia da primeira saída
  int x=0;
  char num1f[64];
  while(x<58){
    //Equivalente XOR
    char num1f[58] = (!(char(num11,x)) && !(char(num12,x))) || (char(num11,x) && (char(num12,x)));
    x++;
  }
  Serial.println(num1f,BIN);
  
    // Criptografia da segunda saída
  int y=0;
  char num2f[64];
  while(y<58){
    //Equivalente XOR
    char num2f[58] = (!(char(num21,y)) && !(char(num22,y))) || (char(num21,y) && (char(num22,y)));
    y++;
  }
  Serial.println(num2f,BIN);
  
    // Criptografia da terceira saída
  int z=0;
  char num3f[64];
  while(z<58){
    //Equivalente XOR
    char num3f[58] = (!(char(num31,z)) && !(char(num32,z))) || (char(num31,i) && (char(num32,z)));
    z++;
  }
  Serial.println(num3f,BIN);
  
  // SAÍDA
  // Saindo com o primeiro sinal
  x=0
  while(x<58){
    if(num1f[x] == '1'){
      digitalWrite(saida1,HIGH);
    }
    else{
      digitalWrite(saida1,LOW);
    }
    x++;
  }
  while(x<64){ //Incrementa 111111
    digitalWrite(saida1,HIGH);
    x++;
  }
  
  // Saindo com o segundo sinal
  z=0
  while(z<58){
    if(num2f[z] == '1'){
      digitalWrite(saida2,HIGH);
    }
    else{
      digitalWrite(saida2,LOW);
    }
    z++;
  }
  while(z<64){ //Incrementa 111111
    digitalWrite(saida2,HIGH);
    z++;
  }
  
  // Saindo com o terceiro sinal
  y=0
  while(y<58){
    if(num1f[y] == '1'){
      digitalWrite(saida3,HIGH);
    }
    else{
      digitalWrite(saida3,LOW);
    }
    y++;
  }
  while(y<64){ //Incrementa 111111
    digitalWrite(saida3,HIGH);
    y++;
  }
  
}

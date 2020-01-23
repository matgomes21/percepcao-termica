int menu=1;
boolean b1_flag = 1,b2_flag = 1,b1_pressed=0,b2_pressed=0,TC_flag=1;
char T[10];

void escolhaMenu(){
  switch(menu){
    case 1:
      menuInicial();
      break;
    case 2:
      menuTC();
      break;
    case 3:
      menuTeste();
      break;
  }
}

void changeMenu(){
  if(!digitalRead(b1)){
    b1_pressed=1;
  }
  if(!digitalRead(b2)){
    b2_pressed=1;
  }
   if(digitalRead(b1) && b1_pressed && b1_flag)
   {
       b1_pressed = 0;
       menu = 2;    
       b1_flag=0;
       delay(200);
   }
   else if(digitalRead(b1) && b1_pressed && !b1_flag){
       b1_pressed=0;
       menu=1;
       b1_flag=1;
       delay(200);
   }
   if(digitalRead(b2) && b2_pressed && b2_flag){
    b2_pressed=0;
    menu=3;
    b2_flag=0;
    delay(200);
   }
   if(digitalRead(b2) && b2_pressed && !b2_flag){
    b2_pressed=0;
    menu = 1;
    b2_flag=1;
    delay(200);
   }
   escolhaMenu();
}

void menuInicial(){
  u8g.setFont(u8g_font_8x13B);//Determina tamanho da fonte e o "B" coloca em negrito
  u8g.drawStr( 18, 15, "Menu Inicial");//Escreve na tela, parâmetros: posição x, posição y, texto
  u8g.setFont(u8g_font_8x13);//Determina tamanho da fonte
  u8g.drawStr( 5,30,"1.Temp Corporal");
  u8g.drawStr( 5,45,"2.Iniciar Teste");


  
}
// Conecte pino 1 do sensor (esquerda) ao +5V
// Conecte pino 2 do sensor ao pino de dados definido em seu Arduino
// Conecte pino 4 do sensor ao GND
// Conecte o resistor de 10K entre pin 2 (dados) 
// e ao pino 1 (VCC) do sensor
float t;
void readTemperatura() 
{
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else
  {
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
  }
}

void menuTC(){
  if(TC_flag){
    readTemperatura();
    TC_flag = 0;
  }
  u8g.setFont(u8g_font_fub30);
  dtostrf(t,3,1,T);
  u8g.drawStr( 10, 57, T);
}

void menuTeste(){
  if(TC_flag){
    readTemperatura();
    TC_flag=0;
  }
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr( 10, 57, "Teste");
}

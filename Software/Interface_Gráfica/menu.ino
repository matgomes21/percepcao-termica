

int menu=1,first=1;
int test_flag=1;
boolean b1_flag = 1,b2_flag = 1,b1_pressed=0,b2_pressed=0,TC_flag=1,a_pressed=0,a_flag=1;
float t;
float T1,T2,T3;
char T[10];
float TC;

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
    case 4:
      menuIniciarTeste();
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
       TC_flag=1;
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
  digitalWrite(RED_LED_PIN,0);
  digitalWrite(GREEN_LED_PIN,1);
  digitalWrite(BLUE_LED_PIN,0);
  u8g.setFont(u8g_font_8x13B);//Determina tamanho da fonte e o "B" coloca em negrito
  u8g.drawStr( 18, 15, "Menu Inicial");//Escreve na tela, parâmetros: posição x, posição y, texto
  u8g.setFont(u8g_font_8x13);//Determina tamanho da fonte
  u8g.drawStr( 5,30,"1.Temp Corporal");
  u8g.drawStr( 5,45,"2.Iniciar Teste"); 
}


void menuTC(){
  if(TC_flag){
    t = tempSensor.getTemperature();
    TC_flag = 0;
  }
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(55, 15, "TC");
  u8g.setFont(u8g_font_fub30);
  dtostrf(t,3,1,T);
  u8g.drawStr( 5, 57, T);
  u8g.drawCircle(93,35,4);//x,y,radius
  u8g.drawStr( 100,57, "C");
}

void menuTeste(){
  
  if(TC_flag){
    TC_flag=0;
    t = tempSensor.getTemperature();
  }
  u8g.setFont(u8g_font_8x13);
  u8g.drawStr(1, 25, "Aperte acionador");
  u8g.drawStr(1,35,"para iniciar");

  if(!digitalRead(acenador)){
    a_pressed=1;
  }
  if(digitalRead(acenador) && a_pressed && a_flag)
  {
      a_pressed = 0;
      menu = 4;    
      a_flag=0;
      test_flag=1;
      escolhaMenu();
  }  
}

void menuIniciarTeste(){

  if(test_flag==0){

    T1 = t;
    u8g.setFont(u8g_font_fub30);
    dtostrf(T1,3,1,T);
    u8g.drawStr( 10, 57, T);
    u8g.drawCircle(93,35,4);//x,y,radius
    u8g.drawStr( 100,57, "C");
    
    digitalWrite(BLUE_LED_PIN,1);
    digitalWrite(GREEN_LED_PIN,0);
    digitalWrite(RED_LED_PIN,0);
    digitalWrite(BUZZER_PIN,0); 
    
  }
  if(first){
    TC = t;
    first=0;
  }
  
  if(first==0&&test_flag){
    
    digitalWrite(BUZZER_PIN,1);
    digitalWrite(GREEN_LED_PIN,0);
    digitalWrite(RED_LED_PIN, 1);
    digitalWrite(BLUE_LED_PIN,0);
    
    dtostrf(TC,3,1,T);
    u8g.setFont(u8g_font_8x13B);
    u8g.drawStr( 8,15,"TC");
    u8g.setFont(u8g_font_8x13);
    u8g.drawStr( 30, 15, T);
    
    t = tempSensor.getTemperature();
    u8g.setFont(u8g_font_fub30);
    dtostrf(t,3,1,T);
    u8g.drawStr( 5, 57, T);
    u8g.drawCircle(93,35,4);//x,y,radius
    u8g.drawStr( 100,57, "C");

    if(!digitalRead(acenador)){
      test_flag=0;
    }
    
  }
}

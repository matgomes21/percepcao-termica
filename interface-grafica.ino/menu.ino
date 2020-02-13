int menu=1,first=1;
boolean terminar;
boolean b1_flag = 1,b2_flag = 1,b1_pressed=0,b2_pressed=0,TC_flag=1,a_pressed=0,a_flag=1;
float t;
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
    Serial.println("passou");
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
  u8g.setFont(u8g_font_fub30);
  dtostrf(t,3,1,T);
  u8g.drawStr( 10, 57, T);
}

void menuTeste(){
  
  if(TC_flag){
    TC_flag=0;
  }
  u8g.setFont(u8g_font_8x13);
  u8g.drawStr(5, 25, "Pressione acenador");
  u8g.drawStr(5,35,"para iniciar");

  if(!digitalRead(acenador)){
    a_pressed=1;
  }
  if(digitalRead(acenador) && a_pressed && a_flag)
  {
      a_pressed = 0;
      menu = 4;    
      a_flag=0;
      terminar=1;
      escolhaMenu();
  }  
}

void menuIniciarTeste(){
  if(!digitalRead(acenador)){
    terminar=0;
  }
  if(terminar==0){
    u8g.setFont(u8g_font_fub30);
    dtostrf(t,3,1,T);
    u8g.drawStr( 10, 57, T);
    digitalWrite(BLUE_LED_PIN,1);
    digitalWrite(GREEN_LED_PIN,0);
    digitalWrite(RED_LED_PIN,0);
    digitalWrite(BUZZER_PIN,0);
  }
  if(first&&terminar){
    TC = t;
    /*u8g.setFont(u8g_font_fub30);
    dtostrf(t,3,1,T);
    u8g.drawStr( 10, 57, T);*/
    first=0;
  }
  if(first==0&&terminar){
    digitalWrite(BUZZER_PIN,1);
    digitalWrite(GREEN_LED_PIN,0);
    digitalWrite(RED_LED_PIN, 1);
    digitalWrite(BLUE_LED_PIN,0);
    //delay(1000);
    dtostrf(TC,3,1,T);
    u8g.setFont(u8g_font_8x13B);
    u8g.drawStr( 8,15,"TC");
    u8g.setFont(u8g_font_8x13);
    u8g.drawStr( 5, 20, T);
    t++;
    u8g.setFont(u8g_font_fub30);
    dtostrf(t,3,1,T);
    u8g.drawStr( 10, 57, T);
  }
}

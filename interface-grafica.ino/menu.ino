int menu=1,i=0;

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
  if(!digitalRead(b1)==HIGH){
    menu = 2;
    i=1;
  }
  if(!digitalRead(b2)==HIGH){
    menu = 3;
  }
  if(i==1&&!digitalRead(b1)==HIGH){
    menu=1;
    i=0;
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

void menuTC(){
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr( 10, 57, "40C");
}

void menuTeste(){
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr( 10, 57, "Teste");
}

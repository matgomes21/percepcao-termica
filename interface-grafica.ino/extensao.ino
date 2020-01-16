void draw() 
{
  //Comandos graficos para o display devem ser colocados aqui
  //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B);
  //Linha superior - temperatura 
  u8g.drawStr( 5, 15, "23"); //Escrever na tela, parametros: xposition, yposition, text
  u8g.drawCircle(28,8,3);//Desenhar circulo, parametros: xposition, yposition, raio
  u8g.drawStr( 34, 15, "C");
  //Hora
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr( 10, 57, "teste");
  //Texto - AM
  u8g.setFont(u8g_font_5x7);
  u8g.drawStr( 115, 33, "AM");
  //moldura relogio
  u8g.drawRFrame(0,18, 128, 46, 4);//Desenhar retangulos, parametros: xposition, yposition, width, height
  //Desenho bateria
  u8g.drawRFrame(105, 3, 20,12 , 0);
  u8g.drawBox(125, 6, 2,6);
  u8g.drawBox(107, 5, 4,8);
  u8g.drawBox(114, 5, 4,8);
  //Desenho linhas sinal
  u8g.drawVLine(99,0, 15);
  u8g.drawVLine(98,0, 15);
  u8g.drawVLine(96,4, 11);
  u8g.drawVLine(95,4, 11);
  u8g.drawVLine(93,8, 7);
  u8g.drawVLine(92,8, 7);
  u8g.drawVLine(90,12, 3);
  u8g.drawVLine(89,12, 3);
}

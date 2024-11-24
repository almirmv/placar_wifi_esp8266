/* Inicializar a tela */
void display_init(){
  display.init();                 // inicializa comunicacao com tela
  display.flipScreenVertically(); // tela estava invertida
  delay(1000);
  display.clear();
  }


/* Atualiza tela com dados da inicialização da conexao WiFi */
void display_wifi_init(int i){
  display.clear();  
  display.setFont(ArialMT_Plain_10);          // ArialMT_Plain_10, ArialMT_Plain_16, ArialMT_Plain_24
  display.setTextAlignment(TEXT_ALIGN_LEFT);  // TEXT_ALIGN_LEFT, TEXT_ALIGN_CENTER, TEXT_ALIGN_RIGHT, TEXT_ALIGN_CENTER_BOTH
  display.drawString(0, 0, "Iniciando WiFi");
  display.drawString(0, 16, ssid);
  char cstr[16];
  itoa(i, cstr, 10);
  display.drawString(64, 32, cstr);
  display.display();
  }

/* Atualiza tela com os novos dados */
void display_data(){
  if (millis() > refresh_disp_timer) {
    display.clear();  //only clears the internal graphics buffer, which can then be shown on the display with display().
    //display.cls();  //will clear the display immediately and empty the logBuffer, meaning the next print statement will print at the top of the display again.
  
    display.setFont(ArialMT_Plain_10);          // ArialMT_Plain_10, ArialMT_Plain_16, ArialMT_Plain_24
    display.setTextAlignment(TEXT_ALIGN_LEFT);  // TEXT_ALIGN_LEFT, TEXT_ALIGN_CENTER, TEXT_ALIGN_RIGHT, TEXT_ALIGN_CENTER_BOTH
    display.drawString(0, 0, "conectado");
      
    display.setFont(DSEG14_Classic_Regular_27); // seleciona Fonte customizada
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 32, txt_dip);
    //display.println("15x15");
    
    display.display();
    refresh_disp_timer += 1000; 
  }
}

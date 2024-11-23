void startButtons() {
  // entradas
  pinMode(BUT_A_UP_PIN, INPUT);
  pinMode(BUT_A_DOWN_PIN, INPUT);
  pinMode(BUT_B_UP_PIN, INPUT);
  pinMode(BUT_B_DOWN_PIN, INPUT);
  pinMode(BUT_MAIN_PIN, INPUT_PULLUP);
  // saidas
  pinMode(BUZZER_PIN, OUTPUT);
}

void checkButtons() {
  // placar A - incrementar
  if (digitalRead(BUT_A_UP_PIN)) {
    // botao pressioando. Passou o tempo?
    if (millis() > a_up_debounce_timer + DEBOUNCE_TIME) {      
      a_score++;      
      a_up_debounce_timer = millis() + 500;  // caso mantenha pressionado, limta incremento a cada 0,5s
    }
  }else{
    a_up_debounce_timer = millis();   // zera contagem do timer
  }
  // placar A - decrementar
  if (digitalRead(BUT_A_DOWN_PIN)) {
    // botao pressioando. Passou o tempo?
    if (millis() > a_down_debounce_timer + DEBOUNCE_TIME) {
      if (a_score > 0) {
        a_score--;
      }
      a_down_debounce_timer = millis() + 1000;  // caso mantenha pressionado, limta incremento a cada 1s
    }
  }else{
    a_down_debounce_timer = millis();   // zera contagem do timer
  }
  // placar B - incrementar
  if (digitalRead(BUT_B_UP_PIN)) {
    // botao pressioando. Passou o tempo?
    if (millis() > b_up_debounce_timer + DEBOUNCE_TIME) {      
      b_score++;      
      b_up_debounce_timer = millis() + 500;  // caso mantenha pressionado, limta incremento a cada 0,5s
    }
  }else{
    b_up_debounce_timer = millis();   // zera contagem do timer
  }
  // placar B - decrementar
  if (digitalRead(BUT_B_DOWN_PIN)) {
    // botao pressioando. Passou o tempo?
    if (millis() > b_down_debounce_timer + DEBOUNCE_TIME) {
      if (b_score > 0) {
        b_score--;
      }
      b_down_debounce_timer = millis() + 1000;  // caso mantenha pressionado, limta incremento a cada 1s
    }
  }else{
    b_down_debounce_timer = millis();   // zera contagem do timer
  }

  // botao inverter placar / zerar placar (segurar 3s)
  if (!digitalRead(BUT_MAIN_PIN)) {
    // acima de 3s pressionando? Zerar placar!
    if (millis() > but_main_debounce_timer + 3000) {
      a_score = 0;
      b_score = 0;
      but_main_debounce_timer = millis();   // zera contagem do timer
    }
    // ainda abaixo de 3s. Já esta pressionado entre 30ms e 40ms?
    else if (millis() > but_main_debounce_timer + DEBOUNCE_TIME && millis() < but_main_debounce_timer + DEBOUNCE_TIME + 10) {
      int buffer = b_score;   // copia b_score
      b_score = a_score;      // b recebe a
      a_score = buffer;       // a recebe copia de b
      delay(15); // evitar executar novamente este if
    }   
  }else{
    but_main_debounce_timer = millis();   // zera contagem do timer
  }
}



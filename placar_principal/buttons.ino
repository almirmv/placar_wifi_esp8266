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
  if (digitalRead(BUT_A_UP_PIN)) {
    // botao pressioando. Passou o tempo?
    if (millis() > a_up_debounce_timer + DEBOUNCE_TIME) {      
      a_score++;      
      a_up_debounce_timer = millis() + 500;  // caso mantenha pressionado, limta incremento a cada 0,5s
    }
  }else{
    a_up_debounce_timer = millis();   // zera contagem do timer
  }

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

  if (digitalRead(BUT_B_UP_PIN)) {
    // botao pressioando. Passou o tempo?
    if (millis() > b_up_debounce_timer + DEBOUNCE_TIME) {      
      b_score++;      
      b_up_debounce_timer = millis() + 500;  // caso mantenha pressionado, limta incremento a cada 0,5s
    }
  }else{
    b_up_debounce_timer = millis();   // zera contagem do timer
  }

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
}
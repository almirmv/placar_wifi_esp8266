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
      sound_num = 1;  // avisar para tocar som 1 no receptor
      a_up_debounce_timer = millis() + 1000;  // caso mantenha pressionado, limta incremento a cada 1s
      tone(BUZZER_PIN, 300, 500);
      delay(500);
      tone(BUZZER_PIN, 400, 500);
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
        sound_num = 2;  // avisar para tocar som 2 no receptor
        tone(BUZZER_PIN, 400, 500);
        delay(500);
        tone(BUZZER_PIN, 300, 500);
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
      sound_num = 3;  // avisar para tocar som 3 no receptor
      tone(BUZZER_PIN, 500, 500);
      delay(500);
      tone(BUZZER_PIN, 600, 500);  
      b_up_debounce_timer = millis() + 1000;  // caso mantenha pressionado, limta incremento a cada 1s
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
        sound_num = 4;  // avisar para tocar som 4 no receptor
        tone(BUZZER_PIN, 600, 500);
        delay(500);
        tone(BUZZER_PIN, 500, 500);
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
      sound_num = 5;  // avisar para tocar som 5 no receptor
      but_main_debounce_timer = millis();   // zera contagem do timer
    }
    // ainda abaixo de 3s. Já esta pressionado entre 30ms e 40ms?
    else if (millis() > but_main_debounce_timer + DEBOUNCE_TIME && millis() < but_main_debounce_timer + DEBOUNCE_TIME + 10) {
      int buffer = b_score;   // copia b_score
      b_score = a_score;      // b recebe a
      a_score = buffer;       // a recebe copia de b
      sound_num = 5;          // avisar para tocar som 6 no receptor
      tone(BUZZER_PIN, 400, 500);
      delay(250);
      tone(BUZZER_PIN, 600, 500);
      delay(250);
      tone(BUZZER_PIN, 500, 500);
      delay(250);
      //delay(15); // evitar executar novamente este if
    }   
  }else{
    but_main_debounce_timer = millis();   // zera contagem do timer
  }
}



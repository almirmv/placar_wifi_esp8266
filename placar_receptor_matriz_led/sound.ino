void playSound(){
  switch (sound_num_str.toInt()){
    case 1:
      // score A++
      tone(BUZZER_PIN, 300, 500);
      delay(500);
      tone(BUZZER_PIN, 400, 500);
      break;
    case 2:
      // score A--
      tone(BUZZER_PIN, 400, 500);
      delay(500);
      tone(BUZZER_PIN, 300, 500);
      break;
    case 3:
      // score B++
      tone(BUZZER_PIN, 500, 500);
      delay(500);
      tone(BUZZER_PIN, 600, 500);
      break;
    case 4:
      // score B--
      tone(BUZZER_PIN, 600, 500);
      delay(500);
      tone(BUZZER_PIN, 500, 500);
      break;
    case 5:
      // inverter placar ou zerar
      tone(BUZZER_PIN, 400, 500);
      delay(250);
      tone(BUZZER_PIN, 600, 500);
      delay(250);
      tone(BUZZER_PIN, 500, 500);
      delay(250);
      break;
    default:
      break;
  }
}
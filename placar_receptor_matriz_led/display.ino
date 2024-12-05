/*
FUNCOES PARA CONTROLE DO DISPLAY COM MAX7219
*/

// Variáveis dos números que serão exibidos na Matriz de Led
// char '0'
byte n0[8] = {
  B00111100,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B00111100,
  };
// char '1'
byte n1[8] = {
  B00111100,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011100,
  B00011000,
  };
// char '2'
byte n2[8] = {
  B01111110,
  B01100110,
  B00001100,
  B00011000,
  B00110000,
  B01100000,
  B01100110,
  B00111100,
  };
// char '3'
byte n3[8] = {
  B00111100,
  B01100110,
  B01100000,
  B01100000,
  B00111000,
  B01100000,
  B01100110,
  B00111100,
  };
// char '4'
byte n4[8] = {
  B11110000,
  B01100000,
  B01100000,
  B01111110,
  B01100110,
  B01101100,
  B01111000,
  B01110000,
  };

byte n5[8] = {
  B00111100,   // 5
  B01100110,
  B01100000,
  B01100000,
  B00111110,
  B00000110,
  B00000110,
  B01111110,
  };

byte n6[8] = {
  B00111100,   // 6
  B01100110,
  B01100110,
  B01100110,
  B00111110,
  B00000110,
  B00001100,
  B00111000,
  };

byte n7[8] = {
  B00011000,   // 7
  B00011000,
  B00011000,
  B00011000,
  B00110000,
  B01100000,
  B01100110,
  B01111110,
  };
// char '8'
byte n8[8] = {
  B00111100,
  B01100110,
  B01100110,
  B01100110,
  B00111100,
  B01100110,
  B01100110,
  B00111100,
  };
// char '9'
byte n9[8] = {
  B00011100,
  B00110000,
  B01100000,
  B01111100,
  B01100110,
  B01100110,
  B01100110,
  B00111100,
  };
// char espaço (leds apagados)
byte char_space[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
  };


void startDisplay(){
  ledMatrix.shutdown(0, false);
  ledMatrix.setIntensity(0, 1);
  ledMatrix.clearDisplay(0);

  ledMatrix.shutdown(1, false);
  ledMatrix.setIntensity(1, 1);
  ledMatrix.clearDisplay(1);

  ledMatrix.shutdown(2, false);
  ledMatrix.setIntensity(2, 1);
  ledMatrix.clearDisplay(2);

  ledMatrix.shutdown(3, false);
  ledMatrix.setIntensity(3, 1);
  ledMatrix.clearDisplay(3);
}

// Atualiza display com o placar atual
void updateDisplay(){
  String a_score_str = String(a_score);
  String b_score_str = String(b_score);
  
  //Imprime na Matriz de Led o placar A
  if(a_score < 10){
    printCharDisp(0, a_score_str[1]); // escolhe modulo 0 do display e manda imprimir char
    printCharDisp(1, a_score_str[0]); 
  }else{
    printCharDisp(0, a_score_str[0]); 
    printCharDisp(1, a_score_str[1]); 
  }
  
  //Imprime na Matriz de Led o placar B
  if (b_score < 10) {
    printCharDisp(2, b_score_str[1]); 
    printCharDisp(3, b_score_str[0]); 
  }else{
    printCharDisp(2, b_score_str[0]); 
    printCharDisp(3, b_score_str[1]);
  }
}

void printCharDisp(int module_num, char disp_char) {
  switch (disp_char) {
    case '0':
      modulePrint(module_num, n0);
      break;
    case '1':
      modulePrint(module_num, n1);
      break;
    case '2':
      modulePrint(module_num, n2);
      break;
    case '3':
      modulePrint(module_num, n3);
      break;
    case '4':
      modulePrint(module_num, n4);
      break;
    case '5':
      modulePrint(module_num, n5);
      break;
    case '6':
      modulePrint(module_num, n6);
      break;
    case '7':
      modulePrint(module_num, n7);
      break;
    case '8':
      modulePrint(module_num, n8);
      break;
    case '9':
      modulePrint(module_num, n9);
      break;
    default:
      modulePrint(module_num, char_space);
      break;
  }
}

// Envia para modulo especifico do display o char_vector escolhido
void modulePrint(int module_num, byte char_vector[]) {
  byte row_buffer = 0;  
  int row = 0;
  for (row = 0; row < 8; row++){
    row_buffer = char_vector[row];    // get row
    //Se module_num for 1 ou 3 (segundo ou quarto bloco), fazemos shift
    // de 1 led neles para deixar números mais juntos e o visual ficar melhor
    if (module_num == 3 || module_num == 1){      
      row_buffer >>= 1;             // shift 1 col
    }
    ledMatrix.setRow(module_num, row, row_buffer);
  }
}
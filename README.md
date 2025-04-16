# placar_wifi_esp8266
 Placar para contagem de pontuação de jogos.

 Placar "Princicpal" possui Display de Matriz de LED (max7219) e microcontrolador ESP8266.
 Pode ser acessado por celular através do wifi. "http://192.168.4.1"

 Placar "Receptor", opcional, possui ESP8266 e duas opções de DISPLAY:
  - Tela 0.96 polegadas SD1306 de OLED.
  - Display de Matriz de LED (max7219) https://github.com/MajicDesigns/MD_MAX72XX

  Display inferior é o Principal. O display Superior é um receptor que faz o espelhamento do placar principal.
![Foto com dois displays max7219, Principal e Receptor](https://github.com/almirmv/placar_wifi_esp8266/blob/main/principal_e_receptor.png)
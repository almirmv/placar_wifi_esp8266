/***************************************************************************
PLACAR PARA CONTROLE DE PONTUAÇÃO DE JOGOS
dev: Almir M Ventura, data inicio: 19/11/2024
DESCRIÇÃO:
Receptor WIFI para o placar principal. Possui tela 0.96 polegadas SD1306 de OLED,
sem retroiluminacao, conectada nos pinos SDA (D6/GPIO14) e SCL (D5/GPIO12).
Conecta pelo wifi no placar principal, puxar os dados e mostra no visor.
Bibliotecas:
* display nome: "ESP8266 and ESP32 Oled Driver for SSD1306 display"
* display github: https://github.com/ThingPulse/esp8266-oled-ssd1306
***************************************************************************/
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"
#include <ESP8266WiFi.h>
#include "DSEG14_Classic_Regular_27.h"  // inclui a fonte customizada no sketch


//CONSTANTES
#define OLED_SDA        14    // (D6/GPIO14)
#define OLED_SCL        12    // (D5/GPIO12)
#define SCREEN_ADDRESS  0x3C  // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SCREEN_WIDTH    128   // OLED display width, in pixels
#define SCREEN_HEIGHT   64    // OLED display height, in pixels
#define INTERVAL        3000  // Intervalo entre atualizaçoes de placar e tela (em ms)
#define STASSID         "Placar WiFi"
#define STAPSK          "thereisnospoon"
#define PORT            80
const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "192.168.4.1"; // 192.168.4.1 (this is the default IP address of our ESP AP)

String url = "/get/placar";

//VARIAVEIS
String http_response = "";
String txt_dip = "..x..";
unsigned long refresh_disp_timer = millis();
unsigned long refresh_http_timer = millis();
//INSTANCIANDO OBJETOS
SSD1306Wire display(SCREEN_ADDRESS, OLED_SDA, OLED_SCL);
WiFiClient wifi_client;


// SETUP ====================================================
void setup(){
  Serial.begin(115200); // inicializa Serial
  display_init();       // inicializa display
  wifi_init();          // inicializa WiFi 
}


// LOOP ====================================================
void loop(){
  wifi_get_data();
  display_data();
}

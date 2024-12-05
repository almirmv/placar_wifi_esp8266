/***************************************************************************
PLACAR PARA CONTROLE DE PONTUAÇÃO DE JOGOS
dev: Almir M Ventura, data inicio: 19/11/2024
DESCRIÇÃO:
Receptor WIFI para o placar principal. Possui tela 0.96 polegadas SD1306 de OLED,
sem retroiluminacao, conectada nos pinos SDA (D6/GPIO14) e SCL (D5/GPIO12).
Conecta pelo wifi no placar principal, puxar os dados e mostra no visor.
Bibliotecas:
* Display: https://github.com/MajicDesigns/MD_MAX72XX
HARDWARE:
* NodeMCU 1.0 (ESP-12E Module)
* Display matriz de leds com 4 modulos (max7219)
***************************************************************************/
#include <ESP8266WiFi.h>
#include <LedControl.h>         // biblioteca para o display


//CONSTANTES
#define DISP_CLK_PIN    D1    // pino de clock do display
#define DISP_DIN_PIN    D2    // pino de entrada de dados (Data In)
#define DISP_CS_PIN     D0    // pino de seleçao de display (Chip Select)
#define DISP_MODULES    4     // numero de matrizes de LED do display
#define INTERVAL        3000  // Intervalo entre atualizaçoes de placar e tela (em ms)
#define STASSID         "Placar WiFi"     // SSID do placar principal
#define STAPSK          "thereisnospoon"  // senha do placar principal
#define PORT            80
const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "192.168.4.1"; // 192.168.4.1 (this is the default IP address of our ESP AP)
String url = "/get/placar";

//VARIAVEIS
byte dig0 = 0x0;
byte dig1 = 0x0;
byte dig2 = 0x0;
byte dig3 = 0x0;
int a_score = 0;
int b_score = 0;
String http_response = "";
String a_score_str = "";    // valor de a durante a requisicao. Pode mudar no meioa da requisicao
String b_score_str = "";
unsigned long refresh_disp_timer = millis();
unsigned long refresh_http_timer = millis();

//INSTANCIANDO OBJETOS
LedControl ledMatrix = LedControl(DISP_DIN_PIN, DISP_CLK_PIN, DISP_CS_PIN, DISP_MODULES);
WiFiClient wifi_client;


// SETUP ====================================================
void setup(){
  Serial.begin(115200); // inicializa Serial
  startDisplay();       // inicializar display led matricial
  startWifi();          // inicilizar e conectar ao Ponto de Acesso (AP)
}


// LOOP ====================================================
void loop(){
  wifi_get_data();    // captura novos valores do outro placar
  updateDisplay();    // mostra novos valores no display
}


/************************************************************
PLACAR PARA CONTROLE DE PONTUAÇÃO DE JOGOS
dev: Almir M Ventura, data inicio: 19/11/2024
funcionamento: Placar principal recebe comandos por um controle remoto
rf433MHz para aumentar ou reduriz pontuação. Marcador possui placar para
dois times. Este placar feito com EESP8266 possui wifi e a pontuação pode
ser visualizada por celular ou pelo receptor personalizado com tela oled.
Placar principal possui botoes fisicos para aumentar ou reduzir pontuação.
Possui mostrador com CI max7219 e 4 matrizes de LED
BIBLIOTECAS:
Display: https://github.com/MajicDesigns/MD_MAX72XX
Websockets: https://github.com/gilmaimon/ArduinoWebsockets

ESP8266 ----------------------------
D0	GPIO16	no interrupt	no PWM or I2C support	HIGH at boot used to wake up from deep sleep
D1	GPIO5	OK	OK	often used as SCL (I2C)
D2	GPIO4	OK	OK	often used as SDA (I2C)
D3	GPIO0	pulled up	OK	connected to FLASH button, boot fails if pulled LOW
D4	GPIO2	pulled up	OK	HIGH at boot connected to on-board LED, boot fails if pulled LOW
D5	GPIO14	OK	OK	SPI (SCLK)
D6	GPIO12	OK	OK	SPI (MISO)
D7	GPIO13	OK	OK	SPI (MOSI)
D8	GPIO15	pulled to GND	OK	SPI (CS) Boot fails if pulled HIGH
RX	GPIO3	OK	RX pin	HIGH at boot
TX	GPIO1	TX pin	OK	HIGH at boot debug output at boot, boot fails if pulled LOW
A0	ADC0	Analog Input	X
************************************************************/

// INCLUDES
#include <ESP8266WiFi.h>        // biblioteca para o WiFi
#include <LedControl.h>         // biblioteca para o display
//#include <MD_MAX72xx.h>       // biblioteca para o display
//#include <ArduinoWebsockets.h>  // biblioteca para conexoes websocket
#include <ESP8266WebServer.h>   // biblioteca para servidor http

//#include <ESP8266mDNS.h>
//#include <FS.h>

//using namespace websockets;
// CONSTANTES
#define BUZZER_PIN      D0  // pino conectado ao buzzer
#define BUT_MAIN_PIN    D4  // pino para alternar placar ou zerar
#define BUT_A_UP_PIN    D5  // pino para aumentar placar A
#define BUT_A_DOWN_PIN  D6  // pino para diminuir placar A
#define BUT_B_UP_PIN    D7  // pino para aumentar placar B
#define BUT_B_DOWN_PIN  D8  // pino para diminuir placar B

#define DISP_CLK_PIN    D1  // pino de clock do display
#define DISP_DIN_PIN    D2  // pino de entrada de dados (Data In)
#define DISP_CS_PIN     D3  // pino de seleçao de display (Chip Select) D0

#define DEBOUNCE_TIME   30  // 30ms de debounce dos botoes
#define DISP_MODULES    4   // numero de matrizes de LED do display
//#define DISP_TYPE MD_MAX72XX::GENERIC_HW
const char *ssid = "Placar WiFi";         // Nome da rede WiFi que sera criada
const char *password = "thereisnospoon";  // Senha da rede, deixar em branco para acesso sem senha

// VARIAVEIS
//byte zero = B00000000;
byte dig0 = 0x0;
byte dig1 = 0x0;
byte dig2 = 0x0;
byte dig3 = 0x0;
byte sound_num = 0;   // aponta para qual som deve ser tocado no receptor
int a_score = 0;
int b_score = 0;
unsigned long a_up_debounce_timer = 0;
unsigned long a_down_debounce_timer = 0;
unsigned long b_up_debounce_timer = 0;
unsigned long b_down_debounce_timer = 0;
unsigned long but_main_debounce_timer = 0;


// INSTANCIAS DE OBJETOS
LedControl ledMatrix = LedControl(DISP_DIN_PIN, DISP_CLK_PIN, DISP_CS_PIN, DISP_MODULES);
ESP8266WebServer server(80);       // Create a webserver object that listens for HTTP request on port 80
//WebSocketsServer socketServer(81);    // padrao porta 81. Criar websocket server


// SETUP ====================================================
void setup() {
  Serial.begin(115200); // inicilizar serial, apenas debug
  Serial.println("");   // pular linha no inicio
  delay(200);
  startButtons();       // inicializar botoes
  startDisplay();       // inicializar display led matricial
  startWifi();          // inicilizar o Ponto de Acesso (AP)
  startWebserver();     // inicilizar o webserver (para responder requisicoes)
  //startWebSocket();
}


// LOOP =====================================================
void loop() {
  checkButtons();
  updateDisplay();
  //updateWebSocket();
  server.handleClient(); // Listen for HTTP requests from clients  
}

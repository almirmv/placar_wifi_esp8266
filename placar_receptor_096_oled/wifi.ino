/*Configuraçoes e funçoes relativas a WiFi*/


//CONFIGURAÇÕES DO WIFI
void wifi_init(){
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);          // configurando como cliente WiFi
  WiFi.begin(ssid, password);   // tentar conectar no AP com SSID e a senha

  int i = 0;
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");    
    display_wifi_init(i); // passa contagem segundos tentanto conectar
    i++;
    }

  Serial.println("");
  Serial.println("WiFi Conectado. IP:");
  Serial.println(WiFi.localIP());
  }

void wifi_get_data(){
  if (millis() > refresh_http_timer) {
    refresh_http_timer += 1000;   // zera contagem para proxima requisicao
    http_response = "";           // zera resposta anterior
    // encerar qualquer conexao antes de iniciar nova    
    wifi_client.stop();  // This will free the socket on the WiFi shield
    
    // criar conexao com webserver
    if (!wifi_client.connect(host, PORT)) {
      Serial.println("[WEB] conexao com o host falhou.");
      return;
    }
  // enviar pedido ao websrver
  String request = "GET " + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n";
  Serial.println("[WEB] GET...");
  Serial.println(request);
  wifi_client.print(request);
  
  }
  // esperando e processando resposta
  if (wifi_client.available()){
    // enquanto houver dados salva em response
    while (wifi_client.available()) {
      char c = wifi_client.read();
      http_response += c;
    }
    //Serial.println("[HTTP response]:");
    //Serial.println(http_response);
    String txt_json = http_response.substring(http_response.indexOf("{") ); // separa a parte {'a':0,'b':0}
    String a_score_str = txt_json.substring(txt_json.indexOf("a':")+3, txt_json.indexOf(","));
    String b_score_str = txt_json.substring(txt_json.indexOf("b':")+3, txt_json.indexOf("}"));
    //Serial.print("JSON ");
    //Serial.println(txt_json);
    //Serial.print("A ");
    //Serial.print(a_score_str);
    //Serial.print("B ");
    //Serial.println(b_score_str);
    txt_dip = a_score_str + "x" + b_score_str;
  }
}
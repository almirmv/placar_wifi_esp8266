/*Configuraçoes e funçoes relativas a WiFi*/


//CONFIGURAÇÕES DO WIFI
void startWifi(){
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);          // configurando como cliente WiFi
  WiFi.begin(ssid, password);   // tentar conectar no AP com SSID e a senha

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
    // vamos usar o display para mostrar tempo ate conectar
    a_score++;
    b_score++;          
    updateDisplay();    // passa contagem segundos tentanto conectar
    }

  Serial.println("");
  Serial.println("WiFi Conectado. IP:");
  Serial.println(WiFi.localIP());
  //voltar os scores para zero
  a_score = 0;
  b_score = 0;
  }

void wifi_get_data(){
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
    a_score_str = txt_json.substring(txt_json.indexOf("a':")+3, txt_json.indexOf(","));
    b_score_str = txt_json.substring(txt_json.indexOf("b':")+3, txt_json.indexOf("}"));
    //Serial.print("RESPONSE:");
    //Serial.println(txt_json);
    //Serial.print("A:");
    //Serial.println(a_score_str);   
    //Serial.print("B:");
    //Serial.println(b_score_str);
      
  }

  // ja pode fazer nova requisicao?
  if (millis() > refresh_http_timer) {
    // vamos atualizar o display agora para ter certeza que todos os dados ja chegaram
    //score_str fica instavel enquanto nao chegar todos os dados da request
    a_score = a_score_str.toInt();  // converter de string para inteiro
    b_score = b_score_str.toInt();  // neste momento ja passou 1 seg. b_score_str ja deve ter o valor final

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
  Serial.println("---------------------");
  wifi_client.print(request);  
  }
}
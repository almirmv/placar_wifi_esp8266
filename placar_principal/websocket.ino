

// Iniciar o servidor de WebSocket
void startWebSocket() {
  socketServer.listen(81);
  Serial.print("Is server live? ");
  Serial.println(socketServer.available()); 
  //webSocket.begin();                          // start the websocket server
  //webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("[WebSocket server] started.");
}

// Processar comunicaçao por webSocket
void updateWebSocket() {
  auto client = socketServer.accept();
  if(client.available()) {
    auto msg = client.readBlocking();

    // log
    Serial.print("Got Message: ");
    Serial.println(msg.data());

    // return echo
    client.send("Echo: " + msg.data());

    // close the connection
    client.close();
  }
}
/*

// Processar eventos de websocket
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
  // When a WebSocket message is received
  switch (type) {
    
    // if the websocket is disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    
    // if a new websocket connection is established
    case WStype_CONNECTED: {              
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      rainbow = false;                  // Turn rainbow off when a new connection is established
      }
      break;
    
    // if new text data is received
    case WStype_TEXT:                     
      Serial.printf("[%u] get Text: %s\n", num, payload);
      if (payload[0] == '#') {            // we get RGB data
        uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);   // decode rgb data
        int r = ((rgb >> 20) & 0x3FF);                     // 10 bits per color, so R: bits 20-29
        int g = ((rgb >> 10) & 0x3FF);                     // G: bits 10-19
        int b =          rgb & 0x3FF;                      // B: bits  0-9

        analogWrite(LED_RED,   r);                         // write it to the LED output pins
        analogWrite(LED_GREEN, g);
        analogWrite(LED_BLUE,  b);
      } else if (payload[0] == 'R') {                      // the browser sends an R when the rainbow effect is enabled
        rainbow = true;
      } else if (payload[0] == 'N') {                      // the browser sends an N when the rainbow effect is disabled
        rainbow = false;
      }
      break;
  }
}
*/
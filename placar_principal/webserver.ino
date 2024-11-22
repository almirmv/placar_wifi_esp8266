
// registra rotas e suas funcoes de tratamento
void startWebserver() {
  Serial.print("[WEBSERVER] iniciando...");
  server.on("/", handleRoot);                 // chama funcao 'handleRoot' quando cliente pedir URL "/"  
  server.on("/get/placar", handleGetPLacar);  // chama funcao 'handleGetPLacar' quando cliente pedir URL "/"
  server.onNotFound(handleNotFound);          // se cliente pedir URL nao listada responde com um 404
  server.begin();                             // inicia o webserver
  Serial.println("Concluido!");
}

void handleRoot() {
  //String placar = "";
  server.send(200, "text/plain", "{'a':" + String(a_score) + ",'b':" + String(b_score) + "}");   // Send HTTP status 200 (Ok) and send some text to the browser/client
  Serial.println("[WEBSERVER] '/'");
}

void handleGetPLacar() {
  server.send(200, "application/json", "{'a':" + String(a_score) + ",'b':" + String(b_score) + "}");   // Send HTTP status 200 (Ok) and send some text to the browser/client
  Serial.println("[WEBSERVER] '/get/placar'");
}

// nao encontrou o endereco...
void handleNotFound(){
  server.send(404, "text/plain", "404: deu ruim...nao encontrei =p"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
  Serial.println("[WEBSERVER] 404");
}


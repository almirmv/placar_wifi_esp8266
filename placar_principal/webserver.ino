
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
  String html = "";
  html += "<!DOCTYPE html><html lang='pt-br'><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Placar Wifi</title>";
  html += "<style>.center{display:flex;justify-content:center;align-items:center;height: 200px;border: 3px solid green;font-size: 135px;}</style>";
  html += "</head><body><div class='center'>";
  html += String(a_score) + "x" + String(b_score);
  html += "</div></body></html>";

  server.send(200, "text/html", html);   // HTTP status 200 (Ok) e HTML para browser/client
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


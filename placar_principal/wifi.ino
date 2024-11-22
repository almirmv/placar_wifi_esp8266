
void startWifi() {
  delay(1000);
  Serial.print("[WIFI] iniciando...");
  WiFi.softAP(ssid, password);
  //192.168.4.1 (this is the default IP address of our ESP AP).
  Serial.print(ssid);
  Serial.println(" Iniciado!");
  Serial.print("[Wifi] IP: ");
  Serial.println(WiFi.softAPIP() );         // Send the IP address of the ESP8266 to the computer
}
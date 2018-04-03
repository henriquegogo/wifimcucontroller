#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

#define LED_BUILTIN 2

const char *ssid = "NodeMCU";
const char *password = "nodepass";

ESP8266WebServer server(80);

void LEDon() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  server.send(200, "text/html", "<h1>LED Switch</h1><button onclick='location.href=\"/off\"'>Turn OFF</button>");
}

void LEDoff() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  server.send(200, "text/html", "<h1>LED Switch</h1><button onclick='location.href=\"/on\"'>Turn ON</button>");
}

void setup() {
	delay(1000);
	Serial.begin(115200);

	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("IP: ");
	Serial.println(myIP);

	server.on("/", LEDoff);
  server.on("/on", LEDon);
  server.on("/off", LEDoff);
	server.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
	server.handleClient();
}

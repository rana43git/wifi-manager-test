#include <Arduino.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "wifiAutomation.h"
#include "index.h"

ESP8266WebServer server(80);

void routerSetUp() {
  server.close();
  Serial.println("");
  Serial.println("HTTP Server Stopped!");
  WiFiManager wmOnDemand;
  wmOnDemand.setConfigPortalTimeout(120);
  wmOnDemand.startConfigPortal(); // auto generated AP name from chipid
  /*Although startConfigPortal() started devide is still connected to the router if wifi availavble.*/
  Serial.println("<<Restarting the ESP>>");
  ESP.restart(); //remove this line and check if every thing still works.
}

void initWiFiAutomation() {
  Serial.begin(115200);
  delay(100);
  pinMode(LED_BUILTIN, OUTPUT);
  
  WiFiManager wm;
  
  bool res;
  res = wm.autoConnect();

  if (!res) {
    Serial.println("Failed to Connect!");
  } else {
    Serial.println("Connected...");
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED On
  }
    server.on("/", []() {
    server.send_P(200, "text/html", INDEX);
  });

  server.on("/router_setup", routerSetUp);

  server.begin();
  Serial.println("");
  Serial.println("HTTP Server Started!");
  
  if (MDNS.begin("esp8266")) {
    Serial.println("\nMDNS responder started at http://esp8266.local");
  }
}

void checkWiFiAutomationStatus(){
    if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Disconnected");
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED Off
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("Connected...");
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED On
    }
  }

  MDNS.update();
  server.handleClient();
}
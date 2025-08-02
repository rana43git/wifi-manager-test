#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Include the header files
#include "index.h"
#include "a_html.h"
#include "b_html.h"

ESP8266WebServer server(80);

void routerSetUp() {
  server.close();
  Serial.println("");
  Serial.println("HTTP Server Stopped!");
  WiFiManager wmOnDemand;
  wmOnDemand.setConfigPortalTimeout(120);
  //wmOnDemand.startConfigPortal(); // auto generated AP name from chipid
  wmOnDemand.startConfigPortal("ESP_E153C6", "admin1234");  // password protected ap
  /*Although startConfigPortal() started devide is still connected to the router if wifi availavble.*/
  //wmOnDemand.resetSettings(); //wipe stored credentials
  Serial.println("<<Restarting the ESP>>");
  ESP.restart(); //remove this line and check if every thing still works.
}

void setup() {
  // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // it is a good practice to make sure your code sets wifi mode how you want it.

  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  // wm.resetSettings();

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result

  bool res;
  //res = wm.autoConnect();  // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  //res = wm.autoConnect("AutoConnectAP", "password");  // password protected ap
  res = wm.autoConnect("ESP_E153C6", "admin1234");  // password protected ap

  if (!res) {
    Serial.println("Failed to Connect!");
    // ESP.restart();
  } else {
    //if you get here you have connected to the WiFi
    Serial.println("Connected...");
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on (Note that LOW is the voltage level
  }

  server.on("/", []() {
    server.send_P(200, "text/html", INDEX);
  });

  server.on("/a.html", []() {
    server.send_P(200, "text/html", A_HTML);
  });

  server.on("/b.html", []() {
    server.send_P(200, "text/html", B_HTML);
  });

  server.on("/router_setup", routerSetUp);

  server.begin();
  Serial.println("");
  Serial.println("HTTP Server Started!");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Disconnected");
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("Connected...");
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on (Note that LOW is the voltage level
    }
  }

  server.handleClient();
  // put your main code here, to run repeatedly:
}
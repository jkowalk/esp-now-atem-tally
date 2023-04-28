
#include "configWebserver.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <EEPROM.h>

#include "memory.h"
#include "leds.h"

const String ssid = "ESP-NOW Tally";
const String password = "";

ESP8266WebServer server(80);
DNSServer dnsServer;

IPAddress local_IP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

const String html[2] = {
    "<html>\
      <head>\
      <title>ESP NOW Tally</title>\
      <style>\
      body { background-color: #e6e5df; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; display: flex; justify-content: center; margin-top: 4rem; }\
      form { display: flex; }\
      .container { display: flex; flex-direction: column; align-items: center; }\
      </style>\
      </head>\
      <body>\
      <div class=\"container\">\
      <h1>Set camera id:</h1><br>\
      <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/set-camera-id/\">\
      <input type=\"number\" name=\"camera-id\" value=\"",
    "\"><br>\
      <input type=\"submit\" value=\"Send\">\
      </form>\
      </div>\
      </body>\
      </html>"};

void handleRoot()
{
  server.send(200, "text/html", html[0] + String(camId) + html[1]);
}

void handleConfig()
{
  if (server.method() != HTTP_POST)
  {
    server.send(405, F("text/plain"), F("Method Not Allowed"));
    return;
  }

  String cameraId = server.arg("camera-id");
  camId = cameraId.toInt();
  Serial.println("Camera ID set to: " + cameraId);

  saveCameraId();

  String message = "Camera ID set to: " + cameraId;
  message += "\n Device will reboot now.";
  server.send(200, "text/html", message);

  delay(1000);

  ESP.restart();
}

void startConfigWebserver()
{
  WiFi.mode(WIFI_AP);
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(ssid + " (" + String(camId) + ")", password) ? "Ready" : "Failed!");

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  /* Setup the DNS server redirecting all the domains to the apIP */
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(53, F("*"), WiFi.softAPIP());

  Serial.println("Connect to WiFi network with SSID: " + String(ssid) + " (" + String(camId) + ")" + " to configure the device.");

  server.on("/", handleRoot);
  server.on("/set-camera-id/", handleConfig);
  server.onNotFound(handleRoot);

  server.begin();
}

void configWebserverLoop()
{
  dnsServer.processNextRequest();
  server.handleClient();
  configLedAnimation();
}
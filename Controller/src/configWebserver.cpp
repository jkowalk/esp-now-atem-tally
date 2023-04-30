#include "configWebserver.h"

#include <WebServer_WT32_ETH01.h>

#include "atemConnection.h"
#include "espNow.h"
#include "memory.h"

WebServer server(80);

const String postForms[2] = {
    F("<html>\
      <head>\
      <title>WebServer_WT32_ETH01 POST handling</title>\
      <style>\
      body { background-color: #e6e5df; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; display: flex; justify-content: center; margin-top: 4rem; }\
      form { display: flex; }\
      .container { display: flex; flex-direction: column; align-items: center; }\
      </style>\
      </head>\
      <body>\
      <div class=\"container\">\
      <h1>Set ATEM IP Adress:</h1><br>\
      <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/postform/\">\
      <input type=\"text\" name=\"ip\" value=\""),
    F("\"><br>\
      <input type=\"submit\" value=\"Submit\">\
      </form>\
      </div>\
      </body>\
      </html>")};

const String debugWebPage = F("<html>\
      <head>\
      <title>WebServer_WT32_ETH01 POST handling</title>\
      <style>\
      body { background-color: #e6e5df; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; display: flex; justify-content: center; margin-top: 4rem; }\
      form { display: flex; }\
      .container { display: flex; flex-direction: column; align-items: center; }\
      </style>\
      </head>\
      <body>\
      <div class=\"container\">\
      <h1>Send message:</h1><br>\
      <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/debugform/\">\
      <label for=\"preview\">Preview:</label><br>\
      <input type=\"number\" name=\"preview\" value=\"preview camera\"><br>\
      <label for=\"program\">Program:</label><br>\
      <input type=\"number\" name=\"program\" value=\"program camera\"><br>\
      <label for=\"transition\">Transition:</label><br>\
      <input type=\"checkbox\" name=\"transition\"><br>\
      <input type=\"submit\" value=\"Send\">\
      </form>\
      </div>\
      </body>\
      </html>");

void handleRoot()
{
  server.send(200, F("text/html"), postForms[0] + switcherIp.toString() + postForms[1]);
}

void handleDebugWebPage()
{
  server.send(200, F("text/html"), debugWebPage);
}

void handleForm()
{
  if (server.method() != HTTP_POST)
  {
    server.send(405, F("text/plain"), F("Method Not Allowed"));
  }
  else
  {
    String message = F("ATEM IP set to:\n");

    for (uint8_t i = 0; i < server.args(); i++)
    {

      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";

      changeSwitcherIp(server.arg(i));
    }

    server.send(200, F("text/plain"), message);
  }
}

void handleDebugForm()
{
  if (server.method() != HTTP_POST)
  {
    server.send(405, F("text/plain"), F("Method Not Allowed"));
  }
  else
  {
    boolean program[21] = {false};
    boolean preview[21] = {false};
    program[server.arg("program").toInt() - 1] = true;
    preview[server.arg("preview").toInt() - 1] = true;
    sendMessage(program, preview, server.arg("transition") == "on" ? true : false, false);

    String message = "Sent with success";
    server.send(200, F("text/plain"), message);
  }
}

void printATEMInformation()
{
  server.send(200, F("text/plain"), getATEMInformation());
}

void handleNotFound()
{
  String message = F("File Not Found\n\n");

  message += F("URI: ");
  message += server.uri();
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? F("GET") : F("POST");
  message += F("\nArguments: ");
  message += server.args();
  message += F("\n");

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, F("text/plain"), message);
}

void setupWebserver()
{
    Serial.print("\nStarting POSTServer on " + String(ARDUINO_BOARD));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);

  // To be called before ETH.begin()
  WT32_ETH01_onEvent();

  // Initialize the Ethernet connection
  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);

  WT32_ETH01_waitForConnect();

  server.on(F("/"), handleRoot);
  server.on(F("/debug"), handleDebugWebPage);

  server.on(F("/postform/"), handleForm);
  server.on(F("/debugform/"), handleDebugForm);
  server.on(F("/atem/"), printATEMInformation);

  server.onNotFound(handleNotFound);

  server.begin();

  Serial.print(F("HTTP POSTServer started @ IP : "));
  Serial.println(ETH.localIP());
}

void webserverLoop()
{
  server.handleClient();
}
#include "espNow.h"

#include <Arduino.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include <WiFi.h>

#include "atemConnection.h"

// Broadcast address, sends to all devices nearby
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message
{
  int program;
  int preview;
  boolean transition;
  boolean request;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

void sendCurrentAtemState()
{
  sendMessage(getProgramInput(), getPreviewInput(), getTransition(), false);
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// callback when data is received
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
{
  struct_message *data = (struct_message *)incomingData;
  Serial.println("Received: ");
  Serial.println("Program: " + String(data->program));
  Serial.println("Preview: " + String(data->preview));
  Serial.println("Transition: " + String(data->transition));
  Serial.println("Request: " + String(data->request));

  if (data->request)
  {
    sendCurrentAtemState();
  }
}

void setupEspNow()
{
  Serial.println("Init ESP-NOW ...");
  WiFi.mode(WIFI_STA);
  // config long range mode
  int a = esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_LR);
  Serial.println(a);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet and register peer data receive
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}

void sendMessage(int program, int preview, boolean transition, boolean request)
{
  struct_message data;
  data.preview = preview;
  data.program = program;
  data.transition = transition;
  data.request = request;

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&data, sizeof(data));

  if (result == ESP_OK)
  {
    Serial.println("Sent with success");
  }
  else
  {
    Serial.println("Error sending the data");
  }
}
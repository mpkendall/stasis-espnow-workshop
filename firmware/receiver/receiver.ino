#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  char msg[32];
  int a;
  float b;
  bool c;
} struct_message;
struct_message packetData;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {}

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  memcpy(&packetData, incomingData, sizeof(packetData));
  Serial.print("received message length: ");
  Serial.println(len);
  Serial.print("msg: ");
  Serial.println(packetData.msg);
  Serial.print("a: ");
  Serial.println(packetData.a);
  Serial.print("b: ");
  Serial.println(packetData.b);
  Serial.print("c: ");
  Serial.println(packetData.c);
  Serial.println();
}
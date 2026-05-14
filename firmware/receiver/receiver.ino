#include <esp_now.h>
#include <WiFi.h>

// structure example to send data
// must match the sender structure
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

  // initialize
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // configure packet receive callback
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}

// callback function for received packets
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
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
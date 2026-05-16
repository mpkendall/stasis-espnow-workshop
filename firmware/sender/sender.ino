#include <WiFi.h>
#include <esp_now.h>

// ****** REPLACE WITH YOUR RECEIVER MAC ADDRESS ******E0:72:A1:70:0A:34
uint8_t broadcastAddress[] = {0xE0, 0x72, 0xA1, 0x70, 0x0A, 0x34};
// ****** REPLACE WITH YOUR RECEIVER MAC ADDRESS ******

// structure example to send data
// must match the receiver structure
typedef struct struct_message {
  char msg[32];
  int a;
  float b;
  bool c;
} struct_message;

struct_message packetData;

// peer info instantiation
esp_now_peer_info_t peerInfo;
 
void setup() {
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);

  // initialization
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // configure packet callback
  esp_now_register_send_cb(OnDataSent);
  
  // register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
   
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  strcpy(packetData.msg, "Hello Stasis!");
  packetData.a = random(1,20);
  packetData.b = 3.14;
  packetData.c = false;
  
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &packetData, sizeof(packetData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\nMessage Attempted: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}
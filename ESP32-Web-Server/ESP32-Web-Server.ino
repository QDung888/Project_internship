// ===== ESP32 SoftAP + SPIFFS static web + routes đơn giản =====
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

const char* AP_SSID = "ESP32-Network";
const char* AP_PASS = "Esp32-Password";

WebServer server(80);

// GPIO
const int PIN16 = 16;
const int PIN17 = 17;
const int D2_PIN = 2;   // đổi nếu LED D2 không ở GPIO2

// --- Helpers ---
String contentType(const String& filename) {
  if (filename.endsWith(".htm") || filename.endsWith(".html")) return "text/html";
  if (filename.endsWith(".css"))  return "text/css";
  if (filename.endsWith(".js"))   return "application/javascript";
  if (filename.endsWith(".png"))  return "image/png";
  if (filename.endsWith(".jpg") || filename.endsWith(".jpeg")) return "image/jpeg";
  if (filename.endsWith(".svg"))  return "image/svg+xml";
  if (filename.endsWith(".ico"))  return "image/x-icon";
  if (filename.endsWith(".json")) return "application/json";
  return "text/plain";
}
void listFS(){
  Serial.println("SPIFFS list:");
  File root = SPIFFS.open("/");
  File f = root.openNextFile();
  while (f) {
    Serial.printf("  %s (%u bytes)\n", f.name(), (unsigned)f.size());
    f = root.openNextFile();
  }
}

bool handleFileRead(String path) {
  if (path.endsWith("/")) path += "index.html";
  if (!SPIFFS.exists(path)) return false;
  File file = SPIFFS.open(path, "r");
  String type = contentType(path);
  server.streamFile(file, type);
  file.close();
  return true;
}

void updateD2() {
  int v16 = digitalRead(PIN16);
  int v17 = digitalRead(PIN17);
  digitalWrite(D2_PIN, (v16 == HIGH && v17 == HIGH) ? HIGH : LOW);
}

void redirectHome() {
  server.sendHeader("Location", "/");
  server.send(303); // See Other -> quay về /
}

void setup() {
  Serial.begin(115200);

  // GPIO init
  pinMode(PIN16, OUTPUT); digitalWrite(PIN16, LOW);
  pinMode(PIN17, OUTPUT); digitalWrite(PIN17, LOW);
  pinMode(D2_PIN, OUTPUT); digitalWrite(D2_PIN, LOW);
  updateD2();

  // SPIFFS
  if (!SPIFFS.begin(true)) { // true: format nếu mount fail (lần đầu)
    Serial.println("SPIFFS mount failed");
    while (1) delay(1000);
  }
  listFS();

  // SoftAP
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.print("AP SSID: "); Serial.println(AP_SSID);
  Serial.print("IP: "); Serial.println(WiFi.softAPIP()); // thường 192.168.4.1

  // Routes bật/tắt
  server.on("/16/on",  HTTP_GET, [](){ digitalWrite(PIN16, HIGH); updateD2(); redirectHome(); });
  server.on("/16/off", HTTP_GET, [](){ digitalWrite(PIN16, LOW ); updateD2(); redirectHome(); });
  server.on("/17/on",  HTTP_GET, [](){ digitalWrite(PIN17, HIGH); updateD2(); redirectHome(); });
  server.on("/17/off", HTTP_GET, [](){ digitalWrite(PIN17, LOW ); updateD2(); redirectHome(); });

  // Route gốc & static
  server.on("/", HTTP_GET, [](){
    if (!handleFileRead("/index.html")) server.send(404, "text/plain", "index.html not found");
  });

  // Bắt mọi path khác -> thử tìm file trong SPIFFS
  server.onNotFound([](){
    if (!handleFileRead(server.uri())) server.send(404, "text/plain", "Not found");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

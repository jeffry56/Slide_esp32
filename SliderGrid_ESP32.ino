/***** documentation AsyncWebServer on https://github.com/me-no-dev/ESPAsyncWebServer **************************/

#include <WiFi.h>
#include <WiFiMulti.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
//#include <ArduinoJson.h>
#include "index.h"
#include "credentials.h"
//#include <Preferences.h>
//#include <WebSerial.h>

#define porta           80
#define socketPort      81
#define HOSTNAME        "MyESP-"


const char* ssid        = WIFI_SSID;
const char* password    = WIFI_PASSWD;
const char* ssid1       = WIFI_SSID1;
const char* password1   = WIFI_PASSWD1;
const char* APssid      = AP_SSID;
const char* APpassword  = AP_PASSWD;

IPAddress ip(192, 168, 1, 51);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);
IPAddress myIP;

int         n;
int         maxfail       = 0;
const int   maxattemp     = 30;                     // assegnare maxattemp >=15 per effettuare la connessione ad una rete WiFi

bool ledState = 0;
const int ledPin = 2;

float actualPosition  = 0;
int maxPosition       = 100;
int minPosition       = 0;
float A_position      = 0;
float B_position      = 0;
int Interval          = 0;
int Shots             = 0;
int ShotsMade         = 0;
bool Achk, Bchk, flag08, flag11 = false;

unsigned long previousMillis = 0;
const long interval = 1000;
unsigned long currentMillis = 0;

WiFiMulti wifiMulti;
AsyncWebServer server(porta);
AsyncWebSocket ws("/ws");

//StaticJsonDocument<500> jmsg;
//char buffer[500];

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  if (!WiFi.config(ip, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  start_SPIFFS();
  startWiFi();
  initWebSocket();
  startServer();
}

void loop() {
  ws.cleanupClients();

  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (flag08) {
      send_values(1);
    }
    if (flag11) {
      send_values(-1);
    }
  }
}

/*** Functions Definitions ****************************************************************/

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
  Serial.println("\nWebSocket server started.");
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      send_values(0);
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    String command = (char*)data;
    Serial.println(command);

    if (command.substring(0, 4) == "V13-") {
      Shots = (command.substring(4)).toInt();
      send_values(0);
    } else {
      if (command.substring(0, 4) == "V14-") {
        Interval = (command.substring(4)).toInt();
        send_values(0);
      } else {
        int nCommand = (command.substring(3)).toInt();

        //Serial.println(nCommand);
        if (nCommand > 0) {
          switch (nCommand) {
            case 1:                                               // Increment position value by 0.1
              send_values(0.1);
              break;
            case 2:                                               // Increment position value by 0.5
              send_values(0.5);
              break;
            case 3:                                               // Increment position value by 1
              send_values(1);
              break;
            case 4:                                               // Decrement position value by 0.1
              send_values(-0.1);
              break;
            case 5:                                               // Decrement position value by 0.5
              send_values(-0.5);
              break;
            case 6:                                               // Decrement position value by 1
              send_values(-1);
              break;
            case 7:                                               // Set (A) value
              A_position = actualPosition;
              send_values(0);
              break;
            case 8:                                               // (A) jog button - see case 20 and 21
              break;
            case 9:                                               // (A) switch - see case 40 and 41
              send_values(0);
              break;
            case 10:                                              // Set (B) value
              B_position = actualPosition;
              send_values(0);
              break;
            case 11:                                              // (B) jog button - see case 30 and 31
              break;
            case 12:                                              // (A) switch - see case 50 and 51
              send_values(0);
              break;
            case 13:                                              // Shots input - not used
              break;
            case 14:                                              // Interval input - not used
              break;
            case 20:                                              // (A) jog button mouse down event
              Serial.println("down08");
              flag08 = true;
              break;
            case 21:                                              // (A) jog button mouse up event
              Serial.println("up08");
              flag08 = false;
              break;
            case 30:                                              // (B) jog button mouse down event
              Serial.println("down11");
              flag11 = true;
              break;
            case 31:                                              // (B) jog button mouse up event
              Serial.println("up11");
              flag11 = false;
              break;
            case 40:                                              // (A) switch on
              Serial.println("chk09");
              Achk = true;
              send_values(0);
              break;
            case 41:                                              // (A) switch off
              Serial.println("unchk09");
              Achk = false;
              send_values(0);
              break;
            case 50:                                              // (B) switch on
              Serial.println("chk12");
              Bchk = true;
              send_values(0);
              break;
            case 51:                                              // (B) switch off
              Serial.println("unchk12");
              Bchk = false;
              send_values(0);
              break;
            default:
              send_values(0);
              break;
          }
        }
      }
    }
  }
}

void send_values(float incdec) {
  actualPosition = actualPosition + incdec;
  if (actualPosition > maxPosition) {
    actualPosition = maxPosition;
  }
  if (actualPosition < minPosition) {
    actualPosition = minPosition;
  }

/*  jmsg["header"]          = "dati";
  jmsg["A_position"]      = String(A_position, 1);
  jmsg["B_position"]      = String(B_position, 1);
  jmsg["actualPosition"]  = String(actualPosition, 1);
  jmsg["Achk"]            = String(Achk);
  jmsg["Bchk"]            = String(Bchk);
  jmsg["Shots"]           = String(Shots);
  jmsg["Interval"]        = String(Interval);
  jmsg["ShotsMade"]       = String(ShotsMade);

  serializeJson(jmsg, buffer);*/

  //  serializeJsonPretty(jmsg, buffer);
  //  Serial.println(buffer);

  String msg = "dati|" + String(A_position, 1) + "|" + String(B_position, 1) + "|" + String(actualPosition, 1) + "|" + String(Achk) + "|" + String(Bchk) + "|" + String(Shots) + "|" + String(Interval) + "|" + String(ShotsMade);
  ws.textAll(msg);
}

String processor(const String& var) {             // Replaces placeholder with values
  Serial.println(var);
  if (var == "actualPosition") {
    return String(actualPosition);
  }
  if (var == "A_position") {
    return String(A_position);
  }
  if (var == "B_position") {
    return String(B_position);
  }
  if (var == "Achk") {
    if (Achk) {
      return String("checked");
    } else {
      return String("");
    }
  }
  if (var == "Bchk") {
    if (Bchk) {
      return String("checked");
    } else {
      return String("");
    }
  }
  if (var == "Shots") {
    return String(Shots);
  }
  if (var == "Interval") {
    return String(Interval);
  }
  if (var == "ShotsMade") {
    return String(ShotsMade);
  }
}

void startServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", webpage, processor);
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
  server.on("/iconic_fill.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/iconic_fill.css", "text/css");
  });
  server.on("/bg_01.jpg", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/bg_01.jpg", "image/jpeg");
  });
  server.on("/icomoon.woff", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/icomoon.woff", "font/woff");
  });
  server.on("/icomoon.ttf", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/icomoon.ttf", "font/ttf");
  });
  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/favicon.ico", "image/ico");
  });

  server.onNotFound([](AsyncWebServerRequest * request) {
    Serial.printf("NOT_FOUND: ");
    if (request->method() == HTTP_GET) Serial.printf("GET");
    else if (request->method() == HTTP_POST) Serial.printf("POST");
    else if (request->method() == HTTP_DELETE) Serial.printf("DELETE");
    else if (request->method() == HTTP_PUT) Serial.printf("PUT");
    else if (request->method() == HTTP_PATCH) Serial.printf("PATCH");
    else if (request->method() == HTTP_HEAD) Serial.printf("HEAD");
    else if (request->method() == HTTP_OPTIONS) Serial.printf("OPTIONS");
    else Serial.printf("UNKNOWN");
    Serial.printf(" http://%s%s\n", request->host().c_str(), request->url().c_str());

    if (request->contentLength()) {
      Serial.printf("_CONTENT_TYPE: %s\n", request->contentType().c_str());
      Serial.printf("_CONTENT_LENGTH: %u\n", request->contentLength());
    }
    int headers = request->headers();
    int i;
    for (i = 0; i < headers; i++) {
      AsyncWebHeader* h = request->getHeader(i);
      Serial.printf("_HEADER[%s]: %s\n", h->name().c_str(), h->value().c_str());
    }
    int params = request->params();
    for (i = 0; i < params; i++) {
      AsyncWebParameter* p = request->getParam(i);
      if (p->isFile()) {
        Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
      } else if (p->isPost()) {
        Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      } else {
        Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    }
    request->send(404);
  });

  server.begin();                                      // Start web server
  Serial.println("\nTCP (HTTP) server started.");
}

void start_SPIFFS() {
  if (SPIFFS.begin(true)) {
    Serial.println("\nSPIFFS Active");
    Serial.println();
  } else {
    Serial.println("Unable to activate SPIFFS");
  }
}

void startWiFi() {
  WiFi.persistent(false);                 // Avoid wear-out
  WiFi.mode(WIFI_STA);
  //  WiFi.mode(WIFI_OFF);
  //  WiFi.forceSleepBegin();
  WiFi.config(ip, gateway, subnet, primaryDNS);

  if (WiFi.status() != WL_CONNECTED) {
    wifiMulti.addAP(ssid, password);
    wifiMulti.addAP(ssid1, password1);
  }

  Serial.println("Connecting...");

  //  ESP.restart();

  while ((wifiMulti.run() != WL_CONNECTED) && (maxfail < maxattemp)) {
    Serial.print(".");
    maxfail += 1;
    delay(500);
  }

  if (maxfail < maxattemp) {
    Serial.print("\nConnected: ");
    Serial.print("SSID: "); Serial.print(WiFi.SSID());
    Serial.print(", IP: "); myIP = WiFi.localIP(); Serial.print(myIP);
    Serial.print(":"); Serial.print(porta);
  }
  else {
    Serial.println("\nNo Connected ");
    Serial.print("Config access point - ");

    WiFi.mode(WIFI_AP);
    //WiFi.softAP(const char* ssid, const char* password, int channel, int ssid_hidden, int max_connection)
    WiFi.softAP(APssid, APpassword);
    WiFi.softAPConfig(ip, gateway, subnet);

    myIP = WiFi.softAPIP();
    Serial.print(" IP: "); Serial.print(myIP);
  }

  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  Serial.println("\n\nHardware info:");
  Serial.printf("\t%d cores Wifi %s%s\n", chip_info.cores, (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "", (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
  Serial.printf("\tSilicon revision: %d\n", chip_info.revision);
  Serial.printf("\t%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024), (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embeded" : "external");

  String chipId = String((uint32_t)ESP.getEfuseMac(), HEX);
  chipId.toUpperCase();

  String hostname(HOSTNAME);
  hostname += chipId;
  WiFi.hostname(hostname);

  Serial.printf("\tChip id: %s\n", chipId.c_str());
  Serial.println();
  //Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s:%d\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str(), porta);
  Serial.print("Hostname: "); Serial.println(hostname);
}

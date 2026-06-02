#include "status.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include "config.h"
#include "dashboard.h"

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

void handleRoot()
{
    int mq2 = 1200;
    int mq135 = 1800;

    String status = getStatus(mq2, mq135);

    String page = generateDashboard(
        mq2,
        mq135,
        status
    );

    server.send(200, "text/html", page);
}

void setup()
{
    Serial.begin(115200);

    server.on("/", handleRoot);

    Serial.println("Server configured");
}

void loop()
{
}
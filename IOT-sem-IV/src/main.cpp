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
    int mq2 = analogRead(MQ2_PIN);
    int mq135 = analogRead(MQ135_PIN);

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
    delay(2000);

    Serial.println("ESP32 Started");

    server.on("/", handleRoot);
}

void loop()
{
     Serial.print("MQ2: ");
    Serial.print(analogRead(MQ2_PIN));

    Serial.print(" | MQ135: ");
    Serial.println(analogRead(MQ135_PIN));

    delay(1000);
}
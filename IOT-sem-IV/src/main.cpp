#include <HTTPClient.h>
#include "secrets.h"
#include "status.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "config.h"
#include "dashboard.h"

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

void sendToSupabase(int mq2, int mq135, String status)
{
    HTTPClient http;

    http.begin(SUPABASE_URL);

    http.addHeader("Content-Type", "application/json");
    http.addHeader("apikey", SUPABASE_KEY);
    http.addHeader("Authorization",
                   "Bearer " + String(SUPABASE_KEY));

    String json =
        "{\"mq2\":" + String(mq2) +
        ",\"mq135\":" + String(mq135) +
        ",\"status\":\"" + status + "\"}";

    int responseCode = http.POST(json);

    Serial.print("Supabase Response: ");
    Serial.println(responseCode);

    http.end();
}

void setup()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi Connected");
    server.begin();

    Serial.begin(115200);
    delay(2000);

    Serial.println("ESP32 Started");

    server.on("/", handleRoot);
}

void loop()
{
    server.handleClient();

    int mq2 = analogRead(MQ2_PIN);
    int mq135 = analogRead(MQ135_PIN);

    String status = getStatus(mq2, mq135);

    Serial.print("MQ2: ");
    Serial.print(mq2);

    Serial.print(" | MQ135: ");
    Serial.print(mq135);

    Serial.print(" | Status: ");
    Serial.println(status);

    sendToSupabase(mq2, mq135, status);

    delay(10000);
}
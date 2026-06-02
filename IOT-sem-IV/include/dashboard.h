#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <Arduino.h>

String generateDashboard(int mq2, int mq135, String status)
{
    String html = R"(
<!DOCTYPE html>
<html>
<head>
    <title>Gas Monitoring Dashboard</title>
    <meta http-equiv="refresh" content="2">
</head>
<body>

<h1>Manhole Gas Monitoring System</h1>

)";

    html += "<h2>MQ-2: " + String(mq2) + "</h2>";
    html += "<h2>MQ-135: " + String(mq135) + "</h2>";
    html += "<h2>Status: " + status + "</h2>";

    html += "</body></html>";

    return html;
}

#endif
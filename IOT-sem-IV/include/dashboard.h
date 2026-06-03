#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <Arduino.h>

String generateDashboard(int mq2, int mq135, String status)
{
    String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>

<meta charset="UTF-8">
<meta http-equiv="refresh" content="2">

<title>Gas Monitoring Dashboard</title>

<style>

body{
    font-family: Arial, sans-serif;
    background: #f4f4f4;
    text-align: center;
    padding: 40px;
}

.card{
    background: white;
    max-width: 600px;
    margin: auto;
    padding: 30px;
    border-radius: 10px;
    box-shadow: 0px 0px 10px rgba(0,0,0,0.2);
}

.safe{
    color: green;
}

.warning{
    color: orange;
}

.danger{
    color: red;
}

</style>

</head>

<body>

<div class="card">

<h1>Manhole Gas Monitoring System</h1>

)rawliteral";

    String statusClass = "safe";

    if(status == "WARNING")
    {
        statusClass = "warning";
    }
    else if(status == "DANGER")
    {
        statusClass = "danger";
    }

    html += "<h2>MQ-2 Value : " + String(mq2) + "</h2>";
    html += "<h2>MQ-135 Value : " + String(mq135) + "</h2>";

    html += "<h1 class='";
    html += statusClass;
    html += "'>";
    html += status;
    html += "</h1>";

    html += R"rawliteral(

</div>

</body>
</html>

)rawliteral";

    return html;
}

#endif
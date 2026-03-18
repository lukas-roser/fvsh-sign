#include "webControlPanel.h"
#include <WiFi.h>
#include <WebServer.h>
#include "display.h"

WebServer server(80);

const char* AP_SSID = "FVSH-Stadionanzeige";
const char* AP_PASS = "FVSH!1993";

String makeHtml()
{
    int digit = getCurrentDigit();
    String shown = digit >= 0 ? String(digit) : "-";

    String html = "<html><body style='font-family:Arial;text-align:center'>";

    html += "<h1>ESP32 Anzeige</h1>";
    html += "<h2>Aktuell: " + shown + "</h2>";

    for(int i=0;i<10;i++)
    {
        html += "<a href='/set?d=" + String(i) + "'>";
        html += "<button style='font-size:30px;margin:5px'>" + String(i) + "</button>";
        html += "</a>";
    }

    html += "<br><br>";
    html += "<a href='/off'><button>Aus</button></a>";

    html += "</body></html>";

    return html;
}

void handleRoot()
{
    server.send(200, "text/html", makeHtml());
}

void handleSet()
{
    int d = server.arg("d").toInt();
    showDigit(d);

    server.sendHeader("Location","/");
    server.send(303);
}

void handleOff()
{
    clearDisplay();

    server.sendHeader("Location","/");
    server.send(303);
}

void webControlPanelInit()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);

    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());

    server.on("/", handleRoot);
    server.on("/set", handleSet);
    server.on("/off", handleOff);

    server.begin();
}

void webControlPanelLoop()
{
    server.handleClient();
}

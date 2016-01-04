#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include "../../../../../config.h"

/*
config.h

#define WIFI_SSID "wifi_name"
#define WIFI_PASSWORD "wifi_pass"
#define OVERMIND_IP "master_ip"
#define OVERMIND_PORT master_port
*/

const char* host = "172.16.18.24";
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

WiFiServer server(80);
WiFiClient client;

void setup(void)
{ 
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  server.begin();
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(A0, INPUT);
  const int httpPort = 80;
  delay(100);
  Serial.println("CONNECTING...");
  while (!client.connect(host, httpPort)){
    Serial.println("CONNECTING...");
    delay(10);
  }
}

void loop(void)
{
  float X, Y, W;
  if(client.connected()){
    digitalWrite(D2, 0); digitalWrite(D3, 0);
    X = analogRead(A0);
    X = map(X * 100, 0, 102400, -100, 100);
    X = (float)X/100;
    digitalWrite(D2, 0); digitalWrite(D3, 1);
    Y = analogRead(A0);
    Y = map(Y * 100, 0, 102400, 100, -100);
    Y = (float)Y/100;
    digitalWrite(D2, 1); digitalWrite(D3, 0);
    W = analogRead(A0);
    W = map(W * 100, 0, 102400, 100, -100);
    W = (float)W/100;
    delay(100);
    String msg;
    msg = "," + (String)X + "," + (String)Y + "," + (String)W + ",";
    Serial.println(msg);
    client.println(msg);
  }
  yield();
}
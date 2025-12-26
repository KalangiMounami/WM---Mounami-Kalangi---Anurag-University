#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define TRIG_PIN 5
#define ECHO_PIN 18

const char *ssid = "YOUR_WIFI";
const char *password = "YOUR_PASSWORD";
const char *mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

float BIN_DEPTH = 100.0;

float get_fill_level()
{
    long duration;
    float distance, fill;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 30000);
    distance = (duration * 0.034) / 2;

    fill = ((BIN_DEPTH - distance) / BIN_DEPTH) * 100;

    if (fill < 0) fill = 0;
    if (fill > 100) fill = 100;

    return fill;
}

void setup_wifi()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
        delay(500);
}

void reconnect()
{
    while (!client.connected())
        client.connect("SmartBinNode");
}

void setup()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
}

void loop()
{
    if (!client.connected())
        reconnect();
    client.loop();

    float fill = get_fill_level();

    if (fill > 80)
    {
        char payload[50];
        sprintf(payload, "{\"bin\":1,\"fill\":%.2f}", fill);
        client.publish("smartbin/data", payload);
    }

    esp_sleep_enable_timer_wakeup(30 * 60 * 1000000ULL);
    esp_deep_sleep_start();
}

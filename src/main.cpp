#include <WiFi.h>
#include "esp_wpa2.h"

const char* ssid = "RUWireless Secure";
const char* username = "rmb304"
const char* password = "daDcaw-karvok-mebro8"

void setup(){
    Serial.begin(921600);
    delay(10);
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);

    esp_wifi_sta_wpa2_ent_set_identity((uint8 *)username, strlen(username));
    esp_wifi_sta_wpa2_ent_set_username((uint8 *)username, strlen(username));
    esp_wifi_sta_wpa2_ent_set_password((uint8 *)password, strlen(password));
    esp_wifi_sta_wap2_ent_enable();

    WiFi.begin(ssid);
    while(WiFi.status() != WL_CONNETED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
}

void loop() {}

// #include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include "Application.h"
#include "config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "nvs_flash.h"

#include "main.h"

void tsk_loop(void* arg);
void setup();
void loop();

const char ssid[] = "ESP32AP-WiFi";
const char pass[] = "esp32apwifi";
const IPAddress ip(192,168,30,3);
const IPAddress subnet(255,255,255,0);

void setup()
{
  //Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  // Serial.begin(115200);
  // Serial.println("Starting up");
  ESP_LOGI("loop", "Starting up");
  delay(1000);
  WiFi.softAP(ssid, pass);
  delay(100);
  WiFi.softAPConfig(ip, ip, subnet);

  // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(500);
  //   Serial.print(".");
  // }
  // disable WiFi sleep mode
  // WiFi.setSleep(WIFI_PS_NONE);

  // Serial.println("");
  // Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  // Serial.print(WiFi.localIP());
  // Serial.println("");

  // startup MDNS
  if (!MDNS.begin(MDNS_DOMAIN))
  {
    // Serial.println("MDNS.begin failed");
    ESP_LOGI("loop", "MDNS.begin failed");
  }
  // Serial.println("Creating microphone");
  ESP_LOGI("loop", "Creating microphone");
  Application *application = new Application();
  application->begin();
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void _main(void)
{
  xTaskCreate(tsk_loop, "loop", 8192, NULL, 5, NULL);
}

void tsk_loop(void* arg)
{
  setup();
  while(1) {
    loop();
    // vTaskDelay(pdMS_TO_TICKS(1000));
    // ESP_LOGI("loop", "test");
  }
}
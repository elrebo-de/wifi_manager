/*
 * wifi_manager.cpp
 *
 *      Author: christophoberle
 *
 * this work is licenced under the Apache 2.0 licence
 */

#include <string>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sdkconfig.h"
#include "esp_log.h"

#include "nvs_flash.h"

#include <wifi_manager.h>
#include <ssid_manager.h>

#include "wifi_manager.hpp"

Wifi::Wifi( std::string tag,
            std::string ssid_prefix,
            std::string language
          ) {
	this->tag = tag;
	this->ssid_prefix = ssid_prefix;
	this->language = language;

    bool startConfigurationAp = false;  // set to true if BUTTON_LONG_PRESS (5000 ms) during start-up
    bool startStation = false;

	ESP_LOGI(tag.c_str(), "Startup");
    // Initialize the default event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    // Initialize NVS flash for Wi-Fi configuration
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Get the WifiManager singleton
    auto& wifiManager = WifiManager::GetInstance();
    // Initialize with configuration
    WifiManagerConfig config;
    config.ssid_prefix = this->ssid_prefix;  // AP mode SSID prefix
    config.language = this->language;        // Web UI language
    wifiManager.Initialize(config);
    // Set event callback to handle WiFi events
    wifiManager.SetEventCallback([](WifiEvent event) {
        switch (event) {
            case WifiEvent::Scanning:
                //ESP_LOGI("WiFi", "Scanning for networks...");
                break;
            case WifiEvent::Connecting:
                //ESP_LOGI("WiFi", "Connecting to network...");
                break;
            case WifiEvent::Connected:
                //ESP_LOGI("WiFi", "Connected successfully!");
                break;
            case WifiEvent::Disconnected:
                //ESP_LOGW("WiFi", "Disconnected from network");
                break;
            case WifiEvent::ConfigModeEnter:
                //ESP_LOGI("WiFi", "Entered config mode");
                break;
            case WifiEvent::ConfigModeExit:
                //ESP_LOGI("WiFi", "Exited config mode");
                break;
        }
    });

    // Check if there are saved Wi-Fi credentials
    auto& ssid_list = SsidManager::GetInstance().GetSsidList();
    if (ssid_list.empty()) {
    #ifdef LED_ACTIVE
            // WiFi configuration AP indicator: white LED
            onBoardLed->setLedPixelColor(0, 16, 16, 16);
            onBoardLed->setLedState(true);
            onBoardLed->show();
    #endif // LED_ACTIVE
        // No credentials saved, start config AP mode
        startConfigurationAp = true;
        wifiManager.StartConfigAp();
    } else {
        // Try to connect to the saved Wi-Fi network
        startStation = true;
        wifiManager.StartStation();
    }

    // hier muss wifiManager.StartConfigAp bzw StartStation aufgerufen werden
    ESP_LOGI(tag.c_str(), "startConfigurationAp=%s startStation=%s", startConfigurationAp ? "true":"false", startStation ? "true":"false");

    if (startStation == true) {
        // if not connected to station after 20 seconds enter Wifi configuration mode
        for (int i=30;i>0;i--) {
            if (wifiManager.IsConnected()) {
                break;
            }
            ESP_LOGI(tag.c_str(), "wait (max. 30 seconds) until Wifi station is connected");
            // 1 Sekunde warten
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        if (!wifiManager.IsConnected()) {
            startStation = false;
            startConfigurationAp = true;
            ESP_LOGI(tag.c_str(), "Wifi station is not started -> start Wifi configuration");
            wifiManager.StartConfigAp();
        }
    }

    if (startStation == false) {
        while(wifiManager.IsConfigMode()) {
            ESP_LOGI(tag.c_str(), "wait until Wifi configuration is finished");
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        wifiManager.StartStation();
        while(!wifiManager.IsConnected()) {
            ESP_LOGI(tag.c_str(), "wait until Wifi station is connected");
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
    ESP_LOGI(tag.c_str(), "Wifi station is connected");
}

Wifi::~Wifi() {}

std::string Wifi::GetSsid() const {
    auto& wifiManager = WifiManager::GetInstance();
    return wifiManager.GetSsid();
}
std::string Wifi::GetIpAddress() const {
    auto& wifiManager = WifiManager::GetInstance();
    return wifiManager.GetIpAddress();
}

int Wifi::GetRssi() const {
    auto& wifiManager = WifiManager::GetInstance();
    return wifiManager.GetRssi();
}

int Wifi::GetChannel() const {
    auto& wifiManager = WifiManager::GetInstance();
    return wifiManager.GetChannel();
}

std::string Wifi::GetMacAddress() const {
    auto& wifiManager = WifiManager::GetInstance();
    return wifiManager.GetMacAddress();
}

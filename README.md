# Wifi manager component

A simple Wifi manager as an ESP-IDF component. It runs on any ESP32 processor and is built using the ESP-IDF build system in version 5.5+.

The component is implemented as C++ class `Wifi`.

## Connecting the component

The constructor of class `Wifi` has three parameters:

| Parameter   | Type of Parameter | Usage                                                     |
|:------------|:------------------|:----------------------------------------------------------|
| tag         | std::string       | the tag to be used in the ESP log                         |
| ssid_prefix | std::string       | the prefix for the ssid of the configuration access point |
| language    | std::string       | the language of the configuration access point            |

# Usage
To use the WifiManager component you have to include "wifi_manager.hpp".

To establish a Wifi connection you have to define an instance of class Wifi.
The constructor will establish the connection and return only after the Wifi is connected.
If no useable credentials are found in NVS_FLASH storage, a configuration access point is started at ```http://192.168.4.1``` where the ssid and the passwort can be given.

Ssid, IpAddress, Rssi, Channel and MacAddress can be retrieved by Getters.

The connection state can be tested with Method ```IsConnected()```.

The connection can be restarted with Method ```RestartStation()```.

Example code:

```
#include "wifi_manager.hpp"

extern "C" void app_main(void)
{
    Wifi wifi(
		std::string("WifiManager"), // tag
		std::string("ESP32"), // ssid prefix for the configuration access point
		std::string("de-DE")  // language of the configuration access point
    );

    ESP_LOGI(tag, "Wifi is %s connected", wifi.IsConnected() ? "" : "not");

    ESP_LOGI(tag, "Ssid: %s", wifi.GetSsid().c_str());
    ESP_LOGI(tag, "IpAddress: %s", wifi.GetIpAddress().c_str());
    ESP_LOGI(tag, "Rssi: %i", wifi.GetRssi());
    ESP_LOGI(tag, "Channel: %i", wifi.GetChannel());
    ESP_LOGI(tag, "MacAddress: %s", wifi.GetMacAddress().c_str());
    
    vTaskDelay(pdMS_TO_TICKS(10000)); // delay 10 seconds

    // RestartStation
    ESP_LOGI(tag, "RestartStation");
    wifi.RestartStation();
    ESP_LOGI(tag, "Wifi is %s", wifi.IsConnected() ? "connected" : "not connected");

    ...
}
```

## API
The API of the component is located in the include directory ```include/wifi_manager.hpp``` and defines the
C++ class ```WifiManager```

```C++
/* class Wifi
   Class to establish a wifi connection.
   Credentials (SSID and Password) are stored in nvs flash storage.
   If nvs flash storage does not contain useable credentials
   an access point is started on 192.178.4.1 where the credentials can be given.
*/
class Wifi {
public:
    // Constructor
	Wifi( std::string tag,          // tag for ESP_LOGx
          std::string ssid_prefix,  // AP mode SSID prefix
          std::string language      // Web UI language
	    );
	virtual ~Wifi();

    void RestartStation();

    std::string GetSsid() const;
    std::string GetIpAddress() const;
    int GetRssi() const;
    int GetChannel() const;
    std::string GetMacAddress() const;

    bool IsConnected() const;

private:
    std::string tag = "WifiManager";
    std::string ssid_prefix = "ESP32";
    std::string language = "de-DE";
};
```

# License
This component is provided under the Apache 2.0 license.

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
If no useable credentials are found in NVS_FLASH storage, a configuration access point is started at 
http://192.168.4.1 where the ssid and the passwort can be given.

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

private:
    std::string tag = "WifiManager";
    std::string ssid_prefix = "ESP32";
    std::string language = "de-DE";
};
```

# License
This component is provided under the Apache 2.0 license.

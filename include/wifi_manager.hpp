/*
 * wifi_manager.hpp
 *
 *      Author: christophoberle
 *
 * this work is licenced under the Apache 2.0 licence
 */

#ifndef WIFI_MANAGER_HPP_
#define WIFI_MANAGER_HPP_

#include <string>

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

#endif /* WIFI_MANAGER_HPP_ */

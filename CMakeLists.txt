idf_component_register( SRCS "wifi_manager.cpp"
                        INCLUDE_DIRS "include"
                        REQUIRES "78__esp-wifi-connect"
                                 "nvs_flash"
                                 "driver"
                                 "esp_driver_gpio"
                                 "esp_timer"
                                 "esp_event"
                      )


idf_component_register( SRCS "main.cpp"
                        INCLUDE_DIRS "."
                        REQUIRES "elrebo-de__wifi_manager"
                                 "nvs_flash"
                                 "driver"
                                 #"esp_driver_gpio"
                                 #"esp_timer"
                                 #"esp_event"
                      )

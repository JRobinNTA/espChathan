idf_component_register(
    SRCS "${PROJECT_DIR}/libs/nrf24l01/src/driver_nrf24l01.c"
         "driver_nrf24l01_interface.c"
    INCLUDE_DIRS "." 
                 "${PROJECT_DIR}/libs/nrf24l01/src/"
    REQUIRES esp_driver_spi
)

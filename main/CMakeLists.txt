idf_component_register(
    SRCS "espChathan.c" "render.c" "touch.c" "graphic.c" "icons.c" "layout.c" "sdcard.c"
    INCLUDE_DIRS "."
    PRIV_REQUIRES hagl_hal microui hagl touch_xpt2046 esp_driver_sdspi fatfs)

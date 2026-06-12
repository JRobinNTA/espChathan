idf_component_register(
    SRCS "espChathan.c" "render.c" "touchScrn.c" "graphicUI.c" "icons.c"
    INCLUDE_DIRS "."
    PRIV_REQUIRES hagl_hal microui hagl touch_xpt2046)

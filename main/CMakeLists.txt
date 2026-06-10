idf_component_register(
    SRCS "espChathan.c" "lcDsply.c" "touchScrn.c" "graphicUI.c"
    INCLUDE_DIRS "."
    PRIV_REQUIRES hagl_hal microui hagl touch_xpt2046)

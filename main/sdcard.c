/*
 * This file is part of the espChathan Project
 *
 * Copyright (C) 2026 Robin John <johnrobin044@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <driver/sdspi_host.h>
#include <esp_vfs_fat.h>

#include "config.h"

#define TAG "SD_CARD"

void
init_spi_bus1(void)
{
    /* Silence the SPI Slaves So SD card can init*/
    gpio_set_direction(LCD_CS_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LCD_CS_PIN, 1);
    gpio_set_direction(TOUCH_CS_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(TOUCH_CS_PIN, 1);
    gpio_set_direction(SDCARD_CS_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(SDCARD_CS_PIN, 1);

    /* Init the bus */
    spi_bus_config_t buscfg
        = { .miso_io_num   = SPI2_BUS_MISO,
            .mosi_io_num   = SPI2_BUS_MOSI,
            .sclk_io_num   = SPI2_BUS_SCK,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1,
            /* Max transfer size in bytes s3 supports 32768*/
            .max_transfer_sz = 4092,
            .flags           = 0 };

    /* ESP32S2 requires DMA channel to match the SPI host. */
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));

    ESP_LOGI(TAG, "SPI2_HOST bus initialized");
}

void
init_sdcard(void)
{
    /* Configure the physical SDSPI device parameters */
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs               = SDCARD_CS_PIN;
    slot_config.host_id = SPI2_HOST; /* Share SPI2 with hagl_hal and touch */

    /* No need for a global handle since vfs handles reads and writes */
    sdspi_dev_handle_t sd_device_handle;
    esp_err_t err = sdspi_host_init_device(&slot_config, &sd_device_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "SD Card initialization failed");
        return;
    }
    ESP_LOGI(TAG, "SD Card initialized");
    esp_vfs_fat_sdmmc_mount_config_t mount_config
        = { .format_if_mount_failed = true,
            .max_files              = 5,
            .allocation_unit_size   = 16 * 1024 };

    sdmmc_card_t *card;
    sdmmc_host_t  host_config = SDSPI_HOST_DEFAULT();
    host_config.slot          = (int)sd_device_handle;
    err                       = esp_vfs_fat_sdspi_mount(
        "/sdcard", &host_config, &slot_config, &mount_config, &card);
    /* If sd card init fails the subsequent slave dev inits will set cs */
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "SD Card Not Mounted (Error: %s)", esp_err_to_name(err));
        return;
    }

    ESP_LOGI(TAG, "SD Card mounted successfully at /sdcard");
}

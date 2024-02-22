/**
 * @file Unit_ENV_M5StickCPlus.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief
 * @version 0.1
 * @date 2024-01-30
 *
 *
 * @Hardwares: M5StickCPlus + Unit ENV
 * @Platform Version: Arduino M5Stack Board Manager v2.1.0
 * @Dependent Library:
 * M5UnitENV: https://github.com/m5stack/M5Unit-ENV
 * M5Unified: https://github.com/m5stack/M5Unified
 */

#include <M5Unified.h>
#include "M5UnitENV.h"

DHT12 dht;
BMP280 bmp;

void setup() {
    M5.begin();
    if (!dht.begin(&Wire, DHT12_I2C_ADDR, 32, 33, 400000U)) {
        Serial.println("Couldn't find DHT12");
        while (1) delay(1);
    }
    if (!bmp.begin(&Wire, BMP280_I2C_ADDR, 32, 33, 400000U)) {
        Serial.println("Couldn't find BMP280");
        while (1) delay(1);
    }
    /* Default settings from datasheet. */
    bmp.setSampling(BMP280::MODE_NORMAL,     /* Operating Mode. */
                    BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    BMP280::FILTER_X16,      /* Filtering. */
                    BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
    if (dht.update()) {
        Serial.println("-----DHT12-----");
        Serial.print("Temperature: ");
        Serial.print(dht.cTemp);
        Serial.println(" degrees C");
        Serial.print("Humidity: ");
        Serial.print(dht.humidity);
        Serial.println("% rH");
        Serial.println("-------------\r\n");
    }

    if (bmp.update()) {
        Serial.println("-----BMP280-----");
        Serial.print(F("Temperature: "));
        Serial.print(bmp.cTemp);
        Serial.println(" degrees C");
        Serial.print(F("Pressure: "));
        Serial.print(bmp.pressure);
        Serial.println(" Pa");
        Serial.print(F("Approx altitude: "));
        Serial.print(bmp.altitude);
        Serial.println(" m");
        Serial.println("-------------\r\n");
    }
    delay(1000);
}

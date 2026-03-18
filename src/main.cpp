#include <Arduino.h>
#include <Wire.h>

#include "display.h"
#include "webControlPanel.h"

constexpr uint8_t I2C_SDA = 21;
constexpr uint8_t I2C_SCL = 22;

void setup()
{
    Serial.begin(115200);

    Wire.begin(I2C_SDA, I2C_SCL);

    displayInit();
    webControlPanelInit();
}

void loop()
{
    webControlPanelLoop();
}
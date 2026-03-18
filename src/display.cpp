#include "display.h"
#include <Wire.h>
#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;

constexpr uint8_t MCP_ADDR = 0x27;

constexpr uint8_t PIN_A = 0;
constexpr uint8_t PIN_B = 1;
constexpr uint8_t PIN_C = 2;
constexpr uint8_t PIN_D = 3;
constexpr uint8_t PIN_E = 4;
constexpr uint8_t PIN_F = 5;
constexpr uint8_t PIN_G = 6;

const uint8_t segmentPins[7] = {
    PIN_A, PIN_B, PIN_C, PIN_D, PIN_E, PIN_F, PIN_G
};

const uint8_t DIGITS[10] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111
};

int currentDigit = -1;

void setSegment(uint8_t pin, bool on)
{
    mcp.digitalWrite(pin, on ? HIGH : LOW);
}

void clearDisplay()
{
    for (int i = 0; i < 7; i++)
        setSegment(segmentPins[i], false);

    currentDigit = -1;
}

void showDigit(uint8_t digit)
{
    if (digit > 9) {
        clearDisplay();
        return;
    }

    uint8_t pattern = DIGITS[digit];

    for (int i = 0; i < 7; i++)
    {
        bool on = (pattern >> i) & 1;
        setSegment(segmentPins[i], on);
    }

    currentDigit = digit;
}

int getCurrentDigit()
{
    return currentDigit;
}

void displayInit()
{
    if (!mcp.begin_I2C(MCP_ADDR))
    {
        Serial.println("MCP23017 nicht gefunden!");
        while (true);
    }

    for (int i = 0; i < 7; i++)
        mcp.pinMode(segmentPins[i], OUTPUT);

    clearDisplay();
}
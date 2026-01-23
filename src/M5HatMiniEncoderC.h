#ifndef __M5HATMINIENCODERC_H
#define __M5HATMINIENCODERC_H

#include "Arduino.h"
#include "Wire.h"

#define MiniEncoderC_ADDR    0x42
#define ENCODER_REG          0x00
#define INCREMENT_REG        0x10
#define BUTTON_REG           0x20
#define RGB_LED_REG          0x30
#define RESET_COUNTER_REG    0x40
#define FIRMWARE_VERSION_REG 0xFE
#define I2C_ADDRESS_REG      0xFF

class M5HatMiniEncoderC {
   private:
    uint8_t _addr;
    TwoWire* _wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);

   public:
    bool begin(TwoWire* wire = &Wire, uint8_t addr = MiniEncoderC_ADDR,
               uint8_t sda = 0, uint8_t scl = 26,
               uint32_t speed = 200000L);  // Default StickC Plus
    int32_t getEncoderValue();
    void setEncoderValue(int32_t value);
    uint32_t getIncrementValue();
    bool getButtonStatus();
    void setLEDColor(uint32_t rgb888color);
    uint8_t setI2CAddress(uint8_t addr);
    uint8_t getI2CAddress(void);
    uint8_t getFirmwareVersion(void);
    void resetCounter(void);
};

#endif

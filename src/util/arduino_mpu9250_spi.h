#pragma once

#include <stdint.h>

class SPIClass;

class MPU9250_SPI {
public:
    void begin(int16_t cs_pin);
    void begin(SPIClass* pSpi, int16_t cs_pin);

    uint8_t write(uint8_t reg_addr, uint8_t length, uint8_t * data);
    uint8_t read(uint8_t reg_addr, uint8_t length, uint8_t * data);
    uint8_t write_compass(uint8_t reg_addr, uint8_t length, uint8_t * data);
    uint8_t read_compass(uint8_t reg_addr, uint8_t length, uint8_t * data);

    uint8_t write(uint8_t addr, uint8_t value);
    uint8_t read(uint8_t addr);
private:
    void select();
    void deselect();

    int16_t cs_pin;
    SPIClass* p_spi;
};

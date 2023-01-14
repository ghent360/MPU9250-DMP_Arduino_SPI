#include <Arduino.h>
#include <SPI.h>
#include "arduino_mpu9250_spi.h"
#define MPU9250
#include "mpu_reg.h"

#define SPI_DATA_RATE       1000000 // 1MHz is the max speed of the MPU-9250
#define SPI_FAST_DATA_RATE 18000000 // 18MHz read INT and sensor data.
#define SPI_MODE           SPI_MODE3
#define READ_FLAG          0x80

void MPU9250_SPI::begin(int16_t cs) {
    begin(&SPI, cs);
}

void MPU9250_SPI::begin(SPIClass* pSpi, int16_t cs) {
    cs_pin = cs;
    p_spi = pSpi;
    pinMode(cs_pin, OUTPUT);
    deselect();
}

// Select slave IC by asserting CS pin
void MPU9250_SPI::select()
{
#ifdef TEENSYDUINO
  digitalWriteFast(cs_pin, LOW);
#else
  digitalWrite(cs_pin, LOW);
#endif
}

// Select slave IC by deasserting CS pin
void MPU9250_SPI::deselect()
{
#ifdef TEENSYDUINO
  digitalWriteFast(cs_pin, HIGH);
#else
  digitalWrite(cs_pin, HIGH);
#endif
}

uint8_t MPU9250_SPI::read(uint8_t reg_addr, uint8_t length, uint8_t *dest) {
  uint32_t data_rate = (reg_addr >= MPU_INT_STATUS && reg_addr <= MPU_S0_DO) ?
    SPI_FAST_DATA_RATE : SPI_DATA_RATE;
  p_spi->beginTransaction(SPISettings(data_rate, MSBFIRST, SPI_MODE));
  select();
#ifdef TEENSYDUINO
  delayNanoseconds(50);
#endif
  p_spi->transfer(reg_addr | READ_FLAG);

  uint8_t i;
  for (i = 0; i < length; i++) {
    dest[i] = p_spi->transfer(0x00);
  }

  deselect();
  p_spi->endTransaction();
#ifdef TEENSYDUINO
  delayNanoseconds(65);
#endif
  return i; // Return number of bytes written
}

uint8_t MPU9250_SPI::write(uint8_t reg_addr, uint8_t length, uint8_t *src) {
  p_spi->beginTransaction(SPISettings(SPI_DATA_RATE, MSBFIRST, SPI_MODE));
  select();
#ifdef TEENSYDUINO
  delayNanoseconds(50);
#endif
  p_spi->transfer(reg_addr);

  uint8_t i;
  for (i = 0; i < length; i++) {
    p_spi->transfer(src[i]);
  }

  deselect();
  p_spi->endTransaction();
#ifdef TEENSYDUINO
  delayNanoseconds(65);
#endif
  return i; // Return number of bytes written
}

uint8_t MPU9250_SPI::write(uint8_t reg_addr, uint8_t value) {
  p_spi->beginTransaction(SPISettings(SPI_DATA_RATE, MSBFIRST, SPI_MODE));
  select();
#ifdef TEENSYDUINO
  delayNanoseconds(50);
#endif
  p_spi->transfer(reg_addr);
  uint8_t result = p_spi->transfer(value);
  deselect();
  p_spi->endTransaction();
#ifdef TEENSYDUINO
  delayNanoseconds(65);
#endif
  return result;
}

uint8_t MPU9250_SPI::read(uint8_t reg_addr) {
  return write(reg_addr | READ_FLAG, 0xff);
}

uint8_t MPU9250_SPI::read_compass(uint8_t reg_addr, uint8_t length, uint8_t *dest) {
  write(MPU_S4_ADDR, (0x80 | MPU_COMPASS_ADDR));
  while (length > 0) {
    write(MPU_S4_REG, reg_addr++);
    uint8_t i2c_ctrl = read(MPU_S4_CTRL);
    write(MPU_S4_CTRL, 0x80|i2c_ctrl); // Start the transfer

    // Wait for the data to be ready
    uint32_t count = 0;
    while(((read(MPU_S4_CTRL) & 0b10000000) != 0) && (count++ < 1000)) { // Checks completion
    }
    if(count > 1000) {
        return 1;
    }
    *dest++ = read(MPU_S4_DI); // Read the data from the SLV4_DI register 
    length--;
  }
  return 0;
}

uint8_t MPU9250_SPI::write_compass(uint8_t reg_addr, uint8_t length, uint8_t *src) {
  write(MPU_S4_ADDR, MPU_COMPASS_ADDR);
  while (length > 0) {
    write(MPU_S4_REG, reg_addr++);
    write(MPU_S4_DO, *src++);
    uint8_t i2c_ctrl = read(MPU_S4_CTRL);
    write(MPU_S4_CTRL, 0x80|i2c_ctrl); // Start the transfer

    // Wait for the data to be ready
    uint32_t count = 0;
    while(((read(MPU_S4_CTRL) & 0b10000000) != 0) && (count++ < 1000)) { // Checks completion
    }
    if(count > 1000) {
        return 1;
    }
    length--;
  }
  return 0;
}
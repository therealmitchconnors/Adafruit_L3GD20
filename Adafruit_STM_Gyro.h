/***************************************************
  This is a library for the L3GD20 GYROSCOPE

  Designed specifically to work with the Adafruit L3GD20 Breakout 
  ----> https://www.adafruit.com/products/1032

  These sensors use I2C or SPI to communicate, 2 pins (I2C) 
  or 4 pins (SPI) are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Kevin "KTOWN" Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#ifndef __L3GD20_H__
#define __L3GD20_H__

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

#define L3GD20_ADDRESS                (0x6B)        // 1101011
#define L3GD20_POLL_TIMEOUT           (100)         // Maximum number of read attempts
#define L3GD20_ID                     (0b11010100)
#define L3G4200D_ADDRESS              (0x69)        // 0b01101001
#define L3G4200D_ID                   (0b11010011)

#define GYRO_SENSITIVITY_250DPS  (0.00875F)      // Roughly 22/256 for fixed point match
#define GYRO_SENSITIVITY_500DPS  (0.0175F)       // Roughly 45/256
#define GYRO_SENSITIVITY_2000DPS (0.070F)        // Roughly 18/256
#define GYRO_DPS_TO_RADS         (0.017453293F)  // degress/s to rad/s multiplier

class Adafruit_STM_Gyro
{
  public:
    typedef enum
    {                                               // DEFAULT    TYPE
      GYRO_REGISTER_WHO_AM_I            = 0x0F,   // 11010100   r
      GYRO_REGISTER_CTRL_REG1           = 0x20,   // 00000111   rw
      GYRO_REGISTER_CTRL_REG2           = 0x21,   // 00000000   rw
      GYRO_REGISTER_CTRL_REG3           = 0x22,   // 00000000   rw
      GYRO_REGISTER_CTRL_REG4           = 0x23,   // 00000000   rw
      GYRO_REGISTER_CTRL_REG5           = 0x24,   // 00000000   rw
      GYRO_REGISTER_REFERENCE           = 0x25,   // 00000000   rw
      GYRO_REGISTER_OUT_TEMP            = 0x26,   //            r
      GYRO_REGISTER_STATUS_REG          = 0x27,   //            r
      GYRO_REGISTER_OUT_X_L             = 0x28,   //            r
      GYRO_REGISTER_OUT_X_H             = 0x29,   //            r
      GYRO_REGISTER_OUT_Y_L             = 0x2A,   //            r
      GYRO_REGISTER_OUT_Y_H             = 0x2B,   //            r
      GYRO_REGISTER_OUT_Z_L             = 0x2C,   //            r
      GYRO_REGISTER_OUT_Z_H             = 0x2D,   //            r
      GYRO_REGISTER_FIFO_CTRL_REG       = 0x2E,   // 00000000   rw
      GYRO_REGISTER_FIFO_SRC_REG        = 0x2F,   //            r
      GYRO_REGISTER_INT1_CFG            = 0x30,   // 00000000   rw
      GYRO_REGISTER_INT1_SRC            = 0x31,   //            r
      GYRO_REGISTER_TSH_XH              = 0x32,   // 00000000   rw
      GYRO_REGISTER_TSH_XL              = 0x33,   // 00000000   rw
      GYRO_REGISTER_TSH_YH              = 0x34,   // 00000000   rw
      GYRO_REGISTER_TSH_YL              = 0x35,   // 00000000   rw
      GYRO_REGISTER_TSH_ZH              = 0x36,   // 00000000   rw
      GYRO_REGISTER_TSH_ZL              = 0x37,   // 00000000   rw
      GYRO_REGISTER_INT1_DURATION       = 0x38    // 00000000   rw
    } gyroRegisters_t;

    typedef enum
    {
      GYRO_RANGE_250DPS,
      GYRO_RANGE_500DPS,
      GYRO_RANGE_2000DPS
    } gyroRange_t;

    static const byte GYRO_ADDRESS_L3G4200D = L3G4200D_ADDRESS;

    typedef struct gyroData_s
    {
      float x;
      float y;
      float z;
    } gyroData;

    Adafruit_STM_Gyro(int8_t cs, int8_t mosi, int8_t miso, int8_t clk);
    Adafruit_STM_Gyro(void);

    bool begin(gyroRange_t rng=GYRO_RANGE_250DPS, byte addr=L3GD20_ADDRESS);
    void read(void);

    gyroData data;    // Last read will be available here

  private:
    void write8(gyroRegisters_t reg, byte value);
    byte read8(gyroRegisters_t reg);
    uint8_t SPIxfer(uint8_t x);
    byte address;
    gyroRange_t range;
    int8_t _miso, _mosi, _clk, _cs;
};

#endif
#pragma once
#include <stdint.h>

#include "arduino_mpu9250_i2c.h"
#include "arduino_mpu9250_spi.h"

#if !defined MPU6050 && !defined MPU9150 && !defined MPU6500 && !defined MPU9250
#error  Which gyro are you using? Define MPUxxxx in your compiler options.
#endif

/* Time for some messy macro work. =]
 * #define MPU9150
 * is equivalent to..
 * #define MPU6050
 * #define AK8975_SECONDARY
 *
 * #define MPU9250
 * is equivalent to..
 * #define MPU6500
 * #define AK8963_SECONDARY
 */
#if defined MPU9150
#ifndef MPU6050
#define MPU6050
#endif                          /* #ifndef MPU6050 */
#if defined AK8963_SECONDARY
#error "MPU9150 and AK8963_SECONDARY cannot both be defined."
#elif !defined AK8975_SECONDARY /* #if defined AK8963_SECONDARY */
#define AK8975_SECONDARY
#endif                          /* #if defined AK8963_SECONDARY */
#elif defined MPU9250           /* #if defined MPU9150 */
#ifndef MPU6500
#define MPU6500
#endif                          /* #ifndef MPU6500 */
#if defined AK8975_SECONDARY
#error "MPU9250 and AK8975_SECONDARY cannot both be defined."
#elif !defined AK8963_SECONDARY /* #if defined AK8975_SECONDARY */
#define AK8963_SECONDARY
#endif                          /* #if defined AK8975_SECONDARY */
#endif                          /* #if defined MPU9150 */

#if defined AK8975_SECONDARY || defined AK8963_SECONDARY
#define AK89xx_SECONDARY
#else
/* #warning "No compass = less profit for Invensense. Lame." */
#endif

/* Hardware registers needed by driver. */

#if defined MPU6050
#define	MPU_XG_OFFSET_H      0x06
#define MPU_XG_OFFSET_L      0x07
#define MPU_YG_OFFSET_H      0x08
#define MPU_YG_OFFSET_L      0x09
#define MPU_ZG_OFFSET_H      0x0A
#define MPU_ZG_OFFSET_L      0x0B
#define MPU_SELF_TEST_X      0x0D
#define MPU_SELF_TEST_Y      0x0E
#define MPU_SELF_TEST_Z      0x0F
#define MPU_WHO_AM_I         0x75
#define MPU_RATE_DIV         0x19
#define MPU_LPF              0x1A
#define MPU_PROD_ID          0x0C
#define MPU_USER_CTRL        0x6A
#define MPU_FIFO_EN          0x23
#define MPU_GYRO_CFG         0x1B
#define MPU_ACCEL_CFG        0x1C
#define MPU_MOTION_THR       0x1F
#define MPU_MOTION_DUR       0x20
#define MPU_FIFO_COUNT_H     0x72
#define MPU_FIFO_R_W         0x74
#define MPU_RAW_GYRO         0x43
#define MPU_RAW_ACCEL        0x3B
#define MPU_TEMP             0x41
#define MPU_INT_ENABLE       0x38
#define MPU_DMP_INT_STATUS   0x39
#define MPU_INT_STATUS       0x3A
#define MPU_PWR_MGMT_1       0x6B
#define MPU_PWR_MGMT_2       0x6C
#define MPU_INT_PIN_CFG      0x37
#define MPU_MEM_R_W          0x6F
#define MPU_ACCEL_OFFS       0x06
#define MPU_I2C_MST          0x24
#define MPU_BANK_SEL         0x6D
#define MPU_MEM_START_ADDR   0x6E
#define MPU_PRGM_START_H     0x70
#define MPU_RAW_COMPASS      0x49
#define MPU_S0_ADDR          0x25
#define MPU_S0_REG           0x26
#define MPU_S0_CTRL          0x27
#define MPU_S0_DO            0x63
#define MPU_S1_ADDR          0x28
#define MPU_S1_REG           0x29
#define MPU_S1_CTRL          0x2A
#define MPU_S1_DO            0x64
#define MPU_S2_ADDR          0x2B
#define MPU_S2_REG           0x2C
#define MPU_S2_CTRL          0x2D
#define MPU_S2_DO            0x65
#define MPU_S3_ADDR          0x2E
#define MPU_S3_REG           0x2F
#define MPU_S3_CTRL          0x30
#define MPU_S3_DO            0x66
#define MPU_S4_ADDR          0x31
#define MPU_S4_REG           0x32
#define MPU_S4_DO            0x33
#define MPU_S4_CTRL          0x34
#define MPU_S4_DI            0x35
#define MPU_I2C_DELAY_CTRL   0x67

#define MPU_I2C_ADDR       0x68
#define MPU_MAX_FIFO       1024
#define MPU_NUM_REG        118
#define MPU_TEMP_SENS      340
#define MPU_TEMP_OFFSET    -521
#define MPU_BANK_SIZE      256
#if defined AK89xx_SECONDARY
#define MPU_COMPASS_FSR    AK89xx_FSR
#endif

#define MPU_GYRO_SENS      (32768/250)
#define MPU_ACCEL_SENS     (32768/16)
#define MPU_REG_RATE_DIV   0    /* 1kHz. */
#define MPU_REG_LPF        1    /* 188Hz. */
#define MPU_REG_GYRO_FSR   0    /* 250dps. */
#define MPU_REG_ACCEL_FSR  0x18 /* 16g. */
#define MPU_WAIT_MS        50
#define MPU_PACKET_THRESH  5    /* 5% */
#define MPU_MIN_DPS        10.f
#define MPU_MAX_DPS        105.f
#define MPU_MAX_GYRO_VAR   0.14f
#define MPU_MIN_G          0.3f
#define MPU_MAX_G          0.95f
#define MPU_MAX_ACCEL_VAR  0.14f

#elif defined MPU6500
#define MPU_SELF_TEST_XG     0x0
#define MPU_SELF_TEST_YG     0x1
#define MPU_SELF_TEST_ZG     0x2
#define MPU_SELF_TEST_XA     0x0D
#define MPU_SELF_TEST_YA     0x0E
#define MPU_SELF_TEST_ZA     0x0F
#define	MPU_XG_OFFSET_H      0x13
#define MPU_XG_OFFSET_L      0x14
#define MPU_YG_OFFSET_H      0x15
#define MPU_YG_OFFSET_L      0x16
#define MPU_ZG_OFFSET_H      0x17
#define MPU_ZG_OFFSET_L      0x18
#define MPU_WHO_AM_I         0x75
#define MPU_RATE_DIV         0x19
#define MPU_LPF              0x1A
#define MPU_PROD_ID          0x0C
#define MPU_USER_CTRL        0x6A
#define MPU_FIFO_EN          0x23
#define MPU_GYRO_CFG         0x1B
#define MPU_ACCEL_CFG        0x1C
#define MPU_ACCEL_CFG2       0x1D
#define MPU_LP_ACCEL_ODR     0x1E
#define MPU_MOTION_THR       0x1F
#define MPU_MOTION_DUR       0x20
#define MPU_FIFO_COUNT_H     0x72
#define MPU_FIFO_R_W         0x74
#define MPU_RAW_GYRO         0x43
#define MPU_RAW_ACCEL        0x3B
#define MPU_TEMP             0x41
#define MPU_INT_ENABLE       0x38
#define MPU_DMP_INT_STATUS   0x39
#define MPU_INT_STATUS       0x3A
#define MPU_ACCEL_INTEL      0x69
#define MPU_PWR_MGMT_1       0x6B
#define MPU_PWR_MGMT_2       0x6C
#define MPU_INT_PIN_CFG      0x37
#define MPU_MEM_R_W          0x6F
#define MPU_ACCEL_OFFS       0x77
#define MPU_I2C_MST          0x24
#define MPU_BANK_SEL         0x6D
#define MPU_MEM_START_ADDR   0x6E
#define MPU_PRGM_START_H     0x70
#define MPU_XA_OFFSET_H      0x77
#define MPU_XA_OFFSET_L      0x78
#define MPU_YA_OFFSET_H      0x7A
#define MPU_YA_OFFSET_L      0x7B
#define MPU_ZA_OFFSET_H      0x7D
#define MPU_ZA_OFFSET_L      0x7E
#define MPU_RAW_COMPASS      0x49
#define MPU_S4_CTRL          0x34
#define MPU_S0_ADDR          0x25
#define MPU_S0_REG           0x26
#define MPU_S0_CTRL          0x27
#define MPU_S0_DO            0x63
#define MPU_S1_ADDR          0x28
#define MPU_S1_REG           0x29
#define MPU_S1_CTRL          0x2A
#define MPU_S1_DO            0x64
#define MPU_S2_ADDR          0x2B
#define MPU_S2_REG           0x2C
#define MPU_S2_CTRL          0x2D
#define MPU_S2_DO            0x65
#define MPU_S3_ADDR          0x2E
#define MPU_S3_REG           0x2F
#define MPU_S3_CTRL          0x30
#define MPU_S3_DO            0x66
#define MPU_S4_ADDR          0x31
#define MPU_S4_REG           0x32
#define MPU_S4_DO            0x33
#define MPU_S4_CTRL          0x34
#define MPU_S4_DI            0x35
#define MPU_I2C_DELAY_CTRL   0x67

#define MPU_ADDR           0x68
#define MPU_MAX_FIFO       1024
#define MPU_NUM_REG        128
#define MPU_TEMP_SENS      321
#define MPU_TEMP_OFFSET    0
#define MPU_BANK_SIZE      256
#if defined AK89xx_SECONDARY
#define MPU_COMPASS_FSR    AK89xx_FSR
#endif

#define MPU_GYRO_SENS      (32768/250)
#define MPU_ACCEL_SENS     (32768/2)  //FSR = +-2G = 16384 LSB/G
#define MPU_REG_RATE_DIV   0     //1kHz.
#define MPU_REG_LPF        2     //92Hz low pass filter
#define MPU_REG_GYRO_FSR   0     //250dps.
#define MPU_REG_ACCEL_FSR  0x0   //Accel FSR setting 2g.
#define MPU_WAIT_MS        200   //200ms stabilization time
#define MPU_PACKET_THRESH  200   //200 samples
#define MPU_MIN_DPS        20.f  //20 dps for Gyro Criteria C
#define MPU_MAX_DPS        60.f  //Must exceed 60 dps threshold for Gyro Criteria B
#define MPU_MAX_GYRO_VAR   .5f   //Must exceed +50% variation for Gyro Criteria A
#define MPU_MIN_G          .225f //Accel must exceed Min 225 mg for Criteria B
#define MPU_MAX_G          .675f //Accel cannot exceed Max 675 mg for Criteria B
#define MPU_MAX_ACCEL_VAR  .5f   //Accel must be within 50% variation for Criteria A
#define MPU_MAX_G_OFFSET   .5f   //500 mg for Accel Criteria C
#define MPU_SAMPLE_WAIT_MS 10    //10ms sample time wait

#else
#error Unsupported MPU
#endif

#define MPU_COMPASS_ADDR 0x0C

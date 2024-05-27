#ifndef __MY_MPU_H
#define __MY_MPU_H

#include "main.h"

typedef enum{
    SELF_TEST_X_GYRO    = 0x00,
    SELF_TEST_Y_GYRO    = 0x01, 
    SELF_TEST_Z_GYRO    = 0x02,
    SELF_TEST_X_ACCEL   = 0x0D,
    SELF_TEST_Y_ACCEL   = 0x0E,
    SELF_TEST_Z_ACCEL   = 0x0F,
    XG_OFFSET_H         = 0x13,
    XG_OFFSET_L         = 0x14,
    YG_OFFSET_H         = 0x15,
    YG_OFFSET_L         = 0x16,
    ZG_OFFSET_H         = 0x17,
    ZG_OFFSET_L         = 0x18,
    SMPLRT_DIV          = 0x19,
    CONFIG              = 0x1A,
    GYRO_CONFIG         = 0x1B,
    ACCEL_CONFIG        = 0x1C,
    ACCEL_CONFIG2       = 0x1D,
    LP_ACCEL_ODR        = 0x1E,
    WOM_THR             = 0x1F,
    FIFO_EN             = 0x23,
    I2C_MST_CTRL        = 0x24,
    INT_PIN_CFG         = 0x37,
    INT_ENABLE          = 0x38,
    INT_STATUS          = 0x3A,
    ACCEL_XOUT_H        = 0x3B,
    ACCEL_XOUT_L        = 0x3C,
    ACCEL_YOUT_H        = 0x3D,
    ACCEL_YOUT_L        = 0x3E,
    ACCEL_ZOUT_H        = 0x3F,
    ACCEL_ZOUT_L        = 0x40,
    TEMP_OUT_H          = 0x41,
    TEMP_OUT_L          = 0x42,
    GYRO_XOUT_H         = 0x43,
    GYRO_XOUT_L         = 0x44,
    GYRO_YOUT_H         = 0x45,
    GYRO_YOUT_L         = 0x46,
    GYRO_ZOUT_H         = 0x47,
    GYRO_ZOUT_L         = 0x48,
    WHOAMI              = 0x75,
    USER_CTRL           = 0x6A,
    PWR_MGMT_1          = 0x6B, 
    PWR_MGMT_2          = 0x6C,
    READ                = 0x80
}MPU_Address;

typedef enum{
    GYRO_250_FS = 0x00,
    GYRO_500_FS = 0x01,
    GYRO_1000_FS = 0x10,
    GYRO_2000_FS = 0x11
}MPU_Gyro_Scale;

typedef enum{
    ACCEL_2G_FS = 0x00,
    ACCEL_4G_FS = 0x01,
    ACCEL_8G_FS = 0x10,
    ACCEL_16G_FS = 0x11
}MPU_Accel_Scale;

typedef enum{
    DLPF_disable = 0x000,
    DLPF_1 = 0x001, // for gyroscope, rate 1kHz, delay 2.9ms
    DLPF_2 = 0x010, // for accelerometer, rate 1kHz, delay 2.88ms
    DLPF_3 = 0x011,
    DLPF_4 = 0x100,
    DLPF_5 = 0x101,
    DLPF_6 = 0x110,
    DLPF_7 = 0x111 
}DLPF_Mode;

typedef struct{
    SPI_HandleTypeDef* port;
    double accel_scale;
    double gyro_scale;
    MPU_Accel_Scale MPU_accel_scale;
    MPU_Gyro_Scale MPU_gyro_scale;

    DLPF_Mode a_DLFP_mode, g_DLFP_mode; 
}MPU;

typedef enum{
    OK = 1,
    ERR = 0
} MPU_STATUS;

MPU_STATUS init(MPU*, SPI_HandleTypeDef*, MPU_Accel_Scale, MPU_Gyro_Scale, DLPF_Mode, DLPF_Mode);

#endif
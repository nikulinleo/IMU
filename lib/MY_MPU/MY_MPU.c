#include "MY_MPU.h"

MPU_STATUS init(MPU* mpu, SPI_HandleTypeDef* spi_instance,
                MPU_Accel_Scale ascale, MPU_Gyro_Scale gscale, DLPF_Mode accel_filter, DLPF_Mode gyro_filter){
    
    mpu -> port = spi_instance;
    mpu -> MPU_accel_scale = ascale;
    mpu -> MPU_gyro_scale = gscale;
    mpu -> a_DLFP_mode = accel_filter;
    mpu -> g_DLFP_mode = gyro_filter;

    double a_scale = 2.0;
    switch (ascale)
    {
    case ACCEL_4G_FS:
        a_scale = 4.0;
        break;
    case ACCEL_8G_FS:
        a_scale = 8.0;
        break;
    case ACCEL_16G_FS:
        a_scale = 16.0;
    }
    mpu -> accel_scale = a_scale;

    double g_scale = 250.0;
    switch (gscale)
    {
    case GYRO_500_FS:
        g_scale = 500.0;
        break;
    case GYRO_1000_FS:
        g_scale = 1000.0;
        break;
    case GYRO_2000_FS:
        g_scale = 2000.0;
        break;
    }
    mpu -> gyro_scale = g_scale;

    uint8_t tx_data[24] = { PWR_MGMT_1, 0x80,
                            USER_CTRL, 0x10, 
                            PWR_MGMT_1, 0x00, 
                            PWR_MGMT_1, 0x01,
                            CONFIG, mpu->g_DLFP_mode,
                            SMPLRT_DIV, 0x00,
                            GYRO_CONFIG, (mpu->MPU_gyro_scale) << 3, 
                            ACCEL_CONFIG, (mpu->MPU_accel_scale) << 3, 
                            ACCEL_CONFIG2, mpu->a_DLFP_mode ,
                            INT_PIN_CFG, 0x32,
                            INT_ENABLE, 0x01,
                            WHOAMI|READ, 0x00,
                            };
    uint8_t rx_data[24];

    for(int i = 0; i < 12; ++i){
        HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_RESET);
        HAL_SPI_TransmitReceive(mpu->port, tx_data + i*2, rx_data + i*2, 2, 500);
        HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_SET);
        HAL_Delay(10);
    }
    

    if(rx_data[23] != 0x70) {return ERR;}

    return OK;

    //HAL_SPI_TransmitReceive(mpu_instance -> port, , )
};
#include "spi.h"

void spi_config(void)
{
    spi_parameter_struct spi_init_struct;
    /* deinitialize SPI and the parameters */
    rcu_periph_clock_enable(RCU_SPI1);
    spi_i2s_deinit(SPI1);
    spi_struct_para_init(&spi_init_struct);

    /* configure SPI1 parameter */
    spi_init_struct.trans_mode = SPI_BIDIRECTIONAL_TRANSMIT;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
    spi_init_struct.nss = SPI_NSS_SOFT;
    spi_init_struct.prescale = SPI_PSC_32;
    spi_init_struct.endian = SPI_ENDIAN_MSB;
    spi_init(SPI1, &spi_init_struct);

    spi_enable(SPI1);

    // nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
    // nvic_irq_enable(SPI0_IRQn, 1, 1);
}
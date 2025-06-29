/**
 **************************************************
 *
 * @file        nRF24-SOLDERED.h
 * @brief       Header file for nRF24 board library.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Zvonimir Haramustek for soldered.com
 ***************************************************/

#ifndef __NRF24_SOLDERED__
#define __NRF24_SOLDERED__

#include <SPI.h>

#include "libs/RF24/RF24.h"
#include "libs/RF24/printf.h"

class nRF24 : public RF24
{
  public:
    nRF24(uint16_t _cepin, uint16_t _cspin, uint32_t _spi_speed = RF24_SPI_SPEED) : RF24(_cepin, _cspin, _spi_speed)
    {
    }
    nRF24(uint32_t _spi_speed = RF24_SPI_SPEED) : RF24(_spi_speed)
    {
    }

  protected:
  private:
};

#endif

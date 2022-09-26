#include "drivers/stm32f446xx_spi.h"

namespace Drivers
{
    // Peripheral clock setup
    void SPI::PeriClockControl(Core::Reg::Def::SPI_t *pSPIx, Core::State enabled)
    {
        if(enabled == Core::State::ENABLE)
        {
            if(pSPIx == Core::Reg::SPI1){ Core::Clock::SPI1_PCLK_EN(); }
            else if(pSPIx == Core::Reg::SPI2){ Core::Clock::SPI2_PCLK_EN(); }
            else if(pSPIx == Core::Reg::SPI3){ Core::Clock::SPI3_PCLK_EN(); }
        }
        else
        {
            if(pSPIx == Core::Reg::SPI1){ Core::Clock::SPI1_PCLK_DI(); }
            else if(pSPIx == Core::Reg::SPI2){ Core::Clock::SPI2_PCLK_DI(); }
            else if(pSPIx == Core::Reg::SPI3){ Core::Clock::SPI3_PCLK_DI(); }
        }
    }

    // Inid and de-init
    void SPI::Init(Handle_t *pSPIx)
    {
        // Configure SPI_CR1 register

        uint32_t tempreg = 0;

        // 1. Configure the device mode
        Core::Bit::Range::Set(tempreg, static_cast<uint8_t>(pSPIx->config.deviceMode) << 2);

        // 2. Configure the bus config
        if(pSPIx->config.busConfig == BusConfig::FullDuplex)
        {
            // BIDIMODE clear
            Core::Bit::Clear(tempreg, 15);
        }
        else if(pSPIx->config.busConfig == BusConfig::HalfDuplex)
        {
            // BIDIMODE set
            Core::Bit::Set(tempreg, 15);
        }
        else if(pSPIx->config.busConfig == BusConfig::SimplexRxOnly)
        {
            // BIDIMODE clear
            Core::Bit::Clear(tempreg, 15);
            // RXONLY set
            Core::Bit::Clear(tempreg, 10);
        }

        // 3. Configure spi serial clock
        Core::Bit::Range::Set(tempreg, static_cast<uint8_t>(pSPIx->config.deviceMode) << 3);

        // 4. Configure DFF
        Core::Bit::Range::Set(tempreg, static_cast<uint8_t>(pSPIx->config.dff) << 11);

        // 5. Configure CPOL
        Core::Bit::Range::Set(tempreg, static_cast<uint8_t>(pSPIx->config.dff) << 1);

        // 5. Configure CPHA
        Core::Bit::Range::Set(tempreg, static_cast<uint8_t>(pSPIx->config.dff) << 0);

        pSPIx->pSPIx->CR1 = tempreg;
    }

    void SPI::DeInit(Core::Reg::Def::SPI_t *pSPIx)
    {
        if(pSPIx == Core::Reg::SPI1){ Core::Clock::SPI1_REG_RESET(); }
        else if(pSPIx == Core::Reg::SPI2){ Core::Clock::SPI2_REG_RESET(); }
        else if(pSPIx == Core::Reg::SPI3){ Core::Clock::SPI3_REG_RESET(); }
    }

    void SPI::PeriControl(Core::Reg::Def::SPI_t *pSPIx, Core::State enabled)
    {
        if(enabled == Core::State::ENABLE)
        {
            Core::Bit::Set(pSPIx->CR1, 6);
        }
        else
        {
            Core::Bit::Clear(pSPIx->CR1, 6);
        }
    }

    void SPI::SendData(Core::Reg::Def::SPI_t *pSPIx, uint8_t *pTxBuffer, uint32_t lenght)
    {
        while(lenght)
        {
            while(!Core::Bit::IsSet(pSPIx->SR, 1));

            if(Core::Bit::IsSet(pSPIx->CR1, 11))
            {
                // 16 bit DFF
                auto buff = reinterpret_cast<uint16_t*>(pTxBuffer);
                pSPIx->DR = *(buff);
                lenght--;
                lenght--;
                buff++;
            }
            else
            {
                // 8 bit DFF
                pSPIx->DR = *pTxBuffer;
                lenght--;
                pTxBuffer++;
            }
        }
    }

    void SPI::ReceiveData(Core::Reg::Def::SPI_t *pSPIx, uint8_t *pRxBuffer, uint32_t lenght)
    {

    }

    void SPI::IRQInterruptConfig(Core::IRQ::Number IRQNumber, Core::State enabled)
    {

    }

    void SPI::IRQPriorityConfig(Core::IRQ::Number IRQNumber, Core::IRQ::Priority IRQpriority)
    {

    }

    void SPI::IRQHandler(Handle_t *pHandle)
    {

    }
}


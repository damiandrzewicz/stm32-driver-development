#pragma once
#include "core/stm32f446xx.h"

namespace Drivers
{
    class SPI
    {
    public:

        enum class DeviceMode
        {
            Slave,
            Master
        };

        enum class BusConfig
        {
            FullDuplex,
            HalfDuplex,
            SimplexRxOnly
        };

        enum class SclkSpeed
        {
            Div2,
            Div4, 
            Div8,
            Div16,
            Div32,
            Div64,
            Div128,
            Div256
        };

        enum class DFF
        {
            Bit8,
            Bit16
        };

        enum class CPOL
        {
            Low,
            High
        };

        enum class CPHA
        {
            Low,
            High
        };

        enum class SSM
        {
            Off,
            On
        };

        typedef struct
        {
            DeviceMode deviceMode;
            BusConfig busConfig;
            SclkSpeed sclkSpeed;
            DFF dff;
            CPOL cpol;
            CPHA cpha;
            SSM ssm;
        }Config_t;
        

        typedef struct 
        {
            Core::Reg::Def::SPI_t *pSPIx;
            Config_t config;
        }Handle_t;
        
        // Peripheral clock setup
        static void PeriClockControl(Core::Reg::Def::SPI_t *pSPIx, Core::State enabled);

        // Inid and de-init
        static void Init(Handle_t *pSPIx);
        static void DeInit(Core::Reg::Def::SPI_t *pSPIx);

        static void PeriControl(Core::Reg::Def::SPI_t *pSPIx, Core::State enabled);

        static void SendData(Core::Reg::Def::SPI_t *pSPIx, uint8_t *pTxBuffer, uint32_t lenght);
        static void ReceiveData(Core::Reg::Def::SPI_t *pSPIx, uint8_t *pRxBuffer, uint32_t lenght);

        static void IRQInterruptConfig(Core::IRQ::Number IRQNumber, Core::State enabled);
        static void IRQPriorityConfig(Core::IRQ::Number IRQNumber, Core::IRQ::Priority IRQpriority);
        static void IRQHandler(Handle_t *pHandle); 

    private:
    };
}
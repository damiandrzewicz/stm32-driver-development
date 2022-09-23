#pragma once

namespace Drivers
{
    class SPI
    {
    public:

        enum class DeviceMode
        {

        };
        enum class BusConfig
        {

        };
        enum class SclkSpeed
        {

        };
        enum class DFF
        {

        };
        enum class CPOL
        {

        };
        enum class CPHA
        {

        };
        enum class SSM
        {

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
            Config_t config;
        }Handle_t;
        

    private:
    };
}
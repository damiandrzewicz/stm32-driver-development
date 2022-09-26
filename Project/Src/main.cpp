#include <cstring>
#include "core/stm32f446xx.h"
#include "drivers/stm32f446xx_gpio.h"
#include "drivers/stm32f446xx_spi.h"

// SPI2 - AF5
// PB15 - MOSI
// PB14 - MISO
// PB13 - SCK
// PB12 - NSS


int main()
{
    /** Initialization  */
    // Core::Clock::GPIOA_PCLK_EN();
    // Core::Clock::GPIOC_PCLK_EN();

    // Drivers::GPIO::Handle_t gpioLed = {};

    // gpioLed.pGPIOx = Core::Reg::GPIOA;
    // gpioLed.pinConfig.number = Drivers::GPIO::PinNumber::PIN5;
    // gpioLed.pinConfig.mode = Drivers::GPIO::Mode::Out;
    // gpioLed.pinConfig.speed = Drivers::GPIO::Speed::LOW;
    // gpioLed.pinConfig.oType = Drivers::GPIO::OutputType::PP;
    // gpioLed.pinConfig.puPdControl = Drivers::GPIO::PuPd::NoPuPd;
    // Drivers::GPIO::Init(&gpioLed);

    // Drivers::GPIO::Handle_t button = {};

    // button.pGPIOx = Core::Reg::GPIOC;
    // button.pinConfig.number = Drivers::GPIO::PinNumber::PIN13;
    // button.pinConfig.mode = Drivers::GPIO::Mode::IT_FE;
    // button.pinConfig.speed = Drivers::GPIO::Speed::HIGH;
    // button.pinConfig.puPdControl = Drivers::GPIO::PuPd::NoPuPd;
    // Drivers::GPIO::Init(&button);

    // Drivers::GPIO::IRQInterruptConfig(Core::IRQ::Number::EXTI15_10, true);
    // Drivers::GPIO::IRQPriorityConfig(Core::IRQ::Number::EXTI15_10, Core::IRQ::Priority::PRI15);

    // SPI
    Drivers::GPIO::PeriClockControl(Core::Reg::GPIOB, true);

    Drivers::GPIO::Handle_t spiPin = {};

    spiPin.pGPIOx = Core::Reg::GPIOB;
    spiPin.pinConfig.mode = Drivers::GPIO::Mode::Alt;
    spiPin.pinConfig.pinAltFunMode = 5;
    spiPin.pinConfig.oType = Drivers::GPIO::OutputType::PP;
    spiPin.pinConfig.puPdControl = Drivers::GPIO::PuPd::NoPuPd;
    spiPin.pinConfig.speed = Drivers::GPIO::Speed::LOW;

    // SCLK
    spiPin.pinConfig.number = Drivers::GPIO::PinNumber::PIN13;
    Drivers::GPIO::Init(&spiPin);

    // MOSI
    spiPin.pinConfig.number = Drivers::GPIO::PinNumber::PIN15;
    Drivers::GPIO::Init(&spiPin);

    // MOSI
    spiPin.pinConfig.number = Drivers::GPIO::PinNumber::PIN14;
    Drivers::GPIO::Init(&spiPin);

    // NSS
    spiPin.pinConfig.number = Drivers::GPIO::PinNumber::PIN12;
    Drivers::GPIO::Init(&spiPin);

    Drivers::SPI::PeriClockControl(Core::Reg::SPI2, Core::State::ENABLE);

    Drivers::SPI::Handle_t spi2 = {};
    spi2.pSPIx = Core::Reg::SPI2;
    spi2.config.busConfig = Drivers::SPI::BusConfig::FullDuplex;
    spi2.config.deviceMode = Drivers::SPI::DeviceMode::Master;
    spi2.config.sclkSpeed = Drivers::SPI::SclkSpeed::Div2;
    spi2.config.dff = Drivers::SPI::DFF::Bit8;
    spi2.config.ssm = Drivers::SPI::SSM::On;

    Drivers::SPI::Init(&spi2);
    Drivers::SPI::PeriControl(spi2.pSPIx, Core::State::ENABLE);

    char buff[] = "Hello World!";

    Drivers::SPI::SendData(spi2.pSPIx, reinterpret_cast<uint8_t*>(buff), strlen(buff));

    /** Infinite loop */
    while(1)
    {
        // auto value = Drivers::GPIO::ReadFromInputPin(Core::Reg::GPIOC, Drivers::GPIO::PinNumber::PIN13);
        // if(value == Core::Bit::State::RESET)
        // {   
        //     //for(uint32_t i = 0; i < 800000; i++);
        //     Drivers::GPIO::ToggleOutputPin(Core::Reg::GPIOA, Drivers::GPIO::PinNumber::PIN5);
        // }
        
        //for(uint32_t i = 0; i < 800000; i++);
    }
}

extern "C" 
{
    // void EXTI15_10_IRQHandler(void)
    // {
    //     Drivers::GPIO::IRQHandler(Drivers::GPIO::PinNumber::PIN13);
    //     Drivers::GPIO::ToggleOutputPin(Core::Reg::GPIOA, Drivers::GPIO::PinNumber::PIN5);
    // }
}


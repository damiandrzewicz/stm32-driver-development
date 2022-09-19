#include "core/stm32f446xx.h"
#include "drivers/stm32f446xx_gpio.h"

int main()
{
    /** Initialization  */
    Core::Clock::GPIOA_PCLK_EN();
    Core::Clock::GPIOC_PCLK_EN();

    Drivers::GPIO::Handle_t gpioLed;
    gpioLed.pGPIOx = Core::Reg::GPIOA;
    gpioLed.pinConfig.number = Drivers::GPIO::PinNumber::PIN5;
    gpioLed.pinConfig.mode = Drivers::GPIO::Mode::Out;
    gpioLed.pinConfig.speed = Drivers::GPIO::Speed::LOW;
    gpioLed.pinConfig.oType = Drivers::GPIO::OutputType::PP;
    gpioLed.pinConfig.puPdControl = Drivers::GPIO::PuPd::NoPuPd;
    Drivers::GPIO::Init(&gpioLed);

    Drivers::GPIO::Handle_t button;
    button.pGPIOx = Core::Reg::GPIOC;
    button.pinConfig.number = Drivers::GPIO::PinNumber::PIN13;
    button.pinConfig.mode = Drivers::GPIO::Mode::In;
    button.pinConfig.speed = Drivers::GPIO::Speed::HIGH;
    button.pinConfig.puPdControl = Drivers::GPIO::PuPd::NoPuPd;
    Drivers::GPIO::Init(&button);

    /** Infinite loop */
    while(1)
    {
        auto value = Drivers::GPIO::ReadFromInputPin(Core::Reg::GPIOC, Drivers::GPIO::PinNumber::PIN13);
        if(value == Core::Bit::State::RESET)
        {   
            //for(uint32_t i = 0; i < 800000; i++);
            Drivers::GPIO::ToggleOutputPin(Core::Reg::GPIOA, Drivers::GPIO::PinNumber::PIN5);
        }
        
        //for(uint32_t i = 0; i < 800000; i++);
    }
}
#include <cstring>
#include "core/stm32f446xx.h"
#include "drivers/stm32f446xx_gpio.h"



int main()
{
    /** Initialization  */
    Core::Clock::GPIOA_PCLK_EN();
    Core::Clock::GPIOC_PCLK_EN();

    Drivers::GPIO::Handle_t gpioLed = {};

    gpioLed.pGPIOx = Core::Reg::GPIOA;
    gpioLed.pinConfig.number = Drivers::GPIO::PinNumber::PIN5;
    gpioLed.pinConfig.mode = Drivers::GPIO::Mode::Out;
    gpioLed.pinConfig.speed = Drivers::GPIO::Speed::LOW;
    gpioLed.pinConfig.oType = Drivers::GPIO::OutputType::PP;
    gpioLed.pinConfig.puPdControl = Drivers::GPIO::PuPd::NoPuPd;
    Drivers::GPIO::Init(&gpioLed);

    Drivers::GPIO::Handle_t button = {};

    button.pGPIOx = Core::Reg::GPIOC;
    button.pinConfig.number = Drivers::GPIO::PinNumber::PIN13;
    button.pinConfig.mode = Drivers::GPIO::Mode::IT_FE;
    button.pinConfig.speed = Drivers::GPIO::Speed::HIGH;
    button.pinConfig.puPdControl = Drivers::GPIO::PuPd::NoPuPd;
    Drivers::GPIO::Init(&button);

    Drivers::GPIO::IRQInterruptConfig(Core::IRQ::Number::EXTI15_10, true);
    Drivers::GPIO::IRQPriorityConfig(Core::IRQ::Number::EXTI15_10, Core::IRQ::Priority::PRI15);

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
    void EXTI15_10_IRQHandler(void)
    {
        Drivers::GPIO::IRQHandler(Drivers::GPIO::PinNumber::PIN13);
        Drivers::GPIO::ToggleOutputPin(Core::Reg::GPIOA, Drivers::GPIO::PinNumber::PIN5);
    }
}


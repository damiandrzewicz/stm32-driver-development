#include "core/stm32f446xx.h"
#include "drivers/stm32f446xx_gpio.h"

int main()
{
    /** Initialization  */
    Core::Clock::GPIOA_PCLK_EN();
    Core::Clock::GPIOH_PCLK_EN();

    /** Infinite loop */
    while(1)
    {
        
    }
}
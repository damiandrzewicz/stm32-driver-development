#include "drivers/stm32f446xx_gpio.h"

namespace Drivers
{
    void GPIO::PeriClockControl(Core::Reg::Def::GPIO_t *pGPIOx, bool enabled)
    {
        if(enabled)
        {
            if(pGPIOx == Core::Reg::GPIOA){ Core::Clock::GPIOA_PCLK_EN(); }
            else if(pGPIOx == Core::Reg::GPIOB){ Core::Clock::GPIOB_PCLK_EN(); }
            else if(pGPIOx == Core::Reg::GPIOC){ Core::Clock::GPIOC_PCLK_EN(); }
            else if(pGPIOx == Core::Reg::GPIOD){ Core::Clock::GPIOD_PCLK_EN(); }
            else if(pGPIOx == Core::Reg::GPIOE){ Core::Clock::GPIOE_PCLK_EN(); }
            else if(pGPIOx == Core::Reg::GPIOF){ Core::Clock::GPIOF_PCLK_EN(); }
            else if(pGPIOx == Core::Reg::GPIOG){ Core::Clock::GPIOG_PCLK_EN(); }
            else if(pGPIOx == Core::Reg::GPIOH){ Core::Clock::GPIOH_PCLK_EN(); }
        }
        else
        {
            if(pGPIOx == Core::Reg::GPIOA){ Core::Clock::GPIOA_PCLK_DI(); }
            else if(pGPIOx == Core::Reg::GPIOB){ Core::Clock::GPIOB_PCLK_DI(); }
            else if(pGPIOx == Core::Reg::GPIOC){ Core::Clock::GPIOC_PCLK_DI(); }
            else if(pGPIOx == Core::Reg::GPIOD){ Core::Clock::GPIOD_PCLK_DI(); }
            else if(pGPIOx == Core::Reg::GPIOE){ Core::Clock::GPIOE_PCLK_DI(); }
            else if(pGPIOx == Core::Reg::GPIOF){ Core::Clock::GPIOF_PCLK_DI(); }
            else if(pGPIOx == Core::Reg::GPIOG){ Core::Clock::GPIOG_PCLK_DI(); }
            else if(pGPIOx == Core::Reg::GPIOH){ Core::Clock::GPIOH_PCLK_DI(); }
        }
    }

    void GPIO::Init(GPIO::Handle_t *pGPIOHandle)
    {
        uint32_t temp;
        // mode
        if(static_cast<uint8_t>(pGPIOHandle->pinConfig.mode) < static_cast<uint8_t>(Mode::Analog))
        {
            // Non-interrupt modes
            
            temp = static_cast<uint32_t>(pGPIOHandle->pinConfig.mode) << (2 * static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
            Core::Bit::Range::Clear(pGPIOHandle->pGPIOx->MODER, 0x3 << static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
            Core::Bit::Range::Set(pGPIOHandle->pGPIOx->MODER, temp);
            temp = 0;
        }
        else
        {
            // interrupt modes
            // TODO
        }

        // speed
        temp = static_cast<uint32_t>(pGPIOHandle->pinConfig.speed) << (2 * static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
        Core::Bit::Range::Clear(pGPIOHandle->pGPIOx->OSPEEDR, 0x3 << static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
        Core::Bit::Range::Set(pGPIOHandle->pGPIOx->OSPEEDR, temp);
        temp = 0;

        // pullup pulldown
        temp = static_cast<uint32_t>(pGPIOHandle->pinConfig.puPdControl) << (2 * static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
        Core::Bit::Range::Clear(pGPIOHandle->pGPIOx->PUPDR, 0x3 << static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
        Core::Bit::Range::Set(pGPIOHandle->pGPIOx->PUPDR, temp);
        temp = 0;

        // output type
        temp = static_cast<uint32_t>(pGPIOHandle->pinConfig.oType) << static_cast<uint32_t>(pGPIOHandle->pinConfig.number);
        Core::Bit::Range::Clear(pGPIOHandle->pGPIOx->OTYPER, 0x1 << static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
        Core::Bit::Range::Set(pGPIOHandle->pGPIOx->OTYPER, temp);
        temp = 0;

        // alt function
        if(static_cast<uint32_t>(pGPIOHandle->pinConfig.mode) == static_cast<uint8_t>(Mode::Alt))
        {
            uint8_t temp1, temp2;

            temp1 = static_cast<uint8_t>(pGPIOHandle->pinConfig.number) / 8;
            temp2 = static_cast<uint8_t>(pGPIOHandle->pinConfig.number) % 8;
            Core::Bit::Range::Clear(pGPIOHandle->pGPIOx->AFR[temp1], 0xF << static_cast<uint32_t>(4 * temp2));
            Core::Bit::Range::Set(
                pGPIOHandle->pGPIOx->AFR[temp1], static_cast<uint32_t>(pGPIOHandle->pinConfig.pinAltFunMode) << (4 * temp2));
        }
    }

    void GPIO::DeInit(Core::Reg::Def::GPIO_t *pGPIOx)
    {

        if(pGPIOx == Core::Reg::GPIOA){ Core::Clock::GPIOA_REG_RESET(); }
        else if(pGPIOx == Core::Reg::GPIOB){ Core::Clock::GPIOB_REG_RESET(); }
        else if(pGPIOx == Core::Reg::GPIOC){ Core::Clock::GPIOC_REG_RESET(); }
        else if(pGPIOx == Core::Reg::GPIOD){ Core::Clock::GPIOD_REG_RESET(); }
        else if(pGPIOx == Core::Reg::GPIOE){ Core::Clock::GPIOE_REG_RESET(); }
        else if(pGPIOx == Core::Reg::GPIOF){ Core::Clock::GPIOF_REG_RESET(); }
        else if(pGPIOx == Core::Reg::GPIOG){ Core::Clock::GPIOG_REG_RESET(); }
        else if(pGPIOx == Core::Reg::GPIOH){ Core::Clock::GPIOH_REG_RESET(); }

    }

    Core::Bit::State GPIO::ReadFromInputPin(Core::Reg::Def::GPIO_t *pGPIOx, PinNumber pinNumber)
    {
        return static_cast<Core::Bit::State>((static_cast<uint32_t>(pGPIOx->IDR) >> static_cast<uint8_t>(pinNumber)) & 0x00000001);
    }

    uint16_t GPIO::ReadFromInputPort(Core::Reg::Def::GPIO_t *pGPIOx)
    {
        return static_cast<uint16_t>(pGPIOx->IDR);
    }

    void GPIO::WriteToOutputPin(Core::Reg::Def::GPIO_t *pGPIOx, PinNumber pinNumber, Core::Bit::State value)
    {
        if(value == Core::Bit::SET)
        {
            Core::Bit::Set(pGPIOx->ODR, static_cast<uint8_t>(value));
        }
        else
        {
            Core::Bit::Clear(pGPIOx->ODR, static_cast<uint8_t>(value));
        }
    }

    void GPIO::WriteToOutputPort(Core::Reg::Def::GPIO_t *pGPIOx, uint16_t value)
    {
        pGPIOx->ODR = value;
    }

    void GPIO::ToggleOutputPin(Core::Reg::Def::GPIO_t *pGPIOx, PinNumber pinNumber)
    {
        Core::Bit::Xor(pGPIOx->ODR, static_cast<uint8_t>(pinNumber));
    }

    void GPIO::IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t enabled)
    {

    }

    void GPIO::IRQHandling(PinNumber pinNumber)
    {

    }
}


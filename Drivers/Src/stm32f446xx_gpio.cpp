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
            // Interrupt modes

            // 1. configure falling/rising/falling&rising selection registers
            if(static_cast<uint8_t>(pGPIOHandle->pinConfig.mode) == static_cast<uint8_t>(Mode::IT_FE))
            {
                Core::Bit::Set(Core::Reg::EXTI->FTSR, static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
                Core::Bit::Clear(Core::Reg::EXTI->RTSR, static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
            }
            else if(static_cast<uint8_t>(pGPIOHandle->pinConfig.mode) == static_cast<uint8_t>(Mode::IT_RE))
            {
                Core::Bit::Set(Core::Reg::EXTI->RTSR, static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
                Core::Bit::Clear(Core::Reg::EXTI->FTSR, static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
            }
            else if(static_cast<uint8_t>(pGPIOHandle->pinConfig.mode) == static_cast<uint8_t>(Mode::IT_RFE))
            {
                Core::Bit::Set(Core::Reg::EXTI->RTSR, static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
                Core::Bit::Set(Core::Reg::EXTI->FTSR, static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
            }

            // 2. Configure GPIO port selection in SYSCFG_EXTICR
            uint8_t temp1 = static_cast<uint32_t>(pGPIOHandle->pinConfig.number) / 4;
            uint8_t temp2 = static_cast<uint32_t>(pGPIOHandle->pinConfig.number) % 4;
            uint8_t portcode = Core::Util::GPIO_ADDR_TO_CODE(pGPIOHandle->pGPIOx);
            Core::Clock::SYSCFG_PCLK_EN();
            Core::Bit::Range::Set(Core::Reg::SYSCFG->EXTICR[temp1], portcode << (temp2 * 4));


            // 3. Enable the EXTI interrupt delivery in IMR
            Core::Bit::Set(Core::Reg::EXTI->IMR, static_cast<uint32_t>(pGPIOHandle->pinConfig.number));
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

    Core::State GPIO::ReadFromInputPin(Core::Reg::Def::GPIO_t *pGPIOx, PinNumber pinNumber)
    {
        return static_cast<Core::State>((static_cast<uint32_t>(pGPIOx->IDR) >> static_cast<uint8_t>(pinNumber)) & 0x00000001);
    }

    uint16_t GPIO::ReadFromInputPort(Core::Reg::Def::GPIO_t *pGPIOx)
    {
        return static_cast<uint16_t>(pGPIOx->IDR);
    }

    void GPIO::WriteToOutputPin(Core::Reg::Def::GPIO_t *pGPIOx, PinNumber pinNumber, Core::State value)
    {
        if(value == Core::State::SET)
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

    void GPIO::IRQInterruptConfig(Core::IRQ::Number IRQNumber, bool enabled)
    {
        auto irqNo = static_cast<uint8_t>(IRQNumber);
        if(enabled)
        {
            if(irqNo <= 31)
            {
                Core::Bit::Set(*Core::Addr::ARMCortexMx::NVIC_ISER0, irqNo);
            }
            else if(irqNo > 31 && irqNo < 64)
            {
                Core::Bit::Set(*Core::Addr::ARMCortexMx::NVIC_ISER1, irqNo % 32);
            }
            else if(irqNo > 64 && irqNo < 96)
            {
                Core::Bit::Set(*Core::Addr::ARMCortexMx::NVIC_ISER3, irqNo % 64);
            }
        }
        else
        {
            if(irqNo <= 31)
            {
                Core::Bit::Clear(*Core::Addr::ARMCortexMx::NVIC_ICER0, irqNo);
            }
            else if(irqNo > 31 && irqNo < 64)
            {
                Core::Bit::Clear(*Core::Addr::ARMCortexMx::NVIC_ICER1, irqNo % 32);
            }
            else if(irqNo > 64 && irqNo < 96)
            {
                Core::Bit::Clear(*Core::Addr::ARMCortexMx::NVIC_ICER3, irqNo % 64);
            }
        }
    }

    void GPIO::IRQPriorityConfig(Core::IRQ::Number IRQNumber, Core::IRQ::Priority IRQpriority)
    {
        auto irqNo = static_cast<uint8_t>(IRQNumber);
        uint8_t iprx = irqNo / 4;
        uint8_t iprxSection = irqNo % 4;

        auto irqPr = static_cast<uint32_t>(IRQpriority);
        uint8_t shift_amount = (8 * iprxSection) + (8 - Core::Addr::ARMCortexMx::NO_PR_BITS_IMPLEMENTED);
        *(Core::Addr::ARMCortexMx::NVIC_PR + iprx) = *(Core::Addr::ARMCortexMx::NVIC_PR + iprx) | (irqPr << shift_amount);
        //Core::Bit::Range::Set(*(Core::Addr::ARMCortexMx::NVIC_PR + iprx), (irqPr << shift_amount));
    }

    void GPIO::IRQHandler(PinNumber pinNumber)
    {
        auto pinNo = static_cast<uint8_t>(pinNumber);
        if((Core::Reg::EXTI->PR) & (1 << pinNo))
        {
            Core::Bit::Set(Core::Reg::EXTI->PR, (1 << pinNo));
        }
    }
}


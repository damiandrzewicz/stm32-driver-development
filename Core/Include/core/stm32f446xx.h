#pragma once
#include <cstdint>

namespace Core
{
    namespace Addr
    {
        namespace ARMCortexMx
        {
            static auto NVIC_ISER0    = reinterpret_cast<volatile uint32_t*>(0xE000E100U);
            static auto NVIC_ISER1    = reinterpret_cast<volatile uint32_t*>(0xE000E104U);
            static auto NVIC_ISER2    = reinterpret_cast<volatile uint32_t*>(0xE000E108U);
            static auto NVIC_ISER3    = reinterpret_cast<volatile uint32_t*>(0xE000E10CU);

            static auto NVIC_ICER0    = reinterpret_cast<volatile uint32_t*>(0xE000E180U);
            static auto NVIC_ICER1    = reinterpret_cast<volatile uint32_t*>(0xE000E184U);
            static auto NVIC_ICER2    = reinterpret_cast<volatile uint32_t*>(0xE000E188U);
            static auto NVIC_ICER3    = reinterpret_cast<volatile uint32_t*>(0xE000E18CU);

            static auto NVIC_PR    = reinterpret_cast<volatile uint32_t*>(0xE000E18CU);

            constexpr auto NO_PR_BITS_IMPLEMENTED = 4;
        }
        namespace Base
        {
            constexpr auto FLASH    = 0x08000000U;      // Flash Memory
            constexpr auto SRAM1    = 0x20000000U;      // SRAM1 Memory
            constexpr auto SRAM2    = 0x2001C000U;      // SRAM2 Memory
            constexpr auto ROM      = 0x1FFF0000U;      // System Memory
            constexpr auto OTP      = 0x1FFF7800U;      // OPT Area Memory
            constexpr auto SRAM     = SRAM1;            // SRAM starts from SRAM1
        }

        namespace Bus
        {
            constexpr auto BASE     = 0x40000000U;
            constexpr auto APB1     = BASE;
            constexpr auto APB2     = 0x40010000U;
            constexpr auto AHB1     = 0x40020000U;
            constexpr auto AHB2     = 0x50000000U;
        }

        namespace Periph
        {
            // Peripherial addresses from AHB1
            constexpr auto GPIOA    = Bus::AHB1 + 0x0000U;
            constexpr auto GPIOB    = Bus::AHB1 + 0x0400U;
            constexpr auto GPIOC    = Bus::AHB1 + 0x0800U;
            constexpr auto GPIOD    = Bus::AHB1 + 0x0C00U;
            constexpr auto GPIOE    = Bus::AHB1 + 0x1000U;
            constexpr auto GPIOF    = Bus::AHB1 + 0x1400U;
            constexpr auto GPIOG    = Bus::AHB1 + 0x1800U;
            constexpr auto GPIOH    = Bus::AHB1 + 0x1C00U;

            // Peripherial addresses from APB1
            constexpr auto I2C1    = Bus::APB1 + 0x0000U;
            constexpr auto I2C2    = Bus::APB1 + 0x5800U;
            constexpr auto I2C3    = Bus::APB1 + 0x5C00U;
            constexpr auto SPI2    = Bus::APB1 + 0x3800U;
            constexpr auto SPI3    = Bus::APB1 + 0x3C00U;
            constexpr auto USART2  = Bus::APB1 + 0x4400U;
            constexpr auto USART3  = Bus::APB1 + 0x4800U;
            constexpr auto UART4   = Bus::APB1 + 0x4C00U;
            constexpr auto UART5   = Bus::APB1 + 0x5000U;

            // Peripherial addresses from APB2
            constexpr auto SPI1    = Bus::APB2 + 0x3000U;
            constexpr auto USART1  = Bus::APB2 + 0x1000U;
            constexpr auto USART6  = Bus::APB2 + 0x1400U;
            constexpr auto EXTI    = Bus::APB2 + 0x3C00U;
            constexpr auto SYSCFG  = Bus::APB2 + 0x3800U;

            constexpr auto RCC     = Bus::AHB1 + 0x3800U;
        }
    }

    namespace Reg
    {
        namespace Def
        {
            typedef struct
            {
                volatile uint32_t MODER;
                volatile uint32_t OTYPER;
                volatile uint32_t OSPEEDR;
                volatile uint32_t PUPDR;
                volatile uint32_t IDR;
                volatile uint32_t ODR;
                volatile uint32_t BSRR;
                volatile uint32_t LCKR;
                volatile uint32_t AFR[2];
            } GPIO_t;

            typedef struct
            {
                volatile uint32_t CR;
                volatile uint32_t PLLCFGR;
                volatile uint32_t CFGR;
                volatile uint32_t CIR;
                volatile uint32_t AHB1RSTR;
                volatile uint32_t AHB2RSTR;
                volatile uint32_t AHB3RSTR;
                volatile uint32_t RESERVED0;
                volatile uint32_t APB1RSTR;
                volatile uint32_t APB2RSTR;
                volatile uint32_t RESERVED1[2];
                volatile uint32_t AHB1ENR;
                volatile uint32_t AHB2ENR;
                volatile uint32_t AHB3ENR;
                volatile uint32_t RESERVED2;
                volatile uint32_t APB1ENR;
                volatile uint32_t APB2ENR;
                volatile uint32_t RESERVED3[2];
                volatile uint32_t AHB1LPENR;
                volatile uint32_t AHB2LPENR;
                volatile uint32_t AHB3LPENR;
                volatile uint32_t RESERVED4;
                volatile uint32_t APB1LPENR;
                volatile uint32_t APB2LPENR;
                volatile uint32_t RESERVED5[2];
                volatile uint32_t BDCR;
                volatile uint32_t CSR;
                volatile uint32_t RESERVED6[2];
                volatile uint32_t SSCGR;
                volatile uint32_t PLLI2SCFGR;
                volatile uint32_t PLLSAICFGR;
                volatile uint32_t DCKCFGR;
                volatile uint32_t CKGATENR;
                volatile uint32_t DCKCFGR2;
            } RCC_t;

            typedef struct
            {
                volatile uint32_t IMR;
                volatile uint32_t EMR;
                volatile uint32_t RTSR;
                volatile uint32_t FTSR;
                volatile uint32_t SWIER;
                volatile uint32_t PR;
            } EXTI_t;

            typedef struct
            {
                volatile uint32_t MEMRMP;
                volatile uint32_t PMC;
                volatile uint32_t EXTICR[4];
                uint32_t RESERVED1[2];
                volatile uint32_t CMPCR;
                uint32_t RESERVED2[2];
                volatile uint32_t CFGR;
            } SYSCFG_t;
        }

        // GPIO
        static auto GPIOA = reinterpret_cast<Def::GPIO_t*>(Addr::Periph::GPIOA);
        static auto GPIOB    = reinterpret_cast<Def::GPIO_t*>(Addr::Periph::GPIOB);
        static auto GPIOC    = reinterpret_cast<Def::GPIO_t*>(Addr::Periph::GPIOC);
        static auto GPIOD    = reinterpret_cast<Def::GPIO_t*>(Addr::Periph::GPIOD);
        static auto GPIOE    = reinterpret_cast<Def::GPIO_t*>(Addr::Periph::GPIOE);
        static auto GPIOF    = reinterpret_cast<Def::GPIO_t*>(Addr::Periph::GPIOF);
        static auto GPIOG    = reinterpret_cast<Def::GPIO_t*>(Addr::Periph::GPIOG);
        static auto GPIOH    = reinterpret_cast<Def::GPIO_t*>(Addr::Periph::GPIOH);

        // RCC
        static auto RCC      = reinterpret_cast<Def::RCC_t*>(Addr::Periph::RCC);

        // EXIT
        static auto EXTI     = reinterpret_cast<Def::EXTI_t*>(Addr::Periph::EXTI);

        // SYSCFG
        static auto SYSCFG   = reinterpret_cast<Def::SYSCFG_t*>(Addr::Periph::SYSCFG);
    }

    namespace Bit
    {
        static auto Set    = [](auto &pReg, auto bit){ pReg = pReg | (1 << bit); };
        static auto Clear  = [](auto &pReg, auto bit){ pReg = pReg & ~(1 << bit); };
        static auto Xor = [](auto &pReg, auto bit){ pReg = pReg ^ (1 << bit); };

        enum class State
        {
            RESET = 0,
            DISABLE = 0,
            SET = 1,
            ENABLE = 1
        };

        namespace Range
        {
            static auto Set    = [](auto &pReg, auto value){ pReg = pReg | value; };
            static auto Clear  = [](auto &pReg, auto value){ pReg = pReg & ~value; };
        }
    }
    

    namespace Clock
    {
        // GPIOx
        static auto GPIOA_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 0); };
        static auto GPIOB_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 1); };
        static auto GPIOC_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 2); };
        static auto GPIOD_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 3); };
        static auto GPIOE_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 4); };
        static auto GPIOF_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 5); };
        static auto GPIOG_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 6); };
        static auto GPIOH_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 7); };

        static auto GPIOA_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 0); };
        static auto GPIOB_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 1); };
        static auto GPIOC_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 2); };
        static auto GPIOD_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 3); };
        static auto GPIOE_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 4); };
        static auto GPIOF_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 5); };
        static auto GPIOG_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 6); };
        static auto GPIOH_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 7); };

        static auto GPIOA_REG_RESET = [](){ Bit::Set(Reg::RCC->AHB1RSTR, 0); Bit::Clear(Reg::RCC->AHB1RSTR, 0); };
        static auto GPIOB_REG_RESET = [](){ Bit::Set(Reg::RCC->AHB1RSTR, 1); Bit::Clear(Reg::RCC->AHB1RSTR, 1); };
        static auto GPIOC_REG_RESET = [](){ Bit::Set(Reg::RCC->AHB1RSTR, 2); Bit::Clear(Reg::RCC->AHB1RSTR, 2); };
        static auto GPIOD_REG_RESET = [](){ Bit::Set(Reg::RCC->AHB1RSTR, 3); Bit::Clear(Reg::RCC->AHB1RSTR, 3); };
        static auto GPIOE_REG_RESET = [](){ Bit::Set(Reg::RCC->AHB1RSTR, 4); Bit::Clear(Reg::RCC->AHB1RSTR, 4); };
        static auto GPIOF_REG_RESET = [](){ Bit::Set(Reg::RCC->AHB1RSTR, 5); Bit::Clear(Reg::RCC->AHB1RSTR, 5); };
        static auto GPIOG_REG_RESET = [](){ Bit::Set(Reg::RCC->AHB1RSTR, 6); Bit::Clear(Reg::RCC->AHB1RSTR, 6); };
        static auto GPIOH_REG_RESET = [](){ Bit::Set(Reg::RCC->AHB1RSTR, 7); Bit::Clear(Reg::RCC->AHB1RSTR, 7); };

        // I2Cx
        static auto I2C1_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 21); };
        static auto I2C2_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 22); };
        static auto I2C3_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 23); };

        static auto I2C1_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 21); };
        static auto I2C2_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 22); };
        static auto I2C3_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 23); };

        // SPIx
        static auto SPI1_PCLK_EN = [](){ Bit::Set(Reg::RCC->APB2ENR, 12); };
        static auto SPI2_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB3ENR, 14); };
        static auto SPI3_PCLK_EN = [](){ Bit::Set(Reg::RCC->AHB1ENR, 15); };

        static auto SPI1_PCLK_DI = [](){ Bit::Clear(Reg::RCC->APB2ENR, 12); };
        static auto SPI2_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB3ENR, 14); };
        static auto SPI3_PCLK_DI = [](){ Bit::Clear(Reg::RCC->AHB1ENR, 15); };

        // USART
        static auto USART1_PCLK_EN = [](){ Bit::Set(Reg::RCC->APB2ENR, 4); };
        static auto USART2_PCLK_EN = [](){ Bit::Set(Reg::RCC->APB1ENR, 17); };
        static auto USART3_PCLK_EN = [](){ Bit::Set(Reg::RCC->APB1ENR, 18); };
        static auto UART4_PCLK_EN  = [](){ Bit::Set(Reg::RCC->APB1ENR, 19); };
        static auto UART5_PCLK_EN  = [](){ Bit::Set(Reg::RCC->APB1ENR, 20); };
        static auto USART6_PCLK_EN = [](){ Bit::Set(Reg::RCC->APB2ENR, 5); };

        static auto USART1_PCLK_DI = [](){ Bit::Clear(Reg::RCC->APB2ENR, 4); };
        static auto USART2_PCLK_DI = [](){ Bit::Clear(Reg::RCC->APB1ENR, 17); };
        static auto USART3_PCLK_DI = [](){ Bit::Clear(Reg::RCC->APB1ENR, 18); };
        static auto UART4_PCLK_DI  = [](){ Bit::Clear(Reg::RCC->APB1ENR, 19); };
        static auto UART5_PCLK_DI  = [](){ Bit::Clear(Reg::RCC->APB1ENR, 20); };
        static auto USART6_PCLK_DI = [](){ Bit::Clear(Reg::RCC->APB2ENR, 5); };

        // SYSCFG
        static auto SYSCFG_PCLK_EN = [](){ Bit::Set(Reg::RCC->APB2ENR, 14); };
        static auto SYSCFG_PCLK_DI = [](){ Bit::Clear(Reg::RCC->APB2ENR, 14); };
    }

    enum class IRQ
    {
        EXTI0 = 6,
        EXTI1,
        EXTI2,
        EXTI3,
        EXTI4,
        EXTI9_5 = 23,
        EXTI15_10 = 40
    };

    namespace Util
    {
        static auto GPIO_ADDR_TO_CODE = [](const auto &reg){ 
            return (reg == Reg::GPIOA) ? 0 :
                   (reg == Reg::GPIOB) ? 1 :
                   (reg == Reg::GPIOC) ? 2 :
                   (reg == Reg::GPIOD) ? 3 :
                   (reg == Reg::GPIOE) ? 4 :
                   (reg == Reg::GPIOF) ? 5 :
                   (reg == Reg::GPIOG) ? 6 :
                   (reg == Reg::GPIOH) ? 7 : 0;
         };
    }
}


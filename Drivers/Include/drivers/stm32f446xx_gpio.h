#pragma once

#include "core/stm32f446xx.h"

namespace Drivers
{
    class GPIO
    {
    public:
        enum class PinNumber{
            PIN1 = 1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7,PIN8,
            PIN9,PIN10,PIN11,PIN12,PIN13,PIN14,PIN15
        };

        enum class Mode{
            In = 0,
            Out = 1,
            Alt = 2,
            Analog = 3,
            IT_FE = 4,      // Falling edge
            IT_RE = 5,      // Rising edge
            IT_RFE = 6      // Falling-rising edge
        };

        enum class OutputType{
            PP = 0,         // Push-pull
            OP = 1          // Open drain
        };

        enum class Speed{
            LOW = 0,
            MEDIUM = 1,
            FASH = 2,
            HIGH = 3
        };

        enum class PuPd{
            NoPuPd = 0,
            Pu = 1,
            Pd = 2
        };

        typedef struct
        {
            PinNumber number;
            Mode mode;
            Speed speed;
            PuPd puPdControl;
            OutputType oType;
            uint8_t pinAltFunMode;
        } PinConfig_t;

        typedef struct
        {
            Core::Reg::Def::GPIO_t *pGPIOx;         // Pointer to hold base address of the GPIO peripheral
            PinConfig_t pinConfig;
        } Handle_t;

        // API
        static void PeriClockControl(Core::Reg::Def::GPIO_t *pGPIOx, bool enabled);

        static void Init(GPIO::Handle_t *pGPIOHandle);
        static void DeInit(Core::Reg::Def::GPIO_t *pGPIOx);

        static Core::State ReadFromInputPin(Core::Reg::Def::GPIO_t *pGPIOx, PinNumber pinNumber);
        static uint16_t ReadFromInputPort(Core::Reg::Def::GPIO_t *pGPIOx);
        static void WriteToOutputPin(Core::Reg::Def::GPIO_t *pGPIOx, PinNumber pinNumber, Core::State state);
        static void WriteToOutputPort(Core::Reg::Def::GPIO_t *pGPIOx, uint16_t value);
        static void ToggleOutputPin(Core::Reg::Def::GPIO_t *pGPIOx, PinNumber pinNumber);

        static void IRQInterruptConfig(Core::IRQ::Number IRQNumber, bool enabled);
        static void IRQPriorityConfig(Core::IRQ::Number IRQNumber, Core::IRQ::Priority IRQpriority);
        static void IRQHandler(PinNumber pinNumber); 


    };
};
#pragma once

#include "core/stm32f446xx.h"

namespace Drivers
{
    class GPIO
    {
    public:
        typedef struct
        {
            uint8_t Number;
            uint8_t Mode;
            uint8_t Speed;
            uint8_t PuPdControl;
            uint8_t OType;
            uint8_t PinAltFunMode;
        } PinConfig_t;

        typedef struct
        {
            Core::Reg::Def::GPIO_t *pGPIOx;         // Pointer to hold base address of the GPIO peripheral
            PinConfig_t PinConfig;
        } Handle_t;

        // API
        void Init();
        void DeInit();
        void PeriClockControl();
        void ReadFromInputPin();
        void ReadFromInputPort();
        void WriteToOutputPin();
        void WriteToOutputPort();
        void ToggleOutputPin();
        void IRQConfig();
        void IRQHandling(); 


    };
};
//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "VolumeRotaryEncoder.h"
#include <Arduino.h>
#include "SystemParameters.h"

const int8_t DebounceTime_ms = 1;

VolumeRotaryEncoder::VolumeRotaryEncoder(DigitalPotmeter& digitalPotmeter) :
    m_digitalPotmeter(digitalPotmeter),
    m_pinALast(0),
    m_debouncer(DebounceTime_ms),
    m_lastTimeUserAction(0)
{
    pinMode (Pin::VolumeEncoderA, INPUT_PULLUP);
    pinMode (Pin::VolumeEncoderB, INPUT_PULLUP);

    pinMode(Pin::RotaryEncoderType, INPUT_PULLUP);

    m_pinALast = digitalRead(Pin::VolumeEncoderA);
}

void VolumeRotaryEncoder::checkRotation()
{
    int8_t valuePinA = digitalRead(Pin::VolumeEncoderA);
    m_debouncer.updateInputState(valuePinA);

    if (m_debouncer.inputChanged())
    { 
        // There exist two kinds of rotaryencoders which use opposite directions. The difference is the length of the knob.
        int8_t rotaryEncoderType = digitalRead(Pin::RotaryEncoderType);

        // Means the knob is rotating.      
        // If the knob is rotating, we need to determine direction.
        // We do that by reading pin B.      
        if (digitalRead(Pin::VolumeEncoderB) != valuePinA) 
        {  
            if (rotaryEncoderType)
                m_digitalPotmeter.down();
            else
                m_digitalPotmeter.up();
        }
        else 
        {
            if (rotaryEncoderType)
                m_digitalPotmeter.up();
            else
                m_digitalPotmeter.down();
        } 
        m_pinALast = valuePinA;
        
        m_lastTimeUserAction = millis();
    }
}

unsigned long VolumeRotaryEncoder::getLastTimeUserAction() const
{
    return m_lastTimeUserAction;
}

//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "VolumeRotaryEncoder.h"
#include <Arduino.h>
#include "SystemParameters.h"

const int DebounceTime_ms = 1;

VolumeRotaryEncoder::VolumeRotaryEncoder(DigitalPotmeter& digitalPotmeter) :
    m_digitalPotmeter(digitalPotmeter),
    m_pinALast(0),
    m_debouncer(DebounceTime_ms)
{
       pinMode (Pin::VolumeEncoderA, INPUT_PULLUP);
       pinMode (Pin::VolumeEncoderB, INPUT_PULLUP);

       m_pinALast = digitalRead(Pin::VolumeEncoderA);
}

void VolumeRotaryEncoder::checkRotation()
{
    int valuePinA = digitalRead(Pin::VolumeEncoderA);
    m_debouncer.updateInputState(valuePinA);

    if (m_debouncer.inputChanged())
    { 
        // Means the knob is rotating.      
        // If the knob is rotating, we need to determine direction.
        // We do that by reading pin B.      
        if (digitalRead(Pin::VolumeEncoderB) != valuePinA) 
        {  
            // Means pin A Changed first - We're Rotating Clockwise        
            m_digitalPotmeter.up();
        }
        else 
        {
            // Otherwise B changed first and we're moving CCW        
            m_digitalPotmeter.down();
        } 
        m_pinALast = valuePinA;
    }
}



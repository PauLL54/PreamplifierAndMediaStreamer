//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "VolumeRotaryEncoder.h"
#include <Arduino.h>

const int pinA = 18;  // PC4
const int pinB = 19;  // PC5
const int BounceTime_ms = 1;

VolumeRotaryEncoder::VolumeRotaryEncoder(DigitalPotmeter& digitalPotmeter) :
    m_digitalPotmeter(digitalPotmeter),
    m_pinALast(0),
    m_debouncer(BounceTime_ms)
{
       pinMode (pinA, INPUT_PULLUP);
       pinMode (pinB, INPUT_PULLUP);

       m_pinALast = digitalRead(pinA);
}

void VolumeRotaryEncoder::checkRotation()
{
    int valuePinA = digitalRead(pinA);
    m_debouncer.updateInputState(valuePinA);

    if (m_debouncer.inputChanged())
    { 
        // Means the knob is rotating.      
        // If the knob is rotating, we need to determine direction.
        // We do that by reading pin B.      
        if (digitalRead(pinB) != valuePinA) 
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



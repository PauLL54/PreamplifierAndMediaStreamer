//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "VolumeRotaryEncoder.h"
#include <Arduino.h>

const int pinA = 19;  // PC5
const int pinB = 18;  // PC4
const int BounceMaxCount = 10;

VolumeRotaryEncoder::VolumeRotaryEncoder() :
    m_pinALast(0),
    m_debouncer(BounceMaxCount)
{
       pinMode (pinA, INPUT);
       pinMode (pinB, INPUT);

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
            //encoderPosCount ++;
        }
        else 
        {
          // Otherwise B changed first and we're moving CCW        
          //encoderPosCount--;      
        } 
        m_pinALast = valuePinA;
    }
}



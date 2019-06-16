//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "NeoPixelRing.h"

const int pinLedRing = 17; // PC3
const int NumberOfLeds = 24;
const int Max5Bits = 31;

NeoPixelRing::NeoPixelRing() :
    m_LedRing(NumberOfLeds, pinLedRing)
{
}

void NeoPixelRing::set5bitsValue(int _5bitsValue)
{
    m_LedRing.begin();
    m_LedRing.setBrightness(50);

    uint16_t ledValue = 0.5 + _5bitsValue * NumberOfLeds / Max5Bits; // normalize

    for (uint16_t i = 0; i < NumberOfLeds; i++) 
    {  
        if (i >= ledValue)               
            m_LedRing.setPixelColor(i, 0, 0, 0);
        else if (i >= 20)               
            m_LedRing.setPixelColor(i, 255, 0, 0);      // red
        else if (i >= 16)               
            m_LedRing.setPixelColor(i, 255, 165, 0);    // orange
        else 
            m_LedRing.setPixelColor(i, 255, 255, 255);  // white
    }

    m_LedRing.show();
}

//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "NeoPixelRing.h"
#include "SystemParameters.h"

const int NumberOfLeds = 24;
const int Max5Bits = 31;
const int DefaultBrightness = 50;

NeoPixelRing::NeoPixelRing() :
    m_LedRing(NumberOfLeds, Pin::NeoPixelLedRing)
{
}

void NeoPixelRing::set5bitsValue(int _5bitsValue)
{
    m_LedRing.begin();
    m_LedRing.setBrightness(DefaultBrightness);

    uint16_t ledValue = 0.5 + _5bitsValue * NumberOfLeds / Max5Bits; // normalize

    // white:
    uint8_t r_white = 255;
    uint8_t g_white = 255;
    uint8_t b_white = 155;

    // green:
    uint8_t r_green = 0;
    uint8_t g_green = 255;
    uint8_t b_green = 0;

    for (uint16_t i = 0; i < NumberOfLeds; i++) 
    {  
        if (i >= ledValue)               
            m_LedRing.setPixelColor(i, r_green, g_green, b_green);
        else 
            m_LedRing.setPixelColor(i, r_white, g_white, b_white);
    }

    m_LedRing.show();
}

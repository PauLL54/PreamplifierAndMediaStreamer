//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "NeoPixelRing.h"
#include "SystemParameters.h"

const int NumberOfLeds = 24;
const int DefaultBrightness = 10;

NeoPixelRing::NeoPixelRing() :
    m_LedRing(NumberOfLeds, Pin::NeoPixelLedRing)
{
}

void NeoPixelRing::setValue(int value, int maxValue)
{
    m_LedRing.begin();
    m_LedRing.setBrightness(DefaultBrightness);

    uint16_t ledValue = 0.5 + float(value) * NumberOfLeds / maxValue; // normalize

    // colorPixelsFromLeft:
    // white:  255, 255, 155
    // orange: 255, 100, 0
    uint8_t r_colorPixelsFromLeft = 255;
    uint8_t g_colorPixelsFromLeft = 100;
    uint8_t b_colorPixelsFromLeft = 0;

    // colorPixelsFromRight: (black)
    uint8_t r_colorPixelsFromRight = 0;
    uint8_t g_colorPixelsFromRight = 0;
    uint8_t b_colorPixelsFromRight = 0;

    for (uint16_t i = 0; i < NumberOfLeds; i++) 
    {  
        if (i >= ledValue)               
            m_LedRing.setPixelColor(i, r_colorPixelsFromRight, g_colorPixelsFromRight, b_colorPixelsFromRight);
        else 
            m_LedRing.setPixelColor(i, r_colorPixelsFromLeft, g_colorPixelsFromLeft, b_colorPixelsFromLeft);
    }

    m_LedRing.show();
}

void NeoPixelRing::disableDisplay()
{
	m_LedRing.clear();
    m_LedRing.show();
}


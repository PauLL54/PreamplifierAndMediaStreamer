//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "NeoPixelRing.h"
#include "SystemParameters.h"

const int8_t NumberOfLeds = 24;
const int8_t DefaultBrightness = 10;

NeoPixelRing::NeoPixelRing() :
    m_LedRing(NumberOfLeds, Pin::NeoPixelLedRing),
    m_lastValue(0),
    m_lastMaxValue(0)
{
}

void NeoPixelRing::setValue(int8_t value, int8_t maxValue)
{
    m_lastValue = value;
    m_lastMaxValue = maxValue;

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
    m_enabled = true;
}

void NeoPixelRing::disableDisplay()
{
	m_LedRing.clear();
    m_LedRing.show();
    m_enabled = false;
}

void NeoPixelRing::enableDisplay()
{
    if (!m_enabled)
        setValue(m_lastValue, m_lastMaxValue);
}

//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "NeoPixelRing.h"
#include <avr/power.h>

const int pinLedRing = 16; // PC2
const int NumberOfLeds = 24;

NeoPixelRing::NeoPixelRing() :
    m_LedRing(pinLedRing, NumberOfLeds)
{
}

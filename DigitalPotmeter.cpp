//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "DigitalPotmeter.h"
#include "SystemParameters.h"

DigitalPotmeter::DigitalPotmeter() :
    XicorX9514(Pin::DigitalPotmeterUp, Pin::DigitalPotmeterDown),
    m_neoPixelRing()
{
}

void DigitalPotmeter::enableDisplay()
{
    m_neoPixelRing.enableDisplay();
}

void DigitalPotmeter::disableDisplay()
{
    m_neoPixelRing.disableDisplay();
}

void DigitalPotmeter::onNewValue(int8_t actualValue, int8_t maxSteps)
{
    m_neoPixelRing.setValue(actualValue, maxSteps);
}
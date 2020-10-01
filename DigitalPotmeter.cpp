//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "DigitalPotmeter.h"
#include "SystemParameters.h"
#include <EEPROM.h>
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

void DigitalPotmeter::initChannelValues()
{
    for (int i = 0; i < 8; ++i)
    {
        int8_t channelVolume;
        EEPROM.get(Eeprom::ChannelVolumes + i, channelVolume);
        if (channelVolume >= 0 && channelVolume <= 31)
        {
            setTargetValue(i, channelVolume);
        }
        else
        {
            setTargetValue(i, 10);
        }
    }
}
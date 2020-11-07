//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "DigitalAttenuator.h"
#include "SystemParameters.h"
#include <EEPROM.h>

DigitalAttenuator::DigitalAttenuator() :
    XicorX9514(Pin::AttenuatorUp, Pin::AttenuatorDown)
{
}

void DigitalAttenuator::initChannelValues()
{
    for (int i = 0; i < 2; ++i)
    {
        int8_t channelVolume;
        EEPROM.get(Eeprom::OutputVolumes + i, channelVolume);
        if (channelVolume >= 0 && channelVolume <= 31)
        {
            setTargetValue(i, channelVolume);
        }
        else
        {
            setTargetValue(i, 31);
        }
    }
}

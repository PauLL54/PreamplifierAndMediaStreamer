//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "DigitalAttenuator.h"
#include "SystemParameters.h"

DigitalAttenuator::DigitalAttenuator() :
    XicorX9514(Pin::AttenuatorUp, Pin::AttenuatorDown)
{
}


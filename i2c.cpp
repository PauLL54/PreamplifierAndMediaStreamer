//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "I2C.h"
#include "InputChannelSelector.h"
#include "Arduino.h"

I2C::I2C(InputChannelSelector &inputChannelSelector) :
    m_inputChannelSelector(inputChannelSelector)
{
}

void I2C::handleInput(char* input)
{
    // Split input (e.g.: "=LedBrightness=12345=") into a name and a value:
    char* command = strtok(input, "="); // command is empty
    char* name = 0;
    char* value = 0;
    if (command != 0)
    {
        name = strtok(NULL, "=");
        Serial.println(name);
    }
    if (command != 0)
    {
        value = strtok(NULL, "=");
        Serial.println(value);
    }

    // handle commands:
    if (strcmp(name, "LedBrightness") == 0)
    {
        int v = atoi(value);
        this->m_inputChannelSelector.setDefaultBrightness(v);
    }
}

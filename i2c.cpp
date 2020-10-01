//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "I2C.h"
#include "InputChannelSelector.h"
#include "OutputChannelSelector.h"
#include "DigitalPotmeter.h"
#include "DigitalAttenuator.h"
#include "Arduino.h"
#include <EEPROM.h>
#include "SystemParameters.h"

I2C::I2C(InputChannelSelector &inputChannelSelector, DigitalPotmeter &digitalPotmeter, DigitalAttenuator &digitalAttenuator, OutputChannelSelector &outputChannelSelector) :
    m_inputChannelSelector(inputChannelSelector),
    m_digitalPotmeter(digitalPotmeter),
    m_digitalAttenuator(digitalAttenuator),
    m_outputChannelSelector(outputChannelSelector)
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
        m_lastTimeUserAction = millis();
    }
    if (strcmp(name, "SetChannel") == 0)
    {
        int v = atoi(value);
        this->m_inputChannelSelector.selectChannel(v);
        m_lastTimeUserAction = millis();
    }
    if (strcmp(name, "SetVolume") == 0)
    {
        if (strcmp(value, "off") == 0)
            this->m_digitalPotmeter.setTargetValue(0);
        else if (strcmp(value, "down") == 0)
            this->m_digitalPotmeter.down();
        else if (strcmp(value, "up") == 0)
            this->m_digitalPotmeter.up();
        else {
            int v = atoi(value);
            this->m_digitalPotmeter.setTargetValue(v);
        }

        m_lastTimeUserAction = millis();
    }
    if (strcmp(name, "SCV") == 0)   // SetChannelVolume
    {
        char* args = strtok(value, ","); 
        char* s = 0;
        int8_t channelVolume;
        for (int i = 0; i < 8; ++i)
        {
            if (args != 0)
            {
                s = strtok(NULL, ",");
                channelVolume = atoi(s);
                Serial.println(channelVolume);
                EEPROM.put(Eeprom::ChannelVolumes + i, channelVolume);
            }
            this->m_digitalPotmeter.initChannelValues();
        }
        m_lastTimeUserAction = millis();
    }
    if (strcmp(name, "OUTPUT") == 0)   // select output channel 0 or 1
    {
        int v = atoi(value);
        this->m_outputChannelSelector.selectChannel(v);
        m_lastTimeUserAction = millis();
    }
    if (strcmp(name, "SOV") == 0)   // SetOutputVolume
    {
        char* args = strtok(value, ","); 
        for (int i = 0; i < 2; ++i)
        {
            char* s = 0;
            int8_t channelVolume;
            if (args != 0)
            {
                s = strtok(NULL, ",");
                channelVolume = atoi(s);
                Serial.println(channelVolume);
                EEPROM.put(Eeprom::OutputVolumes + i, channelVolume);
            }
            this->m_digitalAttenuator.initChannelValues();
        }
        m_lastTimeUserAction = millis();
    }
}

unsigned long I2C::getLastTimeUserAction() const
{
    return m_lastTimeUserAction;
}
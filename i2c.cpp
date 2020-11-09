//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "I2C.h"
#include "InputChannelSelector.h"
#include "OutputChannelSelector.h"
#include "DigitalPotmeter.h"
#include "DigitalAttenuator.h"
#include "IRCommands.h"
#include "Arduino.h"
#include <EEPROM.h>
#include "SystemParameters.h"

I2C::I2C(InputChannelSelector &inputChannelSelector, DigitalPotmeter &digitalPotmeter, DigitalAttenuator &digitalAttenuator,
 OutputChannelSelector &outputChannelSelector, IRCommands &irCommands) :
    m_inputChannelSelector(inputChannelSelector),
    m_digitalPotmeter(digitalPotmeter),
    m_digitalAttenuator(digitalAttenuator),
    m_outputChannelSelector(outputChannelSelector),
    m_irCommands(irCommands)
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
        //Serial.println(name);
    }
    if (command != 0)
    {
        value = strtok(NULL, "=");
        //Serial.println(value);
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
        char* arg = strtok(value, ","); 
        int8_t channelVolume;
        for (int i = 0; i < 8; ++i)
        {
            if (arg != 0)
            {
                channelVolume = atoi(arg);
                //Serial.println(channelVolume);
                EEPROM.put(Eeprom::ChannelVolumes + i, channelVolume);
                arg = strtok(NULL, ",");
            }
        }
        this->m_digitalPotmeter.initChannelValues();
        m_lastTimeUserAction = millis();
    }
    if (strcmp(name, "IREFC") == 0)   // Infra Red EnabledForChannel
    {
        int8_t v = atoi(value);
        EEPROM.put(Eeprom::IRVolumeForChannel, v);
        this->m_irCommands.initVolumeEnabledForChannel();
    }
    if (strcmp(name, "SOV") == 0)   // SetOutputVolume
    {
        char* arg = strtok(value, ","); 
        int8_t channelVolume;
        for (int i = 0; i < 2; ++i)
        {
            if (arg != 0)
            {
                channelVolume = atoi(arg);
                //Serial.println(channelVolume);
                EEPROM.put(Eeprom::OutputVolumes + i, channelVolume);
                arg = strtok(NULL, ",");
            }
        }
        this->m_digitalAttenuator.initChannelValues();
    }
    if (strcmp(name, "OUTPUT") == 0)   // select output channel 0 or 1
    {
        int v = atoi(value);
        this->m_outputChannelSelector.selectChannel(v);
    }
}

unsigned long I2C::getLastTimeUserAction() const
{
    return m_lastTimeUserAction;
}

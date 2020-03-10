//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "LightControl.h"
#include "InputChannelSelectButton.h"
#include "VolumeRotaryEncoder.h"
#include "IRCommands.h"
#include "DigitalPotmeter.h"
#include "InputChannelSelector.h"
#include "Arduino.h"

const unsigned long DisplayOnTime =  1L * 60L * 1000L; // ms after some time, switch off the display
//const unsigned long DisplayOnTime = 3000; // ms for testing

LightControl::LightControl(	InputChannelSelectButton &inputChannelSelectButton,
				            VolumeRotaryEncoder &volumeRotaryEncoder,
				            IRCommands &irCommands,
                            DigitalPotmeter &digitalPotmeter,
                            InputChannelSelector &inputChannelSelector) :
    m_inputChannelSelectButton(inputChannelSelectButton),
    m_volumeRotaryEncoder(volumeRotaryEncoder),
    m_irCommands(irCommands),
    m_digitalPotmeter(digitalPotmeter),
    m_inputChannelSelector(inputChannelSelector),
    m_timeout(millis() + DisplayOnTime),
    m_displayIsEnabled(true)
{
}

void LightControl::checkUserActions()
{
    updateTimeout(m_inputChannelSelectButton.getLastTimeUserAction());
    updateTimeout(m_volumeRotaryEncoder.getLastTimeUserAction());
    updateTimeout(m_irCommands.getLastTimeUserAction());
}

void LightControl::updateTimeout(unsigned long lastTimeUserAction)
{
    unsigned long timeToSwitchOffDisplay = lastTimeUserAction + DisplayOnTime;
    if (millis() < timeToSwitchOffDisplay && timeToSwitchOffDisplay > m_timeout)
    {
        //Serial.println("new timeout set");
        m_timeout = timeToSwitchOffDisplay;
        m_displayIsEnabled = true;
    }
}

void LightControl::checkDisplaySwitchOffNeeded()
{
    checkUserActions();

    if (m_displayIsEnabled)
    {
        if (millis() > m_timeout)
        {
            //Serial.println("LightControl: switch off needed");
            m_displayIsEnabled = false;
            m_digitalPotmeter.disableDisplay();
            m_inputChannelSelector.disableDisplay();
        }
        else
        {
            m_digitalPotmeter.enableDisplay();
            m_inputChannelSelector.enableDisplay();       
        }
    }
}


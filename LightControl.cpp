//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "LightControl.h"
#include "InputChannelSelectButton.h"
#include "VolumeRotaryEncoder.h"
#include "IRCommands.h"
#include "Arduino.h"

//const unsigned long TimeOut = 300000; // ms
const unsigned long LightOnTime = 3000; // ms

LightControl::LightControl(	InputChannelSelectButton &inputChannelSelectButton,
				            VolumeRotaryEncoder &volumeRotaryEncoder,
				            IRCommands &irCommands) :
    m_inputChannelSelectButton(inputChannelSelectButton),
    m_volumeRotaryEncoder(volumeRotaryEncoder),
    m_irCommands(irCommands),
    m_timeout(millis() + LightOnTime)
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
    unsigned long timeout = lastTimeUserAction + LightOnTime;
    if (timeout > millis() && timeout > m_timeout)
    {
        //Serial.println("new timeout set");
        m_timeout = timeout;
    }
}

void LightControl::checkSwitchOffNeeded()
{
    checkUserActions();

    if (m_timeout != 0 && millis() > m_timeout)
    {
        //Serial.println("LightControl: switch off needed");
        m_timeout = 0;
    }
}


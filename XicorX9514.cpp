//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "XicorX9514.h"
#include "Arduino.h"
#include "SystemParameters.h"

const int8_t MaxDebounceTime_ms = 60;  // XICOR X9514 digital potentiometer
const int8_t MaxSteps = 31;            // XICOR X9514 digital potentiometer

XicorX9514::XicorX9514(int8_t pinUp, int8_t pinDown) :
    m_pinUp(pinUp),
    m_pinDown(pinDown),
    m_channel(6),
    m_actualValue(MaxSteps + 1),
    m_state(Idle),
    m_pulseTimeOut(0)
{
    m_targetValue[m_channel] = 0,

   	pinMode(m_pinUp,   OUTPUT);
    pinMode(m_pinDown, OUTPUT);

    digitalWrite(m_pinUp,   HIGH);
    digitalWrite(m_pinDown, HIGH);
}

bool XicorX9514::isInitialized() const
{
    return (m_actualValue == 0);
}

void XicorX9514::setTargetValue(int8_t targetValue)
{
    m_targetValue[m_channel] = targetValue;
}

void XicorX9514::setTargetValue(int8_t channel, int8_t targetValue)
{
    m_targetValue[channel] = targetValue;
}

void XicorX9514::setChannel(int8_t channel)
{
    m_channel = channel;
}

int8_t XicorX9514::getChannel()
{
    return m_channel;
}

void XicorX9514::up()
{
    m_targetValue[m_channel]++;
    if (m_targetValue[m_channel] > MaxSteps)
        m_targetValue[m_channel] = MaxSteps;
}

void XicorX9514::down()
{
    m_targetValue[m_channel]--;
    if (m_targetValue[m_channel] < 0)
        m_targetValue[m_channel] = 0;
}

void XicorX9514::updateToTargetValue()
{
    if (m_state == PulsingUp)
    {
        handlePulsingUp();
        return;
    }

    if (m_state == PulsingDown)
    {
        handlePulsingDown();
        return;
    }

    if (m_state == Idle)
    {
        if (m_targetValue[m_channel] > m_actualValue)
        {
            startPulsingUp();
        }
        if (m_targetValue[m_channel] < m_actualValue)
        {
            startPulsingDown();
        }
    }
}

void XicorX9514::startPulsingUp()
{
    setTimeoutPulse();
    m_state = PulsingUp;
    digitalWrite(m_pinUp, LOW);
}

void XicorX9514::startPulsingDown()
{
    setTimeoutPulse();
    m_state = PulsingDown;
    digitalWrite(m_pinDown, LOW);
}

void XicorX9514::setTimeoutPulse()
{
    m_pulseTimeOut = millis() + MaxDebounceTime_ms;
}

void XicorX9514::handlePulsingUp()
{
    if (millis() > m_pulseTimeOut)
    {
        digitalWrite(m_pinUp, HIGH);
        m_state = Idle;
        m_actualValue++;
        if (m_actualValue > MaxSteps)
            m_actualValue = MaxSteps;
        
        onNewValue(m_actualValue, MaxSteps);
    }
}

void XicorX9514::handlePulsingDown()
{
    if (millis() > m_pulseTimeOut)
    {
        digitalWrite(m_pinDown, HIGH);
        m_state = Idle;
        m_actualValue--;
        if (m_actualValue < 0)
            m_actualValue = 0;
        
        onNewValue(m_actualValue, MaxSteps);
    }
}

void XicorX9514::onNewValue(int8_t actualValue, int8_t maxSteps)
{
    actualValue;
    maxSteps;
}
//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "DigitalPotmeter.h"
#include "Arduino.h"

const int PinUp = 10;
const int PinDown = 10;
const int MaxDebounceTime = 60; // ms
const int MaxSteps = 31;

DigitalPotmeter::DigitalPotmeter() :
    m_targetValue(0),
    m_actualValue(MaxSteps),
    m_state(Idle),
    m_pulseTimeOut(0)
{
   	pinMode(PinUp, OUTPUT);
	pinMode(PinDown, OUTPUT);

    digitalWrite(PinUp, HIGH);
    digitalWrite(PinDown, HIGH);
}

void DigitalPotmeter::up()
{
    m_targetValue++;
    if (m_targetValue > MaxSteps)
        m_targetValue = MaxSteps;
}

void DigitalPotmeter::down()
{
    m_targetValue--;
    if (m_targetValue < 0)
        m_targetValue = 0;
}

void DigitalPotmeter::setTargetValue(int targetValue)
{
    m_targetValue = targetValue;
}

bool DigitalPotmeter::targetValueReached() const
{
    return (m_actualValue == m_targetValue);
}

void DigitalPotmeter::updateDevice()
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
        if (m_targetValue > m_actualValue)
        {
            startPulsingUp();
        }
        if (m_targetValue < m_actualValue)
        {
            startPulsingDown();
        }
    }
}

void DigitalPotmeter::startPulsingUp()
{
    m_pulseTimeOut = millis() + MaxDebounceTime;
    m_state = PulsingUp;
    digitalWrite(PinUp, LOW);
}

void DigitalPotmeter::startPulsingDown()
{
    m_pulseTimeOut = millis() + MaxDebounceTime;
    m_state = PulsingDown;
    digitalWrite(PinDown, LOW);
}

void DigitalPotmeter::handlePulsingUp()
{
    if (millis() > m_pulseTimeOut)
    {
        digitalWrite(PinUp, HIGH);
        m_state = Idle;
        m_actualValue++;
        if (m_actualValue > MaxSteps)
            m_actualValue = MaxSteps;
    }
}

void DigitalPotmeter::handlePulsingDown()
{
    if (millis() > m_pulseTimeOut)
    {
        digitalWrite(PinDown, HIGH);
        m_state = Idle;
        m_actualValue--;
        if (m_actualValue < 0)
            m_actualValue = 0;
    }
}


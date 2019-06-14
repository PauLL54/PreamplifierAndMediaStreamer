//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "DigitalPotmeter.h"
#include "Arduino.h"

const int PinUp = 7;   // PD7
const int PinDown = 8; // PB0
const int MaxDebounceTime = 60; // ms
const int MaxSteps = 31;

DigitalPotmeter::DigitalPotmeter() :
    m_targetValue(0),
    m_actualValue(MaxSteps + 1),
    m_state(Idle),
    m_pulseTimeOut(0),
    m_neoPixelRing()
{
   	pinMode(PinUp, OUTPUT);
	pinMode(PinDown, OUTPUT);

    digitalWrite(PinUp, HIGH);
    digitalWrite(PinDown, HIGH);
}

bool DigitalPotmeter::isInitialized() const
{
    return (m_actualValue == 0);
}

void DigitalPotmeter::setTargetValue(int targetValue)
{
    m_targetValue = targetValue;
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
    setTimeoutPulse();
    m_state = PulsingUp;
    digitalWrite(PinUp, LOW);
}

void DigitalPotmeter::startPulsingDown()
{
    setTimeoutPulse();
    m_state = PulsingDown;
    digitalWrite(PinDown, LOW);
}

void DigitalPotmeter::setTimeoutPulse()
{
    m_pulseTimeOut = millis() + MaxDebounceTime;
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
        
        m_neoPixelRing.set5bitsValue(m_actualValue);
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
        
        m_neoPixelRing.set5bitsValue(m_actualValue);
    }
}


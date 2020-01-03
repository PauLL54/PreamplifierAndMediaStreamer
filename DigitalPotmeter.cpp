//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "DigitalPotmeter.h"
#include "Arduino.h"
#include "SystemParameters.h"

const int MaxDebounceTime_ms = 60;  // XICOR X9514 digital potentiometer
const int MaxSteps = 31;            // XICOR X9514 digital potentiometer

DigitalPotmeter::DigitalPotmeter() :
    m_targetValue(0),
    m_actualValue(MaxSteps + 1),
    m_state(Idle),
    m_pulseTimeOut(0),
    m_neoPixelRing()
{
   	pinMode(Pin::DigitalPotmeterUp,   OUTPUT);
    pinMode(Pin::DigitalPotmeterDown, OUTPUT);

    digitalWrite(Pin::DigitalPotmeterUp,   HIGH);
    digitalWrite(Pin::DigitalPotmeterDown, HIGH);
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

void DigitalPotmeter::updateToTargetValue()
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
    digitalWrite(Pin::DigitalPotmeterUp, LOW);
}

void DigitalPotmeter::startPulsingDown()
{
    setTimeoutPulse();
    m_state = PulsingDown;
    digitalWrite(Pin::DigitalPotmeterDown, LOW);
}

void DigitalPotmeter::setTimeoutPulse()
{
    m_pulseTimeOut = millis() + MaxDebounceTime_ms;
}

void DigitalPotmeter::handlePulsingUp()
{
    if (millis() > m_pulseTimeOut)
    {
        digitalWrite(Pin::DigitalPotmeterUp, HIGH);
        m_state = Idle;
        m_actualValue++;
        if (m_actualValue > MaxSteps)
            m_actualValue = MaxSteps;
        
        m_neoPixelRing.setValue(m_actualValue, MaxSteps);
    }
}

void DigitalPotmeter::handlePulsingDown()
{
    if (millis() > m_pulseTimeOut)
    {
        digitalWrite(Pin::DigitalPotmeterDown, HIGH);
        m_state = Idle;
        m_actualValue--;
        if (m_actualValue < 0)
            m_actualValue = 0;
        
        m_neoPixelRing.setValue(m_actualValue, MaxSteps);
    }
}

void DigitalPotmeter::disableDisplay()
{
    m_neoPixelRing.disableDisplay();
}

void DigitalPotmeter::setAlternateColor(bool on)
{
    m_neoPixelRing.setAlternateColor(on);
    m_neoPixelRing.setValue(m_actualValue, MaxSteps);
}
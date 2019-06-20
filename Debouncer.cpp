//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "Debouncer.h"
#include "Arduino.h"

Debouncer::Debouncer(int time_ms) :
    m_time_ms(time_ms),
    m_timeout(0),
    m_inputState(IsLow)
{
}

void Debouncer::updateInputState(int inputValue)
{
    if (inputValue == 1)
        handleValueHigh();
    else
        handleValueLow();
}

bool Debouncer::inputChanged() const
{
    return (inputChangedToHigh() || inputChangedToHigh());
}

bool Debouncer::inputChangedToHigh() const
{
    return (m_inputState == StartBecomingHigh);
}

bool Debouncer::inputChangedToLow() const
{
    return (m_inputState == StartBecomingLow);
}

void Debouncer::handleValueHigh()
{
    if (m_inputState == StartBecomingHigh)
    {
        m_inputState = BecomingHigh;
    }

    if (m_inputState == IsLow)
    {
        m_inputState = StartBecomingHigh;
        m_timeout = millis() + m_time_ms;
    }

    if (m_inputState == BecomingHigh)
    {
        if (millis() > m_timeout)
        {
            m_inputState = IsHigh;
        }
    }

    if (m_inputState == IsHigh)
    {
    }

    if ((m_inputState == StartBecomingLow) || (m_inputState == BecomingLow))
    {
        if (millis() > m_timeout)
        {
            m_inputState = StartBecomingHigh;
            m_timeout = millis() + m_time_ms;
        }   
    }
}

void Debouncer::handleValueLow()
{
    if (m_inputState == StartBecomingLow)
    {
        m_inputState = BecomingLow;
    }

    if (m_inputState == IsHigh)
    {
        m_inputState = StartBecomingLow;
        m_timeout = millis() + m_time_ms;
    }

    if (m_inputState == BecomingLow)
    {
        if (millis() > m_timeout)
        {
            m_inputState = IsLow;
        }
    }

    if (m_inputState == IsLow)
    {
    }

    if ((m_inputState == StartBecomingHigh) || (m_inputState == BecomingHigh))
    {
        if (millis() > m_timeout)
        {
            m_inputState = StartBecomingLow;
            m_timeout = millis() + m_time_ms;
        }
    }
}

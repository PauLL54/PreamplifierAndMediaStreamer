//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "Debouncer.h"

Debouncer::Debouncer(int bounceMaxCount) :
    m_bounceMaxCount(bounceMaxCount),
    m_bounceCounter(0),
    m_inputState(Off)
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
    return (inputSwitchedOn() || inputSwitchedOff());
}

bool Debouncer::inputSwitchedOn() const
{
    return (m_inputState == SwitchedOn);
}

bool Debouncer::inputSwitchedOff() const
{
    return (m_inputState == SwitchedOff);
}

void Debouncer::handleValueHigh()
{
    if (m_inputState == SwitchedOn)
    {
        m_inputState = On;
    }

    if (m_inputState == SwitchedOff)
    {
        m_inputState = Off;
    }

    if ((m_inputState == Off) || (m_inputState == GoingOn))
    {
        m_inputState = GoingOn;
        m_bounceCounter++;
    
        if (m_bounceCounter > m_bounceMaxCount)
        {
            m_bounceCounter = 0;
            m_inputState = SwitchedOn;
        }
    }

    if ((m_inputState == On) || (m_inputState == GoingOff))
    {
        // do nothing
    }
}

void Debouncer::handleValueLow()
{
    if (m_inputState == SwitchedOn)
    {
        m_inputState = On;
    }

    if (m_inputState == SwitchedOff)
    {
        m_inputState = Off;
    }

    if ((m_inputState == On) || (m_inputState == GoingOff))
    {
        m_inputState = GoingOff;
        m_bounceCounter++;
    
        if (m_bounceCounter > m_bounceMaxCount)
        {
            m_bounceCounter = 0;
            m_inputState = SwitchedOff;
        }
    }

    if ((m_inputState == Off) || (m_inputState == GoingOn))
    {
        // do nothing
    }
}

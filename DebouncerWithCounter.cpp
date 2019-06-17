//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "DebouncerWithCounter.h"

DebouncerWithCounter::DebouncerWithCounter(int bounceMaxCount) :
    m_bounceMaxCount(bounceMaxCount),
    m_bounceCounter(0),
    m_inputState(IsLow)
{
}

void DebouncerWithCounter::updateInputState(int inputValue)
{
    if (inputValue == 1)
        handleValueHigh();
    else
        handleValueLow();
}

bool DebouncerWithCounter::inputChanged() const
{
    return (inputBecameHigh() || inputBecameLow());
}

bool DebouncerWithCounter::inputBecameHigh() const
{
    return (m_inputState == BecameHigh);
}

bool DebouncerWithCounter::inputBecameLow() const
{
    return (m_inputState == BecameLow);
}

void DebouncerWithCounter::handleValueHigh()
{
    if (m_inputState == BecameHigh)
    {
        m_inputState = IsHigh;
    }

    if (m_inputState == BecameLow)
    {
        m_inputState = IsLow;
    }

    if ((m_inputState == IsLow) || (m_inputState == GoingHigh))
    {
        m_inputState = GoingHigh;
        m_bounceCounter++;
    
        if (m_bounceCounter > m_bounceMaxCount)
        {
            m_bounceCounter = 0;
            m_inputState = BecameHigh;
        }
    }

    if ((m_inputState == IsHigh) || (m_inputState == GoingLow))
    {
        // do nothing
    }
}

void DebouncerWithCounter::handleValueLow()
{
    if (m_inputState == BecameHigh)
    {
        m_inputState = IsHigh;
    }

    if (m_inputState == BecameLow)
    {
        m_inputState = IsLow;
    }

    if ((m_inputState == IsHigh) || (m_inputState == GoingLow))
    {
        m_inputState = GoingLow;
        m_bounceCounter++;
    
        if (m_bounceCounter > m_bounceMaxCount)
        {
            m_bounceCounter = 0;
            m_inputState = BecameLow;
        }
    }

    if ((m_inputState == IsLow) || (m_inputState == GoingHigh))
    {
        // do nothing
    }
}

//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "Debouncer.h"

Debouncer::Debouncer(int bounceMaxCount) :
    m_bounceMaxCount(bounceMaxCount),
    m_bounceCounter(0),
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
    return (inputBecameHigh() || inputBecameLow());
}

bool Debouncer::inputBecameHigh() const
{
    return (m_inputState == BecameHigh);
}

bool Debouncer::inputBecameLow() const
{
    return (m_inputState == BecameLow);
}

void Debouncer::handleValueHigh()
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

void Debouncer::handleValueLow()
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

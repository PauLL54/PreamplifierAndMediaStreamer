//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "InputChannelSelectButton.h"
#include "Arduino.h"
#include "SystemParameters.h"

const int BounceTime_ms = 10;

InputChannelSelectButton::InputChannelSelectButton(InputChannelSelector& inputChannelSelector) :
    m_inputChannelSelector(inputChannelSelector),
    m_debouncer(BounceTime_ms)
{
    pinMode(Pin::ChannelSelectButton, INPUT_PULLUP);
}

void InputChannelSelectButton::checkButtonPressed()
{
    int valueButton = digitalRead(Pin::ChannelSelectButton);
    m_debouncer.updateInputState(valueButton);

    if (m_debouncer.inputChangedToLow())
    {
        m_inputChannelSelector.selectNextChannel();
    }
}

//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "InputChannelSelectButton.h"
#include "Arduino.h"
#include "SystemParameters.h"

const int DebounceTime_ms = 10;

InputChannelSelectButton::InputChannelSelectButton(InputChannelSelector& inputChannelSelector) :
    m_inputChannelSelector(inputChannelSelector),
    m_debouncer(DebounceTime_ms),
    m_lastTimeUserAction(0)
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

        m_lastTimeUserAction = millis();
    }
}

unsigned long InputChannelSelectButton::getLastTimeUserAction() const
{
    return m_lastTimeUserAction;
}

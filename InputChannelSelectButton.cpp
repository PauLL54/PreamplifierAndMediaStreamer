//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "InputChannelSelectButton.h"
#include "Arduino.h"

const int Button = 15;	// PC1
const int BounceTime_ms = 2;

InputChannelSelectButton::InputChannelSelectButton(InputChannelSelector& inputChannelSelector) :
    m_inputChannelSelector(inputChannelSelector),
    m_debouncer(BounceTime_ms)
{
    pinMode(Button, INPUT_PULLUP);
}

void InputChannelSelectButton::checkButtonPressed()
{
    int valueButton = digitalRead(Button);
    m_debouncer.updateInputState(valueButton);

    if (m_debouncer.inputChangedToLow())
    {
        m_inputChannelSelector.selectNextChannel();
    }
}

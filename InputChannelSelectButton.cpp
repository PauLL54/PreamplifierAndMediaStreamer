//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "InputChannelSelectButton.h"
#include "Arduino.h"

const int Button = 15;	// PC1
const int BounceMaxCount = 10;

InputChannelSelectButton::InputChannelSelectButton(InputChannelSelector& inputChannelSelector) :
    m_inputChannelSelector(inputChannelSelector),
    m_debouncer(BounceMaxCount)
{
    pinMode(Button, INPUT);
}

void InputChannelSelectButton::checkButtonPressed()
{
    int valueButton = digitalRead(Button);
    m_debouncer.updateInputState(valueButton);

    if (m_debouncer.inputSwitchedOn())
        m_inputChannelSelector.selectNextChannel();
}

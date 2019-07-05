//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "InputChannelSelector.h"

class InputChannelSelectButton {
public:
	InputChannelSelectButton(InputChannelSelector& inputChannelSelector);

    void checkButtonPressed();
    unsigned long getLastTimeUserAction() const;
    
private:
    void handleValueHigh();
    void handleValueLow();

private:
    InputChannelSelector& m_inputChannelSelector;
   	Debouncer m_debouncer;

    int m_bounceCounter;
    enum ButtonState { Off, Pressing, Pressed, Releasing };
    ButtonState m_buttonState;
    unsigned long m_lastTimeUserAction;
};

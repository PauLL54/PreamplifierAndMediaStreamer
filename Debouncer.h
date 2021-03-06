//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

class Debouncer {
public:
	Debouncer(int time_ms);

    void updateInputState(int inputValue);
    bool inputChanged() const;
    bool inputChangedToHigh() const;
    bool inputChangedToLow() const;

private:
    void handleValueHigh();
    void handleValueLow();

private:
    unsigned long m_time_ms;
    unsigned long m_timeout;

    enum InputState { IsLow, StartBecomingHigh, BecomingHigh, IsHigh, StartBecomingLow, BecomingLow };
   
    InputState m_inputState;
};

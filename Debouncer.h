//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

class Debouncer {
public:
	Debouncer(int bounceMaxCount);

    void updateInputState(int inputValue);
    bool inputChanged() const;
    bool inputBecameHigh() const;
    bool inputBecameLow() const;

private:
    void handleValueHigh();
    void handleValueLow();

private:
    int m_bounceMaxCount;
    int m_bounceCounter;

    enum InputState { IsLow, GoingHigh, BecameHigh, IsHigh, GoingLow, BecameLow };
   
    InputState m_inputState;
};

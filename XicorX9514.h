//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "stdint.h"

class XicorX9514 {
public:
	XicorX9514(int8_t pinUp, int8_t pinDown);

    bool isInitialized() const;
    void setTargetValue(int8_t targetValue); // 0..31
    void setTargetValue(int8_t channel, int8_t targetValue); // 0..7, 0..31
    void setChannel(int8_t channel); // 0..7
    int8_t getChannel();
    void up();
    void down();
    void updateToTargetValue();
    virtual void onNewValue(int8_t actualValue, int8_t maxSteps);

private:
    void handlePulsingUp();
    void handlePulsingDown();
    void startPulsingUp();
    void startPulsingDown();
    void setTimeoutPulse();

private:
    int8_t m_pinUp;
    int8_t m_pinDown;
    int8_t m_channel;
    int8_t m_targetValue[8] = {10, 10, 10, 10, 10, 10, 10, 10};
    int8_t m_actualValue;

    enum State { Idle, PulsingUp, PulsingDown };
    State m_state;
    unsigned long m_pulseTimeOut;
};

//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

class XicorX9514 {
public:
	XicorX9514(int pinUp, int pinDown);

    bool isInitialized() const;
    void setTargetValue(int targetValue); // 0..31
    void up();
    void down();
    void updateToTargetValue();
    virtual void onNewValue(int actualValue, int maxSteps);

private:
    void handlePulsingUp();
    void handlePulsingDown();
    void startPulsingUp();
    void startPulsingDown();
    void setTimeoutPulse();

private:
    int m_pinUp;
    int m_pinDown;
    int m_targetValue;
    int m_actualValue;

    enum State { Idle, PulsingUp, PulsingDown };
    State m_state;
    unsigned long m_pulseTimeOut;
};

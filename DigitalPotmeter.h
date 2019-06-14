//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

class DigitalPotmeter {
public:
	DigitalPotmeter();

    bool isInitialized() const;
    void setTargetValue(int targetValue);
    void up();
    void down();
    void updateDevice();

private:
    void handlePulsingUp();
    void handlePulsingDown();
    void startPulsingUp();
    void startPulsingDown();
    void setTimeoutPulse();

private:
    int m_targetValue;
    int m_actualValue;

    enum State { Idle, PulsingUp, PulsingDown };
    State m_state;
    unsigned long m_pulseTimeOut;
};

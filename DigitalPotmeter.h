//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

class DigitalPotmeter {
public:
	DigitalPotmeter();

    void setTargetValue(int targetValue);
    bool targetValueReached() const;
    void updateDevice();
    void up();
    void down();

private:
    void handlePulsingUp();
    void handlePulsingDown();
    void startPulsingUp();
    void startPulsingDown();

private:
    int m_targetValue;
    int m_actualValue;

    enum State { Idle, PulsingUp, PulsingDown };
    State m_state;
    unsigned long m_pulseTimeOut;
};

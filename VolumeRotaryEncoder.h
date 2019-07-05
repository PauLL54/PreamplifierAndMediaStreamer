//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Debouncer.h"
#include "DigitalPotmeter.h"

class VolumeRotaryEncoder {
public:
	VolumeRotaryEncoder(DigitalPotmeter& digitalPotmeter);

	void checkRotation();
    unsigned long getLastTimeUserAction() const;

private:
	DigitalPotmeter& m_digitalPotmeter;
	int m_pinALast;
	Debouncer m_debouncer;
    unsigned long m_lastTimeUserAction;
};

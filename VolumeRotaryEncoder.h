//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Debouncer.h"

class VolumeRotaryEncoder {
public:
	VolumeRotaryEncoder();

	void checkRotation();

private:
	int m_pinALast;
	Debouncer m_debouncer;
};

//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Adafruit_NeoPixel.h"

class NeoPixelRing {
public:
	NeoPixelRing();

	void setValue(int8_t value, int8_t maxValue);
	void enableDisplay();
	void disableDisplay();

private:
	Adafruit_NeoPixel m_LedRing;
	int8_t m_lastValue;
	int8_t m_lastMaxValue;
	bool m_enabled;
};

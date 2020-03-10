//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Adafruit_NeoPixel.h"

class NeoPixelRing {
public:
	NeoPixelRing();

	void setValue(int value, int maxValue);
	void enableDisplay();
	void disableDisplay();

private:
	Adafruit_NeoPixel m_LedRing;
	int m_lastValue;
	int m_lastMaxValue;
	bool m_enabled;
};

//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Adafruit_NeoPixel.h"

class NeoPixelRing {
public:
	NeoPixelRing();

	void setValue(int value, int maxValue);
	void disableDisplay();
	void setAlternateColor(bool on);

private:
	Adafruit_NeoPixel m_LedRing;
	bool m_colorTVIsOn;
};

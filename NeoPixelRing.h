//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Adafruit_NeoPixel.h"

class NeoPixelRing {
public:
	NeoPixelRing();

	void set5bitsValue(int _5bitsValue);

private:
	Adafruit_NeoPixel m_LedRing;
};

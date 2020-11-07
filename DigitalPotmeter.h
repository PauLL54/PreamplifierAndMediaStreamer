//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "NeoPixelRing.h"
#include "XicorX9514.h"

class DigitalPotmeter : public XicorX9514 {
public:
	DigitalPotmeter();

	void initChannelValues();
	void enableDisplay();
	void disableDisplay();
    void onNewValue(int8_t actualValue, int8_t maxSteps) override;

private:
    NeoPixelRing m_neoPixelRing;
};

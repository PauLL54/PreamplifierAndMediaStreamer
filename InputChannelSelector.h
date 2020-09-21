//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Debouncer.h"
#include "DigitalPotmeter.h"

class InputChannelSelector {
public:
	InputChannelSelector(DigitalPotmeter& digitalPotmeter);

	void selectChannel(int channel); // 0..7
	void selectNextChannel();
	void selectPreviousChannel();
	void setDefaultBrightness(int brightness);
	void enableDisplay();
	void disableDisplay();

private:
	void setBrightness(int brightness);
	void switchToChannel(int channel);

private:
	DigitalPotmeter& m_digitalPotmeter;
	int m_brightness;
	int m_currentChannel;
};

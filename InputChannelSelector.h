//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Debouncer.h"
#include "DigitalPotmeter.h"

class InputChannelSelector {
public:
	InputChannelSelector(DigitalPotmeter& digitalPotmeter);

    int8_t getChannel();
	void selectChannel(int8_t channel); // 0..7
	void selectNextChannel();
	void selectPreviousChannel();
	void setDefaultBrightness(int8_t brightness);
	void enableDisplay();
	void disableDisplay();

private:
	void setBrightness(int8_t brightness);
	void switchToChannel(int8_t channel);

private:
	DigitalPotmeter& m_digitalPotmeter;
	int m_brightness;
	int8_t m_currentChannel;
};

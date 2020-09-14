//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

class InputChannelSelector;
class DigitalPotmeter;

class I2C
{
public:
	I2C(InputChannelSelector &inputChannelSelector, DigitalPotmeter &digitalPotmeter);
	
	void handleInput(char* input);
	unsigned long getLastTimeUserAction() const;

private:
	InputChannelSelector &m_inputChannelSelector;
	DigitalPotmeter &m_digitalPotmeter;
	unsigned long m_lastTimeUserAction;
};
//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

class InputChannelSelector;

class I2C
{
public:
	I2C(InputChannelSelector &inputChannelSelector);
	
	void handleInput(char* input);
	unsigned long getLastTimeUserAction() const;

private:
	InputChannelSelector &m_inputChannelSelector;
	unsigned long m_lastTimeUserAction;
};
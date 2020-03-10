//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

class InputChannelSelector;

class I2C
{
public:
	I2C(InputChannelSelector &inputChannelSelector);

	static void receiveEvent(int howMany);

private:

private:
	InputChannelSelector &m_inputChannelSelector;
};
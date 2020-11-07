//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

class InputChannelSelector;
class DigitalPotmeter;
class OutputChannelSelector;
class DigitalAttenuator;
class IRCommands;

class I2C
{
public:
	I2C(InputChannelSelector &inputChannelSelector, DigitalPotmeter &digitalPotmeter, DigitalAttenuator &digitalAttenuator, 
	OutputChannelSelector &outputChannelSelector, IRCommands &irCommands);
	
	void handleInput(char* input);
	unsigned long getLastTimeUserAction() const;

private:
	InputChannelSelector &m_inputChannelSelector;
	DigitalPotmeter &m_digitalPotmeter;
	DigitalAttenuator &m_digitalAttenuator;
	OutputChannelSelector &m_outputChannelSelector;
	IRCommands &m_irCommands;
	unsigned long m_lastTimeUserAction;
};

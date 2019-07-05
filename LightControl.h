//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

class InputChannelSelectButton;
class VolumeRotaryEncoder;
class IRCommands;
class DigitalPotmeter;

class LightControl
{
public:
	LightControl(InputChannelSelectButton &inputChannelSelectButton,
				 VolumeRotaryEncoder &volumeRotaryEncoder,
				 IRCommands &irCommands,
				 DigitalPotmeter &digitalPotmeter);

	void checkSwitchOffNeeded();

private:
	void checkUserActions();
	void updateTimeout(unsigned long lastTimeUserAction);

private:
	InputChannelSelectButton &m_inputChannelSelectButton;
	VolumeRotaryEncoder &m_volumeRotaryEncoder;
	IRCommands &m_irCommands;
	DigitalPotmeter &m_digitalPotmeter;

	unsigned long m_timeout;
};
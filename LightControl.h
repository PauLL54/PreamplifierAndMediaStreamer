//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

class InputChannelSelectButton;
class VolumeRotaryEncoder;
class IRCommands;
class DigitalPotmeter;
class InputChannelSelector;
class I2C;

class LightControl
{
public:
	LightControl(InputChannelSelectButton &inputChannelSelectButton,
				 VolumeRotaryEncoder &volumeRotaryEncoder,
				 IRCommands &irCommands,
				 DigitalPotmeter &digitalPotmeter,
				 InputChannelSelector &inputChannelSelector,
				 I2C &i2c);

	void checkDisplaySwitchOffNeeded();

private:
	void checkUserActions();
	void updateTimeout(unsigned long lastTimeUserAction);

private:
	InputChannelSelectButton &m_inputChannelSelectButton;
	VolumeRotaryEncoder &m_volumeRotaryEncoder;
	IRCommands &m_irCommands;
	DigitalPotmeter &m_digitalPotmeter;
	InputChannelSelector &m_inputChannelSelector;
	I2C &m_i2c;

	unsigned long m_timeout;
	bool m_displayIsEnabled;
};

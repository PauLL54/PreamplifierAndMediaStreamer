//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "OutputChannelSelector.h"
#include "Arduino.h"
#include "SystemParameters.h"
#include "DigitalAttenuator.h"

OutputChannelSelector::OutputChannelSelector(DigitalAttenuator &digitalAttenuator) :
	m_digitalAttenuator(digitalAttenuator)
{
}

int8_t OutputChannelSelector::getChannel()
{
	return m_digitalAttenuator.getChannel();
}

void OutputChannelSelector::selectChannel(int8_t channel) // 0..1
{
  	int v = channel == 0 ? HIGH : LOW;
	digitalWrite(Pin::EnableOutputA_notB, v);
  	m_digitalAttenuator.setChannel(channel);
}

void OutputChannelSelector::enableOutputs()
{
	pinMode(Pin::EnableOutputs, OUTPUT);
	digitalWrite(Pin::EnableOutputs, HIGH);
}

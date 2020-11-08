//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "OutputChannelSelector.h"
#include "Arduino.h"
#include "SystemParameters.h"
#include "DigitalAttenuator.h"

OutputChannelSelector::OutputChannelSelector(DigitalAttenuator &digitalAttenuator) :
	m_digitalAttenuator(digitalAttenuator)
{
	pinMode(Pin::EnableOutputs, OUTPUT);
	pinMode(Pin::EnableOutputA_notB, OUTPUT);
}

int8_t OutputChannelSelector::getChannel() const
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
	digitalWrite(Pin::EnableOutputs, HIGH);
}

void OutputChannelSelector::disableOutputs()
{
	digitalWrite(Pin::EnableOutputs, LOW);
}

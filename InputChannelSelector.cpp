//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "InputChannelSelector.h"
#include "Arduino.h"
#include "SystemParameters.h"

InputChannelSelector::InputChannelSelector()
{
	pinMode(Pin::ChannelSelectBit0, OUTPUT);
	pinMode(Pin::ChannelSelectBit1, OUTPUT);
	pinMode(Pin::ChannelSelectBit2, OUTPUT);

	selectChannel(6); // music server
}

void InputChannelSelector::selectChannel(int channel)
{
	m_currentChannel = channel;
	switchToChannel(m_currentChannel);
}

void InputChannelSelector::selectNextChannel()
{
	m_currentChannel++;
	if (m_currentChannel > 7)
		m_currentChannel = 0;

	switchToChannel(m_currentChannel);
}

void InputChannelSelector::selectPreviousChannel()
{
	m_currentChannel--;
	if (m_currentChannel < 0)
		m_currentChannel = 7;

	switchToChannel(m_currentChannel);
}

void InputChannelSelector::switchToChannel(int channel)
{
	int bit0 = channel & 1 ? HIGH : LOW;
	int bit1 = channel & 2 ? HIGH : LOW;
	int bit2 = channel & 4 ? HIGH : LOW;
	digitalWrite(Pin::ChannelSelectBit0, bit0);
	digitalWrite(Pin::ChannelSelectBit1, bit1);
	digitalWrite(Pin::ChannelSelectBit2, bit2);
	Serial.print("switchToChannel: "); Serial.println(channel);
}


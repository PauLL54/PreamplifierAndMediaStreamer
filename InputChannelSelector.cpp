//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "InputChannelSelector.h"
#include "Arduino.h"

const int BIT0 = 11;	// PB3
const int BIT1 = 10;	// PB2
const int BIT2 =  9;	// PB1

InputChannelSelector::InputChannelSelector()
{
	pinMode(BIT0, OUTPUT);
	pinMode(BIT1, OUTPUT);
	pinMode(BIT2, OUTPUT);
            Serial.println("InputChannelSelector"); 

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

void InputChannelSelector::switchToChannel(int channel)
{
Serial.print("switchToChannel: "); 
Serial.println(channel);
	int bit0 = channel & 1 ? HIGH : LOW;
	int bit1 = channel & 2 ? HIGH : LOW;
	int bit2 = channel & 4 ? HIGH : LOW;
	digitalWrite(BIT0, bit0);
	digitalWrite(BIT1, bit1);
	digitalWrite(BIT2, bit2);
}



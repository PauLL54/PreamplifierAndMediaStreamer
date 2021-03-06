//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "InputChannelSelector.h"
#include "OutputChannelSelector.h"
#include "Arduino.h"
#include "SystemParameters.h"
#include "DigitalPotmeter.h"

const int    MuteTime_ms = 2000;		// mute time when Bluetooth channel is selected
const int8_t DefaultBrightness = 200;

InputChannelSelector::InputChannelSelector(DigitalPotmeter& digitalPotmeter, OutputChannelSelector& outputChannelSelector) :
	m_digitalPotmeter(digitalPotmeter),
	m_outputChannelSelector(outputChannelSelector),
	m_brightness(DefaultBrightness),
	m_currentChannel(0),
	m_muteTimeOut(0)
{
	pinMode(Pin::BrightnessChannelLEDs, OUTPUT);

	pinMode(Pin::ChannelSelectBit0, OUTPUT);
	pinMode(Pin::ChannelSelectBit1, OUTPUT);
	pinMode(Pin::ChannelSelectBit2, OUTPUT);
}

int8_t InputChannelSelector::getChannel()
{
	return m_digitalPotmeter.getChannel();
}

void InputChannelSelector::selectChannel(int8_t channel)
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

void InputChannelSelector::switchToChannel(int8_t channel)
{
	if (channel == 7) { 
		// Bluetooth: disable output for a short moment to prevent clicks
		m_outputChannelSelector.disableOutputs();
		m_muteTimeOut = millis() + MuteTime_ms;
	}

	int8_t bit0 = channel & 1 ? HIGH : LOW;
	int8_t bit1 = channel & 2 ? HIGH : LOW;
	int8_t bit2 = channel & 4 ? HIGH : LOW;
	digitalWrite(Pin::ChannelSelectBit0, bit0);
	digitalWrite(Pin::ChannelSelectBit1, bit1);
	digitalWrite(Pin::ChannelSelectBit2, bit2);
	setBrightness(m_brightness);
    //Serial.print("switchToChannel: "); Serial.println(channel);
    m_digitalPotmeter.setChannel(channel);
}

void InputChannelSelector::checkMuted()
{
	if (m_muteTimeOut != 0) {
		if (millis() > m_muteTimeOut) {
			m_muteTimeOut = 0;
			m_outputChannelSelector.enableOutputs();
		}
	}
}

void InputChannelSelector::enableDisplay()
{
	setBrightness(m_brightness);
}

void InputChannelSelector::disableDisplay()
{
	setBrightness(255);
}

void InputChannelSelector::setDefaultBrightness(int8_t brightness) // 0..255
{
	m_brightness = brightness;
	setBrightness(brightness);
}

void InputChannelSelector::setBrightness(int8_t brightness) // 0..255
{
	analogWrite(Pin::BrightnessChannelLEDs, brightness);
}

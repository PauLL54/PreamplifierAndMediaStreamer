//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "IRLibAll.h"
#include "DigitalPotmeter.h"
#include "InputChannelSelector.h"

class IRCommands {
public:
	IRCommands(InputChannelSelector& inputChannelSelector, DigitalPotmeter& digitalPotmeter);

	void checkForCommands();

private:
	enum Command { 	NoCommand, VolumeUp, VolumeDown, ChannelUp, ChannelDown, TV_On,
					Channel1, Channel2, Channel3, Channel4, Channel5, Channel6, Channel7, Channel8 };

	struct CodeCommandPair { uint32_t code; Command command; };
#define NumberOfCommands 13

	Command getCommand();
	Command getCommand(uint8_t protocol, uint32_t code);
	Command getCommand(CodeCommandPair (&pairs)[NumberOfCommands], uint32_t code);
	void handleCommand(Command command);
	void initValueCommandPairs();
	bool checkJumpers();

private:
	InputChannelSelector& m_inputChannelSelector;
	DigitalPotmeter& m_digitalPotmeter;
	IRrecvPCI m_IRReceiver;
	IRdecode  m_IRDecoder;
	Command   m_lastCommand;
	unsigned long m_lastTimeCommand;
	unsigned long m_lastTimeSonyCommand;
	bool m_checkTV;
	bool m_TV_IsOn;
	bool m_useNEC;
	bool m_useSony;
	bool m_useRC5;

	CodeCommandPair m_NEC[NumberOfCommands];
	CodeCommandPair m_SONY[NumberOfCommands];
	CodeCommandPair m_RC5[NumberOfCommands];
};

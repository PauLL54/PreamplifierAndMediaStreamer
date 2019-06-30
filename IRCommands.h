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
	void checkJumpers();

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

	CodeCommandPair m_NEC[NumberOfCommands] = {
		{ 0xFF18E7, VolumeUp },
		{ 0xFF4AB5, VolumeDown },
		{ 0xFF5AA5, ChannelUp },
		{ 0xFF10EF, ChannelDown },
		{ 0x000000, TV_On },
		{ 0xFFA25D, Channel1 },
		{ 0xFF629D, Channel2 },
		{ 0xFFE21D, Channel3 },
		{ 0xFF22DD, Channel4 },
		{ 0xFF02FD, Channel5 },
		{ 0xFFC23D, Channel6 },
		{ 0xFFE01F, Channel7 },
		{ 0xFFA857, Channel8 }
	};

	CodeCommandPair m_SONY[NumberOfCommands] = {
		{ 0x000490, VolumeUp },
		{ 0x000C90, VolumeDown },
		{ 0x03EB92, ChannelUp },
		{ 0x0DEB92, ChannelDown },
		{ 0x000A50, TV_On },
		{ 0x000B92, Channel1 },
		{ 0x080B92, Channel2 },
		{ 0x040B92, Channel3 },
		{ 0x0C0B92, Channel4 },
		{ 0x020B92, Channel5 },
		{ 0x0A0B92, Channel6 },
		{ 0x060B92, Channel7 },
		{ 0x0E0B92, Channel8 }		
	};

	CodeCommandPair m_RC5[NumberOfCommands] = {
		{ 0x1010, VolumeUp },
		{ 0x1011, VolumeDown },
		{ 1234, ChannelUp },
		{ 1234, ChannelDown },
		{ 0x100C, TV_On },
		{ 1234, Channel1 },
		{ 1234, Channel2 },
		{ 1234, Channel3 },
		{ 1234, Channel4 },
		{ 1234, Channel5 },
		{ 1234, Channel6 },
		{ 1234, Channel7 },
		{ 1234, Channel8 }
	};
};

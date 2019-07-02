//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "arduino.h"

class Protocol {
public:
	Protocol();

    void setEnabled(bool enabled);

	enum Command { 	NoCommand, VolumeUp, VolumeDown, ChannelUp, ChannelDown, ChannelUp2, ChannelDown2,
					Channel1, Channel2, Channel3, Channel4, Channel5, Channel6, Channel7, Channel8, 
                    TV_OnOff, };

    virtual Command getCommand(uint32_t code);

protected:
    void addCodeForCommand(Command command, uint32_t code);

private:
    int findCommandIndex(Command command);
	unsigned int getLengthCodes() const;

private:
    bool m_enabled;

	struct CodeCommandPair { uint32_t code; Command command; };
	CodeCommandPair m_codes[15] = {
		{ 0xFFFFFF, VolumeUp },
		{ 0xFFFFFF, VolumeDown },
		{ 0xFFFFFF, ChannelUp },
		{ 0xFFFFFF, ChannelUp2 },
		{ 0xFFFFFF, ChannelDown },
		{ 0xFFFFFF, ChannelDown2 },
		{ 0xFFFFFF, Channel1 },
		{ 0xFFFFFF, Channel2 },
		{ 0xFFFFFF, Channel3 },
		{ 0xFFFFFF, Channel4 },
		{ 0xFFFFFF, Channel5 },
		{ 0xFFFFFF, Channel6 },
		{ 0xFFFFFF, Channel7 },
		{ 0xFFFFFF, Channel8 },
		{ 0xFFFFFF, TV_OnOff }
	};
};
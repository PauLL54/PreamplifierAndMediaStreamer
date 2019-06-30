//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "Protocol_Sony.h"

const unsigned long SonyTimeout = 100; // millis

Protocol_Sony::Protocol_Sony() : Protocol(),
    m_lastTimeSonyCommand(0)
{
    addCodeForCommand(VolumeUp,     0x000490);
    addCodeForCommand(VolumeDown,   0x000C90);
    addCodeForCommand(ChannelUp,    0x03EB92);
    addCodeForCommand(ChannelDown,  0x0DEB92);
    addCodeForCommand(Channel1,     0x000B92);
    addCodeForCommand(Channel2,     0x080B92);
    addCodeForCommand(Channel3,     0x040B92);
    addCodeForCommand(Channel4,     0x0C0B92);
    addCodeForCommand(Channel5,     0x020B92);
    addCodeForCommand(Channel6,     0x0A0B92);
    addCodeForCommand(Channel7,     0x060B92);
    addCodeForCommand(Channel8,     0x0E0B92);
    addCodeForCommand(TV_On,        0x000A50);
}

Protocol::Command Protocol_Sony::getCommand(uint32_t code)
{
    Command command = NoCommand;

    if (millis() - m_lastTimeSonyCommand > getStartRepeatTime())
        command = Protocol::getCommand( code);

    // a button click produces many codes after each other
    // just take the first one and ignore the rest
    if (millis() - m_lastTimeCommand > SonyTimeout)
    {
        command = Protocol::getCommand(code);
        m_lastTimeSonyCommand = millis();
    }        

    return command;
}


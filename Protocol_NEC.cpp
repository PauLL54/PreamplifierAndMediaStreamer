//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "Protocol_NEC.h"

Protocol_NEC::Protocol_NEC() : Protocol()
{
    addCodeForCommand(VolumeUp,     0xFF18E7);
    addCodeForCommand(VolumeDown,   0xFF4AB5);
    addCodeForCommand(ChannelUp,    0xFF5AA5);
    addCodeForCommand(ChannelDown,  0xFF10EF);
    addCodeForCommand(Channel1,     0xFFA25D);
    addCodeForCommand(Channel2,     0xFF629D);
    addCodeForCommand(Channel3,     0xFFE21D);
    addCodeForCommand(Channel4,     0xFF22DD);
    addCodeForCommand(Channel5,     0xFF02FD);
    addCodeForCommand(Channel6,     0xFFC23D);
    addCodeForCommand(Channel7,     0xFFE01F);
    addCodeForCommand(Channel8,     0xFFA857);
    addCodeForCommand(TV_On,        0x000000);
}

Protocol::Command Protocol_NEC::getCommand(uint32_t code)
{
    Command command = NoCommand;

    if ( (code == getRepeatCode()) && (millis() - m_lastTimeCommand > getStartRepeatingKeyTime()) )
        command = m_lastCommand;
    else
        command = Protocol::getCommand(code);
        
    return command;
}
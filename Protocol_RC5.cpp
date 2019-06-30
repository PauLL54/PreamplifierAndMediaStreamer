//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "Protocol_RC5.h"

Protocol_RC5::Protocol_RC5() : Protocol()
{
    addCodeForCommand(VolumeUp,     0x1010);
    addCodeForCommand(VolumeDown,   0x1011);
    addCodeForCommand(ChannelUp,    0x0000);
    addCodeForCommand(ChannelDown,  0x0000);
    addCodeForCommand(Channel1,     0x0000);
    addCodeForCommand(Channel2,     0x0000);
    addCodeForCommand(Channel3,     0x0000);
    addCodeForCommand(Channel4,     0x0000);
    addCodeForCommand(Channel5,     0x0000);
    addCodeForCommand(Channel6,     0x0000);
    addCodeForCommand(Channel7,     0x0000);
    addCodeForCommand(Channel8,     0x0000);
    addCodeForCommand(TV_On,        0x100C);
}

Protocol::Command Protocol_RC5::getCommand(uint32_t code)
{
    code &= 0xf7ff;
    return Protocol::getCommand(code);
}


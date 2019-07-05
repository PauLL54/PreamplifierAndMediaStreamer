//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "Protocol.h"
#include "Arduino.h"

Protocol::Protocol() :
    m_enabled(true)
{
}

void Protocol::addCodeForCommand(Command command, uint32_t code)
{
    int i = findCommandIndex(command);

    if (i != -1 && i < static_cast<int>(getLengthCodes()) )
        m_codes[i].code = code;
}

Protocol::Command Protocol::getCommand(uint32_t code)
{
    Command command = NoCommand;

    for (uint32_t i = 0; i < getLengthCodes(); ++i) 
    {
        if (m_codes[i].code == code)
        {
            command = m_codes[i].command;
            break;
        }
    }
    Serial.print(code, HEX); Serial.print("; command="); Serial.println(command);

    return command;
}

int Protocol::findCommandIndex(Command command)
{
    for (unsigned int i = 0; i < getLengthCodes(); ++i) 
    {
        if (m_codes[i].command == command)
            return i;
    }
    return -1;
}

unsigned int Protocol::getLengthCodes() const
{
    return sizeof(m_codes) / sizeof(CodeCommandPair);
}
//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "Protocol.h"
#include "Arduino.h"

const unsigned long StartRepeatingKeyTime = 300; // millis
const uint32_t RepeatCode = 0xffffffff;

Protocol::Protocol() :
    m_lastCommand(NoCommand),
    m_lastTimeCommand(0),
    m_enabled(true)
{
}

void Protocol::addCodeForCommand(Command command, uint32_t code)
{
    int i = findCommandIndex(command);

    if (i != -1 && i < NumberOfCommands)
        m_codes[i].code = code;
}

Protocol::Command Protocol::getCommand(uint32_t code)
{
    Command command = NoCommand;

    for (uint32_t i = 0; i < sizeof(m_codes) / sizeof(CodeCommandPair); ++i) 
    {
        if (m_codes[i].code == code)
        {
            command = m_codes[i].command;
            break;
        }
    }

    if (code != RepeatCode) 
    {
        m_lastCommand = command;
        m_lastTimeCommand = millis();
    }

    Serial.print(code, HEX); Serial.print("; command="); Serial.println(command);

    return command;
}

int Protocol::findCommandIndex(Command command)
{
    for (unsigned int i = 0; i < sizeof(m_codes) / sizeof(CodeCommandPair); ++i) 
    {
        if (m_codes[i].command == command)
            return i;
    }
    return -1;
}

unsigned long Protocol::getStartRepeatingKeyTime() const
{
    return StartRepeatingKeyTime;
}

uint32_t Protocol::getRepeatCode() const
{
    return RepeatCode;
}
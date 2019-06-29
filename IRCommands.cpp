//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "IRCommands.h"

const int pinIRReceiver = 2; // PD2 

IRCommands::IRCommands(InputChannelSelector& inputChannelSelector, DigitalPotmeter& digitalPotmeter) :
    m_inputChannelSelector(inputChannelSelector),
    m_digitalPotmeter(digitalPotmeter),
    m_IRReceiver(pinIRReceiver),
    m_IRDecoder()
{
    initValueCommandPairs();
    m_IRReceiver.enableIRIn(); // Start the receiver
}

void IRCommands::checkForCommands()
{
    handleCommand(getCommand());
}

IRCommands::Command IRCommands::getCommand()
{
    IRCommands::Command command = NoCommand;
    if (m_IRReceiver.getResults()) 
    {
        m_IRDecoder.decode();
        command = getCommand(m_IRDecoder.protocolNum, m_IRDecoder.value);
        m_IRReceiver.enableIRIn();
    }

    return command;
}

IRCommands::Command IRCommands::getCommand(uint8_t protocol, uint32_t code)
{
    IRCommands::Command command = NoCommand;
    Serial.print(code, HEX);
    Serial.print(" protocol: ");
    Serial.println(protocol);

    switch (protocol)
    {
        case UNKNOWN:
            break;
        case NEC:
            if (code != REPEAT_CODE) 
                command = getCommand(m_NEC, code);
            break;
        case SONY:
            break;
        case RC5:
            code &= 0xf7ff;
            command = getCommand(m_RC5, code);
            break;
        case RC6:
            code &= 0xfeffff;
            break;
        default:
            break;
    }
    return command;
}

IRCommands::Command IRCommands::getCommand(CodeCommandPair (&pairs)[NumberOfCommands], uint32_t code)
{
    IRCommands::Command command = NoCommand;
    uint32_t size = sizeof(pairs) / sizeof(CodeCommandPair);
    Serial.println(size);
    for (uint32_t i = 0; i < size; ++i) 
    {
        if (pairs[i].code == code)
            return pairs[i].command;
    }

    return command;
}

void IRCommands::handleCommand(Command command)
{
    switch (command)
    {
        case NoCommand:
            break;
        case VolumeUp:
            m_digitalPotmeter.up();
            break;
        case VolumeDown:
            m_digitalPotmeter.down();
            break;
        case ChannelUp:
            m_inputChannelSelector.selectNextChannel();
            break;
        case ChannelDown:
            m_inputChannelSelector.selectPreviousChannel();
            break;
        case TV_On:
            break;
        case Channel1:
            m_inputChannelSelector.selectChannel(0);
            break;
        case Channel2:
            m_inputChannelSelector.selectChannel(1);
            break;
        case Channel3:
            m_inputChannelSelector.selectChannel(2);
            break;
        case Channel4:
            m_inputChannelSelector.selectChannel(3);
            break;
        case Channel5:
            m_inputChannelSelector.selectChannel(4);
            break;
        case Channel6:
            m_inputChannelSelector.selectChannel(5);
            break;
        case Channel7:
            m_inputChannelSelector.selectChannel(6);
            break;
        case Channel8:
            m_inputChannelSelector.selectChannel(7);
            break;
    }
}

void IRCommands::initValueCommandPairs()
{
    m_NEC[0]  = { 0xFF18E7, VolumeUp };
    m_NEC[1]  = { 0xFF4AB5, VolumeDown };
    m_NEC[2]  = { 0xFF5AA5, ChannelUp };
    m_NEC[3]  = { 0xFF10EF, ChannelDown };
    m_NEC[4]  = { 0x000000, TV_On };
    m_NEC[5]  = { 0xFFA25F, Channel1 };
    m_NEC[6]  = { 0xFF629D, Channel2 };
    m_NEC[7]  = { 0xFFE21D, Channel3 };
    m_NEC[8]  = { 0xFF22DD, Channel4 };
    m_NEC[9]  = { 0xFF02FD, Channel5 };
    m_NEC[10] = { 0xFFC2D3, Channel6 };
    m_NEC[11] = { 0xFFE01F, Channel7 };
    m_NEC[12] = { 0xFFA857, Channel8 };

    m_RC5[0]  = { 1234, VolumeUp };
    m_RC5[1]  = { 1234, VolumeDown };
    m_RC5[2]  = { 1234, ChannelUp };
    m_RC5[3]  = { 1234, ChannelDown };
    m_RC5[4]  = { 1234, TV_On };
    m_RC5[5]  = { 1234, Channel1 };
    m_RC5[6]  = { 1234, Channel2 };
    m_RC5[7]  = { 1234, Channel3 };
    m_RC5[8]  = { 1234, Channel4 };
    m_RC5[9]  = { 1234, Channel5 };
    m_RC5[10] = { 1234, Channel6 };
    m_RC5[12] = { 1234, Channel7 };
    m_RC5[12] = { 1234, Channel8 };
}
//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "IRCommands.h"

const int PinIRReceiver = 2; // PD2 
const unsigned long StartRepeatTime = 300; // millis
const unsigned long SonyTimeout = 100; // millis

IRCommands::IRCommands(InputChannelSelector& inputChannelSelector, DigitalPotmeter& digitalPotmeter) :
    m_inputChannelSelector(inputChannelSelector),
    m_digitalPotmeter(digitalPotmeter),
    m_IRReceiver(PinIRReceiver),
    m_IRDecoder(),
    m_lastCommand(NoCommand),
    m_lastTimeCommand(0),
    m_lastTimeSonyCommand(0),
    m_checkTV(false),
    m_TV_IsOn(false)
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
        
        uint32_t code = m_IRDecoder.value;
        command = getCommand(m_IRDecoder.protocolNum, code);
        
        if (code != REPEAT_CODE) 
        {
            m_lastCommand = command;
            m_lastTimeCommand = millis();
        }
        
        m_IRReceiver.enableIRIn();
    }

    return command;
}

IRCommands::Command IRCommands::getCommand(uint8_t protocol, uint32_t code)
{
    IRCommands::Command command = NoCommand;

    switch (protocol)
    {
        case UNKNOWN:
            break;
        case NEC:       // protocol 1
            if ( (code == REPEAT_CODE) && (millis() - m_lastTimeCommand > StartRepeatTime) )
                command = m_lastCommand;
            else
                command = getCommand(m_NEC, code);
            break;
        case SONY:      // protocol 2
            if (millis() - m_lastTimeSonyCommand > StartRepeatTime)
                command = getCommand(m_SONY, code);
            if (millis() - m_lastTimeCommand > SonyTimeout) // a button click produces many codes after each other
            {
                command = getCommand(m_SONY, code);         // just take the first one and ignore the rest
                m_lastTimeSonyCommand = millis();
            }
            break;
        case RC5:       // protocol 3
            code &= 0xf7ff;
            command = getCommand(m_RC5, code);
            break;
        case RC6:       // protocol 4
            code &= 0xfeffff;
            break;
        default:
            break;
    }
    Serial.print(code, HEX); Serial.print(" protocol: "); Serial.println(protocol);
    return command;
}

IRCommands::Command IRCommands::getCommand(CodeCommandPair (&pairs)[NumberOfCommands], uint32_t code)
{
    IRCommands::Command command = NoCommand;
    for (uint32_t i = 0; i < sizeof(pairs) / sizeof(CodeCommandPair); ++i) 
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
            m_TV_IsOn = !m_TV_IsOn;
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
    m_NEC[5]  = { 0xFFA25D, Channel1 };
    m_NEC[6]  = { 0xFF629D, Channel2 };
    m_NEC[7]  = { 0xFFE21D, Channel3 };
    m_NEC[8]  = { 0xFF22DD, Channel4 };
    m_NEC[9]  = { 0xFF02FD, Channel5 };
    m_NEC[10] = { 0xFFC23D, Channel6 };
    m_NEC[11] = { 0xFFE01F, Channel7 };
    m_NEC[12] = { 0xFFA857, Channel8 };

    m_SONY[0]  = { 0x000490, VolumeUp };
    m_SONY[1]  = { 0x000C90, VolumeDown };
    m_SONY[2]  = { 0x03EB92, ChannelUp };
    m_SONY[3]  = { 0x0DEB92, ChannelDown };
    m_SONY[4]  = { 0x000A50, TV_On };
    m_SONY[5]  = { 0x000B92, Channel1 };
    m_SONY[6]  = { 0x080B92, Channel2 };
    m_SONY[7]  = { 0x040B92, Channel3 };
    m_SONY[8]  = { 0x0C0B92, Channel4 };
    m_SONY[9]  = { 0x020B92, Channel5 };
    m_SONY[10] = { 0x0A0B92, Channel6 };
    m_SONY[11] = { 0x060B92, Channel7 };
    m_SONY[12] = { 0x0E0B92, Channel8 };

    m_RC5[0]  = { 0x1010, VolumeUp };
    m_RC5[1]  = { 0x1011, VolumeDown };
    m_RC5[2]  = { 1234, ChannelUp };
    m_RC5[3]  = { 1234, ChannelDown };
    m_RC5[4]  = { 0x100C, TV_On };
    m_RC5[5]  = { 1234, Channel1 };
    m_RC5[6]  = { 1234, Channel2 };
    m_RC5[7]  = { 1234, Channel3 };
    m_RC5[8]  = { 1234, Channel4 };
    m_RC5[9]  = { 1234, Channel5 };
    m_RC5[10] = { 1234, Channel6 };
    m_RC5[12] = { 1234, Channel7 };
    m_RC5[12] = { 1234, Channel8 };
}
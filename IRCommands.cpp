//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "IRCommands.h"

const int PinIRReceiver = 2;        // PD2 
const int PinCheckTV = 13;          // PB5;
const int PinCheckProtocol1 = 5;    // PD5;
const int PinCheckProtocol2 = 6;    // PD6;

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
    m_TV_IsOn(false),
    m_useNEC(false),
    m_useSony(false),
    m_useRC5(false)
{
    pinMode(PinCheckTV,        INPUT_PULLUP);
    pinMode(PinCheckProtocol1, INPUT_PULLUP);
    pinMode(PinCheckProtocol2, INPUT_PULLUP);

    m_IRReceiver.enableIRIn(); // Start the receiver
}

void IRCommands::checkForCommands()
{
    checkJumpers();
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
    //Serial.print(code, HEX); Serial.print(" protocol: "); Serial.println(protocol);
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

void IRCommands::checkJumpers()
{
    m_checkTV = digitalRead(PinCheckTV);

    int p1 = digitalRead(PinCheckProtocol1);
    int p2 = digitalRead(PinCheckProtocol2);
    int protocolSelect = p1 + (p2 << 1);
    switch (protocolSelect)
    {
        case 0:
            m_useNEC  = false;
            m_useSony = false;
            m_useRC5  = false;
            break;
        case 1:
            m_useNEC  = true;
            m_useSony = false;
            m_useRC5  = false;
            break;
        case 2:
            m_useNEC  = false;
            m_useSony = true;
            m_useRC5  = false;
            break;
        case 3:
            m_useNEC  = false;
            m_useSony = false;
            m_useRC5  = true;
            break;
        default:
            m_useNEC  = false;
            m_useSony = false;
            m_useRC5  = false;
            break;
    }
}
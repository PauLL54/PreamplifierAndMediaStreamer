//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "IRCommands.h"
#include "SystemParameters.h"

IRCommands::IRCommands(InputChannelSelector& inputChannelSelector, DigitalPotmeter& digitalPotmeter) :
    m_inputChannelSelector(inputChannelSelector),
    m_digitalPotmeter(digitalPotmeter),
    m_IRReceiver(Pin::IRReceiver),
    m_IRDecoder(),
    m_checkTV(false),
    m_TV_IsOn(false),
    m_useNEC(false),
    m_useSony(false),
    m_useRC5(false)
{
    pinMode(Pin::JumperIRCheckTVIsOn,   INPUT_PULLUP);
    pinMode(Pin::JumperIRProtocol1,     INPUT_PULLUP);
    pinMode(Pin::JumperIRProtocol2,     INPUT_PULLUP);

    m_IRReceiver.enableIRIn(); // Start the receiver
}

void IRCommands::checkForCommands()
{
    checkJumpers();
    handleProtocolCommand(getProtocolCommand());
}

Protocol::Command IRCommands::getProtocolCommand()
{
    Protocol::Command command = Protocol::NoCommand;
    if (m_IRReceiver.getResults()) 
    {
        m_IRDecoder.decode();

        Protocol* protocol = getProtocol(m_IRDecoder.protocolNum);
        if (protocol != nullptr)
        {
            command = protocol->getCommand(m_IRDecoder.value);
        }

        m_IRReceiver.enableIRIn();
    }

    return command;
}

void IRCommands::handleProtocolCommand(Protocol::Command command)
{
    switch (command)
    {
        case Protocol::NoCommand:
            break;
        case Protocol::VolumeUp:
            m_digitalPotmeter.up();
            break;
        case Protocol::VolumeDown:
            m_digitalPotmeter.down();
            break;
        case Protocol::ChannelUp:
        case Protocol::ChannelUp2:
            m_inputChannelSelector.selectNextChannel();
            break;
        case Protocol::ChannelDown:
        case Protocol::ChannelDown2:
            m_inputChannelSelector.selectPreviousChannel();
            break;
        case Protocol::Channel1:
            m_inputChannelSelector.selectChannel(0);
            break;
        case Protocol::Channel2:
            m_inputChannelSelector.selectChannel(1);
            break;
        case Protocol::Channel3:
            m_inputChannelSelector.selectChannel(2);
            break;
        case Protocol::Channel4:
            m_inputChannelSelector.selectChannel(3);
            break;
        case Protocol::Channel5:
            m_inputChannelSelector.selectChannel(4);
            break;
        case Protocol::Channel6:
            m_inputChannelSelector.selectChannel(5);
            break;
        case Protocol::Channel7:
            m_inputChannelSelector.selectChannel(6);
            break;
        case Protocol::Channel8:
            m_inputChannelSelector.selectChannel(7);
            break;
        case Protocol::TV_OnOff:
            m_TV_IsOn = !m_TV_IsOn;
            break;
    }
}

Protocol *IRCommands::getProtocol(uint8_t protocolType)
{
    for (uint32_t i = 0; i < sizeof(m_protocolData) / sizeof(ProtocolData); ++i) 
    {
        if (m_protocolData[i].protocolType == protocolType)
        {
            return m_protocolData[i].protocol;
        }
    }

    Serial.print("getProtocol(): protocolType not found: "); 
    Serial.println(protocolType);
    return nullptr;
}

void IRCommands::checkJumpers()
{
    m_checkTV = digitalRead(Pin::JumperIRCheckTVIsOn);

    int p1 = digitalRead(Pin::JumperIRProtocol1);
    int p2 = digitalRead(Pin::JumperIRProtocol2);
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

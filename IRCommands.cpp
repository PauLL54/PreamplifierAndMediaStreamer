//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "IRCommands.h"
#include "SystemParameters.h"

IRCommands::IRCommands(InputChannelSelector& inputChannelSelector, DigitalPotmeter& digitalPotmeter) :
    m_inputChannelSelector(inputChannelSelector),
    m_digitalPotmeter(digitalPotmeter),
    m_IRReceiver(Pin::IRReceiver),
    m_IRDecoder(),
    m_lastTimeUserAction(0),
    m_spare(false),
    m_TV_IsOn(false)
{
    pinMode(Pin::Spare,   INPUT_PULLUP);

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
            if (!m_TV_IsOn) m_digitalPotmeter.up();
            break;
        case Protocol::VolumeDown:
            if (!m_TV_IsOn) m_digitalPotmeter.down();
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

    if (command != Protocol::NoCommand)
        m_lastTimeUserAction = millis();
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
    m_spare = digitalRead(Pin::Spare);
}

unsigned long IRCommands::getLastTimeUserAction() const
{
    return m_lastTimeUserAction;
}
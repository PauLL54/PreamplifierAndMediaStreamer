//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "IRCommands.h"
#include "SystemParameters.h"
#include <EEPROM.h>

IRCommands::IRCommands(InputChannelSelector& inputChannelSelector, DigitalPotmeter& digitalPotmeter) :
    m_inputChannelSelector(inputChannelSelector),
    m_digitalPotmeter(digitalPotmeter),
    m_IRReceiver(Pin::IRReceiver),
    m_IRDecoder(),
    m_lastTimeUserAction(0),
    m_useNecOnly(false)
{
    pinMode(Pin::NecOnly, INPUT_PULLUP);

    m_IRReceiver.enableIRIn(); // Start the receiver

    initEnabledForChannel();
}

void IRCommands::initEnabledForChannel()
{
    int8_t enabledForChannel;
    EEPROM.get(Eeprom::IREnabledForChannel, enabledForChannel);

    for (int8_t i = 0; i < 8; ++i) {
        m_enabledForChannel[i] = enabledForChannel & (1 << i) ? true : false;
    }
}

int8_t IRCommands::getEnabledForChannel() const
{
    int8_t result = 0;
    for (int8_t i = 0; i < 8; ++i) {
        if (m_enabledForChannel[i]) {
            result |= 1 << i;
        }
    }
    return result;
}

bool IRCommands::enabledForChannel()
{
    return m_enabledForChannel[m_inputChannelSelector.getChannel()];
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
    bool volumeEnabled = enabledForChannel();

    switch (command)
    {
        case Protocol::NoCommand:
            break;
        case Protocol::VolumeUp:
            if (volumeEnabled) m_digitalPotmeter.up();
            break;
        case Protocol::VolumeDown:
            if (volumeEnabled) m_digitalPotmeter.down();
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
            break;
    }

    if (command != Protocol::NoCommand)
        m_lastTimeUserAction = millis();
}

Protocol *IRCommands::getProtocol(uint8_t protocolType)
{
    if (m_useNecOnly && (protocolType != NEC))
        return nullptr;

    for (uint32_t i = 0; i < sizeof(m_protocolData) / sizeof(ProtocolData); ++i) 
    {
        if (m_protocolData[i].protocolType == protocolType)
        {
            return m_protocolData[i].protocol;
        }
    }

    //Serial.print("getProtocol(): protocolType not found: "); 
    //Serial.println(protocolType);
    return nullptr;
}

void IRCommands::checkJumpers()
{
    m_useNecOnly = digitalRead(Pin::NecOnly);
}

unsigned long IRCommands::getLastTimeUserAction() const
{
    return m_lastTimeUserAction;
}

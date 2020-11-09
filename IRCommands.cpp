//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "IRCommands.h"
 
#include "SystemParameters.h"
#include <EEPROM.h>

IRCommands::IRCommands(InputChannelSelector& inputChannelSelector, DigitalPotmeter& digitalPotmeter) :
    m_inputChannelSelector(inputChannelSelector),
    m_digitalPotmeter(digitalPotmeter),
    m_IRReceiver(Pin::IRReceiver),
    m_IRDecoder(),
    m_lastTimeUserAction(0)
{
    m_IRReceiver.enableIRIn(); // Start the receiver

    initVolumeEnabledForChannel();
}

void IRCommands::initVolumeEnabledForChannel()
{
    int8_t volumeEnabledForChannel;
    EEPROM.get(Eeprom::IRVolumeForChannel, volumeEnabledForChannel);

    for (int8_t i = 0; i < 8; ++i) {
        m_volumeEnabledForChannel[i] = volumeEnabledForChannel & (1 << i) ? true : false;
    }
}

uint8_t IRCommands::getVolumeEnabledForChannel() const
{
    int8_t result = 0;
    for (int8_t i = 0; i < 8; ++i) {
        if (m_volumeEnabledForChannel[i]) {
            result |= 1 << i;
        }
    }
    return result;
}

bool IRCommands::volumeEnabledForChannel()
{
    return m_volumeEnabledForChannel[m_inputChannelSelector.getChannel()];
}

void IRCommands::checkForCommands()
{
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
    bool volumeEnabled = volumeEnabledForChannel();

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

    if (volumeEnabled && (command != Protocol::NoCommand))
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

    //Serial.print("getProtocol(): protocolType not found: "); 
    //Serial.println(protocolType);
    return nullptr;
}

unsigned long IRCommands::getLastTimeUserAction() const
{
    return m_lastTimeUserAction;
}

//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "IRLibAll.h"
#include "DigitalPotmeter.h"
#include "InputChannelSelector.h"
#include "Protocol_NEC.h"
#include "Protocol_Sony.h"
#include "Protocol_RC5.h"

class IRCommands {
public:
	IRCommands(InputChannelSelector& inputChannelSelector, DigitalPotmeter& digitalPotmeter);

	void initVolumeEnabledForChannel();
	int8_t getVolumeEnabledForChannel() const;
	void checkForCommands();
	unsigned long getLastTimeUserAction() const;

private:
	bool volumeEnabledForChannel();
	Protocol::Command getProtocolCommand();
	void handleProtocolCommand(Protocol::Command command);

	void checkJumpers();
	Protocol *getProtocol(uint8_t protocolType);

private:
	InputChannelSelector& m_inputChannelSelector;
	DigitalPotmeter& m_digitalPotmeter;
	IRrecvPCI m_IRReceiver;
	IRdecode  m_IRDecoder;
    unsigned long m_lastTimeUserAction;

	bool m_useNecOnly;

	struct ProtocolData { uint8_t protocolType; Protocol *protocol; };
	ProtocolData m_protocolData[3] = {
		{ NEC,  new Protocol_NEC()  },
		{ SONY, new Protocol_Sony() },
		{ RC5,  new Protocol_RC5()  }
	};
    int8_t m_volumeEnabledForChannel[8];
};

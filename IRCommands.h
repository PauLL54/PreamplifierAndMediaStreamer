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

	void checkForCommands();

private:
	Protocol::Command getProtocolCommand();
	void handleProtocolCommand(Protocol::Command command);

	void checkJumpers();
	Protocol *getProtocol(uint8_t protocolType);

private:
	InputChannelSelector& m_inputChannelSelector;
	DigitalPotmeter& m_digitalPotmeter;
	IRrecvPCI m_IRReceiver;
	IRdecode  m_IRDecoder;

	bool m_checkTV;
	bool m_TV_IsOn;
	bool m_useNEC;
	bool m_useSony;
	bool m_useRC5;

	struct ProtocolData { uint8_t protocolType; Protocol *protocol; };
	ProtocolData m_protocolData[3] = {
		{ NEC,  new Protocol_NEC()  },
		{ SONY, new Protocol_Sony() },
		{ RC5,  new Protocol_RC5()  }
	};
};

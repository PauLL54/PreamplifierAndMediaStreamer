//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Protocol.h"

class Protocol_NEC : public Protocol
{
public:
	Protocol_NEC();

	Command getCommand(uint32_t code) override;

private:
	Command         m_lastCommand;
	unsigned long   m_lastTimeCommand;
};

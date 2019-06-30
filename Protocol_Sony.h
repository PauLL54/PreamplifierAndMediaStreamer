//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Protocol.h"

class Protocol_Sony : public Protocol
{
public:
	Protocol_Sony();

	Command getCommand(uint32_t code) override;

private:
	unsigned long m_lastTimeSonyCommand;
};

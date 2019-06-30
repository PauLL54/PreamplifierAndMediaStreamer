//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Protocol.h"

class Protocol_RC5 : public Protocol
{
public:
	Protocol_RC5();

	Command getCommand(uint32_t code) override;
};
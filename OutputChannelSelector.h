//  Copyright © 2020 Paul Langemeijer. All rights reserved.
#pragma once
#include "stdint.h"

class DigitalAttenuator;

class OutputChannelSelector {
public:
	OutputChannelSelector(DigitalAttenuator &digitalAttenuator);

	void selectChannel(int8_t channel); // 0..1
	void enableOutputs();

private:
	DigitalAttenuator &m_digitalAttenuator;
};
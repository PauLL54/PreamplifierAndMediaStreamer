//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once
#include "Debouncer.h"

class InputChannelSelector {
public:
	InputChannelSelector();

	void selectChannel(int channel); // 0..7
	void selectNextChannel();
	void selectPreviousChannel();
	
private:
	void switchToChannel(int channel);

private:
	int m_currentChannel;
};

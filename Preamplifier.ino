//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "InputChannelSelector.h"
#include "InputChannelSelectButton.h"
#include "VolumeRotaryEncoder.h"

InputChannelSelector m_inputChannelSelector;
InputChannelSelectButton m_inputChannelSelectButton(m_inputChannelSelector);
VolumeRotaryEncoder m_volumeRotaryEncoder;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  m_inputChannelSelectButton.checkButtonPressed();
  m_volumeRotaryEncoder.checkRotation();
}

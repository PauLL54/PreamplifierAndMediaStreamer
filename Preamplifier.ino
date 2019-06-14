//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "InputChannelSelector.h"
#include "InputChannelSelectButton.h"
#include "DigitalPotmeter.h"
#include "VolumeRotaryEncoder.h"

InputChannelSelector m_inputChannelSelector;
InputChannelSelectButton m_inputChannelSelectButton(m_inputChannelSelector);
DigitalPotmeter m_digitalPotmeter;
VolumeRotaryEncoder m_volumeRotaryEncoder;
bool m_initializing = true;

void setup() 
{
  Serial.begin(9600);
}

void handleInitialization()
{
    m_digitalPotmeter.updateDevice();
    if (m_digitalPotmeter.targetValueReached())
    {
      m_initializing = false;
      m_digitalPotmeter.setTargetValue(10);
    }
}

void loop() 
{
  if (m_initializing)
  {
    handleInitialization();
  }
  else
  {
    m_inputChannelSelectButton.checkButtonPressed();
    m_volumeRotaryEncoder.checkRotation();
    m_digitalPotmeter.updateDevice();
  }
}

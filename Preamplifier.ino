//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "InputChannelSelector.h"
#include "InputChannelSelectButton.h"
#include "DigitalPotmeter.h"
#include "VolumeRotaryEncoder.h"
#include "IRCommands.h"

InputChannelSelector      m_inputChannelSelector;
InputChannelSelectButton  m_inputChannelSelectButton(m_inputChannelSelector);
DigitalPotmeter           m_digitalPotmeter;
VolumeRotaryEncoder       m_volumeRotaryEncoder(m_digitalPotmeter);
IRCommands                m_IRCommands(m_inputChannelSelector, m_digitalPotmeter);

bool m_initializing = true;

void setup() 
{
  Serial.begin(9600);
}

void initializeDigitalPotmeter()
{
    m_digitalPotmeter.updateToTargetValue();
    if (m_digitalPotmeter.isInitialized())
    {
      m_initializing = false;
      m_digitalPotmeter.setTargetValue(10);
    }
}

void loop() 
{
  if (m_initializing)
  {
    initializeDigitalPotmeter();
  }
  else
  {
    m_inputChannelSelectButton.checkButtonPressed();
    m_volumeRotaryEncoder.checkRotation();
    m_IRCommands.checkForCommands();
    m_digitalPotmeter.updateToTargetValue();
  }
}

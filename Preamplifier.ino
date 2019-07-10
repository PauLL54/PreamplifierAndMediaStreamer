// @title MIT License
// 
//  Copyright © 2019 Paul Langemeijer. All rights reserved.
// 
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

#include "InputChannelSelector.h"
#include "InputChannelSelectButton.h"
#include "DigitalPotmeter.h"
#include "VolumeRotaryEncoder.h"
#include "IRCommands.h"
#include "SystemParameters.h"
#include "LightControl.h"

InputChannelSelector      m_inputChannelSelector;
InputChannelSelectButton  m_inputChannelSelectButton(m_inputChannelSelector);
DigitalPotmeter           m_digitalPotmeter;
VolumeRotaryEncoder       m_volumeRotaryEncoder(m_digitalPotmeter);
IRCommands                m_IRCommands(m_inputChannelSelector, m_digitalPotmeter);
LightControl              m_lightControl(m_inputChannelSelectButton, m_volumeRotaryEncoder, m_IRCommands, m_digitalPotmeter);

bool m_initializing = true;

void enableChannelLedsLeakage()
{
  pinMode(Pin::ChannelLedsLeakage, OUTPUT);
  digitalWrite(Pin::ChannelLedsLeakage, LOW);
}

void setup() 
{
  Serial.begin(9600);
  enableChannelLedsLeakage();
}

void switchOnOutputRelay()
{
  pinMode(Pin::OutputRelay, OUTPUT);
  digitalWrite(Pin::OutputRelay, LOW);
}

void initializeDigitalPotmeter()
{
    m_digitalPotmeter.updateToTargetValue();
    if (m_digitalPotmeter.isInitialized())
    {
      m_initializing = false;
      m_digitalPotmeter.setTargetValue(10);
      switchOnOutputRelay();
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
    m_lightControl.checkDisplaySwitchOffNeeded();
  }
}

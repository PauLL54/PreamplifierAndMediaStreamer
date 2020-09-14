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
#include <Wire.h>
#include "InputChannelSelector.h"
#include "InputChannelSelectButton.h"
#include "DigitalPotmeter.h"
#include "DigitalAttenuator.h"
#include "VolumeRotaryEncoder.h"
#include "IRCommands.h"
#include "SystemParameters.h"
#include "i2c.h"
#include "LightControl.h"

InputChannelSelector m_inputChannelSelector;
InputChannelSelectButton m_inputChannelSelectButton(m_inputChannelSelector);
DigitalPotmeter m_digitalPotmeter;
DigitalAttenuator m_digitalAttenuator;
VolumeRotaryEncoder m_volumeRotaryEncoder(m_digitalPotmeter);
IRCommands m_IRCommands(m_inputChannelSelector, m_digitalPotmeter);
I2C m_i2c(m_inputChannelSelector, m_digitalPotmeter);
LightControl m_lightControl(m_inputChannelSelectButton, m_volumeRotaryEncoder, m_IRCommands, m_digitalPotmeter, m_inputChannelSelector, m_i2c);

bool m_initializing = true;

#define INPUT_SIZE 30
void I2C_receiveEvent(int howMany)
{
  char input[INPUT_SIZE + 1];
  byte i = 0;
  while (Wire.available() > 0 && i < INPUT_SIZE)
  {
    char c = (char)Wire.read();
    input[i] = c;
    i++;
  }
  input[i] = 0;
  m_i2c.handleInput(input);
}

void I2C_requestEvent()
{
  Wire.write(12);
}

void setup()
{
  Serial.begin(9600);

  Wire.begin(4);                    // join i2c bus with address #4
  Wire.onReceive(I2C_receiveEvent); // register event
  //Wire.onRequest(I2C_requestEvent);
}

void EnableOutputs()
{
  pinMode(Pin::EnableOutputs, OUTPUT);
  digitalWrite(Pin::EnableOutputs, HIGH);
}

void initializeDigitalPotmeters()
{
  m_digitalPotmeter.updateToTargetValue();
  m_digitalAttenuator.updateToTargetValue();
  if (m_digitalPotmeter.isInitialized())
  {
    m_initializing = false;
    m_digitalPotmeter.setTargetValue(10);
    m_digitalAttenuator.setTargetValue(31);
    EnableOutputs();
  }
}

void loop()
{
  if (m_initializing)
  {
    initializeDigitalPotmeters();
  }
  else
  {
    m_inputChannelSelectButton.checkButtonPressed();
    m_volumeRotaryEncoder.checkRotation();
    m_IRCommands.checkForCommands();
    m_digitalPotmeter.updateToTargetValue();
    m_digitalAttenuator.updateToTargetValue();
    m_lightControl.checkDisplaySwitchOffNeeded();
  }
}

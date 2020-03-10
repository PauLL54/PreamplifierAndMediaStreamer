//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#include "I2C.h"
#include "InputChannelSelector.h"
#include "Arduino.h"
#include "wire.h"

const unsigned long DisplayOnTime =  1L * 60L * 1000L; // ms after some time, switch off the display
//const unsigned long DisplayOnTime = 3000; // ms for testing

I2C::I2C(InputChannelSelector &inputChannelSelector) :
    m_inputChannelSelector(inputChannelSelector)
{
    Wire.begin(4);                // join i2c bus with address #4
    Wire.onReceive(receiveEvent); // register event
}

static void I2C::receiveEvent(int howMany)
{
    while(Wire.available() > 1) // loop through all but the last
    {
        char c = Wire.read();   // receive byte as a character
        Serial.print(c);        // print the character
    }
    int x = Wire.read();        // receive byte as an integer
    Serial.println(x);          // print the integer
}
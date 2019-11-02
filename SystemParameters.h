//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

namespace Pin
{
                                            // PD0: RXD, used for programming
                                            // PD1: TXD, used for programming
    const int IRReceiver            =  2;   // PD2 
    const int AttenuatorUp          =  3;   // PD3
    const int AttenuatorDown        =  4;   // PD4
    const int BrightnessChannelLEDs =  5;   // PD5 PWM 980 Hz
    const int Spare                 =  6;   // PD6
    const int DigitalPotmeterUp     =  7;   // PD7

    const int DigitalPotmeterDown   =  8;   // PB0
    const int ChannelSelectBit2     =  9;   // PB1
    const int ChannelSelectBit1     = 10;	// PB2
    const int ChannelSelectBit0     = 11;	// PB3
    const int EnableOutputs         = 12;   // PB4
    const int EnableOutputA_notB    = 13;   // PB5
                                            // PB6: cannot be used
                                            // PB7: cannot be used

    const int ChannelSelectButton   = 15;	// PC1
    const int NeoPixelLedRing       = 16;   // PC2

    #define VERSION1

    #ifdef VERSION1
    const int ChannelLedsLeakage    = 17;   // PC3
    const int VolumeEncoderA        = 18;   // PC4
    const int VolumeEncoderB        = 19;   // PC5
    #endif
    #ifdef VERSION2
    const int VolumeEncoderA        = 14;   // PC0
    const int VolumeEncoderB        = 17;   // PC3
    const int SCL                   = 18;   // PC4  I2C bus
    const int SDA                   = 19;   // PC5  I2C bus
    #endif
                                            // PC6: RESET-, used for programming
                                            // PC7: does not exist :)
}
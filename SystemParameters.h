//  Copyright © 2019 Paul Langemeijer. All rights reserved.
#pragma once

namespace Eeprom
{
    const int8_t ChannelVolumes         =  0;   // 8 bytes: volume (0..31) per input channel
    const int8_t OutputVolumes          =  8;   // 2 bytes: volume (0..31) per output channel
    const int8_t IRVolumeForChannel     = 10;   // 1 byte: Each bit determines if IR volume commands can be used for a channel
    const int8_t EncoderLongAxis        = 11;   // 1 byte: 1 if volume encoder with long axis is used else 0
}

namespace Pin
{
                                                // PD0: RXD, used for programming
                                                // PD1: TXD, used for programming
    const int8_t IRReceiver            =  2;    // PD2 
    const int8_t AttenuatorUp          =  3;    // PD3
    const int8_t AttenuatorDown        =  4;    // PD4
    const int8_t BrightnessChannelLEDs =  5;    // PD5 PWM 980 Hz
    const int8_t NecOnly               =  6;    // PD6
    const int8_t DigitalPotmeterUp     =  7;    // PD7

    const int8_t DigitalPotmeterDown   =  8;    // PB0
    const int8_t ChannelSelectBit2     =  9;    // PB1
    const int8_t ChannelSelectBit1     = 10;	// PB2
    const int8_t ChannelSelectBit0     = 11;	// PB3
    const int8_t EnableOutputs         = 12;    // PB4
    const int8_t EnableOutputA_notB    = 13;    // PB5
                                                // PB6: cannot be used
                                                // PB7: cannot be used

    const int8_t ChannelSelectButton   = 15;	// PC1
    const int8_t NeoPixelLedRing       = 16;   // PC2

    #define VERSION2

    #ifdef VERSION1
    const int8_t ChannelLedsLeakage    = 17;   // PC3
    const int8_t VolumeEncoderA        = 18;   // PC4
    const int8_t VolumeEncoderB        = 19;   // PC5
    #endif
    #ifdef VERSION2
    const int8_t VolumeEncoderA        = 14;   // PC0
    const int8_t VolumeEncoderB        = 17;   // PC3
    const int8_t SCL                   = 18;   // PC4  I2C bus
    const int8_t SDA                   = 19;   // PC5  I2C bus
    #endif
                                            // PC6: RESET-, used for programming
                                            // PC7: does not exist :)
}
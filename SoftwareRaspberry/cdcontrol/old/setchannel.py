import sys
import platform
import smbus

bus = smbus.SMBus(1)

def _StringToBytes(val):
    retVal = []
    for c in val:
        retVal.append(ord(c))
    return retVal

def set_channel(ch):
    command = "=SetChannel=" + ch + "="
    print command
    data = _StringToBytes(command)
    bus.write_i2c_block_data(4, 1, data)
        
channel = sys.argv[1]

set_channel(channel)
    


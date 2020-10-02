import sys
import platform
import smbus

# Usage: python selectoutputchannel.py 0
# Expected 1 argument: 0..1

bus = smbus.SMBus(1)

def _StringToBytes(val):
    retVal = []
    for c in val:
        retVal.append(ord(c))
    return retVal

def set_channelOutput(channel):
    command = "=OUTPUT=" + channel + "="
    print(command)
    data = _StringToBytes(command)
    bus.write_i2c_block_data(4, 1, data)
        
set_channelOutput(sys.argv[1])
    


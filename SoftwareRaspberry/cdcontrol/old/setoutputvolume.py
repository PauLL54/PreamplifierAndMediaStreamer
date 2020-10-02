import sys
import platform
import smbus

# Usage: python setoutputvolume.py 10 10
# Expected 2 arguments: a value of 0..31 to set the default volume of the two output channels

bus = smbus.SMBus(1)

def _StringToBytes(val):
    retVal = []
    for c in val:
        retVal.append(ord(c))
    return retVal

def set_channelVolume(channelVolumes):
    command = "=SOV=" + channelVolumes + "="
    print(command)
    data = _StringToBytes(command)
    bus.write_i2c_block_data(4, 1, data)
        
ch0 = sys.argv[1]
ch1 = sys.argv[2]
channelVolumes = ch0 + "," + ch1
set_channelVolume(channelVolumes)
    


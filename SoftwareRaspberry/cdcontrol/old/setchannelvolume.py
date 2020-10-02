import sys
import platform
import smbus

# Usage: python setchannelvolume.py 10 10 10 10 10 10 31 10 
# Expected 8 arguments: a value of 0..31 to set the default volume of a channelVolume

bus = smbus.SMBus(1)

def _StringToBytes(val):
    retVal = []
    for c in val:
        retVal.append(ord(c))
    return retVal

def set_channelVolume(channelVolumes):
    command = "=SCV=" + channelVolumes + "="
    print(command)
    data = _StringToBytes(command)
    bus.write_i2c_block_data(4, 1, data)
        
ch0 = sys.argv[1]
ch1 = sys.argv[2]
ch2 = sys.argv[3]
ch3 = sys.argv[4]
ch4 = sys.argv[5]
ch5 = sys.argv[6]
ch6 = sys.argv[7]
ch7 = sys.argv[8]
channelVolumes = ch0 + "," + ch1 + "," + ch2 + "," + ch3 + "," + ch4 + "," + ch5 + "," + ch6 + "," + ch7
set_channelVolume(channelVolumes)
    


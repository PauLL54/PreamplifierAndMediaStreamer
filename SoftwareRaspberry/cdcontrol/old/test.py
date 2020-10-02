import platform
import smbus

class App:

	bus = smbus.SMBus(1)

	def _StringToBytes(self, val):
		retVal = []
		for c in val:
			retVal.append(ord(c))
		return retVal
    
	def _set_LMS_channel(self):
		data = self._StringToBytes("=SetChannel=6=")
		self.bus.write_i2c_block_data(4, 1, data)

	def start_cd(self):
		self._set_LMS_channel()
		
app = App()
app.start_cd()

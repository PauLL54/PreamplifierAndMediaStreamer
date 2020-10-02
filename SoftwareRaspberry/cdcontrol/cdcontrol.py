#!/usr/bin/python

import subprocess
import time
import datetime
import logging
from logging.handlers import RotatingFileHandler
from startcd import CDPlayer
import os.path
from os import path

class App():

	msg_prev = ''
	logfile = '/var/log/cdcontrol.log'
	#logfile = 'cdcontrol.log'

	def __init__(self):
		logging.basicConfig(
				filename=self.logfile,
				handlers=[RotatingFileHandler(self.logfile, maxBytes=100000, backupCount=5)],
				level=logging.INFO,
				format='[%(asctime)s] %(levelname)s [%(name)s.%(funcName)s:%(lineno)d] %(message)s',
				datefmt='%Y-%m-%dT%H:%M:%S')

		self.logger = logging.getLogger()
		self.cd_is_started = True
		self.cd_player = None

	def log_msg(self, msg):
		if self.msg_prev != msg:
			self.logger.info(msg)
			self.msg_prev = msg

	def start_cd(self):
		self.log_msg('start_cd')
		if not self.cd_player:
			self.cd_player = CDPlayer()
		return self.cd_player.start_cd()

	def run(self):
		while True:			
			try:
				cdinfo = subprocess.check_output(['/usr/bin/setcd', '-i'])
				if 'Disc found in drive: audio disc' in cdinfo:
					if not path.exists("/opt/cdcontrol/RippingFast"):
						self.log_msg('Adapt the cdrom speed for audio')
						subprocess.call(['/usr/bin/eject', '-x4'])
					
					if (path.exists("/opt/cdcontrol/AutoStartCD") and self.cd_is_started == False):
						message = self.start_cd()
						self.log_msg(message)
						self.cd_is_started = True
					time.sleep(1)
				
				elif 'No disc is inserted' in cdinfo:
					self.log_msg('No disc is inserted.')
					self.cd_is_started = False
					time.sleep(10)
					
				elif 'Drive is not ready' in cdinfo:
					self.log_msg('Drive is not ready.')
					self.cd_is_started = False
					time.sleep(10)
					
				elif 'CD tray is open' in cdinfo:
					self.log_msg('CD tray is open.')
					self.cd_is_started = False
					time.sleep(5)
				else:
					raise Exception('Error by setcd -i')

			except Exception as e:
				self.log_msg('An exception occurred: ' + str(e))
				self.cd_is_started = False
				time.sleep(5)

app = App()
app.run()
	
	


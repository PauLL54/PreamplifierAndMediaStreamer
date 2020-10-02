import platform
from LMSTools import LMSServer, LMSMenuHandler
import smbus

# Definitions
SERVER_IP = "127.0.0.1"

class CDPlayer:

	bus = smbus.SMBus(1)

	def __init__(self):
		# create the server object
		server = LMSServer(SERVER_IP)

		# get the attached players
		self.players = server.get_players()
		
		hostname = platform.uname()[1]
		self.player_name = hostname

	def _StringToBytes(self, val):
		retVal = []
		for c in val:
			retVal.append(ord(c))
		return retVal
    
	def _set_LMS_channel(self):
		data = self._StringToBytes("=SetChannel=6=")
		self.bus.write_i2c_block_data(4, 1, data)
		
	def start_cd(self):
		result = False
		message = 'CD is started.'
		try:
			self._set_LMS_channel()
			my_player = self._find_player(self.players, self.player_name)
			player_menu_items = self._get_player_menu_items(my_player)
			cd_menu = self._get_cd_menu(my_player, player_menu_items)
			result = True
		except Exception as e:
			message = e.message
			result = False

		if (result == True):
			my_player.playlist_clear()
			first_menu_item = cd_menu[0]
			class_name = str(first_menu_item.__class__)
			if 'PlaylistMenuItem' in class_name:
				first_menu_item.play()
			else:
				result = False
				message = 'Something wrong with the CD.'
		return message

	def _find_player(self, players, name):
		i = 0
		loop = True
		while i < len(players) and loop:
			player_name = players[i].name
			if name == player_name:
				loop = False
			else:
				i += 1
		if loop == True:
			raise Exception('Cannot find player.')
		return players[i]


	def _get_player_menu_items(self, player):
		return LMSMenuHandler(player)
		
	def _get_cd_menu(self, player, player_menu_items):
		# find CDplayer menu
		menu_item = self._find_menu(player_menu_items, "CDplayer")

		class_name = str(menu_item.__class__)
		if 'NextMenuItem' in class_name:
			try:
				cd_menu_items = player_menu_items.getMenu(menu_item.cmd)
			except TypeError:
				raise Exception('Exception: There is no CD in the drive.')
		return cd_menu_items


	def _find_menu(self, handler, name):
		home = handler.getHomeMenu()
		i=0
		loop = True
		while i< len(home) and loop:
			text = home[i].text
			if name == text:
				loop = False
			else:
				i += 1
		if loop == True:
			raise Exception('Cannot find menu item.')
			
		return home[i]



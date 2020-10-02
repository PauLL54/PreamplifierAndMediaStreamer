# returns current mode: stop or play
import sys
import platform
from LMSTools import LMSServer, LMSMenuHandler

SERVER_IP = "127.0.0.1"

def _find_player(players, name):
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

server = LMSServer(SERVER_IP)
players = server.get_players()
my_player = _find_player(players, platform.uname()[1])

print my_player.mode

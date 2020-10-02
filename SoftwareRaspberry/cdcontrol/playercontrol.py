import sys
import platform
from LMSTools import LMSServer, LMSMenuHandler
import os.path
from os import path

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
print players

if len(sys.argv) < 2:
	sys.exit()

# expect: prev stop play next
command = sys.argv[1]

if command == "stop":
	my_player.stop()

if command == "play":
	my_player.play()

if command == "next":
	my_player.next()

if command == "prev":
	my_player.prev()

if command == "toggle":
	my_player.toggle()

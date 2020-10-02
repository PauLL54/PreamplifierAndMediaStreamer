Author: Alfred Homsma

The ledpoweractive module enables pin 23 to low. The purpose of this program is to indicate that the Raspberry Pi is up and running.

Installation:
sudo mkdir /opt/ledpoweractive
sudo cp ledpoweractive.py /opt/ledpoweractive

Call ledpoweractive.py from /etc/rc.local by placing the following text before exit 0:
sudo leafpad /etc/rc.local

#Amplifier in activate mode
printf "Amplifier is in active mode"
/opt/ledpoweractive/ledpoweractive.py

Author: Alfred Homsma

The cdcontrol package is a python implementation for controlling a cd player for Audio purposes.

This package is intended to use on a Raspberry PI:
* A usb-cd player must be connected.
* Logitech Media Server must be installed on the Raspberry PI.
* CDplayer plugin of Bryan Alton must be enabled.

It supports the following features:
* Speed control - On regular basis the speed is set to the lowest value
* Auto start - When the software detects that a CD is inserted it will starts playing.
* log file: /var/log/cdcontrol.log

The package must be copied to the directory: /opt/cdcontrol 
It will run as system deamon.

Installation:
sudo mkdir /opt/cdcontrol
sudo cp cdcontrol.py /opt/cdcontrol/.
sudo cp startcd.py /opt/cdcontrol/.
sudo cp -r LMSTools /opt/cdcontrol/.
sudo cp cdcontrol.service /etc/systemd/system/.
sudo systemctl enable cdcontrol
sudo systemctl start cdcontrol

That’s it, success.


